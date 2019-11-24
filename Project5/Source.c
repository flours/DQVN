#define _CRT_SECURE_NO_WARNINGS

#include "Header.h"

#include<time.h>
#include<windows.h>

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>




//#define printf //





char playerName[][5 * 2 + 1] =
{
	" 主人公 ",
	"ビアンカ",
	"A",
	"B",
	"C"
};


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

	for (int i = 0; i < 4; i++) {
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
	for (int i = 0; i < fielddata.playernum; i++) {
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
	for (int i = 0; i < fielddata.playernum; i++)
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
	for (int i = 0; i < fielddata.playernum; i++) {
		base_spell_cure_single_target(playerId, i, character, 100, 120);
	}
	printf("＋―――――――――――――――――＋\n");
	printf("｜ぜんいんのHPがかいふくした　　　　｜\n");
	printf("＋―――――――――――――――――＋\n");
}
Spell behomaraa = { L"キアリク",18,FALSE,spell_behomaraa };


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
	for (int i = 0; i < 4; i++)character[i].MP -= 10;

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


void tool_tatakainodoramu(int playerId, Character* character, int target) {
	printf("＋――――――――――――――――――＋\n");
	printf("｜%sはたたかいのドラムを使った　　　　｜\n", playerName[playerId]);
	printf("＋――――――――――――――――――＋\n");
	for (int i = 0; i < 4; i++) {
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
	char filename[128];
	char *sep[32];
	sprintf(filename, "character_datas/%s_status.csv", name);
	fp = fopen(filename, "r");
	char line[128];
	int level, power, agility, endurance, clevar, luck, HP, MP, exp;
	while (fscanf(fp, "%s", line) != EOF) {
		int count = split(sep, line, ',');
		level = atoi(sep[0]);
		power = atoi(sep[1]);
		agility = atoi(sep[2]);
		endurance = atoi(sep[3]);
		clevar = atoi(sep[4]);
		luck = atoi(sep[5]);
		HP = atoi(sep[6]);
		MP = atoi(sep[7]);
		exp = atoi(sep[8]);
		if (level == target_level)break;
	}
	if (level != target_level)printf("該当するステータスがありません:%s,%dレベル",name,target_level);


	character[id].base_strength = power;
	character[id].agility = agility;
	character[id].base_endurance = endurance;
	character[id].maxHP = HP;
	character[id].maxMP = MP;

	fclose(fp);
}

//装備品のステータスを反映させる
void set_Character_equip_status(int id, Character *character, char *wepon_name, char *armar_name, char *helmet_name, char *shield_name)
{
	FILE *fp;
	char filename[128];
	char *sep[128];
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
	int damageBase = (character[id].strength / 2 - character[target].endurance / 4);
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
			printf("＋――――――――――――――――――＋\n");
			printf("｜%sは凍てつく波動をとなえた　｜\n", playerName[id]);
			printf("＋――――――――――――――――――＋\n");
			for (int i = 0; i < fielddata.playernum; i++) {
				characters[i].strength = characters[i].base_strength;
				characters[i].endurance = characters[i].base_endurance;
				characters[i].bless = 1;
			}
			printf("＋――――――――――――――――――＋\n");
			printf("｜プレイヤー全員にかかっている　　　　｜\n");
			printf("｜良い効果が消えた　　　　　　　　　　｜\n");
			printf("＋――――――――――――――――――＋\n");
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
	character[id].maxHP = 7;
	character[id].HP = character[id].maxHP;
}
void suraimu_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage=enemy_dyrect_attack(id, character, target);
	message_disp(id,target,damage);
}

void kubinagaweasel_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 11;
	character[id].agility = 8;
	character[id].base_endurance = 9;
	character[id].maxHP = 16;
	character[id].HP = character[id].maxHP;
}
void kubinagaweasel_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = enemy_dyrect_attack(id, character, target);//通常のみ
	message_disp(id, target, damage);
}

void prisoncat_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 24;
	character[id].agility = 20;
	character[id].base_endurance = 18;
	character[id].maxHP = 26;
	character[id].HP = character[id].maxHP;
}
void prisoncat_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = enemy_dyrect_attack(id, character, target);
	message_disp(id, target, damage);
}

void bubbleslime_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 12;
	character[id].agility = 7;
	character[id].base_endurance = 7;
	character[id].maxHP = 15;
	character[id].HP = character[id].maxHP;
}
void bubbleslime_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = enemy_dyrect_attack(id, character, target);//通常のみ
	message_disp(id, target, damage);
}

