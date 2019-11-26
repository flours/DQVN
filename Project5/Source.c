#define _CRT_SECURE_NO_WARNINGS

#include "Header.h"

#include<time.h>
#include<windows.h>

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include <locale.h>


#define SPELL_MAX 256


#define printf //





char playerName[12][10 * 2 + 1];

BattleSetting fielddata;





int base_spell_cure_single_target(int playerId, int target, Character* character, int cureMin, int cureMax)
{
	if (character[target].HP == 0)return -1;//体力がない
	int cure = cureMin + rand() % (cureMax - cureMin);

	character[target].HP += cure;
	if (character[target].HP > character[target].maxHP) {
		cure = character[target].HP - character[target].maxHP;
		character[target].HP = character[target].maxHP;
	}
	return cure;//正常に回復
}

int base_spell_attack_single_target(int playerId, int target, Character* character, int damageMin, int damageMax) {
	if (character[target].HP == 0)return -1;//体力がない
	int damage = damageMin + rand() % (damageMax - damageMin);

	character[target].HP -= damage;
	if (character[target].HP < 0) {
		character[target].HP = 0;
	}

	return damage;//正常に回復
}


//0で生き返った,1で失敗,2はまだ生きているrand()%p==0で復活
int revive(int playerId, int target, Character* character, int p)
{
	if (character[target].HP == 0)
	{
		int random = rand() % p;
		if (random == 0) {
			character[character[playerId].action_spell_target].HP = character[character[playerId].action_spell_target].maxHP / 2;
			return 0;
		}
		else
			return -1;
	}
	else
	{
		return -2;
	}
}

int  endurance_up(int playerId, int target, Character* character) {

	if (character[target].endurance >= character[target].base_endurance * 2) {
		character[target].endurance = character[target].endurance;
		return 1;
	}
	else {
		character[target].endurance += character[target].base_endurance / 2;
		return 0;
	}
}

void ally_loop(int id, int* start, int* end)
{
	if (id < fielddata.playernum)
	{
		*start = 0;
		*end = fielddata.playernum;
	}
	else {
		*start = fielddata.playernum;
		*end = fielddata.fullcharacters;

	}
}

void enemy_loop(int id, int* start, int* end)
{
	if (id < fielddata.playernum)
	{
		*start = fielddata.playernum;
		*end = fielddata.fullcharacters;
	}
	else {
		*start = 0;
		*end = fielddata.playernum;

	}
}


void spell_hoimi(int playerId, Character* character, int target) {
	int cure = base_spell_cure_single_target(playerId, target, character, 30, 40);
	character[playerId].MP -= 3;
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはホイミをとなえた　　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはHPが%dかいふくした　｜\n",playerName[target], cure);
	printf("＋―――――――――――――――――＋\n");
}
Spell hoimi = { L"ホイミ",3,TRUE,spell_hoimi};

void spell_kiarii(int playerId, Character* character, int target) {
	character[playerId].MP -= 2;
	character[target].poison = 0;
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはキアリーをとなえた　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sのドクをけしさった　　　｜\n",playerName[target]);
	printf("＋―――――――――――――――――＋\n");
}
Spell kiarii = { L"キアリー",2,TRUE,spell_kiarii};


void spell_bagi(int playerId, Character* character, int target) {
	int damage = base_spell_attack_single_target(playerId, target, character, 8, 24);
	character[playerId].MP -= 2;
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはバギをとなえた　　　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	printf("＋―――――――――――――――――――――――――＋\n");
	printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[playerId], playerName[target], damage);
	printf("＋―――――――――――――――――――――――――＋\n");
}
Spell bagi = { L"バギ",2,TRUE,spell_bagi };


void spell_sukara(int playerId, Character* character, int target) {
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはスカラをとなえた　　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	character[playerId].MP -= 2;
	endurance_up(playerId, target, character);
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sのみのまもりがあがった　｜\n", playerName[target]);
	printf("＋―――――――――――――――――＋\n");
}
Spell sukara = { L"スカラ",2,TRUE,spell_sukara };

void spell_behoimi(int playerId, Character* character, int target) {
	int cure = base_spell_cure_single_target(playerId, target, character, 75, 95);
	character[playerId].MP -= 5;
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはべホイミをとなえた　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはHPが%dかいふくした　｜\n", playerName[target], cure);
	printf("＋―――――――――――――――――＋\n");
}
Spell behoimi = { L"ベホイミ",5,TRUE,spell_behoimi };

void spell_bagima(int playerId, Character* character, int target) {
	int damage = base_spell_attack_single_target(playerId, target, character, 25, 55);
	character[playerId].MP -= 4;
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはバギマをとなえた　　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	printf("＋―――――――――――――――――――――――――＋\n");
	printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[playerId], playerName[target], damage);
	printf("＋―――――――――――――――――――――――――＋\n");
}
Spell bagima = { L"バギマ",4,TRUE,spell_bagima };

void spell_behoma(int playerId, Character* character, int target) {
	character[playerId].MP -= 7;
	character[target].HP = character[target].maxHP;
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはベホマをとなえた　　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはHPがぜんかいふくした　｜\n", playerName[target]);
	printf("＋―――――――――――――――――＋\n");
}
Spell behoma = { L"ベホマ",4,TRUE,spell_behoma };

void spell_zaoraru(int playerId, Character* character, int target) {
	int keep = revive(playerId, target, character, 2);
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはザオラルをとなえた　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	character[playerId].MP -= 10;
	if (keep == 0) {
		printf("＋―――――――――――――――――＋\n");
		printf("｜%sはいきかえった　　　　　｜\n", playerName[target]);
		printf("＋―――――――――――――――――＋\n");
	}
	if (keep == -1) {
		printf("＋―――――――――――――――――＋\n");
		printf("｜しかし、失敗した　　　　　　　　　｜\n");
		printf("＋―――――――――――――――――＋\n");
	}
	if (keep == -2)
	{
		printf("＋―――――――――――――――――＋\n");
		printf("｜しかし、%sはいきている　　｜\n", playerName[target]);
		printf("＋―――――――――――――――――＋\n");
	}
}
Spell zaoraru = { L"ザオラル",10,TRUE,spell_zaoraru };

void spell_megazaru(int playerId, Character* character, int target) {
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはメガザルをとなえた　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	character[playerId].HP = 0;
	character[playerId].MP = 0;
	for (int i = 0; i < fielddata.playernum; i++) {
		if (i != playerId) {
			character[i].HP = character[i].maxHP;
		}
	}
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはMPが0になり死亡した　　｜\n", playerName[playerId]);
	printf("｜ぜんいんが、かんぜんかいふくした　｜\n");
	printf("＋―――――――――――――――――＋\n");
}
Spell megazaru = { L"メガザル",0,TRUE,spell_megazaru };

void spell_bagikurosu(int playerId, Character* character, int target) {
	int m_damage = base_spell_attack_single_target(playerId, target, character, 80, 180);
	character[playerId].MP -= 8;
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはバギクロスをとなえた　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	printf("＋―――――――――――――――――――――――――＋\n");
	printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[playerId], playerName[target], m_damage);
	printf("＋―――――――――――――――――――――――――＋\n");
}
Spell bagikurosu = { L"バギクロス",8,TRUE,spell_bagikurosu };

void spell_mera(int playerId, Character* character, int target) {
	int m_damage = base_spell_attack_single_target(playerId, target, character, 12, 15);
	character[playerId].MP -= 2;
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはメラをとなえた　　　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	printf("＋―――――――――――――――――――――――――＋\n");
	printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[playerId], playerName[target], m_damage);
	printf("＋―――――――――――――――――――――――――＋\n");
}
Spell mera = { L"メラ",2,TRUE,spell_mera };


void spell_gira(int playerId, Character* character, int target) {
	int m_damage = base_spell_attack_single_target(playerId, target, character, 16, 24);
	character[playerId].MP -= 4;
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはギラをとなえた　　　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	printf("＋―――――――――――――――――――――――――＋\n");
	printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[playerId], playerName[target], m_damage);
	printf("＋―――――――――――――――――――――――――＋\n");
}
Spell gira = { L"ギラ",4,TRUE,spell_gira };


void spell_baikiruto(int playerId, Character* character, int target) {
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはバイキルトをとなえた　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	character[playerId].MP -= 6;
	if (character[character[playerId].action_spell_target].strength >= character[character[playerId].action_spell_target].base_strength * 2)
	{
		character[character[playerId].action_spell_target].strength = character[character[playerId].action_spell_target].strength;
		printf("＋―――――――――――――――――――――――＋\n");
		printf("｜しかし、%sのちからはもうあがらない　｜\n", playerName[character[playerId].action_spell_target]);
		printf("＋―――――――――――――――――――――――＋\n");
	}
	else
	{
		character[character[playerId].action_spell_target].strength *= 2;
		printf("＋―――――――――――――――――＋\n");
		printf("｜%sはちからがばいになった　｜\n", playerName[character[playerId].action_spell_target]);
		printf("＋―――――――――――――――――＋\n");
	}
}
Spell baikiruto = { L"バイキルト",6,TRUE,spell_baikiruto };

void spell_begirama(int playerId, Character* character, int target) {
	int m_damage = base_spell_attack_single_target(playerId, target, character, 30, 42);
	character[playerId].MP -= 6;
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはベギラマをとなえた　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	printf("＋―――――――――――――――――――――――――＋\n");
	printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[playerId], playerName[target], m_damage);
	printf("＋―――――――――――――――――――――――――＋\n");
}
Spell begirama = { L"ベギラマ",6,TRUE,spell_begirama };

void spell_merami(int playerId, Character* character, int target) {
	int m_damage = base_spell_attack_single_target(playerId, target, character, 70, 90);
	character[playerId].MP -= 4;
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはメラミをとなえた　　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	printf("＋―――――――――――――――――――――――――＋\n");
	printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[playerId], playerName[target], m_damage);
	printf("＋―――――――――――――――――――――――――＋\n");
}
Spell merami = { L"メラミ",4,TRUE,spell_merami };

void spell_begiragon(int playerId, Character* character, int target) {
	int m_damage = base_spell_attack_single_target(playerId, target, character, 88, 112);
	character[playerId].MP -= 10;
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはベギラゴンをとなえた　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	printf("＋―――――――――――――――――――――――――＋\n");
	printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[playerId], playerName[target], m_damage);
	printf("＋―――――――――――――――――――――――――＋\n");
}
Spell begiragon = { L"ベギラゴン",10,TRUE,spell_begiragon };


void spell_merazooma(int playerId, Character* character, int target) {
	int m_damage = base_spell_attack_single_target(playerId, target, character, 180, 200);
	character[playerId].MP -= 2;
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはメラゾーマをとなえた　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	printf("＋―――――――――――――――――――――――――＋\n");
	printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[playerId], playerName[target], m_damage);
	printf("＋―――――――――――――――――――――――――＋\n");
}
Spell merazooma = { L"メラゾーマ",2,TRUE,spell_merazooma };



void spell_sukuruto(int playerId, Character* character, int target) {
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはスクルトをとなえた　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	character[playerId].MP -= 3;
	int start, end;
	ally_loop(playerId, &start, &end);
	

	for (int i = start; i < end; i++) {
		if (character[i].endurance >= character[i].base_endurance * 2)
		{
			character[i].endurance = character[i].endurance;
			printf("＋――――――――――――――――――――――――＋\n");
			printf("｜しかし、%sのみのまもりはもうあがらない　｜\n", playerName[i]);
			printf("＋――――――――――――――――――――――――＋\n");
		}
		else
		{
			character[i].endurance *= 6 / 5;
			printf("＋―――――――――――――――――＋\n");
			printf("｜%sのみのまもりがあがった　｜\n", playerName[i]);
			printf("＋―――――――――――――――――＋\n");
		}
	}
}
Spell sukuruto = { L"スクルト",3,TRUE,spell_sukuruto };


void spell_kiariku(int playerId, Character* character, int target) {
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはキアリクをとなえた　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	character[playerId].MP -= 2;

	int start, end;
	ally_loop(playerId, &start, &end);
	for (int i = start; i < end; i++) {
		if (character[i].paralysis == 0)continue;
		character[i].paralysis = 0;
		printf("＋―――――――――――――――――＋\n");
		printf("｜%sのマヒをけしさった　　　｜\n", playerName[i]);
		printf("＋―――――――――――――――――＋\n");
	}
}
Spell kiariku = { L"キアリク",2,TRUE,spell_kiariku };

void spell_hubaaha(int playerId, Character* character, int target) {
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはフバーハをとなえた　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	character[playerId].MP -= 3;
	int start, end;
	ally_loop(playerId, &start, &end);
	for (int i = start; i < end; i++)
		character[i].bless = 1.0 / 2;
	printf("＋―――――――――――――――――＋\n");
	printf("｜ぜんいんのブレスたいせいがあがった｜\n");
	printf("＋―――――――――――――――――＋\n");
}
Spell hubaaha = { L"フバーハ",3,FALSE,spell_hubaaha };


void spell_raidein(int playerId, Character* character, int target) {
	int m_damage = base_spell_attack_single_target(playerId, target, character, 70, 90);
	character[playerId].MP -= 6;
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはライデインをとなえた　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	printf("＋―――――――――――――――――――――――――＋\n");
	printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[playerId], playerName[target], m_damage);
	printf("＋―――――――――――――――――――――――――＋\n");
}
Spell raidein = { L"ライデイン",6,TRUE,spell_raidein };

void spell_zaoriku(int playerId, Character* character, int target) {
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはザオリクをとなえた　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	character[playerId].MP -= 20;
	int keep = revive(playerId, target, character, 1);
	if (keep == 0) {
		printf("＋――――――――――――――――――――――――＋\n");
		printf("｜%sはいきかえって、かんぜんかいふくした　｜\n", playerName[character[playerId].action_spell_target]);
		printf("＋――――――――――――――――――――――――＋\n");
	}
	else if (keep == -2)
	{
		printf("＋―――――――――――――――――＋\n");
		printf("｜しかし、%sはいきている　　｜\n", playerName[character[playerId].action_spell_target]);
		printf("＋―――――――――――――――――＋\n");
	}

}
Spell zaoriku = { L"ザオリク",20,TRUE,spell_zaoriku };


void spell_behomaraa(int playerId, Character* character, int target) {
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはベホマラーをとなえた　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	character[playerId].MP -= 18;
	int start, end;
	ally_loop(playerId, &start, &end);
	for (int i = start; i < end; i++) {
		base_spell_cure_single_target(playerId, i, character, 100, 120);
	}
	printf("＋―――――――――――――――――＋\n");
	printf("｜ぜんいんのHPがかいふくした　　　　｜\n");
	printf("＋―――――――――――――――――＋\n");
}
Spell behomaraa = { L"ベホマラー",18,FALSE,spell_behomaraa };


