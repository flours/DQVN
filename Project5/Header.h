#pragma once

#include <windows.h>
#include<stdio.h>


#ifdef CAP_EXPORTS
#define CAP_API __declspec(dllexport)
#else
#define CAP_API __declspec(dllimport)
#endif


typedef struct {
	wchar_t name[8*2+1];
	int mp;
    int isSelectTarget;
	void (*main)(int playerid,struct Character* character, int target);
}Spell;

typedef struct
{
	int base_strength;
	int agility;
	int base_endurance;
	int maxHP;
	int maxMP;

	BOOL poison;
	BOOL paralysis;
	BOOL sleep;
	BOOL can_action;
	BOOL dragon;

	double bless;

	int strength;
	int endurance;
	int attack;
	int defense;
	int HP;
	int MP;
	int action;
	int action_spell;
	int action_spell_target;
	int action_tool;
	Spell *(spells[20]);
	wchar_t name[10 * 2 + 1];	
}Character;


typedef struct {
	wchar_t name[8 * 2 + 1];
	int id;
	void(*init)(int id, Character* character,int level);
	Character data;
}PresetCharacter;

typedef struct {
	int playernum;
	int enemynum;
	int fullcharacters;
}BattleSetting;

typedef struct {
	void(*init)(int id, Character* character);
	void(*attack)(int id, Character* character);
	wchar_t name[10 * 2 + 1];
}Enemy;


CAP_API void init(Character* character, int partyid);
CAP_API void status_check(Character* character);
CAP_API void battle_main(Character* character, BOOL wait, BOOL disp);
CAP_API void get_fielddata(int *playernum,int *enemynum);