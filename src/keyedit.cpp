/*
	This file is part of Warzone 2100.
	Copyright (C) 1999-2004  Eidos Interactive
	Copyright (C) 2005-2020  Warzone 2100 Project

	Warzone 2100 is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	Warzone 2100 is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Warzone 2100; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/
/*
 * keyedit.c
 * keymap editor
 * alexl.
 */

// ////////////////////////////////////////////////////////////////////////////
// includes
#include <string.h>
#include <physfs.h>
#include <optional-lite/optional.hpp>

#include "lib/framework/frame.h"
#include "lib/framework/frameresource.h"
#include "lib/ivis_opengl/bitimage.h"
#include "lib/ivis_opengl/pieblitfunc.h"
#include "lib/sound/audio.h"
#include "lib/sound/audio_id.h"
#include "lib/widget/button.h"
#include "lib/widget/scrollablelist.h"

#include "frend.h"
#include "frontend.h"
#include "hci.h"
#include "init.h"
#include "intdisplay.h"
#include "keybind.h"
#include "keyedit.h"
#include "keymap.h"
#include "loadsave.h"
#include "main.h"
#include "multiint.h"
#include "multiplay.h"
#include "ingameop.h"

// ////////////////////////////////////////////////////////////////////////////
// defines

#define	KM_START			10204
#define	KM_END				10399

#define KM_W				FRONTEND_BOTFORMW
#define KM_H				440
#define KM_X				FRONTEND_BOTFORMX
#define KM_Y				20
#define KM_SX				FRONTEND_SIDEX


#define KM_ENTRYW			(FRONTEND_BOTFORMW - 80)
#define KM_ENTRYH			(16)

class KeyMapForm : public IntFormAnimated
{
protected:
	KeyMapForm(): IntFormAnimated(false) {}
	void initialize(bool isInGame);

public:
	static std::shared_ptr<KeyMapForm> make(bool isInGame)
	{
		class make_shared_enabler: public KeyMapForm {};
		auto widget = std::make_shared<make_shared_enabler>();
		widget->initialize(isInGame);
		return widget;
	}

	void checkPushedKeyCombo();
	bool pushedKeyCombo(const KeyMappingInput input);

private:
	std::shared_ptr<ScrollableListWidget> keyMapList;
	std::shared_ptr<W_BUTTON> createKeyMapButton(const unsigned int id, const KeyMappingSlot slot, struct DisplayKeyMapData* targetFunctionData);
	void unhighlightSelected();
	void addButton(int buttonId, int y, const char *text);
};

struct DisplayKeyMapData {
	explicit DisplayKeyMapData(void (* const function)(), const std::string name)
		: mappings(std::vector<KEY_MAPPING*>(static_cast<unsigned int>(KeyMappingSlot::LAST), nullptr))
		, function(function)
		, name(name)
	{
	}

	std::vector<KEY_MAPPING*> mappings;
	void (*function)();
	const std::string name; // TODO refact-process-input: is this required?

	WzText wzNameText;
};

struct DisplayKeyMapButtonData {
	WzText wzBindingText;
	KeyMappingSlot slot;
	DisplayKeyMapData* targetFunctionData;
};

// ////////////////////////////////////////////////////////////////////////////
// variables

struct KeyMappingSelection {
	bool               hasActiveSelection;
	KeyMappingSlot slot;
	DisplayKeyMapData* data;

public:
	bool isSelected(void (*const otherFunction)(), const KeyMappingSlot otherSlot) const
	{
		return hasActiveSelection && data->function == otherFunction && slot == otherSlot;
	}

	void select(const KeyMappingSlot newSlot, DisplayKeyMapData* const newData)
	{
		hasActiveSelection = true;
		slot = newSlot;
		data = newData;
	}

	void clearSelection()
	{
		hasActiveSelection = false;
		data = nullptr;
		slot = KeyMappingSlot::LAST;
	}
};

static KeyMappingSelection keyMapSelection;
static bool maxKeyMapNameWidthDirty = true;
static const std::string NOT_BOUND_LABEL = "<not bound>";