void ghost_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 15;
	character[id].agility = 14;
	character[id].base_endurance = 15;
	character[id].maxHP = 19;
	character[id].HP = character[id].maxHP;
}
void ghost_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = enemy_dyrect_attack(id, character, target);//通常のみ
	message_disp(id, target, damage);
}

void obakevcandle_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 20;
	character[id].agility = 13;
	character[id].base_endurance = 17;
	character[id].maxHP = 20;
	character[id].HP = character[id].maxHP;
}
void obakevcandle_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = enemy_dyrect_attack(id, character, target);
	message_disp(id, target, damage);
}

void oyabunghost_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 36;
	character[id].agility = 20;
	character[id].base_endurance = 50;
	character[id].maxHP = 200;
	character[id].HP = character[id].maxHP;
}
void oyabunghost_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = 0;//奇数ターン…通常。偶数ターン…通常・メラ・ギラ・ルカニ
	switch(rand() % 4) {
	case 0:damage = enemy_dyrect_attack(id, character, target);
				message_disp(id, target, damage); break;
		case 1:spell_mera(id, character, target); break;
		case 2:spell_gira(id, character, target); break;
		case 3:spell_rukani; break;
		default: break;
	}
}


void soilchild_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 22;
	character[id].agility = 13;
	character[id].base_endurance = 11;
	character[id].maxHP = 22;
	character[id].HP = character[id].maxHP;
}
void soilchild_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = enemy_dyrect_attack(id, character, target);
	message_disp(id, target, damage);
}

void meralizard_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 20;
	character[id].agility = 16;
	character[id].base_endurance = 20;
	character[id].maxHP = 24;
	character[id].HP = character[id].maxHP;
}
void meralizard_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = enemy_dyrect_attack(id, character, target);
	message_disp(id, target, damage);
}

void nightsplit_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 18;
	character[id].agility = 12;
	character[id].base_endurance = 14;
	character[id].maxHP = 17;
	character[id].HP = character[id].maxHP;
}
void nightsplit_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = enemy_dyrect_attack(id, character, target);
	message_disp(id, target, damage);
}

void gappurin_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 23;
	character[id].agility = 12;
	character[id].base_endurance = 17;
	character[id].maxHP = 19;
	character[id].HP = character[id].maxHP;
}
void gappurin_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = enemy_dyrect_attack(id, character, target);
	message_disp(id, target, damage);
}

void sabotenball_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 22;
	character[id].agility = 14;
	character[id].base_endurance = 14;
	character[id].maxHP = 22;
	character[id].HP = character[id].maxHP;
}
void sabotenball_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = enemy_dyrect_attack(id, character, target);
	message_disp(id, target, damage);
}

void witch_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 21;
	character[id].agility = 15;
	character[id].base_endurance = 17;
	character[id].maxHP = 20;
	character[id].HP = character[id].maxHP;
}
void witch_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = enemy_dyrect_attack(id, character, target);
	message_disp(id, target, damage);
}

void zairu_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 42;
	character[id].agility = 28;
	character[id].base_endurance = 30;
	character[id].maxHP = 140;
	character[id].HP = character[id].maxHP;
}
void zairu_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = 0;
	switch (rand()%3) {
	case 0:damage = enemy_dyrect_attack(id, character, target); break;
	case 1:spell_mahotora(id, character, target); break;
	case 2:spell_hoimi(id, character, target);  break;
	defalt:break;
	}
    
	message_disp(id, target, damage);
}

void snowqueen_init(int id, Character* character) {
	character[id].can_action = TRUE;
	character[id].base_strength = 50;
	character[id].agility = 18;
	character[id].base_endurance = 45;
	character[id].maxHP = 550;
	character[id].HP = character[id].maxHP;
}
void snowqueen_attack(int id, Character* character) {
	int target = get_random_player_id(character);
	int damage = 0;
	BOOL damage_up = FALSE;
	switch (rand() % 6) {
	case 0:damage = enemy_dyrect_attack(id, character, target); break;
	case 1:
		int damageMin = 13;
		int damageMax = 16;
		damage = damageMin + rand() % (damageMax - damageMin);
		printf("＋―――――――――――――――――＋\n");
		printf("｜%sはこおりつく息をはいた　｜\n", playerName[id]);
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
		damage_up= FALSE;
		break;
	case 2:damage = enemy_dyrect_attack(id, character, target); break;
	case 3:spell_hyado(id, character, target); break;
	case 4:spell_hoimi(id, character, target); break;
	case 5://息を吸い込む
		damage_up=TRUE;
		printf("＋―――――――――――――――――＋\n");
		printf("｜%sはおおきくいきをすいこんだ　｜\n", playerName[id]);
		printf("＋―――――――――――――――――＋\n");
		break;
	default:break;
	}
	message_disp(id, target, damage);
}

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