void spell_gigadein(int playerId, Character* character, int target) {
	int m_damage = base_spell_attack_single_target(playerId, target, character, 175, 225);
	character[playerId].MP -= 15;
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはギガデインをとなえた　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	printf("＋―――――――――――――――――――――――――＋\n");
	printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[playerId], playerName[target], m_damage);
	printf("＋―――――――――――――――――――――――――＋\n");
}
Spell gigadein = { L"ギガデイン",15,TRUE,spell_gigadein};

void spell_minadein(int playerId, Character* character, int target) {
	int m_damage = base_spell_attack_single_target(playerId, target, character, 300, 350);
	for (int i = 0; i < fielddata.playernum; i++)character[i].MP -= 10;

	printf("＋―――――――――――――――――――＋\n");
	printf("｜%sはぜんいんからちからをあつめ｜\n", playerName[playerId]);
	printf("｜ミナデインをとなえた　　　　　　　　　｜\n");
	printf("＋―――――――――――――――――――＋\n");
	printf("＋―――――――――――――――――――＋\n");
	printf("｜%sに%dのダメージをあたえた　｜\n", playerName[target], m_damage);
	printf("＋―――――――――――――――――――＋\n");

}
Spell minadein = { L"ミナデイン",10,TRUE,spell_minadein };

void spell_hyado(int playerId, Character* character, int target) {
	int m_damage = base_spell_attack_single_target(playerId, target, character, 25, 35);
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはヒャドをとなえた　　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	character[playerId].MP -= 3;
	printf("＋―――――――――――――――――――――――――＋\n");
	printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[playerId], playerName[target], m_damage);
	printf("＋―――――――――――――――――――――――――＋\n");
}
Spell hyado = { L"ヒャド",3,TRUE,spell_hyado };

void spell_io(int playerId, Character* character, int target) {
	int m_damage = base_spell_attack_single_target(playerId, target, character, 20, 30);
	character[playerId].MP -= 5;
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはイオをとなえた　　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	printf("＋―――――――――――――――――――――――――＋\n");
	printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[playerId], playerName[target], m_damage);
	printf("＋―――――――――――――――――――――――――＋\n");
}
Spell io = { L"ヒャド",5,TRUE,spell_io };

void spell_hyadaruko(int playerId, Character* character, int target) {
	int m_damage = base_spell_attack_single_target(playerId, target, character, 42, 58);
	character[playerId].MP -= 5;
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはヒャダルコをとなえた　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	printf("＋―――――――――――――――――――――――――＋\n");
	printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[playerId], playerName[target], m_damage);
	printf("＋―――――――――――――――――――――――――＋\n");
}
Spell hyadaruko = { L"ヒャダルコ",5,TRUE,spell_hyadaruko };


void spell_rukanan(int playerId, Character* character, int target) {
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはルカナンをとなえた　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	character[playerId].MP -= 4;
	int start, end;
	enemy_loop(playerId,&start,&end);
	for (int i = start; i < end; i++) {
		if (character[i].base_endurance == 0)
		{
			printf("＋――――――――――――――――――――＋\n");
			printf("｜%sのみのまもりはもうさがらない｜\n", playerName[i]);
			printf("＋――――――――――――――――――――＋\n");
		}
		else
		{
			character[i].base_endurance -= character[i].base_endurance / 2;
			printf("＋―――――――――――――――――＋\n");
			printf("｜%sのみのまもりがさがった｜\n", playerName[i]);
			printf("＋―――――――――――――――――＋\n");
		}
	}
}
Spell rukanan = { L"ルカナン",4,TRUE,spell_rukanan };


void spell_iora(int playerId, Character* character, int target) {
	int m_damage = base_spell_attack_single_target(playerId, target, character, 52, 68);
	character[playerId].MP -= 8;
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはイオラをとなえた　　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	printf("＋―――――――――――――――――――――――――＋\n");
	printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[playerId], playerName[target], m_damage);
	printf("＋―――――――――――――――――――――――――＋\n");
}
Spell iora = { L"イオラ",8,TRUE,spell_iora };


void spell_mahyado(int playerId, Character* character, int target) {
	int m_damage = base_spell_attack_single_target(playerId, target, character, 80, 104);
	character[playerId].MP -= 12;
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはマヒャドをとなえた　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	printf("＋―――――――――――――――――――――――――＋\n");
	printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[playerId], playerName[target], m_damage);
	printf("＋―――――――――――――――――――――――――＋\n");
}
Spell mahyado = { L"マヒャド",12,TRUE,spell_mahyado };

void spell_doragoramu(int playerId, Character* character, int target) {
	character[playerId].MP -= 18;
	character[playerId].dragon = 1;
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはドラゴラムをとなえた　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはドラゴンになった　　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");


	//ドラゴンのデフォルトアクション
	int damageBase;
	int damageMin;
	int damageMax;
	int damage;

	switch (rand() % 3)
	{
	case 0:
		damageBase = character[playerId].attack / 2 - character[target].base_endurance / 4;
		damageMin = damageBase * 7 / 8 + 60;
		damageMax = damageBase * 9 / 8 + 60;
		damage = damageMin + rand() % (damageMax - damageMin);
		printf("＋―――――――――――――――――――＋\n");
		printf("｜%sはするどいツメでこうげきした｜\n", playerName[playerId]);
		printf("＋―――――――――――――――――――＋\n");
		character[target].HP -= damage;
		printf("＋――――――――――――――――――＋\n");
		printf("｜%sは%dのダメージをうけた｜\n", playerName[target], damage);
		printf("＋――――――――――――――――――＋\n");
		break;
	default:
		damageMin = 65;
		damageMax = 85;
		damage = damageMin + rand() % (damageMax - damageMin);
		printf("＋――――――――――――――＋\n");
		printf("｜%sはほのおをはいた　｜\n", playerName[playerId]);
		printf("＋――――――――――――――＋\n");
		character[target].HP -= damage;
		printf("＋――――――――――――――――――＋\n");
		printf("｜%sは%dのダメージをうけた｜\n", playerName[target], damage);
		printf("＋――――――――――――――――――＋\n");
		break;
	}
}
Spell doragoramu = { L"ドラゴラム",18,TRUE,spell_doragoramu };


void spell_ionazun(int playerId, Character* character, int target) {
	int m_damage = base_spell_attack_single_target(playerId, target, character, 120, 160);
	character[playerId].MP -= 15;
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはイオナズンをとなえた　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	printf("＋―――――――――――――――――――――――――＋\n");
	printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[playerId], playerName[target], m_damage);
	printf("＋―――――――――――――――――――――――――＋\n");
}
Spell ionazun = { L"イオナズン",15,TRUE,spell_ionazun };

void spell_rukani(int playerId, Character* character, int target) {
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはルカニをとなえた　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	character[playerId].MP -= 3;
	if (character[target].base_endurance == 0)
	{
		printf("＋――――――――――――――――――――＋\n");
		printf("｜%sのみのまもりはもうさがらない｜\n", playerName[target]);
		printf("＋――――――――――――――――――――＋\n");
	}
	else
	{
		character[target].base_endurance -= character[target].base_endurance / 2;
		printf("＋―――――――――――――――――＋\n");
		printf("｜%sのみのまもりがさがった｜\n", playerName[target]);
		printf("＋―――――――――――――――――＋\n");
	}
}
Spell rukani = { L"ルカニ",3,TRUE,spell_rukani };

void spell_mahotora(int playerId, Character* character, int target) {
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはマホトラをとなえた　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	character[playerId].MP -= 4;
	if (character[target].MP == 0)
	{
		printf("＋――――――――――――――――――――＋\n");
		printf("｜%sのMPはもうさがらない｜\n", playerName[target]);
		printf("＋――――――――――――――――――――＋\n");
	}
	else
	{
		int down_MP = (rand() % 6) + 5;
		character[target].MP -= down_MP;
		if(character[target].MP < 0)
			character[target].MP = 0;

		printf("＋―――――――――――――――――＋\n");
		printf("｜%sのMPをすいとった｜\n", playerName[target]);
		printf("＋―――――――――――――――――＋\n");
	}
}
Spell mahotora = { L"マホトラ",4,TRUE,spell_mahotora };


void spell_firebress(int playerId, Character* character, int target) {
	int damage = 0;
	int damageMin = 40;
	int damageMax = 60;
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはほのうをはいた　　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	int start, end;
	enemy_loop(playerId, &start, &end);
	
	for (int i = start; i < end; i++)
	{
		damage = damageMin + rand() % (damageMax - damageMin);
		character[i].HP -= damage;
		if (character[i].HP < 0)
			character[i].HP = 0;
	}
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはプレイヤー全員に　　　｜\n", playerName[playerId]);
	printf("｜%dのダメージを与えた　　　　　　｜\n", damage);
	printf("＋―――――――――――――――――＋\n");
}
Spell firebress = { L"かえんのいき",0,TRUE,spell_firebress };

void spell_mahokanta(int playerId, Character* character, int target) {
	//呪文を跳ね返すバリアを張る・できてない
}Spell mahokanta = { L"マホカンタ",4,TRUE,spell_mahokanta };

void spell_yaketukuiki(int playerId, Character* character, int target) {
	for (int i = 0; i < fielddata.playernum; i++) {
		character[i].paralysis = 5+rand()%5;//5~9ターン
	}
}
Spell yaketukuiki = { L"やけつくいき",4,TRUE,spell_yaketukuiki };

void spell_shinybress(int playerId, Character* character, int target) {
	int damageMin = 120;
	int damageMax = 140;
	int damage = damageMin + rand() % (damageMax - damageMin);
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはかがやくいきをはいた　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	int start, end;
	enemy_loop(playerId, &start, &end);
	for (int i = start; i < end; i++) {
		character[i].HP -= damage;
		if (character[i].HP < 0)
			character[i].HP = 0;
		printf("＋―――――――――――――――――＋\n");
		printf("｜%sは%sに　　　　　｜\n", playerName[playerId], playerName[i]);
		printf("｜%dのダメージを与えた　　　　　　｜\n", damage);
		printf("＋―――――――――――――――――＋\n");

	}
}
Spell shinybress = { L"かがやくいき",0,TRUE,spell_shinybress };

void spell_itetukuhado(int playerId, Character* character, int target) {
	printf("＋――――――――――――――――――＋\n");
	printf("｜%sは凍てつく波動をとなえた　｜\n", playerName[playerId]);
	printf("＋――――――――――――――――――＋\n");
	int start, end;
	enemy_loop(playerId, &start, &end);
	for (int i = start; i < end; i++) {
		character[i].strength = character[i].base_strength;
		character[i].endurance = character[i].base_endurance;
		character[i].bless = 1;
	}
	printf("＋――――――――――――――――――＋\n");
	printf("｜プレイヤー全員にかかっている　　　　｜\n");
	printf("｜良い効果が消えた　　　　　　　　　　｜\n");
	printf("＋――――――――――――――――――＋\n");
}
Spell itetukuhado = { L"いてつくはどう",0,TRUE,spell_itetukuhado };

void spell_syakunetuhono(int playerId, Character* character, int target) {
	int damageMin = 150;
	int damageMax = 170;
	int damage = damageMin + rand() % (damageMax - damageMin);
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはしゃくねつほのおをはいた　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	int start, end;
	enemy_loop(playerId, &start, &end);
	for (int i = start; i < end; i++) {
		character[i].HP -= damage;
		if (character[i].HP < 0)
			character[i].HP = 0;
		printf("＋―――――――――――――――――＋\n");
		printf("｜%sは%sに　　　　　｜\n", playerName[playerId], playerName[i]);
		printf("｜%dのダメージを与えた　　　　　　｜\n", damage);
		printf("＋―――――――――――――――――＋\n");
	}

}
Spell syakunetuhono = { L"しゃくねつほのお",0,TRUE,spell_syakunetuhono };

void spell_sweetbress(int playerId, Character* character, int target) {
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはあまいいきをはいた　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	int start, end;
	enemy_loop(playerId, &start, &end);
	for (int i = start; i < end; i++) {
		if (0 == character[i].sleep) {
			character[i].sleep = 2 + rand() % 4;
			printf("＋―――――――――――――――――＋\n");
			printf("｜%sは眠った　　　　　｜\n", playerName[i]);
			printf("＋―――――――――――――――――＋\n");
		}
	}
}

Spell sweetbress = { L"あまいいき",0,TRUE,spell_sweetbress };

void spell_poisonattack(int playerId, Character* character, int target) {
	int damage = enemy_dyrect_attack(playerId, character, target);
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sのどくこうげき　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	character[target].HP -= damage;
	character[target].poison = TRUE;
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sは%sに　　　　　｜\n", playerName[playerId], playerName[target]);
	printf("｜%dのダメージを与えた　　　　　　｜\n", damage);
	printf("＋―――――――――――――――――＋\n");
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはどくになった     ｜\n",playerName[target]);
	printf("＋―――――――――――――――――＋\n");
}
Spell poisonattack = { L"どくこうげき",0,TRUE,spell_poisonattack };

void spell_rarihoo(int playerId, Character* character, int target) {

	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはラリホーを唱えた　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	int start, end;
	enemy_loop(playerId, &start, &end);
	for (int i = start; i < end; i++) {
		if (0 == character[i].sleep) {
			character[i].sleep = 2 + rand() % 4;
			printf("＋―――――――――――――――――＋\n");
			printf("｜%sは眠った　　　　　｜\n", playerName[i]);
			printf("＋―――――――――――――――――＋\n");
		}
	}
}
Spell rarihoo = { L"ラリホー",3,TRUE,spell_rarihoo };

void spell_bukiminahikari(int playerId, Character* character, int target) {
	//敵グループに対して呪文や特技が効きやすくなる・できてない
}
Spell bukiminahikari = { L"ぶきみなひかり",0,TRUE,spell_bukiminahikari };

void spell_manuusa(int playerId, Character* character, int target) {
	//敵グループに対して通常攻撃の命中率を下げる・できてない
}
Spell manuusa = { L"マヌーサ",4,TRUE,spell_manuusa };

void spell_hardfire(int playerId, Character* character, int target) {
	int damageMin = 65;
	int damageMax = 85;
	int damage = damageMin + rand() % (damageMax - damageMin);
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sははげしいほのおをはいた　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	int start, end;
	enemy_loop(playerId, &start, &end);
	for (int i = start; i < end; i++) {
		character[i].HP -= damage;
		if (character[i].HP < 0)
			character[i].HP = 0;
		printf("＋―――――――――――――――――＋\n");
		printf("｜%sは%sに　　　　　｜\n", playerName[playerId], playerName[i]);
		printf("｜%dのダメージを与えた　　　　　　｜\n", damage);
		printf("＋―――――――――――――――――＋\n");
	}
}
Spell hardfire = { L"はげしいほおの",0,TRUE,spell_hardfire };