// ////////////////////////////////////////////////////////////////////////////
// funcs
// ////////////////////////////////////////////////////////////////////////////
static KEY_CODE scanKeyBoardForPressedBindableKey()
{
	for (unsigned int i = 0; i < KEY_MAXSCAN; i++)
	{
		if (keyPressed((KEY_CODE)i))
		{
			if (i !=	KEY_RALT			// exceptions
			    && i !=	KEY_LALT
			    && i != KEY_RCTRL
			    && i != KEY_LCTRL
			    && i != KEY_RSHIFT
			    && i != KEY_LSHIFT
			    && i != KEY_LMETA
			    && i != KEY_RMETA
			   )
			{
				return (KEY_CODE)i;             // top row key pressed
			}
		}
	}
	return (KEY_CODE)0;
}

static MOUSE_KEY_CODE scanMouseForPressedBindableKey()
{
	for (unsigned int i = 0; i < MOUSE_KEY_CODE::MOUSE_END; i++)
	{
		const MOUSE_KEY_CODE mouseKeyCode = (MOUSE_KEY_CODE)i;
		if (mousePressed(mouseKeyCode))
		{
			if (   mouseKeyCode != MOUSE_KEY_CODE::MOUSE_LMB // exceptions
				&& mouseKeyCode != MOUSE_KEY_CODE::MOUSE_RMB
				&& mouseKeyCode != MOUSE_KEY_CODE::MOUSE_MMB)
			{
				return mouseKeyCode; // Bindable mouse key pressed
			}
		}
	}
	return (MOUSE_KEY_CODE)0;
}

bool runInGameKeyMapEditor(unsigned id)
{
	if (id == KM_RETURN || id == KM_GO_BACK)			// return
	{
		saveKeyMap();
		widgDelete(psWScreen, KM_FORM);
		inputLoseFocus();
		bAllowOtherKeyPresses = true;
		if (id == KM_GO_BACK)
		{
			intReopenMenuWithoutUnPausing();
			return false;
		}
		return true;
	}
	if (id == KM_DEFAULT)
	{
		// reinitialise key mappings
		keyInitMappings(true);
		widgDelete(psWScreen, KM_FORM); // readd the widgets
		maxKeyMapNameWidthDirty = true;
		startInGameKeyMapEditor(false);
	}

	if (auto kmForm = (KeyMapForm *)widgGetFromID(psWScreen, KM_FORM))
	{
		kmForm->checkPushedKeyCombo();
	}
	return false;
}

// ////////////////////////////////////////////////////////////////////////////
bool runKeyMapEditor()
{
	WidgetTriggers const &triggers = widgRunScreen(psWScreen);
	unsigned id = triggers.empty() ? 0 : triggers.front().widget->id; // Just use first click here, since the next click could be on another menu.

	if (id == KM_RETURN)			// return
	{
		saveKeyMap();
		changeTitleMode(OPTIONS);
	}
	if (id == KM_DEFAULT)
	{
		// reinitialise key mappings
		keyInitMappings(true);
		widgDelete(psWScreen, FRONTEND_BACKDROP); // readd the widgets
		startKeyMapEditor(false);
	}

	if (auto kmForm = (KeyMapForm *)widgGetFromID(psWScreen, KM_FORM))
	{
		kmForm->checkPushedKeyCombo();
	}

	widgDisplayScreen(psWScreen);				// show the widgets currently running

	if (CancelPressed())
	{
		changeTitleMode(OPTIONS);
	}

	return true;
}

// ////////////////////////////////////////////////////////////////////////////
std::vector<std::reference_wrapper<const KeyFunctionInfo>> getVisibleKeymapEntries()
{
	std::vector<std::reference_wrapper<const KeyFunctionInfo>> visibleMappings;
	for (const KeyFunctionInfo& info : allKeymapEntries())
	{
		// TODO: this does not hide keybinds which used to have __HIDE status
		if (info.context != InputContext::__DEBUG)
		{
			visibleMappings.push_back(info);
		}
	}


	return visibleMappings;
}

