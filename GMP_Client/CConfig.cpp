
/*
MIT License

Copyright (c) 2022 Gothic Multiplayer Team (pampi, skejt23, mecio)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma warning (disable : 4996 4800)
#include "CConfig.h"

using namespace Gothic_II_Addon;

zSTRING Multiplayer = "MULTIPLAYER";
zSTRING Engine = "ENGINE";
zSTRING Game = "GAME";
DWORD KEYBOARDLAYOUT;

CConfig::CConfig()
{
	zCOption* Opt;
    CGameManager* gameMan;
	MultiSection = Opt->GetSectionByName(Multiplayer, 1);
	LoadConfigFromFile();
};

CConfig::~CConfig()
{
	SaveConfigToFile();
};

void CConfig::LoadConfigFromFile()
{
	// Sprawdzanie czy iloœæ wejœæ w sekcji [MULTIPLAYER] siê zgadza, jeœli nie ustawienie configu na default.
      if (Opt->ReadString(Multiplayer, "Nickname", "").IsEmpty() || Opt->GetNumEntries(MultiSection) != 12) {
		if(Opt->SectionExists(Multiplayer)) Opt->RemoveSection(Multiplayer);
		d=TRUE;
		DefaultSettings();
	}
	else{
       Nickname = Opt->ReadString(Multiplayer, "Nickname", "");
       skintexture = Opt->ReadInt(Multiplayer, "Skintexture", 0);
       facetexture = Opt->ReadInt(Multiplayer, "Facetexture", 0);
       headmodel = Opt->ReadInt(Multiplayer, "Headmodel", 0);
       walkstyle = Opt->ReadInt(Multiplayer, "Walkstyle", 0);
       lang = Opt->ReadInt(Multiplayer, "Lang", 0);
       logchat = Opt->ReadBool(Multiplayer, "Logchat", 0);
       watch = Opt->ReadBool(Multiplayer, "Watch", 0);
       WatchPosX = Opt->ReadInt(Multiplayer, "WatchPosX", 0);
       WatchPosY = Opt->ReadInt(Multiplayer, "WatchPosY", 0);
       ChatLines = Opt->ReadInt(Multiplayer, "ChatLines", 0);
       keyboardlayout = Opt->ReadInt(Multiplayer, "KeyboardLayout", 0);
       antialiasing = Opt->ReadBool(Engine, "zVidEnableAntiAliasing", 0);
       joystick = Opt->ReadBool(Game, "enableJoystick", 0);
       potionkeys = Opt->ReadBool(Game, "usePotionKeys", 0);
       logovideos = Opt->ReadBool(Game, "playLogoVideos", 0);
		d=FALSE;
	}
};

void CConfig::DefaultSettings()
{
	Nickname.Clear();
	skintexture = 9;
	facetexture = 18;
	headmodel = 3;
	walkstyle = 0;
	// 0 - polski, 1 - angielski
	lang = 0;
	logchat = false;
	watch = false;
	logovideos = true;
	antialiasing = false;
	joystick = false;
	potionkeys = false;
	keyboardlayout = 0;
	WatchPosX = 7000;
	WatchPosY = 2500;
	ChatLines = 6;
	KEYBOARDLAYOUT = 0x00000409;
};

void CConfig::SaveConfigToFile()
{
	// [MULTIPLAYER] Ini Section
	Opt->WriteString(Multiplayer, "Nickname", Nickname, 0);
    Opt->WriteInt(Multiplayer, "Skintexture", skintexture, 0);
    Opt->WriteInt(Multiplayer, "Facetexture", facetexture, 0);
    Opt->WriteInt(Multiplayer, "Headmodel", headmodel, 0);
    Opt->WriteInt(Multiplayer, "Walkstyle", walkstyle, 0);
    Opt->WriteInt(Multiplayer, "Lang", lang, 0);
    Opt->WriteBool(Multiplayer, "Logchat", logchat, 0);
    Opt->WriteBool(Multiplayer, "Watch", watch, 0);
    Opt->WriteInt(Multiplayer, "WatchPosX", WatchPosX, 0);
    Opt->WriteInt(Multiplayer, "WatchPosY", WatchPosY, 0);
    Opt->WriteInt(Multiplayer, "ChatLines", ChatLines, 0);
    Opt->WriteInt(Multiplayer, "KeyboardLayout", keyboardlayout, 0);
	// Other Sections
    Opt->WriteBool(Engine, "zVidEnableAntiAliasing", antialiasing, 0);
    Opt->WriteBool(Game, "enableJoystick", joystick, 0);
    Opt->WriteBool(Game, "usePotionKeys", potionkeys, 0);
    Opt->WriteBool(Game, "playLogoVideos", logovideos, 0);
	// Apply changes
	gameMan->ApplySomeSettings();
}

BOOL CConfig::IsDefault(){ return (BOOL)d; }