void spell_kogoeruhubuki(int playerId, Character* character, int target) {
	int damageMin = 50;
	int damageMax = 60;
	int damage = damageMin + rand() % (damageMax - damageMin);
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはこごえるふぶきをつかった　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	int start, end;
	enemy_loop(playerId, &start, &end);
	for (int i = start; i < end; i++) {
		character[i].HP -= damage;
		if (character[i].HP < 0)
			character[i].HP = 0;
		printf("＋―――――――――――――――――＋\n");
		printf("｜%sは%sに　　　　　｜\n", playerName[playerId], playerName[i]);
		printf("｜%dのダメージを与えた　　　　　　｜\n", damage);
		printf("＋―――――――――――――――――＋\n");
	}
}
Spell kogoeruhubuki = { L"こごえるふぶき",0,TRUE,spell_kogoeruhubuki };

void spell_medapani(int playerId, Character* character, int target) {
	//(敵が使った場合)敵単体を混乱状態にする・できてない(6-9ターン)
}
Spell medapani = { L"メダパニ",5,TRUE,spell_medapani };

void spell_mahotoon(int playerId, Character* character, int target) {
	//敵グループに対して呪文を使用不可にする・できてない(7-10ターン)
}
Spell mahotoon = { L"マホトーン",3,TRUE,spell_mahotoon };

void spell_namemawasi(int playerId, Character* character, int target) {
	//敵単体を1ターン休み・できてない
}
Spell namemawasi = { L"なめまわし",0,TRUE,spell_namemawasi };



void tool_tatakainodoramu(int playerId, Character* character, int target) {
	printf("＋――――――――――――――――――＋\n");
	printf("｜%sはたたかいのドラムを使った　　　　｜\n", playerName[playerId]);
	printf("＋――――――――――――――――――＋\n");
	int start, end;
	ally_loop(playerId, &start, &end);
	for (int i = start; i < end; i++) {
		if (character[i].strength >= character[i].base_strength * 2)
		{
			printf("＋――――――――――――――――――――――――＋\n");
			printf("｜しかし、%sのちからはもうあがらない　　　｜\n", playerName[i]);
			printf("＋――――――――――――――――――――――――＋\n");
		}
		else
		{
			character[i].strength *= 2;
			printf("＋―――――――――――――――――＋\n");
			printf("｜%sのちからがあがった　　　｜\n", playerName[i]);
			printf("＋―――――――――――――――――＋\n");
		}
	}
}


Spell *(presetspell1[20]) = {&hoimi,&kiarii,&bagi,&sukara,&behoimi,&bagima,&behoma,&zaoraru,&megazaru,&bagikurosu};
Spell *presetspell2[20] = {&mera,&gira,&baikiruto,&begirama,&merami,&begiragon,&merazooma};
Spell *presetspell3[20] = { &sukuruto,&behoimi,&kiariku,&behoma,&hubaaha,&raidein,&zaoriku,&behomaraa,&gigadein,&minadein};
Spell *presetspell4[20] = { &hyado,&io,&hyadaruko,&baikiruto,&rukanan,&iora,&mahyado,&doragoramu,&ionazun};


Spell *(all_spell[SPELL_MAX]) = {&hoimi,&kiarii,&bagi,&sukara,&behoimi,&bagima,&behoma,&zaoraru,&megazaru,&bagikurosu,&mera,&gira,&baikiruto,&begirama,&merami,&begiragon,&merazooma,&sukuruto,&kiariku,&hubaaha,&raidein,&zaoriku,&behomaraa,&gigadein,&minadein,&hyado,&io,&hyadaruko,&rukanan,&iora,&mahyado,&doragoramu,&ionazun,&rukani,&mahotora};

int get_random_player_id(Character *character) {
	int count = 0;
	while (TRUE) {
		int random = rand() % fielddata.playernum;
		if (character[random].HP != 0)return random;
		if (count++ == 100) return -1;
	}
}


int isDelimiter(char p, char delim) {
	return p == delim;
}

int split(char *dst[], char *src, char delim) {
	int count = 0;
	for (;;) {
		while (isDelimiter(*src, delim)) {
			src++;
		}
		if (*src == '\0') break;
		dst[count++] = src;
		while (*src && !isDelimiter(*src, delim)) {
			src++;
		}
		if (*src == '\0') break;
		*src++ = '\0';
	}
	return count;
}

//レベルとキャラを指定してbasestatusを決定
void set_Character_base_status(int id, Character *character, char *name, int target_level)
{

	FILE *fp;
	char filename[256];
	char *sep[32];
	sprintf(filename, "character_datas/%s_status.csv", name);
	fp = fopen(filename, "r");
	char line[1024];
	int level=0, power = 0, agility = 0, endurance = 0, clevar = 0, luck = 0, HP = 0, MP = 0, exp = 0;
	printf("filename=%s\n",filename);

	while (fscanf(fp, "%s", line) != EOF) {
		printf("line=%s\n",line);
		int count = split(sep, line, ',');
		printf("count=%d", count);
		if (count > 8) {
			level = atoi(sep[0]);
			power = atoi(sep[1]);
			agility = atoi(sep[2]);
			endurance = atoi(sep[3]);
			clevar = atoi(sep[4]);
			luck = atoi(sep[5]);
			HP = atoi(sep[6]);
			MP = atoi(sep[7]);
			exp = atoi(sep[8]);
		}
		if (level == target_level)break;
	}
	if (level != target_level)printf("該当するステータスがありません:%s,レベル%d",name,target_level);

	character[id].base_strength = power;
	character[id].agility = agility;
	character[id].base_endurance = endurance;
	character[id].maxHP = HP;
	character[id].maxMP = MP;

	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].HP = character[id].maxHP;
	character[id].MP = character[id].maxMP;

	fclose(fp);
}

//装備品のステータスを反映させる
void set_Character_equip_status(int id, Character *character, char *wepon_name, char *armar_name, char *helmet_name, char *shield_name)
{
	FILE *fp;
	char filename[128];
	char* sep[128];
	char line[128];


	sprintf(filename, "character_datas/武器.csv");
	fp = fopen(filename, "r");
	int strength = 0;
	while (fscanf(fp, "%s", line) != EOF) {
		int count = split(sep, line, ',');
		if (!strcmp(sep[0], wepon_name)) {
			printf("%s", sep[3]);
			strength = atoi(sep[3]);
			break;
		}
	}
	if (strcmp(sep[0], wepon_name))printf("該当する武器がありません:%s", wepon_name);
	fclose(fp);

	sprintf(filename, "character_datas/よろい.csv");
	fp = fopen(filename, "r");
	int endurance = 0;
	while (fscanf(fp, "%s", line) != EOF) {
		int count = split(sep, line, ',');
		if (!strcmp(sep[0], armar_name)) {
			endurance = atoi(sep[3]);
			break;
		}
	}
	if (strcmp(sep[0], armar_name))printf("該当する武器がありません:%s", armar_name);
	fclose(fp);


	sprintf(filename, "character_datas/かぶと.csv");
	fp = fopen(filename, "r");
	while (fscanf(fp, "%s", line) != EOF) {
		int count = split(sep, line, ',');
		if (!strcmp(sep[0], helmet_name)) {
			endurance += atoi(sep[3]);
			break;
		}
	}
	if (strcmp(sep[0], helmet_name))printf("該当する武器がありません:%s", helmet_name);
	fclose(fp);


	sprintf(filename, "character_datas/たて.csv");
	fp = fopen(filename, "r");
	while (fscanf(fp, "%s", line) != EOF) {
		int count = split(sep, line, ',');
		if (strcmp(sep[0], shield_name)) {
			endurance += atoi(sep[3]);
			break;
		}
	}
	if (!strcmp(sep[0], shield_name))printf("該当する武器がありません:%s", shield_name);

	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength + strength;
	character[id].defense = character[id].endurance + endurance;
	character[id].HP = character[id].maxHP;
	character[id].MP = character[id].maxMP;

	fclose(fp);
}










int enemy_dyrect_attack(int id,Character* character,int target) {
	int damageBase = (character[id].strength / 2 - character[target].defense / 4);
	printf("damagebase=%d\n",damageBase);
	int damageMin = damageBase * 7 / 8;
	int damageMax = damageBase * 9 / 8;
	int damage = damageMin + rand() % (damageMax - damageMin);

	if (damage <= 0)damage = 0;

	character[target].HP-=damage;
	if (character[target].HP < 0)character[target].HP = 0;
	return damage;
}

void estark_init(int id,Character* character) {
	printf("estark_init");
	character[id].can_action = TRUE;
	character[id].base_strength = 450;
	character[id].agility = 85;
	character[id].base_endurance = 250;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].maxHP = 9000;
	character[id].HP = character[id].maxHP;
	strcpy(character[id].name,L"エスターク");
}

void estark_action(int id,Character *characters) {
	// 2回攻撃
	printf("estarc_action_start");
	int attack_count = 0;
	int damageBase, damageMin, damageMax, damage;

	for (int attack_count = 0; attack_count < 2; attack_count++)
	{
		int target = get_random_player_id(characters);
		if (target == -1)return;
		switch (rand() % 6)
		{
		case 0:
			if (characters[0].HP == 0 && characters[1].HP == 0 && characters[2].HP == 0 && characters[3].HP == 0)break;

			damageBase = characters[id].base_strength / 2 - characters[target].defense / 4;
			damageMin = damageBase * 7 / 8;
			damageMax = damageBase * 9 / 8;
			damage = damageMin + rand() % (damageMax - damageMin);
			printf("＋―――――――――――――――――＋\n");
			printf("｜%sのこうげき　　　　　　　｜\n", playerName[id]);
			printf("＋―――――――――――――――――＋\n");
			characters[target].HP -= damage;
			if (characters[target].HP < 0)
				characters[target].HP = 0;
			printf("＋―――――――――――――――――＋\n");
			printf("｜%sは%sに　　　　　｜\n", playerName[id], playerName[target]);
			printf("｜%dのダメージを与えた　　　　　　｜\n", damage);
			printf("＋―――――――――――――――――＋\n");
			break;
		case 1:
			damageMin = 72;
			damageMax = 88;
			printf("＋―――――――――――――――――＋\n");
			printf("｜%sはイオナズンをとなえた　｜\n", playerName[id]);
			printf("＋―――――――――――――――――＋\n");
			for (int i = 0; i < fielddata.playernum; i++)
			{
				damage = damageMin + rand() % (damageMax - damageMin);
				characters[i].HP -= damage;
				if (characters[i].HP < 0)
					characters[i].HP = 0;
			}
			printf("＋―――――――――――――――――＋\n");
			printf("｜%sはプレイヤー全員に　　　｜\n", playerName[id]);
			printf("｜%dのダメージを与えた　　　　　　      ｜\n", damage);
			printf("＋―――――――――――――――――＋\n");
			break;
		case 2:
			damageMin = 150;
			damageMax = 170;
			printf("＋―――――――――――――――――＋\n");
			printf("｜%sは灼熱の炎をとなえた　　｜\n", playerName[id]);
			printf("＋―――――――――――――――――＋\n");
			for (int i = 0; i < fielddata.playernum; i++)
			{
				damage = damageMin + rand() % (damageMax - damageMin);
				characters[i].HP -= damage * characters[i].bless;
				if (characters[i].HP < 0)
					characters[i].HP = 0;
			}
			printf("＋―――――――――――――――――＋\n");
			printf("｜%sはプレイヤー全員に　　　｜\n", playerName[id]);
			printf("｜%dのダメージを与えた　　　　　　　　　｜\n", damage);
			printf("＋―――――――――――――――――＋\n");
			break;
		case 3:
			damageMin = 120;
			damageMax = 140;
			printf("＋―――――――――――――――――＋\n");
			printf("｜%sは輝く息をとなえた　　　｜\n", playerName[id]);
			printf("＋―――――――――――――――――＋\n");
			for (int i = 0; i < 4; i++)
			{
				damage = damageMin + rand() % (damageMax - damageMin);
				characters[i].HP -= damage * characters[i].bless;
				if (characters[i].HP < 0)
					characters[i].HP = 0;
			}
			printf("＋―――――――――――――――――＋\n");
			printf("｜%sはプレイヤー全員に　　　｜\n", playerName[id]);
			printf("｜%dのダメージを与えた　　　　　　｜\n", damage);
			printf("＋―――――――――――――――――＋\n");
			break;
		case 4:
			target = rand() % 4;
			damageMin = 92;
			damageMax = 128;
			damage = damageMin + rand() % (damageMax - damageMin);
			printf("＋―――――――――――――――――＋\n");
			printf("｜%sはメラゾーマをとなえた　｜\n", playerName[id]);
			printf("＋―――――――――――――――――＋\n");
			characters[target].HP -= damage;
			if (characters[target].HP < 0)
				characters[target].HP = 0;
			printf("＋―――――――――――――――――＋\n");
			printf("｜%sは%sに　　　　　｜\n", playerName[id], playerName[target]);
			printf("｜%dのダメージを与えた　　　　　　｜\n", damage);
			printf("＋―――――――――――――――――＋\n");
			break;
		case 5:
			spell_itetukuhado(id, characters, target);
			break;
		}
	}
}


void message_disp(int id,int target,int damage) {
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sのこうげき　　　　　　　｜\n", playerName[id]);
	printf("＋―――――――――――――――――＋\n");
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sは%sに　　　　　｜\n", playerName[id], playerName[target]);
	printf("｜%dのダメージを与えた　　　　　　｜\n", damage);
	printf("＋―――――――――――――――――＋\n");
}

void suraimu_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 7;
	character[id].agility = 3;
	character[id].base_endurance = 5;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].maxHP = 7;
	character[id].HP = character[id].maxHP;
}
void suraimu_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = enemy_dyrect_attack(id, character, target);
	message_disp(id,target,damage);
}//スライム

void kubinagaweasel_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 11;
	character[id].agility = 8;
	character[id].base_endurance = 9;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].maxHP = 16;
	character[id].HP = character[id].maxHP;
}
void kubinagaweasel_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = 0;
	switch (rand() % 2) {
	case 0:damage =	enemy_dyrect_attack(id, character, target);
		message_disp(id, target, damage); break;
	case 1:spell_sweetbress(id, character, target);
		break;
	default:break;
	}
}//くびながイタチ

void prisoncat_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 24;
	character[id].agility = 20;
	character[id].base_endurance = 18;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].maxHP = 26;
	character[id].HP = character[id].maxHP;
}
void prisoncat_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = 0;
	switch (rand() % 3) {
	case 0:damage=enemy_dyrect_attack(id, character, target);
		message_disp(id, target, damage); break;
	case 1:			
		printf("＋―――――――――――――――――＋\n");
		printf("｜%sは様子をみた　　　　　　　｜\n", playerName[id]);
		printf("＋―――――――――――――――――＋\n");
		break;
	case 2:spell_hyado(id, character, target);
		break;
	default:break;
	}
}//プリズニャン