std::vector<std::reference_wrapper<const KEY_MAPPING>> getVisibleMappings()
{
	std::vector<std::reference_wrapper<const KEY_MAPPING>> visibleMappings;
	for (const KeyFunctionInfo& info : getVisibleKeymapEntries())
	{
		for (unsigned int slotIndex = 0; slotIndex < static_cast<unsigned int>(KeyMappingSlot::LAST); ++slotIndex)
		{
			const KeyMappingSlot slot = static_cast<KeyMappingSlot>(slotIndex);
			if (const KEY_MAPPING* mapping = keyGetMappingFromFunction(info.function, slot))
			{
				visibleMappings.push_back(*mapping);
			}
		}
	}

	return visibleMappings;
}

static unsigned int getMaxKeyMapNameWidth()
{
	static unsigned int max = 0;

	if (maxKeyMapNameWidthDirty) {
		WzText displayText;
		displayText.setText(NOT_BOUND_LABEL, font_regular);
		max = static_cast<int>(displayText.width());

		char sKey[MAX_STR_LENGTH];
		for (const KEY_MAPPING& mapping : getVisibleMappings()) {
			mapping.toString(sKey);
			displayText.setText(sKey, font_regular);
			max = MAX(max, static_cast<unsigned int>(displayText.width()));
		}

		maxKeyMapNameWidthDirty = false;
	}

	return max;
}

// ////////////////////////////////////////////////////////////////////////////
static void displayKeyMapButton(WIDGET* psWidget, UDWORD xOffset, UDWORD yOffset)
{
	ASSERT_OR_RETURN(, psWidget != nullptr, "Cannot display keyMap button: Widget was null!");
	ASSERT_OR_RETURN(, psWidget->parent() != nullptr, "Keymap buttons should have a parent container!");
	const WIDGET& parent = *psWidget->parent().get();

	ASSERT_OR_RETURN(, psWidget->pUserData != nullptr, "Any widget using displayKeyMapButton must have its pUserData initialized to a (DisplayKeyMapButtonData*)");
	DisplayKeyMapButtonData& data = *static_cast<DisplayKeyMapButtonData*>(psWidget->pUserData);
	ASSERT_OR_RETURN(, data.targetFunctionData != nullptr, "DisplayKeyMapButtonData is missing target function data!");

	// Update layout
	const int numSlots = static_cast<int>(KeyMappingSlot::LAST);
	const int buttonHeight = (parent.height() / numSlots);
	const int layoutYOffset = buttonHeight * static_cast<int>(data.slot);
	const int buttonWidth = getMaxKeyMapNameWidth();
	psWidget->setGeometry(
		parent.width() - buttonWidth,
		layoutYOffset,
		buttonWidth,
		buttonHeight
	);

	int x = xOffset + psWidget->x();
	int y = yOffset + psWidget->y();
	int h = psWidget->height();
	int w = psWidget->width();

	const KeyFunctionInfo* info = keyFunctionInfoByFunction(data.targetFunctionData->function);
	ASSERT_OR_RETURN(, info != nullptr, "Invalid key function on key map button, could not find matching key function info!");

	// Draw base
	if (keyMapSelection.isSelected(data.targetFunctionData->function, data.slot))
	{
		pie_BoxFill(x, y, x + w, y + h, WZCOL_KEYMAP_ACTIVE);
	}
	else if (!info->assignable)
	{
		pie_BoxFill(x, y, x + w, y + h, WZCOL_KEYMAP_FIXED);
	}
	else
	{
		drawBlueBoxInset(x, y, w, h);
	}

	// Select label text and color
	const KEY_MAPPING* mapping = data.targetFunctionData->mappings[static_cast<unsigned int>(data.slot)];
	PIELIGHT bindingTextColor = WZCOL_FORM_TEXT;
	char sPrimaryKey[MAX_STR_LENGTH];
	if (mapping && !mapping->input.isCleared())
	{
		// Check to see if key is on the numpad, if so tell user and change color
		const bool isBoundToNumpad = mapping->input.source == KeyMappingInputSource::KEY_CODE && mapping->input.value.keyCode >= KEY_KP_0 && mapping->input.value.keyCode <= KEY_KPENTER;
		if (isBoundToNumpad)
		{
			bindingTextColor = WZCOL_YELLOW;
		}
		mapping->toString(sPrimaryKey);
	}
	else
	{
		strcpy(sPrimaryKey, info->assignable ? NOT_BOUND_LABEL.c_str() : "\0");
	}

	data.wzBindingText.setText(sPrimaryKey, font_regular);
	data.wzBindingText.render(x, y + (h / 2) + 3, bindingTextColor);
}