Enemy estark = { estark_init,estark_action};
Enemy *enemies[5];
//力，素早さ，身の守り，maxHP，maxMP


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

	character[id].base_strength = 55;
	character[id].agility = 120;
	character[id].base_endurance = 68;
	character[id].maxHP = 291;
	character[id].maxMP = 290;

	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength + 100;
	character[id].defense = character[id].endurance + 157;
	character[id].HP = character[id].maxHP;
	character[id].MP = character[id].maxMP;
	spell_copy(character[id].spells , presetspell2);

}
void rex_init(int id, Character* character, int level) {

	character[id].base_strength = 123;
	character[id].agility = 95;
	character[id].base_endurance = 50;
	character[id].maxHP = 324;
	character[id].maxMP = 180;

	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength + 130;
	character[id].defense = character[id].endurance + 235;
	character[id].HP = character[id].maxHP;
	character[id].MP = character[id].maxMP;
	spell_copy(character[id].spells, presetspell3);
}

void tabasa_init(int id, Character* character, int level) {
	character[id].base_strength = 50;
	character[id].agility = 115;
	character[id].base_endurance = 75;
	character[id].maxHP = 271;
	character[id].maxMP = 190;
	character[id].strength = character[id].base_strength;
	character[id].endurance = character[id].base_endurance;
	character[id].attack = character[id].strength + 100;
	character[id].defense = character[id].endurance + 180;
	character[id].HP = character[id].maxHP;
	character[id].MP = character[id].maxMP;
	spell_copy(character[id].spells, presetspell4);
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
	fielddata.fullcharacters++;
	fielddata.playernum++;
}
void add_Enemy(Enemy addCharacter, Character* character) {
	printf("enemynum=%d",fielddata.enemynum);
	strcpy(character[fielddata.fullcharacters].name, addCharacter.name);
	enemies[fielddata.enemynum] = &addCharacter;
	enemies[fielddata.enemynum]->init(fielddata.fullcharacters, character);
	fielddata.fullcharacters++;
	fielddata.enemynum++;
}




//キャラクター設定
void init(Character* character)
{
	field_init();
	//addCharacterすべてしてからaddEnemy
	add_character(hero, character);
	add_character(bianka, character);
	add_Enemy(kubinagaweasel, character);
	add_Enemy(prisoncat, character);
	add_Enemy(prisoncat, character);
}

void party0_init(Character* character) {
	field_init();
	//addCharacterすべてしてからaddEnemy
	add_character(hero, character);
	add_character(bianka, character);
	add_Enemy(suraimu, character);
	add_Enemy(suraimu, character);
	add_Enemy(suraimu, character);
}

void party1_init(Character* character) {
	field_init();
	//addCharacterすべてしてからaddEnemy
	add_character(hero, character);
	add_character(bianka, character);
	add_Enemy(oyabunghost, character);
}
void party2_init(Character* character) {
	field_init();
	//addCharacterすべてしてからaddEnemy
	add_character(hero, character);
	add_character(bianka, character);
	add_Enemy(meralizard, character);
	add_Enemy(soilchild, character);
	add_Enemy(nightsplit, character);
}
void party3_init(Character* character) {
	field_init();
	//addCharacterすべてしてからaddEnemy
	add_character(hero, character);
	add_character(bianka, character);
	add_Enemy(zairu, character);
}
void party4_init(Character* character) {
	field_init();
	//addCharacterすべてしてからaddEnemy
	add_character(hero, character);
	add_character(bianka, character);
	add_Enemy(snowqueen, character);
}




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



void status_check(Character* character) {
	// 毒判定
	status_poison(character);
	for (int i = 0; i < fielddata.playernum; i++) {
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
	int agility[10];
	for (int i = 0; i < fielddata.fullcharacters; i++)
		agility[i] = characters[i].agility;

	int agility_id[10];


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
			suraimu.attack(p_turn,characters);
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
	}
}