void bubbleslime_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 12;
	character[id].agility = 7;
	character[id].base_endurance = 7;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].maxHP = 15;
	character[id].HP = character[id].maxHP;
}
void bubbleslime_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = 0;
	switch (rand() % 2) {
	case 0:damage=enemy_dyrect_attack(id, character, target);
		message_disp(id, target, damage); break;
	case 1:spell_poisonattack(id, character, target);
		break;
	default:break;
	}
}//バブルスライム

void ghost_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 15;
	character[id].agility = 14;
	character[id].base_endurance = 15;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].maxHP = 19;
	character[id].HP = character[id].maxHP;
}
void ghost_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = enemy_dyrect_attack(id, character, target);//通常のみ
	message_disp(id, target, damage);
}//ゴースト

void obakevcandle_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 20;
	character[id].agility = 13;
	character[id].base_endurance = 17;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].maxHP = 20;
	character[id].HP = character[id].maxHP;
}
void obakevcandle_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = 0;
	switch (rand() % 2) {
	case 0:damage=enemy_dyrect_attack(id, character, target);
		message_disp(id, target, damage); break;
	case 1:spell_mera(id, character, target);
		break;
	default:break;
	}
}//おばけキャンドル

void oyabunghost_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 36;
	character[id].agility = 20;
	character[id].base_endurance = 50;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].maxHP = 200;
	character[id].HP = character[id].maxHP;
}
void oyabunghost_attack(int id, Character* character) {
	static int turn_count_oyabun=1;
	int target = get_random_player_id(character);
	int damage = 0;//奇数ターン…通常。偶数ターン…通常・メラ・ギラ・ルカニ
	if (turn_count_oyabun % 2 == 1) {//奇数ターン
		damage = enemy_dyrect_attack(id, character, target);
		message_disp(id, target, damage);
	}
	else
		switch(rand() % 4) {//偶数ターン
	    case 0:damage = enemy_dyrect_attack(id, character, target);
			message_disp(id, target, damage); break;
		case 1:spell_mera(id, character, target); break;
		case 2:spell_gira(id, character, target); break;
		case 3:spell_rukani; break;
		default: break;
	}
	turn_count_oyabun++;
}//おやぶんゴースト


void soilchild_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 22;
	character[id].agility = 13;
	character[id].base_endurance = 11;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].maxHP = 22;
	character[id].HP = character[id].maxHP;
}
void soilchild_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = 0;
	switch (rand() % 2) {
	case 0:damage=enemy_dyrect_attack(id, character, target);
		message_disp(id, target, damage); break;
	case 1://仲間を呼ぶ(ホイミスライム)・できてない
		break;
	default:break;
	}
}//つちわらし

void meralizard_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 20;
	character[id].agility = 16;
	character[id].base_endurance = 20;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].maxHP = 24;
	character[id].HP = character[id].maxHP;
}
void meralizard_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = 0;
	switch (rand() % 2) {
	case 0:damage=enemy_dyrect_attack(id, character, target);
		message_disp(id, target, damage); break;
	case 1:spell_mera(id, character, target);
		break;
	default:break;
	}
}//メラリザード

void nightsplit_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 18;
	character[id].agility = 12;
	character[id].base_endurance = 14;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].maxHP = 17;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].HP = character[id].maxHP;
}
void nightsplit_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = 0;
	switch (rand() % 2) {
	case 0:damage=enemy_dyrect_attack(id, character, target);
		message_disp(id, target, damage); break;
	case 1:spell_rukani(id, character, target);
		break;
	default:break;
	}
}//ナイトウイプス

void gappurin_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 23;
	character[id].agility = 12;
	character[id].base_endurance = 17;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].maxHP = 19;
	character[id].HP = character[id].maxHP;
}
void gappurin_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = 0;
	switch (rand() % 2) {
	case 0:damage=enemy_dyrect_attack(id, character, target);
		message_disp(id, target, damage); break;
	case 1:spell_rarihoo(id, character, target);
		break;
	default:break;
	}
}//ガップリン

void sabotenball_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 22;
	character[id].agility = 14;
	character[id].base_endurance = 14;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].maxHP = 22;
	character[id].HP = character[id].maxHP;
}
void sabotenball_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = enemy_dyrect_attack(id, character, target);
	message_disp(id, target, damage);
}//サボテンボール

void witch_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 21;
	character[id].agility = 15;
	character[id].base_endurance = 17;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].maxHP = 20;
	character[id].HP = character[id].maxHP;
}
void witch_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = 0;
	switch (rand() % 4) {
	case 0:damage=enemy_dyrect_attack(id, character, target);
		message_disp(id, target, damage); break;
	case 1:spell_hyado(id, character, target);
		break;
	case 2:spell_mahotoon(id, character, target);//マホトーン・できてない
		break;
	case 3:spell_sukuruto(id, character,target);
		break;
	default:break;
	}
}//まほうつかい

void zairu_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 42;
	character[id].agility = 28;
	character[id].base_endurance = 30;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].maxHP = 140;
	character[id].HP = character[id].maxHP;
}
void zairu_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = 0;
	switch (rand()%3) {
	case 0:damage = enemy_dyrect_attack(id, character, target);
		message_disp(id, target, damage); break;
	case 1:spell_mahotora(id, character, target); break;
	case 2:spell_hoimi(id, character, target);  break;
	defalt:break;
	}
}//ザイル

void snowqueen_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 50;
	character[id].agility = 18;
	character[id].base_endurance = 45;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].maxHP = 550;
	character[id].HP = character[id].maxHP;
}
void snowqueen_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = 0;
	static int turn_count_snowqueen=1;
	if (turn_count_snowqueen%3==1) {//1ターン目・4ターン目
		switch (rand() % 2) {
		case 0:
			damage = enemy_dyrect_attack(id, character, target);
			message_disp(id, target, damage);
			character[id].strength= character[id].base_strength;//攻撃力を元に戻す
			break;
		case 1:
		{
			int damageMin = 13;
			int damageMax = 16;
			damage = damageMin + rand() % (damageMax - damageMin);
			printf("＋―――――――――――――――――＋\n");
			printf("｜%sはこおりつくいきをはいた　｜\n", playerName[id]);
			printf("＋―――――――――――――――――＋\n");
			for (int i = 0; i < fielddata.playernum; i++) {
				character[i].HP -= damage;
				if (character[i].HP < 0)
					character[i].HP = 0;
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sは%sに　　　　　｜\n", playerName[id], playerName[i]);
				printf("｜%dのダメージを与えた　　　　　　｜\n", damage);
				printf("＋―――――――――――――――――＋\n");
			}
			character[id].strength = character[id].base_strength;//攻撃力を元に戻す
		}break;
		default:break;
		}
	}
	else if (turn_count_snowqueen % 3 == 2) {//2ターン目・5ターン目
		switch (rand() % 2) {
		case 0:damage = enemy_dyrect_attack(id, character, target); 
			message_disp(id, target, damage); 
			break;
		case 1:spell_hyado(id, character, target); break;
		default:break;
		}
	}
	else {//3ターン目・6ターン目...
		switch (rand() % 2){
		case 0:spell_hoimi(id, character, id); break;
		case 1://息を吸い込む
			character[id].strength = character[id].base_strength * 2;//攻撃力を2倍
			printf("＋―――――――――――――――――＋\n");
			printf("｜%sはおおきくいきをすいこんだ　｜\n", playerName[id]);
			printf("＋―――――――――――――――――＋\n");
			break;
		default:break;
		}
	}
	turn_count_snowqueen++;
}//ゆきのじょうおう


void obakekinoko_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 43;
	character[id].agility = 24;
	character[id].base_endurance = 37;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].maxHP = 35;
	character[id].HP = character[id].maxHP;
}
void obakekinoko_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = 0;
	switch (rand() % 2) {
	case 0:damage = enemy_dyrect_attack(id, character, target);
		message_disp(id, target, damage); break;
	case 1:spell_sweetbress(id, character, target);
		break;
	default:break;
	}
}//おばけキノコ

void evilapple_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 41;
	character[id].agility = 19;
	character[id].base_endurance = 35;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].maxHP = 30;
	character[id].HP = character[id].maxHP;
}
void evilapple_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = 0;
	switch (rand() % 3) {
	case 0:damage = enemy_dyrect_attack(id, character, target);
		message_disp(id, target, damage); break;
	case 1:spell_bagi(id, character, target);
		break;
	case 2:
		printf("＋―――――――――――――――――＋\n");
		printf("｜%sは笑っている　　　　　　　｜\n", playerName[id]);
		printf("＋―――――――――――――――――＋\n");
		break;
	default:break;
	}
}//エビルアップル

void waraibag_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 33;
	character[id].agility = 25;
	character[id].base_endurance = 15;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].maxHP = 31;
	character[id].HP = character[id].maxHP;
}
void waraibag_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = 0;
	switch (rand() % 4) {
	case 0:damage = enemy_dyrect_attack(id, character, target);
		message_disp(id, target, damage); break;
	case 1:spell_rarihoo(id, character, target);
		break;
	case 2:spell_mahotoon(id, character, target);//マホトーン・できてない
		break;
	case 3:spell_medapani(id, character, target);//メダパニ・できてない
		break;
	//case 4://仲間を呼ぶ(ホイミスライム)・できてない
	//	break;
	default:break;
	}
}//わらいぶくろ

void hoimislime_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 17;
	character[id].agility = 15;
	character[id].base_endurance = 20;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].maxHP = 35;
	character[id].HP = character[id].maxHP;
}
void hoimislime_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = 0;
	switch (rand() % 2) {
	case 0:damage = enemy_dyrect_attack(id, character, target);
		message_disp(id, target, damage);break;
	case 1:spell_hoimi(id, character, target);
		break;
	}

}//ホイミスライム

void skelsoldier_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 52;
	character[id].agility = 20;
	character[id].base_endurance = 50;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].maxHP = 42;
	character[id].HP = character[id].maxHP;
}
void skelsoldier_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = 0;
	switch (rand() % 2) {
	case 0:damage=enemy_dyrect_attack(id, character, target);
		message_disp(id, target, damage); break;
	case 1:spell_poisonattack(id, character, target);
		break;
	default:break;
	}
}//がいこつへい

void falsetaiko_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 150;
	character[id].agility = 35;
	character[id].base_endurance = 100;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].maxHP = 650;
	character[id].HP = character[id].maxHP;
}
void falsetaiko_attack(int id, Character* character) {
	static int turn_count_falsetaiko = 1;
	int target = get_random_player_id(character);
	int damage = 0;
	if (turn_count_falsetaiko % 3 == 1) {//1ターン・4ターン
		switch (rand() % 1) {
		case 0:damage = enemy_dyrect_attack(id, character, target);
			message_disp(id, target, damage); break;
		//case 1://わらいぶくろを呼ぶ・できてない
		//	break;
		default:break;
		}
	}
	else if(turn_count_falsetaiko % 3 == 2){//2ターン・5ターン
		switch(rand() % 2) {
		case 0:
			character[id].strength = character[id].base_strength * 2;//攻撃力を二倍にする
			break;
		case 1:spell_firebress(id, character, target);
			break;
		default:break;
		}
	}
	else {
		switch (rand() % 1) {//3ターン・6ターン
		case 0:damage = enemy_dyrect_attack(id, character, target);
			message_disp(id, target, damage);
			character[id].strength = character[id].base_strength;//攻撃力を元に戻す
			break;
		//case 1://がいこつ兵を呼ぶ・できてない
		//	character[id].strength = character[id].base_strength;//攻撃力を元に戻す
		//	break;
		default: break;
		}
	}
	turn_count_falsetaiko++;
}//ニセたいこう

void behomaslime_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 47;
	character[id].agility = 37;
	character[id].base_endurance = 62;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].maxHP = 69;
	character[id].HP = character[id].maxHP;
}
void behomaslime_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = 0;
	switch (rand() % 2) {
	case 0:damage = enemy_dyrect_attack(id, character, target);
		message_disp(id, target, damage); break;
	case 1:spell_behoimi(id, character, target);
		break;
	}
}//ベホマスライム

void madolooper_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 91;
	character[id].agility = 40;
	character[id].base_endurance = 35;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].maxHP = 83;
	character[id].HP = character[id].maxHP;
}
void madolooper_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = 0;
	switch (rand() % 2) {
	case 0:damage = enemy_dyrect_attack(id, character, target);
		message_disp(id, target, damage); break;
	case 1:spell_sukara(id, character, target);
		break;
	}
}//マドルーパー

void snakebat_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 79;
	character[id].agility = 42;
	character[id].base_endurance = 61;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].maxHP = 63;
	character[id].HP = character[id].maxHP;
}
void snakebat_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = 0;
	switch (rand() % 2) {
	case 0:damage = enemy_dyrect_attack(id, character, target);
		message_disp(id, target, damage); break;
	case 1:spell_yaketukuiki(id, character, target);//やけつくいき
		break;
	}
}//へびこうもり

void kandata_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 235;
	character[id].agility = 30;
	character[id].base_endurance = 80;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].maxHP = 1400;
	character[id].HP = character[id].maxHP;
}
void kandata_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = 0;
	switch (rand() % 3) {
	case 0:damage = enemy_dyrect_attack(id, character, target);
		message_disp(id, target, damage); break;
	case 1: {
		int c_damageBase = character[id].attack;
		int c_damageMin = c_damageBase;
		int c_damageMax = c_damageBase * 74 / 64;
		damage = c_damageMin + rand() % (c_damageMax - c_damageMin);
		message_disp(id, target, damage);
		break;//会心の一撃
	}
	case 2:spell_behoimi(id, character, id);
		break;
	default:break;
	}
}//カンダタ

void shieldhipo_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 105;
	character[id].agility = 45;
	character[id].base_endurance = 120;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].maxHP = 90;
	character[id].HP = character[id].maxHP;
}
void shieldhipo_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = 0;
	switch (rand() % 2) {
	case 0:character[id].endurance = character[id].base_endurance;
		damage = enemy_dyrect_attack(id, character, target);
		message_disp(id, target, damage); break;
	case 1:
		character[id].endurance= character[id].base_endurance*2;//防御
		break;
	}
}//シールドヒッポ

void oak_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 155;
	character[id].agility = 70;
	character[id].base_endurance = 121;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].maxHP = 800;
	character[id].HP = character[id].maxHP;
}
void oak_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = 0;
	switch (rand() % 2) {
	case 0:damage = enemy_dyrect_attack(id, character, target);
		message_disp(id, target, damage); break;
	case 1:spell_rukanan(id, character, target);
		break;
	default:break;
	}
}//オークLv20

void kimeera_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 145;
	character[id].agility = 80;
	character[id].base_endurance = 150;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].maxHP = 800;
	character[id].HP = character[id].maxHP;
}
void kimeera_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = 0;
	for (int attack_num = rand() % 2; 0 <= attack_num; attack_num--) {//1～2回攻撃
		switch (rand() % 4) {
		case 0:damage = enemy_dyrect_attack(id, character, target);
			message_disp(id, target, damage); break;
		case 1:
			spell_firebress(id, character, target);
			break;
		case 2:spell_begirama(id, character, target);
			break;
		case 3:spell_hyadaruko(id, character, target);
			break;
		default:break;
		}
	}
}//キメーラLv35