static void displayKeyMapLabel(WIDGET* psWidget, UDWORD xOffset, UDWORD yOffset)
{
	ASSERT_OR_RETURN(, psWidget != nullptr, "Cannot display keyMap label: Widget was null!");
	ASSERT_OR_RETURN(, psWidget->parent() != nullptr, "Keymap labels should have a parent container!");
	const WIDGET& parent = *psWidget->parent().get();

	ASSERT(psWidget->pUserData != nullptr, "Any widget using displayKeyMapLabel must have its pUserData initialized to a (DisplayKeyMapData*)");
	DisplayKeyMapData& data = *static_cast<DisplayKeyMapData*>(psWidget->pUserData);

	// Update layout
	const int buttonWidth = getMaxKeyMapNameWidth();
	psWidget->setGeometry(
		0,
		0,
		parent.width() - buttonWidth,
		parent.height()
	);

	const int x = xOffset + psWidget->x();
	const int y = yOffset + psWidget->y();
	const int w = psWidget->width();
	const int h = psWidget->height();
	drawBlueBoxInset(x, y, w, h);
	data.wzNameText.setText(_(data.name.c_str()), font_regular);
	data.wzNameText.render(x + 2, y + (psWidget->height() / 2) + 3, WZCOL_FORM_TEXT);
}

// ////////////////////////////////////////////////////////////////////////////
static bool keyMapEditor(bool first, WIDGET *parent, bool isInGame)
{
	if (first)
	{
		loadKeyMap();									// get the current mappings.
	}

	parent->attach(KeyMapForm::make(isInGame));

	/* Stop when the right number or when alphabetically last - not sure...! */
	/* Go home... */
	return true;
}

bool startInGameKeyMapEditor(bool first)
{
	bAllowOtherKeyPresses = false;
	return keyMapEditor(first, psWScreen->psForm.get(), true);
}

bool startKeyMapEditor(bool first)
{
	addBackdrop();
	addSideText(FRONTEND_SIDETEXT, KM_SX, KM_Y, _("KEY MAPPING"));
	WIDGET *parent = widgGetFromID(psWScreen, FRONTEND_BACKDROP);
	return keyMapEditor(first, parent, false);
}

// ////////////////////////////////////////////////////////////////////////////
// save current keymaps to registry
bool saveKeyMap()
{
	WzConfig ini(KeyMapPath, WzConfig::ReadAndWrite);
	if (!ini.status() || !ini.isWritable())
	{
		// NOTE: Changed to LOG_FATAL, since we want to inform user via pop-up (windows only)
		debug(LOG_FATAL, "Could not open %s", ini.fileName().toUtf8().c_str());
		return false;
	}

	ini.setValue("version", 1);

	ini.beginArray("mappings");
	for (auto const &mapping : keyMappings)
	{
		ini.setValue("meta", mapping.metaKeyCode);

		switch (mapping.input.source) {
		case KeyMappingInputSource::KEY_CODE:
			ini.setValue("source", "default");
			ini.setValue("sub", mapping.input.value.keyCode);
			break;
		case KeyMappingInputSource::MOUSE_KEY_CODE:
			ini.setValue("source", "mouse_key");
			ini.setValue("sub", mapping.input.value.mouseKeyCode);
			break;
		default:
			debug(LOG_WZ, "Encountered invalid key mapping source %u while saving keymap!", static_cast<unsigned int>(mapping.input.source));
			break;
		}
		switch (mapping.slot)
		{
		case KeyMappingSlot::PRIMARY:
			ini.setValue("slot", "primary");
			break;
		case KeyMappingSlot::SECONDARY:
			ini.setValue("slot", "secondary");
			break;
		default:
			debug(LOG_WZ, "Encountered invalid key mapping slot %u while saving keymap!", static_cast<unsigned int>(mapping.slot));
			break;
		}

		ini.setValue("action", mapping.action);
		if (auto info = keyFunctionInfoByFunction(mapping.function))
		{
			ini.setValue("function", info->name);
		}

		ini.nextArrayItem();
	}
	ini.endArray();

	debug(LOG_WZ, "Keymap written ok to %s.", KeyMapPath);
	return true;	// saved ok.
}

