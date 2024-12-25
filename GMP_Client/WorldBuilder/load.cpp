
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

#pragma warning( disable : 4996 )
#include "load.h"

using namespace Gothic_II_Addon;

oCGame* Game;

void LoadWorld::LoadWorld(const char* MapName, vector<Info>& Vobs)
{
	FILE *file = fopen(MapName, "rb");
	if(!file) {
		return;
	}
	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	fseek(file, 0, SEEK_SET); 
	unsigned char* map = (unsigned char*)malloc(size);
	fread(map, 1, size, file);
	fclose(file);
	int length;
	Info info;
	unsigned char code[64];
	zVEC3 Pos;
	oCMobInter* MobInter;
	oCVisualFX* Particle;
	zCParticleFX* ParticleVisual;
	zSTRING tmp = NULL;
	string strtmp;
	for(int pos = 0; pos < size;){
		switch (map[pos])
		{
			case 0xF1:
				info.Type = TYPE_MOB;
				pos++;
				length = (int)map[pos];
				pos++;
				memcpy(code, map+pos, length);
				strtmp = (char*)code;
				//strtmp[length] = '\0';
				info.VisualName = strtmp;
				pos += length;
				memcpy(code, map+pos, 12);
				pos += 12;
				Pos.x = *(float*)(code);
				Pos.y = *(float*)(code+4);
				Pos.z = *(float*)(code+8);
				memset(code, 0, 64);
				memcpy(code, map+pos, 36);
				pos += 36;
				if(pos < size) info.MType = map[pos];
				else info.MType = MOB_NORMAL;
				pos++;
				if(info.MType == MOB_NORMAL) MobInter = oCMobInter::_CreateNewInstance();
				else if(info.MType == MOB_DOOR) MobInter = oCMobDoor::_CreateNewInstance();
				else if(info.MType == MOB_CONTAINER) MobInter = oCMobContainer::_CreateNewInstance();
				else if(info.MType == MOB_LADDER) MobInter = oCMobLadder::_CreateNewInstance();
				else {
					info.MType = MOB_NORMAL;
					MobInter = oCMobInter::_CreateNewInstance();
					pos--;
				}
				tmp = strtmp.c_str();
				MobInter->SetVisualInter(zCVisual::LoadVisual(tmp));
				MobInter->trafoObjToWorld.v[0][0] = *(float*)(code);
				MobInter->trafoObjToWorld.v[1][0] = *(float*)(code+4);
				MobInter->trafoObjToWorld.v[2][0] = *(float*)(code+8);
				MobInter->trafoObjToWorld.v[0][2] = *(float*)(code+12);
				MobInter->trafoObjToWorld.v[1][2] = *(float*)(code+16);
				MobInter->trafoObjToWorld.v[2][2] = *(float*)(code+20);
				MobInter->trafoObjToWorld.v[0][1] = *(float*)(code+24);
				MobInter->trafoObjToWorld.v[1][1] = *(float*)(code+28);
				MobInter->trafoObjToWorld.v[2][1] = *(float*)(code+32);
				memset(code, 0, 64);
				Game->GetWorld()->AddVob(MobInter);
				MobInter->SetPositionWorld(Pos);
				info.Vob = MobInter;
				Vobs.push_back(info);
				continue;
			break;
			case 0xF2:
				info.Type = TYPE_PARTICLE;
				pos++;
				length = (int)map[pos];
				pos++;
				memcpy(code, map+pos, length);
				strtmp = (char*)code;
				info.VisualName = strtmp;
				pos += length;
				memcpy(code, map+pos, 12);
				pos += 12;
				Pos.x = *(float*)(code);
				Pos.y = *(float*)(code+4);
				Pos.z = *(float*)(code+8);
				memset(code, 0, 64);
				memcpy(code, map+pos, 24);
				pos += 24;
				Particle = oCVisualFX::_CreateNewInstance();
				tmp = strtmp.c_str();
				ParticleVisual =  zCParticleFX::Load(tmp);
				ParticleVisual->GetEmitter()->SetLooping(1);
				Particle->SetVisual(ParticleVisual);
				Particle->SetPositionWorld(Pos);
				Particle->trafoObjToWorld.v[0][0] = *(float*)(code);
				Particle->trafoObjToWorld.v[1][0] = *(float*)(code+4);
				Particle->trafoObjToWorld.v[2][0] = *(float*)(code+8);
				Particle->trafoObjToWorld.v[0][2] = *(float*)(code+12);
				Particle->trafoObjToWorld.v[1][2] = *(float*)(code+16);
				Particle->trafoObjToWorld.v[2][2] = *(float*)(code+20);
				memset(code, 0, 64);
				Game->GetWorld()->AddVob(Particle);
				info.Vob = Particle;
				Vobs.push_back(info);
				continue;
			break;
			case 0xF3:
				info.Type = TYPE_MOBNOCOLLIDE;
				pos++;
				length = (int)map[pos];
				pos++;
				memcpy(code, map+pos, length);
				strtmp = (char*)code;
				//strtmp[length] = '\0';
				info.VisualName = strtmp;
				pos += length;
				memcpy(code, map+pos, 12);
				pos += 12;
				Pos.x = *(float*)(code);
				Pos.y = *(float*)(code+4);
				Pos.z = *(float*)(code+8);
				memset(code, 0, 64);
				memcpy(code, map+pos, 36);
				pos += 36;
				info.MType = map[pos];
				pos++;
				if(info.MType == MOB_NORMAL) MobInter = oCMobInter::_CreateNewInstance();
				else if(info.MType == MOB_DOOR) MobInter = oCMobDoor::_CreateNewInstance();
				else if(info.MType == MOB_CONTAINER) MobInter = oCMobContainer::_CreateNewInstance();
				else if(info.MType == MOB_LADDER) MobInter = oCMobLadder::_CreateNewInstance();
				else {
					MobInter = oCMobInter::_CreateNewInstance();
					pos--;
				}
				tmp = strtmp.c_str();
				MobInter->SetVisualInter(zCVisual::LoadVisual(tmp));
				MobInter->trafoObjToWorld.v[0][0] = *(float*)(code);
				MobInter->trafoObjToWorld.v[1][0] = *(float*)(code+4);
				MobInter->trafoObjToWorld.v[2][0] = *(float*)(code+8);
				MobInter->trafoObjToWorld.v[0][2] = *(float*)(code+12);
				MobInter->trafoObjToWorld.v[1][2] = *(float*)(code+16);
				MobInter->trafoObjToWorld.v[2][2] = *(float*)(code+20);
				MobInter->trafoObjToWorld.v[0][1] = *(float*)(code+24);
				MobInter->trafoObjToWorld.v[1][1] = *(float*)(code+28);
				MobInter->trafoObjToWorld.v[2][1] = *(float*)(code+32);
				memset(code, 0, 64);
				Game->GetWorld()->AddVob(MobInter);
				MobInter->SetPositionWorld(Pos);
				info.Vob = MobInter;
				Vobs.push_back(info);
				continue;
			break;
		};
		pos++;
	};
	free(map);
};

string LoadWorld::GetZenName(const char* MapName)
{
	FILE *file = fopen(MapName, "rb");
	if(!file) {
		return string("");
	}
	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	fseek(file, 0, SEEK_SET); 
	unsigned char* map = (unsigned char*)malloc(size);
	fread(map, 1, size, file);
	fclose(file);
	int pos = 0;
	unsigned char code[32];
	int length = (int)map[pos];
	pos++;
	memcpy(code, map+pos, length);
	string temp = (char*)code;
	free(map);
	return temp;
};