void jami_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 220;
	character[id].agility = 50;
	character[id].base_endurance = 120;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].maxHP = 1200;
	character[id].HP = character[id].maxHP;
}
void jami_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = 0;
	switch (rand() % 4) {
	case 0:damage = enemy_dyrect_attack(id, character, target);
		message_disp(id, target, damage); break;
	case 1: {//こごえるふぶき
		int damageMin = 50;
		int damageMax = 60;
		damage = damageMin + rand() % (damageMax - damageMin);
		printf("＋―――――――――――――――――＋\n");
		printf("｜%sはこごえるいぶきをはなった　｜\n", playerName[id]);
		printf("＋―――――――――――――――――＋\n");
		for (int i = 0; i < fielddata.playernum; i++) {
			character[i].HP -= damage;
			if (character[i].HP < 0)
				character[i].HP = 0;
			printf("＋―――――――――――――――――＋\n");
			printf("｜%sは%sに　　　　　｜\n", playerName[id], playerName[i]);
			printf("｜%dのダメージを与えた　　　　　　｜\n", damage);
			printf("＋―――――――――――――――――＋\n");
		}
		break;
	}
	case 2:spell_bagikurosu(id, character, target);
		break;
	case 3:spell_merami(id, character, target);
		break;
	default:break;
	}
}//ジャミ

void berogonload_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 95;
	character[id].agility = 48;
	character[id].base_endurance = 40;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].maxHP = 110;
	character[id].HP = character[id].maxHP;
}
void berogonload_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = 0;
	switch (rand() % 2) {
	case 0:damage = enemy_dyrect_attack(id, character, target);//直接攻撃
		message_disp(id, target, damage); break;
	case 1:damage = enemy_dyrect_attack(id, character, target);//酸液のツバ
		break;
	//case 2:spell_namemawasi(id, character, target);//なめまわし・できてない
	//	break;
	default:break;
	}
}//ベロゴンロード

void magekimera_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 82;
	character[id].agility = 57;
	character[id].base_endurance = 67;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].maxHP = 99;
	character[id].HP = character[id].maxHP;
}
void magekimera_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = 0;
	switch (rand() % 4) {
	case 0:damage = enemy_dyrect_attack(id, character, target);//直接攻撃
		message_disp(id, target, damage); break;
	case 1:spell_hoimi(id, character, target);
		break;
	case 2:spell_gira(id, character, target);
		break;
	case 3:spell_hyado(id, character, target);
		break;
	//case 4:spell_manuusa(id, character, target);//マヌーサ・できてない
	//	break;
	default:break;
	}
}//メイジキメラ

void minidaemon_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 79;
	character[id].agility = 55;
	character[id].base_endurance = 68;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].maxHP = 70;
	character[id].HP = character[id].maxHP;
}
void minidaemon_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = 0;
	switch (rand() % 3) {
	case 0:damage = enemy_dyrect_attack(id, character, target);//直接攻撃
		message_disp(id, target, damage); break;
	case 1:spell_merami(id, character, target);
		break;
	case 2:
		printf("＋―――――――――――――――――＋\n");
		printf("｜%sはイオナズンを唱えた　｜\n", playerName[id]);
		printf("＋―――――――――――――――――＋\n");
		printf("＋―――――――――――――――――＋\n");
		printf("｜しかしMPが足りない　              ｜\n");
		printf("＋―――――――――――――――――＋\n");
		break;
	default:break;
	}
}//ミニデーモン

void messaara_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 107;
	character[id].agility = 60;
	character[id].base_endurance = 67;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].maxHP = 99;
	character[id].HP = character[id].maxHP;
}
void messaara_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = 0;
	switch (rand() % 1) {
	case 0:damage = enemy_dyrect_attack(id, character, target);//直接攻撃
		message_disp(id, target, damage); break;
	//case 1:spell_mahotoon(id, character, target);//マホトーン・できてない
	//	break;
	//case 2:spell_bukiminahikari(id, character, target);//ぶきみなひかり・できてない
	//	break;
	default:break;
	}
}//メッサーラ

void gons_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 300;
	character[id].agility = 80;
	character[id].base_endurance = 135;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].maxHP = 2400;
	character[id].HP = character[id].maxHP;
}
void gons_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = 0;
	if (rand() % 2 == 0) {
		damage = enemy_dyrect_attack(id, character, target);
	}
	else {
		damage = (int)(enemy_dyrect_attack(id, character, target)*1.25);//武器を振り回す・1.25倍
	}
	message_disp(id, target, damage);
}//ゴンズ

void gema_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 285;
	character[id].agility = 260;
	character[id].base_endurance = 90;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].maxHP = 3800;
	character[id].HP = character[id].maxHP;
}
void gema_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = 0;
	for (int attack_num = rand() % 2; 0 <= attack_num; attack_num--) {//1～2回攻撃
		switch (rand() % 4) {
		case 0:damage = enemy_dyrect_attack(id, character, target);
			message_disp(id, target, damage); break;
		case 1: {//はげしいほのお
			int damageMin = 65;
			int damageMax = 85;
			damage = damageMin + rand() % (damageMax - damageMin);
			printf("＋―――――――――――――――――＋\n");
			printf("｜%sははげしいほのおをはなった　｜\n", playerName[id]);
			printf("＋―――――――――――――――――＋\n");
			for (int i = 0; i < fielddata.playernum; i++) {
				character[i].HP -= damage;
				if (character[i].HP < 0)
					character[i].HP = 0;
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sは%sに　　　　　｜\n", playerName[id], playerName[i]);
				printf("｜%dのダメージを与えた　　　　　　｜\n", damage);
				printf("＋―――――――――――――――――＋\n");
			}
			break;
		}
		case 2:spell_merazooma(id, character, target);
			break;
		case 3:spell_mahokanta(id, character, target);//マホカンタ・できてない
			break;
		default:break;
		}
	}
}//ゲマ

void buoon_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 300;
	character[id].agility = 160;
	character[id].base_endurance = 75;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].maxHP = 4700;
	character[id].HP = character[id].maxHP;
}
void buoon_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = 0;
	for (int attack_num = rand() % 2; 0 <= attack_num; attack_num--) {//1～2回攻撃
		switch (rand() % 5) {
		case 0:damage = enemy_dyrect_attack(id, character, target);
			message_disp(id, target, damage); break;
		case 1: {//はげしいほのお
			int damageMin = 65;
			int damageMax = 85;
			damage = damageMin + rand() % (damageMax - damageMin);
			printf("＋―――――――――――――――――＋\n");
			printf("｜%sははげしいほのおをはなった　｜\n", playerName[id]);
			printf("＋―――――――――――――――――＋\n");
			for (int i = 0; i < fielddata.playernum; i++) {
				character[i].HP -= damage;
				if (character[i].HP < 0)
					character[i].HP = 0;
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sは%sに　　　　　｜\n", playerName[id], playerName[i]);
				printf("｜%dのダメージを与えた　　　　　　｜\n", damage);
				printf("＋―――――――――――――――――＋\n");
			}
			break;
		}
		case 2: {//いなずま
			int damageMin = 50;
			int damageMax = 70;
			damage = damageMin + rand() % (damageMax - damageMin);
			printf("＋―――――――――――――――――＋\n");
			printf("｜%sはいなずまをはなった　｜\n", playerName[id]);
			printf("＋―――――――――――――――――＋\n");
			for (int i = 0; i < fielddata.playernum; i++) {
				character[i].HP -= damage;
				if (character[i].HP < 0)
					character[i].HP = 0;
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sは%sに　　　　　｜\n", playerName[id], playerName[i]);
				printf("｜%dのダメージを与えた　　　　　　｜\n", damage);
				printf("＋―――――――――――――――――＋\n");
			}
			break;
		}
			break;
		case 3:spell_sukara(id, character, target);
			break;
		case 4:spell_rukanan(id, character, target);
		default:break;
		}
	}
}//ブオーン

void izrairu_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 140;
	character[id].agility = 69;
	character[id].base_endurance = 121;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].maxHP = 135;
	character[id].HP = character[id].maxHP;
}
void izrairu_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = 0;
	switch (rand() % 3) {
	case 0:damage = enemy_dyrect_attack(id, character, target);//直接攻撃
		message_disp(id, target, damage); break;
	case 1:spell_behomaraa(id, character, target);//ベホマラー
		break;
	case 2:spell_firebress(id, character, target);//かえんのいき
		break;
	default:break;
	}
}//イズライール

void ramada_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 300;
	character[id].agility = 55;
	character[id].base_endurance = 180;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].maxHP = 3500;
	character[id].HP = character[id].maxHP;
}
void ramada_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = 0;
	switch (rand() % 4) {
	case 0:damage = enemy_dyrect_attack(id, character, target);
		message_disp(id, target, damage); break;
	case 1: {//はげしいほのお
		int damageMin = 65;
		int damageMax = 85;
		damage = damageMin + rand() % (damageMax - damageMin);
		printf("＋―――――――――――――――――＋\n");
		printf("｜%sははげしいほのおをはなった　｜\n", playerName[id]);
		printf("＋―――――――――――――――――＋\n");
		for (int i = 0; i < fielddata.playernum; i++) {
			character[i].HP -= damage;
			if (character[i].HP < 0)
				character[i].HP = 0;
			printf("＋―――――――――――――――――＋\n");
			printf("｜%sは%sに　　　　　｜\n", playerName[id], playerName[i]);
			printf("｜%dのダメージを与えた　　　　　　｜\n", damage);
			printf("＋―――――――――――――――――＋\n");
		}
		break;
	}
	case 2:spell_begiragon(id, character, target);
		break;
	case 3:spell_mahyado(id, character, target);
		break;
	default:break;
	}
}//ラマダ

void iburu_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 21;
	character[id].agility = 73;
	character[id].base_endurance = 240;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].maxHP = 4200;
	character[id].HP = character[id].maxHP;
}
void iburu_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = 0;
	static int turn_count_snowqueen = 1;
	if (turn_count_snowqueen % 3 == 1) {//1ターン目・4ターン目
		switch (rand() % 2) {
		case 0: spell_shinybress(id, character, target);
			break;
		case 1:
			spell_mahokanta(id, character, target);
		default:break;
		}
	}
	else if (turn_count_snowqueen % 3 == 2) {//2ターン目・5ターン目
		switch (rand() % 2) {
		case 0:			
			printf("＋―――――――――――――――――＋\n");
			printf("｜%sは%sにつうこんないちげき　｜\n", playerName[id], playerName[target]);
			printf("＋―――――――――――――――――＋\n"); 
			character[target].HP -= 105;
			break;
		case 1:character[id].endurance = character[id].base_endurance * 5;//ぼうぎょ・5分の1に軽減
			break;
		default:break;
		}
	}
	else {//3ターン目・6ターン目...
		switch (rand() % 2) {
		case 0:character[id].endurance = character[id].base_endurance;//ぼうぎょ元に戻す
			spell_ionazun(id, character, target);
			break;
		case 1:character[id].endurance = character[id].base_endurance;//ぼうぎょ元に戻す
			spell_itetukuhado(id, character, target);//いてつくはどう
			break;
		default:break;
		}
	}
	turn_count_snowqueen++;
}//イーブル

void evilswplits_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 145;
	character[id].agility = 108;
	character[id].base_endurance = 67;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].maxHP = 155;
	character[id].HP = character[id].maxHP;
}
void evilswplits_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = 0;
	switch (rand() % 3) {
	case 0:damage = enemy_dyrect_attack(id, character, target);
		message_disp(id, target, damage); break;
	case 1:spell_sweetbress(id, character, target);
		break;
	case 2:tool_tatakainodoramu(id, character, target);
		break;
	default:break;
	}
}//エビルスプリッツ

void springer_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 190;
	character[id].agility = 91;
	character[id].base_endurance = 145;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].maxHP = 175;
	character[id].HP = character[id].maxHP;
}
void springer_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = 0;
	switch (rand() % 4) {
	case 0:damage = enemy_dyrect_attack(id, character, target);
		message_disp(id, target, damage); break;
	case 1://斬りつけ・通常と同じダメージ
		damage = enemy_dyrect_attack(id, character, target);
		message_disp(id, target, damage);
		break;
	case 2:spell_rukanan(id, character, target);
		break;
	case 3:spell_sukara(id, character, target);
		break;
	default:break;
	}
}//シュプリンガー

void gema2_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 305;
	character[id].agility = 75;
	character[id].base_endurance = 245;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].maxHP = 4000;
	character[id].HP = character[id].maxHP;
}
void gema2_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = 0;
	for (int attack_num = rand() % 2; 0 <= attack_num; attack_num--) {//1～2回攻撃
		switch (rand() % 5) {
		case 0:damage = enemy_dyrect_attack(id, character, target);
			message_disp(id, target, damage); break;
		case 1: {//はげしいほのお
			int damageMin = 65;
			int damageMax = 85;
			damage = damageMin + rand() % (damageMax - damageMin);
			printf("＋―――――――――――――――――＋\n");
			printf("｜%sははげしいほのおをはなった　｜\n", playerName[id]);
			printf("＋―――――――――――――――――＋\n");
			for (int i = 0; i < fielddata.playernum; i++) {
				character[i].HP -= damage;
				if (character[i].HP < 0)
					character[i].HP = 0;
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sは%sに　　　　　｜\n", playerName[id], playerName[i]);
				printf("｜%dのダメージを与えた　　　　　　｜\n", damage);
				printf("＋―――――――――――――――――＋\n");
			}
			break;
		}
		case 2:spell_shinybress(id, character, target);
			break;
		case 3:spell_yaketukuiki(id, character, target);
			break;
		case 4:spell_merazooma(id, character, target);
			break;
		default:break;
		}
	}
}//ゲマ(2回目)

void skaldon_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 190;
	character[id].agility = 65;
	character[id].base_endurance = 93;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].maxHP = 300;
	character[id].HP = character[id].maxHP;
}
void skaldon_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = 0;
	switch (rand() % 3) {
	case 0:damage = enemy_dyrect_attack(id, character, target);
		message_disp(id, target, damage); break;
	case 1:spell_mahyado(id, character, target);
		break;
	case 2:spell_kogoeruhubuki(id, character, target);
		break;
	default:break;
	}
}//スカルドン

void flaredoragon_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 125;
	character[id].agility = 87;
	character[id].base_endurance = 115;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].maxHP = 125;
	character[id].HP = character[id].maxHP;
}
void flaredoragon_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = 0;
	switch (rand() % 3) {
	case 0:damage = enemy_dyrect_attack(id, character, target);
		message_disp(id, target, damage); break;
	case 1:spell_hardfire(id, character, target);//はげしいほのお
		break;
	case 2:spell_yaketukuiki(id, character, target);
		break;
	default:break;
	}
}//フレアドラゴン