// ////////////////////////////////////////////////////////////////////////////
static KeyMappingInput createInputForSource(const KeyMappingInputSource source, const unsigned int keyCode)
{
	switch (source) {
	case KeyMappingInputSource::KEY_CODE:
		return (KEY_CODE)keyCode;
	case KeyMappingInputSource::MOUSE_KEY_CODE:
		return (MOUSE_KEY_CODE)keyCode;
	default:
		debug(LOG_WZ, "Encountered invalid key mapping source %u while loading keymap!", static_cast<unsigned int>(source));
		return KEY_CODE::KEY_MAXSCAN;
	}
}

// load keymaps from registry.
bool loadKeyMap()
{
	// throw away any keymaps!!
	keyMappings.clear();

	WzConfig ini(KeyMapPath, WzConfig::ReadOnly);
	if (!ini.status())
	{
		debug(LOG_WZ, "%s not found", KeyMapPath);
		return false;
	}

	for (ini.beginArray("mappings"); ini.remainingArrayItems(); ini.nextArrayItem())
	{
		auto meta = (KEY_CODE)ini.value("meta", 0).toInt();
		auto sub = ini.value("sub", 0).toInt();
		auto action = (KEY_ACTION)ini.value("action", 0).toInt();
		auto functionName = ini.value("function", "").toWzString();
		auto info = keyFunctionInfoByName(functionName.toUtf8());
		if (info == nullptr)
		{
			debug(LOG_WARNING, "Skipping unknown keymap function \"%s\".", functionName.toUtf8().c_str());
			continue;
		}

		const WzString sourceName = ini.value("source", "default").toWzString();
		const KeyMappingInputSource source = keyMappingSourceByName(sourceName.toUtf8().c_str());
		const KeyMappingInput input = createInputForSource(source, sub);

		const WzString slotName = ini.value("slot", "primary").toWzString();
		const KeyMappingSlot slot = keyMappingSlotByName(slotName.toUtf8().c_str());

		keyAddMapping(meta, input, action, info->function, slot);
	}
	ini.endArray();
	return true;
}

std::shared_ptr<W_BUTTON> KeyMapForm::createKeyMapButton(const unsigned int buttonId, const KeyMappingSlot slot, DisplayKeyMapData* targetFunctionData)
{
	W_BUTINIT emptyInit;
	DisplayKeyMapButtonData* buttonData = new DisplayKeyMapButtonData();
	buttonData->slot = slot;
	buttonData->targetFunctionData = targetFunctionData;

	auto button = std::make_shared<W_BUTTON>(&emptyInit);
	button->setGeometry(0, 0, KM_ENTRYW / 3, KM_ENTRYH); // Initially set to occupy 1/3 of the width. Display func will determine and update the actual size
	button->id = buttonId;
	button->displayFunction = displayKeyMapButton;
	button->pUserData = buttonData;
	button->setOnDelete([](WIDGET* psWidget) {
		assert(psWidget->pUserData != nullptr);
		delete static_cast<DisplayKeyMapButtonData*>(psWidget->pUserData);
		psWidget->pUserData = nullptr;
	});
	button->addOnClickHandler([=](W_BUTTON& clickedButton) {
		const DisplayKeyMapButtonData* data = static_cast<DisplayKeyMapButtonData*>(clickedButton.pUserData);

		const int slotIndex = static_cast<unsigned int>(data->slot);
		const KeyFunctionInfo* info = keyFunctionInfoByFunction(data->targetFunctionData->function);
		ASSERT_OR_RETURN(, info != nullptr, "Could not find key function info for function during onClick handler!");
		if (!info->assignable)
		{
			audio_PlayTrack(ID_SOUND_BUILD_FAIL);
			unhighlightSelected();
			return;
		}

		const KEY_MAPPING* clickedMapping = data->targetFunctionData->mappings[slotIndex];
		if (clickedMapping && keyMapSelection.isSelected(data->targetFunctionData->function, data->slot))
		{
			unhighlightSelected();
			return;
		}

		keyMapList->disableScroll();
		keyMapSelection.select(data->slot, data->targetFunctionData);
	});

	return button;
}

