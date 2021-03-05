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

#include <vector>

#include "keyconfig.h"

#include "lib/framework/frame.h"
#include "lib/framework/input.h"

#include "../keybind.h"

// Definitions/Configuration for all mappable Key Functions
//
// NOTE: The initialization is done as a function with bunch of emplace_backs instead of an initializer list for two reasons:
//        1.) KeyFunctionInfo is marked as non-copy to avoid unnecessarily copying them around. Using an initializer list requires
//            types to be copyable, so we cannot use initializer lists, at all (we use move-semantics with std::move instead)
//        2.) The initializer list itself would require >20kb of stack memory due to sheer size of this thing. Inserting all
//            entries one-by-one requires only one entry on the stack at a time, mitigating the risk of a stack overflow.
static void initializeKeyFunctions(std::vector<KeyFunctionInfo>& entries)
{
	entries.emplace_back(KeyFunctionInfo(InputContext::ALWAYS_ACTIVE,   KeyMappingType::FIXED,       kf_ChooseManufacture,                                          "ChooseManufacture",            N_("Manufacture"),                                  {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_F1,           KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::ALWAYS_ACTIVE,   KeyMappingType::FIXED,       kf_ChooseResearch,                                             "ChooseResearch",               N_("Research"),                                     {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_F2,           KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::ALWAYS_ACTIVE,   KeyMappingType::FIXED,       kf_ChooseBuild,                                                "ChooseBuild",                  N_("Build"),                                        {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_F3,           KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::ALWAYS_ACTIVE,   KeyMappingType::FIXED,       kf_ChooseDesign,                                               "ChooseDesign",                 N_("Design"),                                       {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_F4,           KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::ALWAYS_ACTIVE,   KeyMappingType::FIXED,       kf_ChooseIntelligence,                                         "ChooseIntelligence",           N_("Intelligence Display"),                         {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_F5,           KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::ALWAYS_ACTIVE,   KeyMappingType::FIXED,       kf_ChooseCommand,                                              "ChooseCommand",                N_("Commanders"),                                   {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_F6,           KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_QuickSave,                                                  "QuickSave",                    N_("QuickSave"),                                    {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_F7,           KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_ToggleRadar,                                                "ToggleRadar",                  N_("Toggle Radar"),                                 {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LSHIFT,   KEY_CODE::KEY_F7,           KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_QuickLoad,                                                  "QuickLoad",                    N_("QuickLoad"),                                    {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_F8,           KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_ToggleConsole,                                              "ToggleConsole",                N_("Toggle Console Display"),                       {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LSHIFT,   KEY_CODE::KEY_F8,           KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_ToggleEnergyBars,                                           "ToggleEnergyBars",             N_("Toggle Damage Bars On/Off"),                    {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_F9,           KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::BACKGROUND,      KeyMappingType::FIXED,       kf_ScreenDump,                                                 "ScreenDump",                   N_("Take Screen Shot"),                             {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_F10,          KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_ToggleFormationSpeedLimiting,                               "ToggleFormationSpeedLimiting", N_("Toggle Formation Speed Limiting"),              {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_F11,          KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_MoveToLastMessagePos,                                       "MoveToLastMessagePos",         N_("View Location of Previous Message"),            {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_F12,          KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_ToggleSensorDisplay,                                        "ToggleSensorDisplay",          N_("Toggle Sensor display"),                        {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LSHIFT,   KEY_CODE::KEY_F12,          KeyAction::PRESSED}}}));
	// ASSIGN GROUPS
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_AssignGrouping_N(0),                                        "AssignGrouping_0",             N_("Assign Group 0"),                               {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LCTRL,    KEY_CODE::KEY_0,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_AssignGrouping_N(1),                                        "AssignGrouping_1",             N_("Assign Group 1"),                               {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LCTRL,    KEY_CODE::KEY_1,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_AssignGrouping_N(2),                                        "AssignGrouping_2",             N_("Assign Group 2"),                               {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LCTRL,    KEY_CODE::KEY_2,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_AssignGrouping_N(3),                                        "AssignGrouping_3",             N_("Assign Group 3"),                               {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LCTRL,    KEY_CODE::KEY_3,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_AssignGrouping_N(4),                                        "AssignGrouping_4",             N_("Assign Group 4"),                               {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LCTRL,    KEY_CODE::KEY_4,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_AssignGrouping_N(5),                                        "AssignGrouping_5",             N_("Assign Group 5"),                               {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LCTRL,    KEY_CODE::KEY_5,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_AssignGrouping_N(6),                                        "AssignGrouping_6",             N_("Assign Group 6"),                               {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LCTRL,    KEY_CODE::KEY_6,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_AssignGrouping_N(7),                                        "AssignGrouping_7",             N_("Assign Group 7"),                               {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LCTRL,    KEY_CODE::KEY_7,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_AssignGrouping_N(8),                                        "AssignGrouping_8",             N_("Assign Group 8"),                               {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LCTRL,    KEY_CODE::KEY_8,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_AssignGrouping_N(9),                                        "AssignGrouping_9",             N_("Assign Group 9"),                               {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LCTRL,    KEY_CODE::KEY_9,            KeyAction::PRESSED}}}));
	// ADD TO GROUP
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_AddGrouping_N(0),                                           "AddGrouping_0",                N_("Add to Group 0"),                               {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LSHIFT,   KEY_CODE::KEY_0,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_AddGrouping_N(1),                                           "AddGrouping_1",                N_("Add to Group 1"),                               {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LSHIFT,   KEY_CODE::KEY_1,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_AddGrouping_N(2),                                           "AddGrouping_2",                N_("Add to Group 2"),                               {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LSHIFT,   KEY_CODE::KEY_2,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_AddGrouping_N(3),                                           "AddGrouping_3",                N_("Add to Group 3"),                               {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LSHIFT,   KEY_CODE::KEY_3,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_AddGrouping_N(4),                                           "AddGrouping_4",                N_("Add to Group 4"),                               {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LSHIFT,   KEY_CODE::KEY_4,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_AddGrouping_N(5),                                           "AddGrouping_5",                N_("Add to Group 5"),                               {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LSHIFT,   KEY_CODE::KEY_5,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_AddGrouping_N(6),                                           "AddGrouping_6",                N_("Add to Group 6"),                               {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LSHIFT,   KEY_CODE::KEY_6,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_AddGrouping_N(7),                                           "AddGrouping_7",                N_("Add to Group 7"),                               {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LSHIFT,   KEY_CODE::KEY_7,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_AddGrouping_N(8),                                           "AddGrouping_8",                N_("Add to Group 8"),                               {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LSHIFT,   KEY_CODE::KEY_8,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_AddGrouping_N(9),                                           "AddGrouping_9",                N_("Add to Group 9"),                               {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LSHIFT,   KEY_CODE::KEY_9,            KeyAction::PRESSED}}}));
	// SELECT GROUPS - Will jump to the group as well as select if group is ALREADY selected
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectGrouping_N(0),                                        "SelectGrouping_0",             N_("Select Group 0"),                               {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_0,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectGrouping_N(1),                                        "SelectGrouping_1",             N_("Select Group 1"),                               {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_1,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectGrouping_N(2),                                        "SelectGrouping_2",             N_("Select Group 2"),                               {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_2,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectGrouping_N(3),                                        "SelectGrouping_3",             N_("Select Group 3"),                               {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_3,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectGrouping_N(4),                                        "SelectGrouping_4",             N_("Select Group 4"),                               {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_4,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectGrouping_N(5),                                        "SelectGrouping_5",             N_("Select Group 5"),                               {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_5,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectGrouping_N(6),                                        "SelectGrouping_6",             N_("Select Group 6"),                               {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_6,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectGrouping_N(7),                                        "SelectGrouping_7",             N_("Select Group 7"),                               {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_7,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectGrouping_N(8),                                        "SelectGrouping_8",             N_("Select Group 8"),                               {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_8,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectGrouping_N(9),                                        "SelectGrouping_9",             N_("Select Group 9"),                               {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_9,            KeyAction::PRESSED}}}));
	// SELECT COMMANDER - Will jump to the group as well as select if group is ALREADY selected
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectCommander_N(0),                                       "SelectCommander_0",            N_("Select Commander 0"),                           {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LALT,     KEY_CODE::KEY_0,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectCommander_N(1),                                       "SelectCommander_1",            N_("Select Commander 1"),                           {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LALT,     KEY_CODE::KEY_1,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectCommander_N(2),                                       "SelectCommander_2",            N_("Select Commander 2"),                           {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LALT,     KEY_CODE::KEY_2,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectCommander_N(3),                                       "SelectCommander_3",            N_("Select Commander 3"),                           {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LALT,     KEY_CODE::KEY_3,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectCommander_N(4),                                       "SelectCommander_4",            N_("Select Commander 4"),                           {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LALT,     KEY_CODE::KEY_4,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectCommander_N(5),                                       "SelectCommander_5",            N_("Select Commander 5"),                           {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LALT,     KEY_CODE::KEY_5,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectCommander_N(6),                                       "SelectCommander_6",            N_("Select Commander 6"),                           {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LALT,     KEY_CODE::KEY_6,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectCommander_N(7),                                       "SelectCommander_7",            N_("Select Commander 7"),                           {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LALT,     KEY_CODE::KEY_7,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectCommander_N(8),                                       "SelectCommander_8",            N_("Select Commander 8"),                           {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LALT,     KEY_CODE::KEY_8,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectCommander_N(9),                                       "SelectCommander_9",            N_("Select Commander 9"),                           {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LALT,     KEY_CODE::KEY_9,            KeyAction::PRESSED}}}));
	// MULTIPLAYER
	entries.emplace_back(KeyFunctionInfo(InputContext::BACKGROUND,      KeyMappingType::ASSIGNABLE,  kf_addMultiMenu,                                               "addMultiMenu",                 N_("Multiplayer Options / Alliance dialog"),        {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_KPENTER,      KeyAction::PRESSED}}}));
	// GAME CONTROLS - Moving around, zooming in, rotating etc
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_ScrollCamera(0, 1),                                         "CameraUp",                     N_("Move Camera Up"),                               {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_UPARROW,      KeyAction::DOWN   }}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_ScrollCamera(0, -1),                                        "CameraDown",                   N_("Move Camera Down"),                             {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_DOWNARROW,    KeyAction::DOWN   }}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_ScrollCamera(1, 0),                                         "CameraRight",                  N_("Move Camera Right"),                            {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_RIGHTARROW,   KeyAction::DOWN   }}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_ScrollCamera(-1, 0),                                        "CameraLeft",                   N_("Move Camera Left"),                             {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_LEFTARROW,    KeyAction::DOWN   }}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SeekNorth,                                                  "SeekNorth",                    N_("Snap View to North"),                           {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_BACKSPACE,    KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_ToggleCamera,                                               "ToggleCamera",                 N_("Toggle Tracking Camera"),                       {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_SPACE,        KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::BACKGROUND,      KeyMappingType::FIXED,       kf_addInGameOptions,                                           "addInGameOptions",             N_("Display In-Game Options"),                      {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_ESC,          KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::RADAR,           KeyMappingType::ASSIGNABLE,  kf_RadarZoom(-1),                                              "RadarZoomOut",                 N_("Zoom Radar Out"),                               {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_MINUS,        KeyAction::PRESSED}}, {KeyMappingSlot::SECONDARY, {KEY_CODE::KEY_IGNORE, MOUSE_KEY_CODE::MOUSE_WDN, KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::RADAR,           KeyMappingType::ASSIGNABLE,  kf_RadarZoom(1),                                               "RadarZoomIn",                  N_("Zoom Radar In"),                                {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_EQUALS,       KeyAction::PRESSED}}, {KeyMappingSlot::SECONDARY, {KEY_CODE::KEY_IGNORE, MOUSE_KEY_CODE::MOUSE_WUP, KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_Zoom(-1),                                                   "ZoomIn",                       N_("Zoom In"),                                      {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_KP_PLUS,      KeyAction::DOWN   }}, {KeyMappingSlot::SECONDARY, {KEY_CODE::KEY_IGNORE, MOUSE_KEY_CODE::MOUSE_WUP, KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_Zoom(1),                                                    "ZoomOut",                      N_("Zoom Out"),                                     {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_KP_MINUS,     KeyAction::DOWN   }}, {KeyMappingSlot::SECONDARY, {KEY_CODE::KEY_IGNORE, MOUSE_KEY_CODE::MOUSE_WDN, KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_PitchForward,                                               "PitchForward",                 N_("Pitch Forward"),                                {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_KP_2,         KeyAction::DOWN   }}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_RotateLeft,                                                 "RotateLeft",                   N_("Rotate Left"),                                  {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_KP_4,         KeyAction::DOWN   }}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_ResetPitch,                                                 "ResetPitch",                   N_("Reset Pitch"),                                  {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_KP_5,         KeyAction::DOWN   }}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_RotateRight,                                                "RotateRight",                  N_("Rotate Right"),                                 {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_KP_6,         KeyAction::DOWN   }}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_PitchBack,                                                  "PitchBack",                    N_("Pitch Back"),                                   {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_KP_8,         KeyAction::DOWN   }}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_RightOrderMenu,                                             "RightOrderMenu",               N_("Orders Menu"),                                  {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_KP_0,         KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SlowDown,                                                   "SlowDown",                     N_("Decrease Game Speed"),                          {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LCTRL,    KEY_CODE::KEY_MINUS,        KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SpeedUp,                                                    "SpeedUp",                      N_("Increase Game Speed"),                          {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LCTRL,    KEY_CODE::KEY_EQUALS,       KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_NormalSpeed,                                                "NormalSpeed",                  N_("Reset Game Speed"),                             {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LCTRL,    KEY_CODE::KEY_BACKSPACE,    KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_FaceNorth,                                                  "FaceNorth",                    N_("View North"),                                   {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LCTRL,    KEY_CODE::KEY_UPARROW,      KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_FaceSouth,                                                  "FaceSouth",                    N_("View South"),                                   {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LCTRL,    KEY_CODE::KEY_DOWNARROW,    KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_FaceEast,                                                   "FaceEast",                     N_("View East"),                                    {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LCTRL,    KEY_CODE::KEY_LEFTARROW,    KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_FaceWest,                                                   "FaceWest",                     N_("View West"),                                    {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LCTRL,    KEY_CODE::KEY_RIGHTARROW,   KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_JumpToResourceExtractor,                                    "JumpToResourceExtractor",      N_("View next Oil Derrick"),                        {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_KP_STAR,      KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_JumpToUnits(DROID_REPAIR),                                  "JumpToRepairUnits",            N_("View next Repair Unit"),                        {}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_JumpToUnits(DROID_CONSTRUCT),                               "JumpToConstructorUnits",       N_("View next Truck"),                              {}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_JumpToUnits(DROID_SENSOR),                                  "JumpToSensorUnits",            N_("View next Sensor Unit"),                        {}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_JumpToUnits(DROID_COMMAND),                                 "JumpToCommandUnits",           N_("View next Commander"),                          {}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_ToggleOverlays,                                             "ToggleOverlays",               N_("Toggle Overlays"),                              {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_TAB,          KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_ToggleConsoleDrop,                                          "ToggleConsoleDrop",            N_("Toggle Console History "),                      {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_BACKQUOTE,    KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_ToggleTeamChat,                                             "ToggleTeamChat",               N_("Toggle Team Chat History"),                     {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LCTRL,    KEY_CODE::KEY_BACKQUOTE,    KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_RotateBuildingCW,                                           "RotateBuildingClockwise",      N_("Rotate Building Clockwise"),                    {}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_RotateBuildingACW,                                          "RotateBuildingAnticlockwise",  N_("Rotate Building Anticlockwise"),                {}));
	// IN GAME MAPPINGS - Single key presses - ALL __DEBUG keymappings will be removed for master
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_CentreOnBase,                                               "CentreOnBase",                 N_("Center View on HQ"),                            {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_B,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SetDroid(DSO_ATTACK_LEVEL, DSS_ALEV_NEVER),                 "SetDroidAttackCease",          N_("Hold Fire"),                                    {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_C,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_JumpToUnassignedUnits,                                      "JumpToUnassignedUnits",        N_("View Unassigned Units"),                        {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_D,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SetDroid(DSO_ATTACK_LEVEL, DSS_ALEV_ATTACKED),              "SetDroidAttackReturn",         N_("Return Fire"),                                  {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_E,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SetDroid(DSO_ATTACK_LEVEL, DSS_ALEV_ALWAYS),                "SetDroidAttackAtWill",         N_("Fire at Will"),                                 {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_F,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SetDroid(DSO_HALTTYPE, DSS_HALT_GUARD),                     "SetDroidMoveGuard",            N_("Guard Position"),                               {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_G,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SetDroid(DSO_RETURN_TO_LOC, DSS_RTL_BASE),                  "SetDroidReturnToBase",         N_("Return to HQ"),                                 {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LSHIFT,   KEY_CODE::KEY_H,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_OrderDroid(DORDER_HOLD),                                    "SetDroidOrderHold",            N_("Hold Position"),                                {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_H,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SetDroid(DSO_ATTACK_RANGE, DSS_ARANGE_OPTIMUM),             "SetDroidRangeOptimum",         N_("Optimum Range"),                                {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_I,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SetDroid(DSO_ATTACK_RANGE, DSS_ARANGE_SHORT),               "SetDroidRangeShort",           N_("Short Range"),                                  {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_O,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SetDroid(DSO_HALTTYPE, DSS_HALT_PURSUE),                    "SetDroidMovePursue",           N_("Pursue"),                                       {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_P,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SetDroid(DSO_PATROL, DSS_PATROL_SET),                       "SetDroidMovePatrol",           N_("Patrol"),                                       {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_Q,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SetDroid(DSO_RETURN_TO_LOC, DSS_RTL_REPAIR),                "SetDroidGoForRepair",          N_("Return For Repair"),                            {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_R,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_OrderDroid(DORDER_STOP),                                    "SetDroidOrderStop",            N_("Stop Droid"),                                   {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_S,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SetDroid(DSO_RETURN_TO_LOC, DSS_RTL_TRANSPORT),             "SetDroidGoToTransport",        N_("Go to Transport"),                              {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_T,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SetDroid(DSO_ATTACK_RANGE, DSS_ARANGE_LONG),                "SetDroidRangeLong",            N_("Long Range"),                                   {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_U,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SendGlobalMessage,                                          "SendGlobalMessage",            N_("Send Global Text Message"),                     {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_RETURN,       KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SendTeamMessage,                                            "SendTeamMessage",              N_("Send Team Text Message"),                       {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LCTRL,    KEY_CODE::KEY_RETURN,       KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_AddHelpBlip,                                                "AddHelpBlip",                  N_("Drop a beacon"),                                {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LALT,     KEY_CODE::KEY_H,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_ToggleShadows,                                              "ToggleShadows",                N_("Toggles shadows"),                              {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LALT,     KEY_CODE::KEY_S,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_toggleTrapCursor,                                           "toggleTrapCursor",             N_("Trap cursor"),                                  {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LALT,     KEY_CODE::KEY_T,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::RADAR,           KeyMappingType::ASSIGNABLE,  kf_ToggleRadarTerrain,                                         "ToggleRadarTerrain",           N_("Toggle radar terrain"),                         {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LCTRL,    KEY_CODE::KEY_TAB,          KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::RADAR,           KeyMappingType::ASSIGNABLE,  kf_ToggleRadarAllyEnemy,                                       "ToggleRadarAllyEnemy",         N_("Toggle ally-enemy radar view"),                 {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LSHIFT,   KEY_CODE::KEY_TAB,          KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_ShowMappings,                                               "ShowMappings",                 N_("Show all keyboard mappings"),                   {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_M,            KeyAction::PRESSED}}}));
	// Some extra non QWERTY mappings but functioning in same way
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SetDroid(DSO_REPAIR_LEVEL, DSS_REPLEV_LOW),                 "SetDroidRetreatMedium",        N_("Retreat at Medium Damage"),                     {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_COMMA,        KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SetDroid(DSO_REPAIR_LEVEL, DSS_REPLEV_HIGH),                "SetDroidRetreatHeavy",         N_("Retreat at Heavy Damage"),                      {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_FULLSTOP,     KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SetDroid(DSO_REPAIR_LEVEL, DSS_REPLEV_NEVER),               "SetDroidRetreatNever",         N_("Do or Die!"),                                   {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_FORWARDSLASH, KeyAction::PRESSED}}}));
	// In game mappings - COMBO (CTRL + LETTER) presses
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectUnits(DST_ALL_COMBAT),                                "SelectAllCombatUnits",         N_("Select all Combat Units"),                      {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LCTRL,    KEY_CODE::KEY_A,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectUnits(DST_CYBORG),                                    "SelectAllCyborgs",             N_("Select all Cyborgs"),                           {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LCTRL,    KEY_CODE::KEY_C,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectUnits(DST_ALL_DAMAGED),                               "SelectAllDamaged",             N_("Select all Heavily Damaged Units"),             {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LCTRL,    KEY_CODE::KEY_D,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectUnits(DST_HALF_TRACKED),                              "SelectAllHalfTracked",         N_("Select all Half-tracks"),                       {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LCTRL,    KEY_CODE::KEY_F,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectUnits(DST_HOVER),                                     "SelectAllHovers",              N_("Select all Hovers"),                            {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LCTRL,    KEY_CODE::KEY_H,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SetDroid(DSO_RECYCLE, DSS_RECYCLE_SET),                     "SetDroidRecycle",              N_("Return for Recycling"),                         {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LCTRL,    KEY_CODE::KEY_R,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectUnits(DST_UNUSED, DS_ALL_UNITS, true),                "SelectAllOnScreenUnits",       N_("Select all Units on Screen"),                   {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LCTRL,    KEY_CODE::KEY_S,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectUnits(DST_TRACKED),                                   "SelectAllTracked",             N_("Select all Tracks"),                            {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LCTRL,    KEY_CODE::KEY_T,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectUnits(DST_UNUSED, DS_ALL_UNITS),                      "SelectAllUnits",               N_("Select EVERY unit"),                            {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LCTRL,    KEY_CODE::KEY_U,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectUnits(DST_VTOL),                                      "SelectAllVTOLs",               N_("Select all VTOLs"),                             {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LCTRL,    KEY_CODE::KEY_V,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectUnits(DST_VTOL_ARMED),                                "SelectAllArmedVTOLs",          N_("Select all fully-armed VTOLs"),                 {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LSHIFT,   KEY_CODE::KEY_V,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectUnits(DST_WHEELED),                                   "SelectAllWheeled",             N_("Select all Wheels"),                            {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LCTRL,    KEY_CODE::KEY_W,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::__DEBUG,         KeyMappingType::HIDDEN,      kf_FrameRate,                                                  "FrameRate",                    N_("Show frame rate"),                              {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LCTRL,    KEY_CODE::KEY_Y,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectUnits(DST_ALL_SAME),                                  "SelectAllSameType",            N_("Select all units with the same components"),    {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LCTRL,    KEY_CODE::KEY_Z,            KeyAction::PRESSED}}}));
	// In game mappings - COMBO (SHIFT + LETTER) presses
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectUnits(DST_ALL_COMBAT_CYBORG),                         "SelectAllCombatCyborgs",       N_("Select all Combat Cyborgs"),                    {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LSHIFT,   KEY_CODE::KEY_C,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectUnits(DST_ENGINEER),                                  "SelectAllEngineers",           N_("Select all Engineers"),                         {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LSHIFT,   KEY_CODE::KEY_E,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectUnits(DST_ALL_COMBAT_LAND),                           "SelectAllLandCombatUnits",     N_("Select all Land Combat Units"),                 {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LSHIFT,   KEY_CODE::KEY_G,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectUnits(DST_MECHANIC),                                  "SelectAllMechanics",           N_("Select all Mechanics"),                         {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LSHIFT,   KEY_CODE::KEY_M,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectUnits(DST_TRANSPORTER),                               "SelectAllTransporters",        N_("Select all Transporters"),                      {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LSHIFT,   KEY_CODE::KEY_P,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectUnits(DST_REPAIR_TANK),                               "SelectAllRepairTanks",         N_("Select all Repair Tanks"),                      {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LSHIFT,   KEY_CODE::KEY_R,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectUnits(DST_SENSOR),                                    "SelectAllSensorUnits",         N_("Select all Sensor Units"),                      {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LSHIFT,   KEY_CODE::KEY_S,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectUnits(DST_TRUCK),                                     "SelectAllTrucks",              N_("Select all Trucks"),                            {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LSHIFT,   KEY_CODE::KEY_T,            KeyAction::PRESSED}}}));
	// SELECT PLAYERS - DEBUG ONLY
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectNextFactory(REF_FACTORY),                             "SelectNextFactory",            N_("Select next Factory"),                          {}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectNextResearch(),                                       "SelectNextResearch",           N_("Select next Research Facility"),                {}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectNextPowerStation(),                                   "SelectNextPowerStation",       N_("Select next Power Generator"),                  {}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectNextFactory(REF_CYBORG_FACTORY),                      "SelectNextCyborgFactory",      N_("Select next Cyborg Factory"),                   {}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectNextFactory(REF_VTOL_FACTORY),                        "SelectNextVtolFactory",        N_("Select next VTOL Factory"),                     {}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectNextFactory(REF_FACTORY, true),                       "JumpNextFactory",              N_("Jump to next Factory"),                         {}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectNextResearch(true),                                   "JumpNextResearch",             N_("Jump to next Research Facility"),               {}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectNextPowerStation(true),                               "JumpNextPowerStation",         N_("Jump to next Power Generator"),                 {}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectNextFactory(REF_CYBORG_FACTORY, true),                "JumpNextCyborgFactory",        N_("Jump to next Cyborg Factory"),                  {}));
	entries.emplace_back(KeyFunctionInfo(InputContext::GAMEPLAY,        KeyMappingType::ASSIGNABLE,  kf_SelectNextFactory(REF_VTOL_FACTORY, true),                  "JumpNextVtolFactory",          N_("Jump to next VTOL Factory"),                    {}));
	// Debug options
	entries.emplace_back(KeyFunctionInfo(InputContext::BACKGROUND,      KeyMappingType::HIDDEN,      kf_ToggleDebugMappings,                                        "ToggleDebugMappings",          N_("Toggle Debug Mappings"),                        {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LSHIFT,   KEY_CODE::KEY_BACKSPACE,    KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::__DEBUG,         KeyMappingType::HIDDEN,      kf_ToggleShowPath,                                             "ToggleShowPath",               N_("Toggle display of droid path"),                 {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LCTRL,    KEY_CODE::KEY_M,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::__DEBUG,         KeyMappingType::HIDDEN,      kf_ToggleShowGateways,                                         "ToggleShowGateways",           N_("Toggle display of gateways"),                   {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LCTRL,    KEY_CODE::KEY_E,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::__DEBUG,         KeyMappingType::HIDDEN,      kf_ToggleVisibility,                                           "ToggleVisibility",             N_("Toggle visibility"),                            {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_V,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::__DEBUG,         KeyMappingType::HIDDEN,      kf_RaiseTile,                                                  "RaiseTile",                    N_("Raise tile height"),                            {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_W,            KeyAction::DOWN   }}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::__DEBUG,         KeyMappingType::HIDDEN,      kf_LowerTile,                                                  "LowerTile",                    N_("Lower tile height"),                            {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_A,            KeyAction::DOWN   }}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::__DEBUG,         KeyMappingType::HIDDEN,      kf_ToggleFog,                                                  "ToggleFog",                    N_("Toggles All fog"),                              {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LCTRL,    KEY_CODE::KEY_J,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::__DEBUG,         KeyMappingType::HIDDEN,      kf_ToggleWeather,                                              "ToggleWeather",                N_("Trigger some weather"),                         {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LCTRL,    KEY_CODE::KEY_Q,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::__DEBUG,         KeyMappingType::HIDDEN,      kf_TriFlip,                                                    "TriFlip",                      N_("Flip terrain triangle"),                        {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_IGNORE,   KEY_CODE::KEY_K,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::__DEBUG,         KeyMappingType::HIDDEN,      kf_PerformanceSample,                                          "PerformanceSample",            N_("Make a performance measurement sample"),        {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LCTRL,    KEY_CODE::KEY_K,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::__DEBUG,         KeyMappingType::HIDDEN,      kf_AllAvailable,                                               "AllAvailable",                 N_("Make all items available"),                     {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LALT,     KEY_CODE::KEY_A,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::__DEBUG,         KeyMappingType::HIDDEN,      kf_KillSelected,                                               "KillSelected",                 N_("Kill Selected Unit(s)"),                        {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LALT,     KEY_CODE::KEY_K,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::__DEBUG,         KeyMappingType::HIDDEN,      kf_ToggleGodMode,                                              "ToggleGodMode",                N_("Toggle god Mode Status"),                       {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LCTRL,    KEY_CODE::KEY_G,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::__DEBUG,         KeyMappingType::HIDDEN,      kf_ChooseOptions,                                              "ChooseOptions",                N_("Display Options Screen"),                       {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LCTRL,    KEY_CODE::KEY_O,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::__DEBUG,         KeyMappingType::HIDDEN,      kf_FinishResearch,                                             "FinishResearch",               N_("Complete current research"),                    {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LCTRL,    KEY_CODE::KEY_X,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::__DEBUG,         KeyMappingType::HIDDEN,      kf_RevealMapAtPos,                                             "RevealMapAtPos",               N_("Reveal map at mouse position"),                 {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LSHIFT,   KEY_CODE::KEY_W,            KeyAction::PRESSED}}}));
	entries.emplace_back(KeyFunctionInfo(InputContext::__DEBUG,         KeyMappingType::HIDDEN,      kf_TraceObject,                                                "TraceObject",                  N_("Trace a game object"),                          {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LCTRL,    KEY_CODE::KEY_L,            KeyAction::PRESSED}}}));


	// Hidden/"Hardcoded" mappings
	entries.emplace_back(KeyFunctionInfo(InputContext::ALWAYS_ACTIVE,   KeyMappingType::HIDDEN,      kf_ToggleFullscreen,                                           "ToggleFullscreen",             N_("Toggle fullscreen"),                            {{KeyMappingSlot::PRIMARY, {KEY_CODE::KEY_LALT,     KEY_CODE::KEY_RETURN,       KeyAction::PRESSED}}}));
}

KeyFunctionConfiguration::KeyFunctionConfiguration()
{
	initializeKeyFunctions(entries);
	for (size_t i = 0; i < entries.size(); ++i)
	{
		nameToIndexMap[entries[i].name] = i;
	}
}

nonstd::optional<std::reference_wrapper<const KeyFunctionInfo>> KeyFunctionConfiguration::keyFunctionInfoByName(std::string const& name) const
{
	auto it = nameToIndexMap.find(name);
	if (it != nameToIndexMap.end()) {
		return entries[it->second];
	}
	return nonstd::nullopt;
}

const KeyFunctionEntries KeyFunctionConfiguration::allKeyFunctionEntries() const
{
	KeyFunctionEntries allEntries;
	for (std::vector<KeyFunctionInfo>::const_iterator i = entries.cbegin(); i != entries.cend(); ++i)
	{
		allEntries.push_back(*i);
	}
	return allEntries;
}

KeyFunctionInfo::KeyFunctionInfo(
	const InputContext& context,
	const KeyMappingType type,
	const MappableFunction function,
	const std::string name,
	const std::string displayName
)
	: KeyFunctionInfo(context, type, function, name, displayName, {})
{
}

KeyFunctionInfo::KeyFunctionInfo(
	const InputContext& context,
	const KeyMappingType type,
	const MappableFunction function,
	const std::string name,
	const std::string displayName,
	const std::vector<std::pair<KeyMappingSlot, KeyCombination>> defaultMappings
)
	: context(context)
	, type(type)
	, function(function)
	, name(name)
	, displayName(displayName)
	, defaultMappings(defaultMappings)
{
}

KeyFunctionInfo::KeyFunctionInfo(
	const InputContext& context,
	const KeyMappingType type,
	const MappableFunction function,
	const std::string name
)
	: context(context)
	, type(type)
	, function(function)
	, name(name)
	, displayName("")
	, defaultMappings({})
{
}

bool KeyMappingInput::isPressed() const
{
	switch (source) {
	case KeyMappingInputSource::KEY_CODE:
		return keyPressed(value.keyCode);
	case KeyMappingInputSource::MOUSE_KEY_CODE:
		return mousePressed(value.mouseKeyCode);
	default:
		return false;
	}
}

bool KeyMappingInput::isDown() const
{
	switch (source) {
	case KeyMappingInputSource::KEY_CODE:
		return keyDown(value.keyCode);
	case KeyMappingInputSource::MOUSE_KEY_CODE:
		return mouseDown(value.mouseKeyCode);
	default:
		return false;
	}
}

bool KeyMappingInput::isReleased() const
{
	switch (source) {
	case KeyMappingInputSource::KEY_CODE:
		return keyReleased(value.keyCode);
	case KeyMappingInputSource::MOUSE_KEY_CODE:
		return mouseReleased(value.mouseKeyCode);
	default:
		return false;
	}
}

bool KeyMappingInput::isCleared() const
{
	return source == KeyMappingInputSource::KEY_CODE && value.keyCode == KEY_CODE::KEY_MAXSCAN;
}

bool KeyMappingInput::is(const KEY_CODE keyCode) const
{
	return source == KeyMappingInputSource::KEY_CODE && value.keyCode == keyCode;
}

bool KeyMappingInput::is(const MOUSE_KEY_CODE mouseKeyCode) const
{
	return source == KeyMappingInputSource::MOUSE_KEY_CODE && value.mouseKeyCode == mouseKeyCode;
}

nonstd::optional<KEY_CODE> KeyMappingInput::asKeyCode() const
{
	if (source == KeyMappingInputSource::KEY_CODE)
	{
		return value.keyCode;
	}
	else
	{
		return nonstd::nullopt;
	}
}

nonstd::optional<MOUSE_KEY_CODE> KeyMappingInput::asMouseKeyCode() const
{
	if (source == KeyMappingInputSource::MOUSE_KEY_CODE)
	{
		return value.mouseKeyCode;
	}
	else
	{
		return nonstd::nullopt;
	}
}

KeyMappingInput::KeyMappingInput()
	: source(KeyMappingInputSource::KEY_CODE)
	, value(KEY_CODE::KEY_IGNORE)
{
}

KeyMappingInput::KeyMappingInput(const KEY_CODE KeyCode)
	: source(KeyMappingInputSource::KEY_CODE)
	, value(KeyMappingInputValue(KeyCode))
{
}

KeyMappingInput::KeyMappingInput(const MOUSE_KEY_CODE mouseKeyCode)
	: source(KeyMappingInputSource::MOUSE_KEY_CODE)
	, value(KeyMappingInputValue(mouseKeyCode))
{
}

KeyMappingInputValue::KeyMappingInputValue(const KEY_CODE keyCode)
	: keyCode(keyCode)
{
}

KeyMappingInputValue::KeyMappingInputValue(const MOUSE_KEY_CODE mouseKeyCode)
	: mouseKeyCode(mouseKeyCode)
{
}

// Key mapping inputs are unions with type enum attached, so we overload the equality
// comparison for convenience.
bool operator==(const KeyMappingInput& lhs, const KeyMappingInput& rhs)
{
	if (lhs.source != rhs.source) {
		return false;
	}

	switch (lhs.source) {
	case KeyMappingInputSource::KEY_CODE:
		return lhs.value.keyCode == rhs.value.keyCode;
	case KeyMappingInputSource::MOUSE_KEY_CODE:
		return lhs.value.mouseKeyCode == rhs.value.mouseKeyCode;
	default:
		return false;
	}
}

bool operator!=(const KeyMappingInput& lhs, const KeyMappingInput& rhs)
{
	return !(lhs == rhs);
}