void wightking_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 150;
	character[id].agility = 87;
	character[id].base_endurance = 142;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].maxHP = 250;
	character[id].HP = character[id].maxHP;
}
void wightking_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = 0;
	switch (rand() % 3) {
	case 0:damage = enemy_dyrect_attack(id, character, target);
		message_disp(id, target, damage); break;
	case 1:spell_bagikurosu (id, character, target);//バギクロス
		break;
	case 2:spell_mahotoon(id, character, target);//マホトーン・できてない
		break;
	default:break;
	}
}//ワイトキング

void mildrous_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 240;
	character[id].agility = 80;
	character[id].base_endurance = 230;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength;
	character[id].defense = character[id].endurance;
	character[id].maxHP = 9500;
	character[id].HP = character[id].maxHP;
}
void mildrous_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = 0;
	static int trun_count_mildrous = 1;
	//ミルドラース第一形態
	if (7000 < character[id].HP) {
		switch (rand() % 5) {
		case 0:damage = enemy_dyrect_attack(id, character, target);
			message_disp(id, target, damage); break;
		case 1:spell_shinybress(id, character, target);
			break;
		case 2:
			spell_itetukuhado(id, character, target);//いてつくはどう
			break;
		case 3:spell_merazooma(id, character, target);
			break;
		case 4://もし手下が2匹いなかったらあくましんかんを2匹呼ぶ・できてない
			break;
		case 5://もし手下が2匹いなかったらきらーましんを2匹呼ぶ・できてない
			break;
		default:break;
		}
		if (character[id].HP < 7000){
			character[id].HP = 7000;
			trun_count_mildrous = 0;
		}
	}
	else if (4500 < character[id].HP) {//ミルドラース最終形態・7000～4500
		for (int attack_num = rand() % 2; 0 <= attack_num; attack_num--) {//1～2回行動
			if (trun_count_mildrous % 3 == 1) {//1ターン・4ターン
				switch (rand() % 2) {
				case 0:damage = enemy_dyrect_attack(id, character, target);
					message_disp(id, target, damage); break;
				case 1:spell_syakunetuhono(id, character, target);//しゃくねつ
					break;
				default:break;
				}
			}
			else if (trun_count_mildrous % 3 == 2) {//2ターン・5ターン
				switch (rand() % 2) {
				case 0:spell_itetukuhado(id, character, target);//いてつくはどう
					break;
				case 1:spell_ionazun(id, character,target);//イオナズン
					break;
				default:break;
				}
			}
			else {//3ターン・6ターン
				switch (rand() % 2) {
				case 0:spell_rukanan(id, character, target);//ルカナン
					break;
				case 1:spell_mahokanta(id, character, target);//マホカンタ
					break;
				default: break;
				}
			}
		}
	}
	else if (2500 < character[id].HP) {//ミルドラース最終形態・4500～2500
		for (int attack_num = rand() % 2; 0 <= attack_num; attack_num--) {//1～2回行動
			if (trun_count_mildrous % 3 == 1) {//1ターン・4ターン
				switch (rand() % 2) {
				case 0:damage = enemy_dyrect_attack(id, character, target);
					message_disp(id, target, damage); break;
				case 1:spell_syakunetuhono(id, character, target);//しゃくねつ
					break;
				default:break;
				}
			}
			else if (trun_count_mildrous % 3 == 2) {//2ターン・5ターン
				switch (rand() % 2) {
				case 0:spell_itetukuhado(id, character, target);//いてつくはどう
					break;
				case 1:character[id].HP += 500;//めいそう(HP500回復)
					break;
				default:break;
				}
			}
			else {//3ターン・6ターン
				switch (rand() % 2) {
				case 0:spell_rukanan(id, character, target);//ルカナン
					break;
				case 1:spell_merazooma(id, character, target);//メラゾーマ
					break;
				default: break;
				}
			}
		}
	}
	else {//ミルドラース最終形態・2500～0
		for (int attack_num = rand() % 2; 0 <= attack_num; attack_num--) {//1～2回行動
			if (trun_count_mildrous % 3 == 1) {//1ターン・4ターン
				switch (rand() % 2) {
				case 0://痛恨な一撃
					printf("＋―――――――――――――――――＋\n");
					printf("｜%sは%sにつうこんないちげき　｜\n", playerName[id], playerName[target]);
					printf("＋―――――――――――――――――＋\n");
					character[target].HP -= 215; break;
				case 1:spell_syakunetuhono(id, character, target);//しゃくねつ
					break;
				default:break;
				}
			}
			else if (trun_count_mildrous % 3 == 2) {//2ターン・5ターン
				switch (rand() % 2) {
				case 0:spell_itetukuhado(id, character, target);//いてつくはどう
					break;
				case 1:spell_ionazun(id, character, target);//イオナズン
					break;
				default:break;
				}
			}
			else {//3ターン・6ターン
				switch (rand() % 2) {
				case 0:spell_rukanan(id, character, target);//ルカナン
					break;
				case 1:spell_merazooma(id, character, target);//メラゾーマ
					break;
				default: break;
				}
			}
		}
	}

	trun_count_mildrous++;
	
}//ミルドラース


//Enemy  = {_init,_attack};
Enemy suraimu = { suraimu_init,suraimu_attack ,L"スライム"};//スライム

Enemy kubinagaweasel = { kubinagaweasel_init,kubinagaweasel_attack ,L"くびながイタチ" };//くびながイタチ
Enemy prisoncat = { prisoncat_init,prisoncat_attack ,L"プリズニャン" };//プリズニャン・味方1lvのステータス
Enemy bubbleslime = { bubbleslime_init,bubbleslime_attack ,L"バブルスライム" };//バブルスライム
Enemy ghost = { ghost_init,ghost_attack, L"ゴースト" };//ゴースト
Enemy obakevcandle = { obakevcandle_init,obakevcandle_attack, L"おばけキャンドル" };//おばけキャンドル
Enemy oyabunghost = { oyabunghost_init,oyabunghost_attack, L"おやぶんゴースト" };//BOSSおやぶんゴースト

Enemy soilchild= { soilchild_init,soilchild_attack, L"つちわらし" };//つちわらし
Enemy meralizard= { meralizard_init,meralizard_attack, L"メラリザード" };//メラリザード
Enemy nightsplit = { nightsplit_init,nightsplit_attack, L"ナイトウィップス" };//ナイトウィップス
Enemy gappurin= { gappurin_init,gappurin_attack, L"ガップリン" };//ガップリン
Enemy sabotenball= { sabotenball_init,sabotenball_attack , L"サボテンボール" };//サボテンボール
Enemy witch= { witch_init,witch_attack, L"まほうつかい" };//まほうつかい
Enemy zairu = { zairu_init,zairu_attack , L"ザイル" };//ザイル
Enemy snowqueen= { snowqueen_init,snowqueen_attack , L"ゆきのじょうおう" };//ゆきのじょうおう

Enemy obakekinoko= { obakekinoko_init,obakekinoko_attack ,L"おばけキノコ" };//おばけキノコ
Enemy evilapple= { evilapple_init,evilapple_attack ,L"エビルアップル" };//エビルアップル
Enemy waraibag= { waraibag_init,waraibag_attack ,L"わらいぶくろ" };//わらいぶくろ
Enemy hoimislime= { hoimislime_init,hoimislime_attack ,L"ホイミスライム" };//ホイミスライム
Enemy skelsoldier= { skelsoldier_init,skelsoldier_attack ,L"がいこつへい" };//がいこつへい
Enemy falsetaiko= { falsetaiko_init,falsetaiko_attack ,L"ニセたいこう" };//ニセたいこう
Enemy behomaslime= { behomaslime_init,behomaslime_attack ,L"ベホマスラロードイム" };//ベホマスライム
Enemy madolooper= { madolooper_init,madolooper_attack ,L"マドルーパー*2" };//マドルーパー*2
Enemy snakebat= { snakebat_init,snakebat_attack ,L"へびこうもり" };//へびこうもり
Enemy kandata= { kandata_init,kandata_attack ,L"カンダタ" };//カンダタ
Enemy shieldhipo = { shieldhipo_init,shieldhipo_attack ,L"シールドヒッポ" };//シールドヒッポ
Enemy oak = { oak_init,oak_attack ,L"オークLv20" };//オークLv20
Enemy kimeera= { kimeera_init,kimeera_attack ,L"キメーラLv35" };//キメーラLv35
Enemy jami= { jami_init,jami_attack ,L"ジャミ" };//ジャミ
Enemy berogonload= { berogonload_init,berogonload_attack ,L"ベロゴンロード" };//ベロゴンロード
Enemy magekimera= { magekimera_init,magekimera_attack ,L"メイジキメラ" };//メイジキメラ
Enemy minidaemon= { minidaemon_init,minidaemon_attack ,L"ミニデーモン" };//ミニデーモン
Enemy messaara= { messaara_init,messaara_attack ,L"メッサーラ" };//メッサーラ
Enemy gons= { gons_init,gons_attack ,L"ゴンズ" };//ゴンズ
Enemy gema= { gema_init,gema_attack ,L"ゲマ" };//ゲマ
Enemy buoon= { buoon_init,buoon_attack ,L"ブオーン" };//ブオーン
Enemy izrairu= { izrairu_init,izrairu_attack ,L"イズライール" };//イズライール
Enemy ramada= { ramada_init,ramada_attack ,L"ラマダ" };//ラマダ
Enemy iburu= { iburu_init,iburu_attack ,L"イーブル" };//イーブル
Enemy evilswplits= { evilswplits_init,evilswplits_attack ,L"エビルスプリッツ" };//エビルスプリッツ
Enemy springer= { springer_init,springer_attack ,L"シュプリンガー" };//シュプリンガー
Enemy gema2= { gema2_init,gema2_attack ,L"ゲマ(2回目)" };//ゲマ(2回目)
Enemy skaldon= { skaldon_init,skaldon_attack ,L"スカルドラゴン" };//スカルドン
Enemy flaredoragon= { flaredoragon_init,flaredoragon_attack ,L"フレアドラゴン" };//フレアドラゴン
Enemy wightking= { wightking_init,wightking_attack ,L"ワイトキング" };//ワイトキング
Enemy mildrous= { mildrous_init,mildrous_attack ,L"ミルドラース" };//ミルドラース

Enemy estark = { estark_init,estark_action,L"エスターク"};//エスターク
Enemy* enemies[5] = {&estark};




void set_spells(int id, Character* character, char* name, int char_level) {
	FILE* fp;
	char filename[128];
	char* sep[32];
	sprintf(filename, "character_datas/%sspell.csv", name);
	fp = fopen(filename, "r");
	char line[128], spell_name[32];
	int level;

	int magic_num = 0;
	while (fscanf(fp, "%s", line) != EOF) {
		int count = split(sep, line, ',');
		level = atoi(sep[0]);
		if (char_level >= level)
		{
			for (int i = 0; i < SPELL_MAX; i++) {
				if (all_spell[i] == NULL) {
					continue;
				}
				wchar_t target_name[32] = L"";
				strcpy_s(target_name, 32, all_spell[i]->name);

				wcstombs_s(NULL, spell_name, 32, target_name, _TRUNCATE);
				if (!strcmp(spell_name, sep[1]))
				{
					printf("%d,%s",magic_num,sep[1]);
					character[id].spells[magic_num] = all_spell[i];
					magic_num++;
				}
			}
		}
	}
	fclose(fp);
}

void spell_copy(Spell *dst[20],Spell *src[20]) {
	for (int i = 0; i < 20; i++)
	{
		dst[i] = src[i];
	}
}





void hero_init(int id, Character* character, int level) {
	set_Character_base_status(id, character, "主人公", level);
	set_Character_equip_status(id, character, "メタルキングのけん", "メタルキングよろい", "メタルキングヘルム","メタルキングのたて");
	spell_copy(character[id].spells ,presetspell1);
}
void bianka_init(int id, Character* character, int level) {
	set_Character_base_status(id, character, "ビアンカ", level);
	spell_copy(character[id].spells , presetspell2);
}
void rex_init(int id, Character* character, int level) {
	set_Character_base_status(id, character, "レックス", level);
	spell_copy(character[id].spells, presetspell2);
}
void tabasa_init(int id, Character* character, int level) {
	set_Character_base_status(id, character, "タバサ", level);
	spell_copy(character[id].spells, presetspell2);
}

PresetCharacter hero = {L"主人公",0,hero_init};
PresetCharacter bianka = { L"ビアンカ",1,bianka_init };
PresetCharacter rex = { L"レックス",2,rex_init };
PresetCharacter tabasa = { L"タバサ",3,tabasa_init };

void field_init() {
	fielddata.playernum = 0;
	fielddata.enemynum = 0;
	fielddata.fullcharacters = 0;
}


void add_character(PresetCharacter addCharacter, Character* character) {
	addCharacter.init(fielddata.fullcharacters, character, 45);
	strcpy(character[fielddata.fullcharacters].name, addCharacter.name);
	wcstombs_s(NULL, playerName[fielddata.fullcharacters], 20, addCharacter.name, _TRUNCATE);
	fielddata.fullcharacters++;
	fielddata.playernum++;
}
void add_Enemy(Enemy *addCharacter, Character* character) {
	strcpy(character[fielddata.fullcharacters].name, addCharacter->name);
		
	wcstombs_s(NULL, playerName[fielddata.fullcharacters], 20, addCharacter->name, _TRUNCATE);
	printf("%s,%p,%p", playerName[fielddata.fullcharacters],&estark,addCharacter);
	enemies[fielddata.enemynum] = addCharacter;
	enemies[fielddata.enemynum]->init(fielddata.fullcharacters, character);
	fielddata.fullcharacters++;
	fielddata.enemynum++;
}
void player_character_init(int id, Character* character, int level, char* name) {
	printf("set_status\n");
	set_Character_base_status(id, character, name, level);
	printf("set_spell\n");
	set_spells(id, character, name, level);
	printf("set_spell_end\n");

}

void add_character_from_name(Character* character, char* name, int level) {
	player_character_init(fielddata.fullcharacters, character, level, name);
	
	mbstowcs_s(NULL, character[fielddata.fullcharacters].name, 21, name, _TRUNCATE);
	strcpy(playerName[fielddata.fullcharacters], name);

	fielddata.fullcharacters++;
	fielddata.playernum++;
}

void add_character_from_name_and_equip(Character* character, char* name, int level, char* wepon, char* armar, char* sheild, char* helmet) {
	player_character_init(fielddata.fullcharacters, character, level, name);
	set_Character_equip_status(fielddata.fullcharacters, character, wepon, armar, helmet, sheild);

	mbstowcs_s(NULL, character[fielddata.fullcharacters].name, 21, name, _TRUNCATE);
	strcpy(playerName[fielddata.fullcharacters], name);
	fielddata.fullcharacters++;
	fielddata.playernum++;
}