void KeyMapForm::initialize(bool isInGame)
{
	id = KM_FORM;

	attach(keyMapList = ScrollableListWidget::make());
	if (!isInGame)
	{
		setCalcLayout(LAMBDA_CALCLAYOUT_SIMPLE({
			psWidget->setGeometry(KM_X, KM_Y, KM_W, KM_H);
		}));
		keyMapList->setGeometry(52, 10, KM_ENTRYW, 26 * KM_ENTRYH);

		addMultiBut(*this, KM_RETURN,			// return button.
				8, 5,
				iV_GetImageWidth(FrontImages, IMAGE_RETURN),
				iV_GetImageHeight(FrontImages, IMAGE_RETURN),
				_("Return To Previous Screen"), IMAGE_RETURN, IMAGE_RETURN_HI, IMAGE_RETURN_HI);

		addMultiBut(*this, KM_DEFAULT,
				11, 45,
				iV_GetImageWidth(FrontImages, IMAGE_KEYMAP_DEFAULT),
				iV_GetImageHeight(FrontImages, IMAGE_KEYMAP_DEFAULT),
				_("Select Default"),
				IMAGE_KEYMAP_DEFAULT, IMAGE_KEYMAP_DEFAULT_HI, IMAGE_KEYMAP_DEFAULT_HI);	// default.
	}
	else
	{
		// Text versions for in-game where image resources are not available
		setCalcLayout(LAMBDA_CALCLAYOUT_SIMPLE({
			psWidget->setGeometry(((300-(KM_W/2))+D_W), ((240-(KM_H/2))+D_H), KM_W, KM_H + 10);
		}));
		keyMapList->setGeometry(52, 10, KM_ENTRYW, 24 * KM_ENTRYH);

		addButton(KM_GO_BACK, KM_H - 40, _("Go Back"));

		addButton(KM_RETURN, KM_H - 24, _("Resume Game"));

		if (!(bMultiPlayer && NetPlay.bComms != 0)) // no editing in true multiplayer
		{
			addButton(KM_DEFAULT, KM_H - 8, _("Select Default"));
		}
	}

	auto infos = getVisibleKeymapEntries();
	std::sort(infos.begin(), infos.end(), [](const KeyFunctionInfo& a, const KeyFunctionInfo& b) {
		return a.displayName < b.displayName;
	});

	/* Add key mappings to the form */
	for (std::vector<std::reference_wrapper<const KeyFunctionInfo>>::const_iterator i = infos.begin(); i != infos.end(); ++i)
	{
		const KeyFunctionInfo& info = *i;
		DisplayKeyMapData* data = new DisplayKeyMapData(info.function, info.displayName);

		const unsigned int numSlots = static_cast<unsigned int>(KeyMappingSlot::LAST);

		const unsigned int index = i - infos.begin();
		const unsigned int containerId = KM_START + index * (numSlots + 2);
		const unsigned int labelId = KM_START + index * (numSlots + 2) + 1;

		auto label = std::make_shared<WIDGET>();
		label->setGeometry(0, 0, KM_ENTRYW / 3, KM_ENTRYH);
		label->id = labelId;
		label->displayFunction = displayKeyMapLabel;
		label->pUserData = data;
		label->setOnDelete([](WIDGET* psWidget) {
			assert(psWidget->pUserData != nullptr);
			delete static_cast<DisplayKeyMapData*>(psWidget->pUserData);
			psWidget->pUserData = nullptr;
		});

		auto container = std::make_shared<WIDGET>();
		container->setGeometry(0, 0, KM_ENTRYW, KM_ENTRYH * numSlots);
		container->id = containerId;
		container->attach(label);

		for (unsigned int slotIndex = 0; slotIndex < numSlots; ++slotIndex)
		{
			const auto slot = static_cast<KeyMappingSlot>(slotIndex);
			const auto buttonId = KM_START + index * (numSlots + 2) + 2 + slotIndex;
			const auto button = createKeyMapButton(buttonId, slot, data);
			container->attach(button);

			data->mappings[slotIndex] = keyGetMappingFromFunction(info.function, slot);
		}

		keyMapList->addItem(container);
	}
}

