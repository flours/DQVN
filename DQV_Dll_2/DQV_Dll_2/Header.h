#pragma once

#include <windows.h>
#include<stdio.h>


#ifdef CAP_EXPORTS
#define CAP_API __declspec(dllexport)
#else
#define CAP_API __declspec(dllimport)
#endif


typedef struct
{
	char(*name)[8 * 2 + 1];
	int* mp;
	BOOL* isSelectTarget;
	int size;
}SpellData;

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
	SpellData spells;

}Character;

extern "C" CAP_API void init(Character* character);
extern "C" CAP_API void status_check(Character* character);
extern "C" CAP_API void battle_main(Character* character, BOOL wait, BOOL disp);