//キャラクター設定


 
void party0_init(Character* character) {
	field_init();
	//addCharacterすべてしてからaddEnemy
	add_character_from_name(character, "主人公", 3);
	add_character_from_name(character, "ビアンカ",3);
	add_Enemy(&suraimu, character);
	add_Enemy(&suraimu, character);
	add_Enemy(&suraimu, character);
}//スライム*3
void party1_init(Character* character) {
	field_init();
	//addCharacterすべてしてからaddEnemy
	add_character_from_name_and_equip(character, "主人公", 8, "ブーメラン", "たびびとのふく", "かわのたて", "かわのぼうし");
	add_character_from_name_and_equip(character, "ビアンカ",8, "くだものナイフ", "ておりのケープ", "おなべのふた", "かわのぼうし");
	add_Enemy(&oyabunghost, character);
}//おやぶんゴースト
void party2_init(Character* character) {
	field_init();
	//addCharacterすべてしてからaddEnemy
	add_character_from_name(character, "主人公",8);
	add_character_from_name(character, "ベビーパンサー",2);
	add_character_from_name(character, "ベラ",7);
	add_Enemy(&meralizard, character);
	add_Enemy(&soilchild, character);
	add_Enemy(&nightsplit, character);
}//メラリザード・つちわらし・ナイトウィップス
void party3_init(Character* character) {
	field_init();
	//addCharacterすべてしてからaddEnemy
	add_character_from_name(character, "主人公", 10);
	add_character_from_name(character, "ベビーパンサー", 5);
	add_character_from_name(character, "ベラ", 7);
	add_Enemy(&zairu, character);
}//ザイル
void party4_init(Character* character) {
	field_init();
	//addCharacterすべてしてからaddEnemy
	add_character_from_name_and_equip(character, "主人公", 10, "ブーメラン", "たびびとのふく", "かわのたて", "かわのぼうし");
	add_character_from_name_and_equip(character, "ベビーパンサー", 10,"とがったホネ", "ておりのケーブ", "", "かわのぼうし");
	add_character_from_name_and_equip(character, "ベラ", 7,"かしのつえ","きぬのローブ","かわのたて","ヘアバンド");
	add_Enemy(&snowqueen, character);
}//ゆきのじょうおう
void party5_init(Character* character) {
	field_init();
	//addCharacterすべてしてからaddEnemy
	add_character_from_name(character,"主人公", 10);
	add_character_from_name(character,"ヘンリー", 3);
	add_Enemy(&obakekinoko, character);
	add_Enemy(&evilapple, character);
}//おばけキノコ*3・エビルアップル<主人公・ヘンリー>
void party6_init(Character* character) {
	field_init();
	//addCharacterすべてしてからaddEnemy
	add_character_from_name_and_equip(character,"主人公",10,"チェーンクロス","うろこのよろい","てつのたて", "けがわのフード");
	add_character_from_name_and_equip(character,"エビルアップル",5,"はがねのキバ", "スライムのふく","","");
	add_character_from_name_and_equip(character,"ヘンリー",7,"チェーンクロス", "ドレイのふく", "うろこのたて", "きのぼうし");
	add_character_from_name_and_equip(character,"スライムナイト",1,"ブロンズナイフ","","うろこのたて", "きのぼうし");
	add_Enemy(&suraimu, character);
	add_Enemy(&suraimu, character);
	add_Enemy(&suraimu, character);
	add_Enemy(&suraimu, character);
	add_Enemy(&suraimu, character);
	add_Enemy(&suraimu, character);
	add_Enemy(&suraimu, character);
	add_Enemy(&suraimu, character);
}//スライム*8<エビルアップル・主人公・ヘンリー・スライムナイト2,10,7,1>
void party7_init(Character* character) {
	field_init();
	//addCharacterすべてしてからaddEnemy
	add_character_from_name_and_equip(character,"主人公", 13,"チェーンクロス", "うろこのよろい", "てつのたて", "けがわのフード");
	add_character_from_name_and_equip(character,"エビルアップル",10,"はがねのつるぎ", "","うろこのたて", "きのぼうし");
	add_character_from_name_and_equip(character,"ヘンリー",13,"チェーンクロス", "ドレイのふく", "うろこのたて", "きのぼうし");
	add_character_from_name_and_equip(character,"スライムナイト",10,"はがねのキバ", "スライムのふく","","");
	add_Enemy(&waraibag, character);
	add_Enemy(&waraibag, character);
	add_Enemy(&hoimislime, character);
	add_Enemy(&hoimislime, character);
	add_Enemy(&hoimislime, character);
	add_Enemy(&skelsoldier, character);
}//わらいぶくろ*2・ホイミスライム*3・がいこつへい<エビルアップル・主人公・ヘンリー・スライムナイト12,13,13,12>
void party8_init(Character* character) {
	field_init();
	//addCharacterすべてしてからaddEnemy
	add_character_from_name_and_equip(character,"主人公", 16, "チェーンクロス", "うろこのよろい", "てつのたて", "けがわのフード");
	add_character_from_name_and_equip(character,"エビルアップル", 15, "はがねのつるぎ", "", "うろこのたて", "きのぼうし");
	add_character_from_name_and_equip(character,"ヘンリー", 15, "チェーンクロス", "ドレイのふく", "うろこのたて", "きのぼうし");
	add_character_from_name_and_equip(character,"スライムナイト", 15, "はがねのキバ", "スライムのふく", "", "");
	add_Enemy(&falsetaiko, character);
}//ニセたいこう<エビルアップル・主人公・ヘンリー・スライムナイト12,13,13,12>
void party9_init(Character* character) {
	field_init();
	//addCharacterすべてしてからaddEnemy
	add_character_from_name_and_equip(character,"主人公",19 , "チェーンクロス", "うろこのよろい", "てつのたて", "けがわのフード");
	add_character_from_name_and_equip(character,"スライムナイト",20 , "はがねのつるぎ","", "うろこのたて", "きのぼうし");
	add_character_from_name_and_equip(character,"エビルアップル",15, "はがねのキバ", "スライムのふく","","");
	add_Enemy(&behomaslime, character);
	add_Enemy(&behomaslime, character);
	add_Enemy(&madolooper, character);
	add_Enemy(&madolooper, character);
	add_Enemy(&snakebat, character);
}//ベホマスライム*2・マドルーパー*2・へびこうもり<主人公・エビルアップル・スライムナイト,14,13,13>
void party10_init(Character* character) {
	field_init();
	//addCharacterすべてしてからaddEnemy
	add_character_from_name_and_equip(character,"主人公",25 , "パパスのつるぎ", "ドラゴンメイル", "ふうじんのたて", "てっかめん");
	add_character_from_name_and_equip(character,"スライムナイト",25, "はがねのつるぎ", "はがねのよろい", "ふうじんのたて", "てつかぶと");
	add_character_from_name_and_equip(character,"エビルアップル",20, "はがねのキバ", "スライムのふく","", "シルクハット");
	add_character_from_name_and_equip(character,"キラーパンサー",25 , "ほのおのツメ", "ぎんのむねあて","", "てつかぶと");
	add_Enemy(&kandata, character);
	add_Enemy(&shieldhipo, character);
}//カンダタ・シールドヒッポ<主人公・エビルアップル・スライムナイト,キラーパンサー,14,13,13,15>
void party11_init(Character* character) {
	field_init();
	//addCharacterすべてしてからaddEnemy
	add_character_from_name_and_equip(character,"主人公",25, "パパスのつるぎ", "ドラゴンメイル", "ふうじんのたて", "てっかめん");
	add_character_from_name_and_equip(character,"スライムナイト",25, "はがねのつるぎ", "はがねのよろい", "ふうじんのたて", "てつかぶと");
	add_character_from_name_and_equip(character,"エビルアップル",20, "はがねのキバ", "スライムのふく","", "シルクハット");
	add_character_from_name_and_equip(character,"キラーパンサー",25, "ほのおのツメ", "ぎんのむねあて","", "てつかぶと");
	add_Enemy(&oak, character);
}//オークLv20<主人公・エビルアップル・スライムナイト,キラーパンサー,14,14,14,15>
void party12_init(Character* character) {
	field_init();
	//addCharacterすべてしてからaddEnemy
	add_character_from_name_and_equip(character,"主人公",25, "パパスのつるぎ", "ドラゴンメイル", "ふうじんのたて", "てっかめん（道具てんくうのたて）	");
	add_character_from_name_and_equip(character,"スライムナイト",25, "はがねのつるぎ", "はがねのよろい", "ふうじんのたて", "てつかぶと（道具てんくうのつるぎ）");
	add_character_from_name_and_equip(character,"エビルアップル",20, "はがねのキバ", "スライムのふく","", "シルクハット");
	add_character_from_name_and_equip(character,"キラーパンサー",25, "ほのおのツメ", "ぎんのむねあて","", "てつかぶと");
	add_Enemy(&kimeera, character);
}//キメーラLv35<主人公・エビルアップル・スライムナイト,キラーパンサー,14,14,14,15>
void party13_init(Character* character) {
	field_init();
	//addCharacterすべてしてからaddEnemy
	add_character_from_name_and_equip(character,"主人公",30, "パパスのつるぎ", "ドラゴンメイル", "ふうじんのたて", "てっかめん（道具てんくうのたて）	");
	add_character_from_name_and_equip(character,"スライムナイト",30, "はがねのつるぎ", "はがねのよろい", "ふうじんのたて", "てつかぶと（道具てんくうのつるぎ）");
	add_character_from_name_and_equip(character,"エビルアップル",20, "はがねのキバ", "スライムのふく","", "シルクハット");
	add_character_from_name_and_equip(character,"キラーパンサー",30, "ほのおのツメ", "ぎんのむねあて","", "てつかぶと");
	add_Enemy(&jami, character);
}//ジャミ<主人公・エビルアップル・スライムナイト,キラーパンサー,14,14,14,15>
void party14_init(Character* character) {
	field_init();
	//addCharacterすべてしてからaddEnemy
	add_character_from_name_and_equip(character,"サンチョ",20, "らいじんのヤリ", "まほうのよろい", "ふうじんのたて", "しあわせのぼうし");
	add_character_from_name_and_equip(character,"エビルアップル",20, "はがねのキバ", "スライムのふく", "","シルクハット");
	add_character_from_name_and_equip(character,"男の子",10, "てんくうのつるぎ", "ドラゴンメイル", "てんくうのたて", "てんくうのかぶと");
	add_character_from_name_and_equip(character,"女の子",10, "ようせいのけん", "プリンセスローブ", "うろこのたて", "おうごんのティアラ");
	add_Enemy(&berogonload, character);
	add_Enemy(&magekimera, character);
	add_Enemy(&minidaemon, character);
	add_Enemy(&messaara, character);
}//ベロゴンロード・メイジキメラ・ミニデーモン・メッサーラ<サンチョ・エビルアップル・男の子・女の子,20,15,5,5>
void party15_init(Character* character) {
	field_init();
	//addCharacterすべてしてからaddEnemy
	add_character_from_name_and_equip(character,"主人公",31, "ドラゴンのつえ", "ほのおのよろい", "たからのたて", "ちりょくのかぶと");
	add_character_from_name_and_equip(character,"サンチョ",30, "らいじんのヤリ", "まほうのよろい", "ふうじんのたて", "しあわせのぼうし");
	add_character_from_name_and_equip(character,"男の子",29, "てんくうのつるぎ", "ドラゴンメイル", "てんくうのたて", "てんくうのかぶと");
	add_character_from_name_and_equip(character,"女の子",29, "ようせいのけん", "プリンセスローブ", "うろこのたて", "おうごんのティアラ");
	add_Enemy(&gons, character);
}//ゴンズ<サンチョ・男の子・女の子・主人公, 26, 23, 22, 22>
void party16_init(Character* character) {
	field_init();
	//addCharacterすべてしてからaddEnemy
	add_character_from_name_and_equip(character,"主人公",33, "ドラゴンのつえ", "ほのおのよろい", "たからのたて", "ちりょくのかぶと");
	add_character_from_name_and_equip(character,"サンチョ",31, "らいじんのヤリ", "まほうのよろい", "ふうじんのたて", "しあわせのぼうし");
	add_character_from_name_and_equip(character,"男の子",30, "てんくうのつるぎ", "ドラゴンメイル", "てんくうのたて", "てんくうのかぶと");
	add_character_from_name_and_equip(character,"女の子",30, "ようせいのけん", "プリンセスローブ", "うろこのたて", "おうごんのティアラ");
	add_Enemy(&gema, character);
}//ゲマ<サンチョ・男の子・女の子・主人公, 26, 23, 22, 22>
void party17_init(Character* character) {
	field_init();
	//addCharacterすべてしてからaddEnemy
	add_character_from_name_and_equip(character,"主人公",33 , "ドラゴンのつえ", "ほのおのよろい", "ちからのたて", "ちりょくのかぶと");
	add_character_from_name_and_equip(character,"サンチョ",32 , "らいじんのヤリ", "まほうのよろい", "ふうじんのたて", "しあわせのぼうし");
	add_character_from_name_and_equip(character,"男の子",31 , "てんくうのつるぎ", "ドラゴンメイル", "てんくうのたて", "てんくうのかぶと");
	add_character_from_name_and_equip(character,"女の子",31, "ようせいのけん", "プリンセスローブ", "うろこのたて", "おうごんのティアラ");
	add_Enemy(&buoon, character);
}//ブオーン<サンチョ・男の子・女の子・主人公, 26, 23, 22, 22>
void party18_init(Character* character) {
	field_init();
	//addCharacterすべてしてからaddEnemy
	add_character_from_name_and_equip(character,"主人公",33, "ドラゴンのつえ", "おうじゃのマント", "ちからのたて", "ちりょくのかぶと");
	add_character_from_name_and_equip(character,"サンチョ",32, "らいじんのヤリ", "まほうのよろい", "ふうじんのたて", "しあわせのぼうし");
	add_character_from_name_and_equip(character,"男の子",31, "てんくうのつるぎ", "てんくうのよろい", "てんくうのたて", "てんくうのかぶと");
	add_character_from_name_and_equip(character,"女の子",31, "ようせいのけん", "プリンセスローブ", "うろこのたて", "おうごんのティアラ");
	add_Enemy(&izrairu, character);
	add_Enemy(&izrairu, character);
	add_Enemy(&izrairu, character);
}//イズライール*3<サンチョ・男の子・女の子・主人公,27,25,24,24>
void party19_init(Character* character) {
	field_init();
	//addCharacterすべてしてからaddEnemy
	add_character_from_name_and_equip(character,"主人公",33, "ドラゴンのつえ", "おうじゃのマント", "ちからのたて", "ちりょくのかぶと");
	add_character_from_name_and_equip(character,"サンチョ",32, "らいじんのヤリ", "まほうのよろい", "ふうじんのたて", "しあわせのぼうし");
	add_character_from_name_and_equip(character,"男の子",31, "てんくうのつるぎ", "てんくうのよろい", "てんくうのたて", "てんくうのかぶと");
	add_character_from_name_and_equip(character,"女の子",31, "ようせいのけん", "プリンセスローブ", "うろこのたて", "おうごんのティアラ");
	add_Enemy(&ramada, character);
}//ラマダ<サンチョ・男の子・女の子・主人公,27,25,24,24>
void party20_init(Character* character) {
	field_init();
	//addCharacterすべてしてからaddEnemy
	add_character_from_name_and_equip(character,"主人公",33, "ドラゴンのつえ", "おうじゃのマント", "ちからのたて", "ちりょくのかぶと");
	add_character_from_name_and_equip(character,"サンチョ",33, "らいじんのヤリ", "まほうのよろい", "ふうじんのたて", "しあわせのぼうし");
	add_character_from_name_and_equip(character,"男の子",32, "てんくうのつるぎ", "てんくうのよろい", "てんくうのたて", "てんくうのかぶと");
	add_character_from_name_and_equip(character,"女の子",32, "ようせいのけん", "プリンセスローブ", "うろこのたて", "おうごんのティアラ");
	add_Enemy(&iburu, character);
}//イーブル<サンチョ・男の子・女の子・主人公,28,25,25,24>
void party21_init(Character* character) {
	field_init();
	//addCharacterすべてしてからaddEnemy
	add_character_from_name_and_equip(character,"主人公",36, "ドラゴンのつえ", "おうじゃのマント", "みかがみのたて", "メタルキングヘルム");
	add_character_from_name_and_equip(character,"サンチョ",36, "ビッグボウガン", "まほうのよろい", "オーガシールド", "グレートヘルム");
	add_character_from_name_and_equip(character,"男の子",35, "てんくうのけん", "てんくうのよろい", "てんくうのたて", "てんくうのかぶと");
	add_character_from_name_and_equip(character,"女の子",35, "ようせいのけん", "プリンセスローブ", "みかがみのたて", "おうごんのティアラ");
	add_Enemy(&evilswplits, character);
	add_Enemy(&evilswplits, character);
	add_Enemy(&springer,character);
	add_Enemy(&springer, character);
}//エビルスプリッツ*2・シュプリンガー*2<サンチョ・男の子・女の子・主人公,29,27,26,26>
void party22_init(Character* character) {
	field_init();
	//addCharacterすべてしてからaddEnemy
	add_character_from_name_and_equip(character,"主人公",36, "ドラゴンのつえ", "おうじゃのマント", "みかがみのたて", "メタルキングヘルム");
	add_character_from_name_and_equip(character,"サンチョ",36, "ビッグボウガン", "まほうのよろい", "オーガシールド", "グレートヘルム");
	add_character_from_name_and_equip(character,"男の子",35, "てんくうのけん", "てんくうのよろい", "てんくうのたて", "てんくうのかぶと");
	add_character_from_name_and_equip(character,"女の子",35, "ようせいのけん", "プリンセスローブ", "みかがみのたて", "おうごんのティアラ");
	add_Enemy(&gema2, character);
}//ゲマ(2回目)<サンチョ・男の子・女の子・主人公,29,27,26,26>
void party23_init(Character* character) {
	field_init();
	//addCharacterすべてしてからaddEnemy
	add_character_from_name_and_equip(character,"主人公", 38, "ドラゴンのつえ", "おうじゃのマント", "みかがみのたて", "メタルキングヘルム");
	add_character_from_name_and_equip(character,"サンチョ", 38, "ビッグボウガン", "まほうのよろい", "オーガシールド", "グレートヘルム");
	add_character_from_name_and_equip(character,"男の子",37, "てんくうのけん", "てんくうのよろい", "てんくうのたて", "てんくうのかぶと");
	add_character_from_name_and_equip(character,"女の子",37, "ようせいのけん", "プリンセスローブ", "みかがみのたて", "おうごんのティアラ");
	add_Enemy(&skaldon, character);
	add_Enemy(&flaredoragon, character);
	add_Enemy(&flaredoragon, character);
	add_Enemy(&flaredoragon, character);
	add_Enemy(&wightking, character);
}//スカルドラゴン・フレアドラゴン * 3・ワイトキング<サンチョ・男の子・女の子・主人公,29,27,27,26>
void party24_init(Character* character) {
	field_init();
	//addCharacterすべてしてからaddEnemy
	add_character_from_name_and_equip(character,"主人公",40, "ドラゴンのつえ", "おうじゃのマント", "みかがみのたて", "メタルキングヘルム");
	add_character_from_name_and_equip(character,"サンチョ",40, "ビッグボウガン", "まほうのよろい", "オーガシールド", "グレートヘルム");
	add_character_from_name_and_equip(character,"男の子",38, "てんくうのけん", "てんくうのよろい", "てんくうのたて", "てんくうのかぶと");
	add_character_from_name_and_equip(character,"女の子",38, "ようせいのけん", "プリンセスローブ", "みかがみのたて", "おうごんのティアラ");
	add_Enemy(&mildrous, character);
}//ミルドラース<サンチョ・男の子・女の子・主人公,29,27,27,26>