void KeyMapForm::addButton(int buttonId, int y, const char *text)
{
	W_BUTINIT sButInit;

	sButInit.formID		= KM_FORM;
	sButInit.style		= WBUT_PLAIN | WBUT_TXTCENTRE;
	sButInit.width		= KM_W;
	sButInit.FontID		= font_regular;
	sButInit.x			= 0;
	sButInit.height		= 10;
	sButInit.pDisplay	= displayTextOption;
	sButInit.initPUserDataFunc = []() -> void * { return new DisplayTextOptionCache(); };
	sButInit.onDelete = [](WIDGET *psWidget) {
		assert(psWidget->pUserData != nullptr);
		delete static_cast<DisplayTextOptionCache *>(psWidget->pUserData);
		psWidget->pUserData = nullptr;
	};

	sButInit.id			= buttonId;
	sButInit.y			= y;
	sButInit.pText		= text;

	attach(std::make_shared<W_BUTTON>(&sButInit));
}

void KeyMapForm::checkPushedKeyCombo()
{
	if (keyMapSelection.hasActiveSelection)
	{
		const KEY_CODE kc = scanKeyBoardForPressedBindableKey();
		if (kc)
		{
			pushedKeyCombo(kc);
		}
		const MOUSE_KEY_CODE mkc = scanMouseForPressedBindableKey();
		if (mkc)
		{
			pushedKeyCombo(mkc);
		}
	}
}

bool KeyMapForm::pushedKeyCombo(const KeyMappingInput input)
{
	KEY_CODE metakey = KEY_IGNORE;

	if (keyDown(KEY_RALT) || keyDown(KEY_LALT))
	{
		metakey = KEY_LALT;
	}
	else if (keyDown(KEY_RCTRL) || keyDown(KEY_LCTRL))
	{
		metakey = KEY_LCTRL;
	}
	else if (keyDown(KEY_RSHIFT) || keyDown(KEY_LSHIFT))
	{
		metakey = KEY_LSHIFT;
	}
	else if (keyDown(KEY_RMETA) || keyDown(KEY_LMETA))
	{
		metakey = KEY_LMETA;
	}

	const auto selectedFunction = keyMapSelection.data->function;
	const KeyFunctionInfo* info = keyFunctionInfoByFunction(selectedFunction);
	ASSERT_OR_RETURN(false, info != nullptr, "Could not find key function info for function while creating a new mapping!");

	/* check if bound to a fixed combo. */
	if (!info->assignable)
	{
		unhighlightSelected();
		return false;
	}

	/* Clear down mappings using these keys */
	clearKeyMappingIfConflicts(metakey, input, info->context);

	/* Try and see if its there already - add it if not. e.g. secondary keybinds are expected to be null on default key sets */
	const unsigned int slotIndex = static_cast<unsigned int>(keyMapSelection.slot);
	KEY_MAPPING* psMapping = keyGetMappingFromFunction(selectedFunction, keyMapSelection.slot);
	if (!psMapping)
	{
		psMapping = keyAddMapping(metakey, input, KEY_ACTION::KEYMAP_PRESSED, selectedFunction, keyMapSelection.slot);
		keyMapSelection.data->mappings[slotIndex] = psMapping;
	}
	else
	{
		/* Found existing mapping, alter it to the new values */
		psMapping->input       = input;
		psMapping->info        = info;
		psMapping->metaKeyCode = metakey;
	}
	invalidateKeyMappingSortOrder();
	maxKeyMapNameWidthDirty = true;
	unhighlightSelected();
	return true;
}

void KeyMapForm::unhighlightSelected()
{
	keyMapList->enableScroll();
	keyMapSelection.clearSelection();
}