void party25_init(Character* character) {
	field_init();
	//addCharacterすべてしてからaddEnemy
	add_character_from_name_and_equip(character,"主人公",45,"メタルキングのけん","メタルキングよろい","メタルキングのたて","メタルキングヘルム");
	add_character_from_name_and_equip(character,"ビアンカ",45, "グリンガムのムチ", "プリンセスローブ", "うろこのたて", "メタルキングヘルム");
	add_character_from_name_and_equip(character, "男の子",45, "メタルキングのけん", "メタルキングよろい", "メタルキングのたて", "メタルキングヘルム");
	add_character_from_name_and_equip(character, "女の子",45, "グリンガムのムチ", "プリンセスローブ", "みかがみのたて", "おうごんのティアラ");
	add_Enemy(&estark, character);
}//エスターク<主人公・ビアンカ・男の子・女の子,45,45,45,45>

void (*party_inits[26])(Character* character) = { party0_init,party1_init,party2_init,party3_init,party4_init,party5_init,party6_init,party7_init,party8_init,party9_init,party10_init,party11_init,party12_init,party13_init,party14_init,party15_init,party16_init,party17_init,party18_init,party19_init,party20_init,party21_init,party22_init,party23_init,party24_init,party25_init };


void init(Character* character,int partyid)
{
	setlocale(LC_ALL, "Japanese");
	field_init();
	//addCharacterすべてしてからaddEnemy
	party_inits[partyid](character);

}//スライム


void status_poison(Character *character)
{
	for (int i = 0; i < fielddata.playernum; i++)
	{
		if (character[i].poison)
		{
			character[i].HP -= (character[i].maxHP / 6);
			printf("＋――――――――――――――――――――＋\n");
			printf("｜%sは毒によるダメージを受けた　　　　　　｜\n", playerName[i]);
			printf("＋――――――――――――――――――――＋\n");
		}
	}
}

void status_sleep(Character* character) {
	for (int i = 0; i < fielddata.playernum; i++)
	{
		if (character[i].sleep)
		{
			character[i].sleep -= 1;
			character[i].can_action=FALSE;
			if (character[i].sleep == 0)
			{
				printf("＋――――――――――――――――――――＋\n");
				printf("｜%sは目を覚ました　　　　　｜\n", playerName[i]);
				printf("＋――――――――――――――――――――＋\n");
			}
			else {
				printf("＋――――――――――――――――――――＋\n");
				printf("｜%sはすやすや眠っている　　　　　｜\n", playerName[i]);
				printf("＋――――――――――――――――――――＋\n");
			}
		}
	}

}


void status_check(Character* character) {
	// 毒判定
	status_poison(character);
	status_sleep(character);
	for (int i = 0; i < fielddata.fullcharacters; i++) {
		if (character[i].HP == 0 || character[i].sleep || character[i].paralysis) {
			character[i].action = 0;
			character[i].can_action = FALSE;
		}
		else
			character[i].can_action = TRUE;
	}
}



void display() {

}

void spell(int p_turn, BOOL wait, BOOL disp,Character* character)
{
	if (disp)display();

	if(character[p_turn].spells[character[p_turn].action_spell]!=NULL)
		character[p_turn].spells[character[p_turn].action_spell]->main(p_turn,character, character[p_turn].action_spell_target);

	if (wait)_getch();
}


// 道具
void tool(int playerId, BOOL wait, BOOL disp,Character* character)
{
	if (disp)display();
	if (character[playerId].action_tool == 0)
	{
		tool_tatakainodoramu(playerId,character,character[playerId].action_spell_target);
	}
	if (wait)_getch();
}



int get_random_enemy_id() {
	return rand() % fielddata.enemynum + fielddata.playernum;
}


void battle_main(Character* characters, BOOL wait, BOOL disp) {
	printf("enter_battle_main");
	// すばやさの比較
	int agility[12];
	for (int i = 0; i < fielddata.fullcharacters; i++)
		agility[i] = characters[i].agility;

	int agility_id[12];


	int action_players = 0;
	for (int i = 0; i < fielddata.fullcharacters; i++)
		if (characters[i].can_action == TRUE)
		{
			agility[action_players] = characters[i].agility;
			agility_id[action_players] = i;
			action_players++;
		}

	// agility[] をバブルソート
	for (int i = 0; i < action_players; i++)
	{
		for (int j = action_players - 1; j > i; j--)
		{
			if (agility[j - 1] < agility[j])
			{
				int d = agility[j - 1];
				agility[j - 1] = agility[j];
				agility[j] = d;

				d = agility_id[j - 1];
				agility_id[j - 1] = agility_id[j];
				agility_id[j]=d;
			}
		}
	}



	int damageBase;
	int damageMin;
	int damageMax;
	int damage;
	int c_damageBase;
	int c_damageMin;
	int c_damageMax;
	int c_damage;
	int keep;
	int b_turn = 0;			// バトルターン

							// バトル
	for(int action_num=0;action_num<action_players;action_num++)
	{
		int p_turn = agility_id[action_num];
		if (characters[p_turn].can_action == FALSE)continue;


		if (characters[p_turn].dragon == 1)
		{
			if (disp)display();
			int target = get_random_enemy_id();
			switch (rand() % 3)
			{
			case 0:
				damageBase = characters[p_turn].attack / 2 - characters[target].base_endurance / 4;
				damageMin = damageBase * 7 / 8 + 60;
				damageMax = damageBase * 9 / 8 + 60;
				damage = damageMin + rand() % (damageMax - damageMin);
				printf("＋―――――――――――――――――――＋\n");
				printf("｜%sはするどいツメでこうげきした｜\n", playerName[p_turn]);
				printf("＋―――――――――――――――――――＋\n");
				characters[target].HP -= damage;
				printf("＋――――――――――――――――――＋\n");
				printf("｜%sは%dのダメージをうけた｜\n", playerName[target], damage);
				printf("＋――――――――――――――――――＋\n");
				break;
			default:
				damageMin = 65;
				damageMax = 85;
				damage = damageMin + rand() % (damageMax - damageMin);
				printf("＋――――――――――――――＋\n");
				printf("｜%sはほのおをはいた　｜\n", playerName[p_turn]);
				printf("＋――――――――――――――＋\n");
				characters[target].HP -= damage;
				printf("＋――――――――――――――――――＋\n");
				printf("｜%sは%dのダメージをうけた｜\n", playerName[target], damage);
				printf("＋――――――――――――――――――＋\n");
				break;
			}
			if (wait)_getch();
			continue;
		}

		if (p_turn >= fielddata.playernum)
		{
			enemies[p_turn-fielddata.playernum]->attack(p_turn, characters);
		}

		else
		{
			if (characters[p_turn].action == 0)
			{
				int target = characters[p_turn].action_spell_target;
				if (target < 0 || target >= fielddata.fullcharacters) {
					printf("不正なターゲット");
					continue;
				}
				damageBase = characters[p_turn].attack / 2 - characters[target].base_endurance / 4;
				damageMin = damageBase * 7 / 8;
				damageMax = damageBase * 9 / 8;
				damage = damageMin + rand() % (damageMax - damageMin);
				if (damage < 0)damage = 0;
				switch (keep = rand() % 32)
				{
				case 0:
					c_damageBase = characters[p_turn].attack;
					c_damageMin = c_damageBase;
					c_damageMax = c_damageBase * 74 / 64;
					c_damage = c_damageMin + rand() % (c_damageMax - c_damageMin);
					break;
				default:
					break;
				}
				if (disp)display();
				printf("＋―――――――――――――――――＋\n");
				printf("｜%sのこうげき　　　　　　　　｜\n", playerName[p_turn]);
				printf("＋―――――――――――――――――＋");
				if (wait)_getch();
				if (keep == 0)
				{
					if (disp)display();
					printf("＋―――――――――――――――――＋\n");
					printf("｜会心の一撃！　　　　　　　　　　　｜\n");
					characters[target].HP -= c_damage;
					if (characters[target].HP < 0)
						characters[target].HP = 0;
					printf("｜%sは%sに　　　　　｜\n", playerName[p_turn], playerName[target]);
					printf("｜%dのダメージを与えた　　　　　　　｜\n", c_damage);
					printf("＋―――――――――――――――――＋\n");
					if (wait)_getch();
				}
				else
				{
					characters[target].HP -= damage;
					if (characters[target].HP < 0)
						characters[target].HP = 0;
					if (disp)display();
					printf("＋―――――――――――――――――＋\n");
					printf("｜%sは%sに　　　　　｜\n", playerName[p_turn], playerName[target]);
					printf("｜%dのダメージを与えた　　　　　　　｜\n", damage);
					printf("＋―――――――――――――――――＋\n");
					if (wait)_getch();
				}
			}
			else if (characters[p_turn].action == 1) {
				int target = characters[p_turn].action_spell_target;
				if (target < 0 || target >= fielddata.fullcharacters) {
					printf("不正なターゲット");
					continue;
				}
				spell(p_turn, wait, disp, characters);
			}
			else if (characters[p_turn].action == 2)
				tool(p_turn, wait, disp,characters);
		}
		for (int i = 0; i < fielddata.fullcharacters; i++)
			if (characters[i].HP < 0)
				characters[i].HP = 0;

		b_turn++;

		BOOL enemy_alive = FALSE;
		BOOL player_alive = FALSE;
		for (int i = fielddata.playernum; i < fielddata.fullcharacters; i++)
			if (characters[i].HP != 0)enemy_alive = TRUE;
		for (int i = 0; i < fielddata.playernum; i++)
			if (characters[i].HP != 0)player_alive = TRUE;

		if (enemy_alive == FALSE)break;
		if (player_alive == FALSE)break;
		printf("%d,,",action_num);
	}
}

void get_fielddata(int *a,int *b)
{
	a[0] = fielddata.playernum;
	b[0] = fielddata.enemynum;
}