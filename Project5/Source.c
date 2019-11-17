#define _CRT_SECURE_NO_WARNINGS

#include "Header.h"

#include<time.h>
#include<windows.h>

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>




#define printf //

char playerName[][5 * 2 + 1] =
{
	" 主人公 ",
	"ビアンカ",
	"レックス",
	" タバサ ",
};

char enemyName[][5 * 2 + 1] =
{
	"エスターク"
};

enum commandFirst
{
	COMMAND_ATTACK,
	COMMAND_SPELL,
	COMMAND_TOOL,
	COMMAND_MAX
};
char commandFirst[][4 * 2 + 1] =
{
	"こうげき",		//COMMAND_ATTACK
	"じゅもん",		//COMMAND_SPELL
	"　どうぐ",		//COMMAND_TOOL
};

enum detailSpell1
{
	SPELL1_HOIMI,
	SPELL1_KIARI,
	SPELL1_BAGI,
	SPELL1_SUKARA,
	SPELL1_BEHOIMI,
	SPELL1_BAGIMA,
	SPELL1_BEHOMA,
	SPELL1_ZAORARU,
	SPELL1_MEGAZARU,
	SPELL1_BAGIKUROSU,
	SPELL1_MAX
};
char detailSpell1[][8 * 2 + 1] =
{
	"　　ホイミ(3)",		//0
	"　キアリー(2)",		//1
	"　　　バギ(2)",		//2　
	"　　スカラ(2)",		//3
	"　ベホイミ(5)",		//4
	"　　バギマ(4)",		//5
	"　  ベホマ(7)",		//6
	" ザオラル(10)",			//7
	"メガザル(all)",		//8
	"バギクロス(8)"			//9
};
int SpellMP1[10] = { 3,2,2,2,5,4,7,10,0,8 };//Spellの消費MP
BOOL SelectTargetSpell1[10] = { TRUE,TRUE,FALSE,TRUE,TRUE,FALSE,TRUE,TRUE };//0,1,3,4,6,7番目のスペルは対象を選ぶ

enum detailSpell2
{
	SPELL2_MERA,
	SPELL2_GIRA,
	SPELL2_BAIKIRUTO,
	SPELL2_BEGIRAMA,
	SPELL2_MERAMI,
	SPELL2_BEGIRAGON,
	SPELL2_MERAZOMA,
	SPELL2_MAX
};
char detailSpell2[][8 * 2 + 1]=
{
	"　　　 メラ(2)",		//0
	"　　　 ギラ(4)",		//1
	" バイキルト(6)",		//2
	"　 ベギラマ(6)",		//3
	"　　 メラミ(4)",		//4
	"ベギラゴン(10)",		//5
	"メラゾーマ(10)",		//6
};
int SpellMP2[10] = { 2,4,6,6,4,10,10 };
BOOL SelectTargetSpell2[10] = { FALSE,TRUE };//0,1,3,4,6,7番目のスペルは対象を選ぶ

enum detailSpell3
{
	SPELL3_SUKURUTO,
	SPELL3_BEHOIMI,
	SPELL3_KIARIKU,
	SPELL3_BEHOMA,
	SPELL3_FUBAHA,
	SPELL3_RAIDEIN,
	SPELL3_ZAORIKU,
	SPELL3_BEHOMARA,
	SPELL3_GIGADEIN,
	SPELL3_MINADEIN,
	SPELL3_MAX
};
char detailSpell3[][8 * 2 + 1]=
{
	"　 　スクルト(3)",		//0
	"　 　ベホイミ(5)",		//1
	"　 　キアリク(2)",		//2
	"　　 　ベホマ(7)",		//3
	"　 　フバーハ(3)",		//4
	" 　ライデイン(6)",		//5
	"　　ザオリク(20)",		//6
	"　ベホマラー(18)",		//7
	"　ギガデイン(15)",		//8
	"ミナデイン(ev10)"		//9
};
int SpellMP3[10] = { 3,5,2,7,3,6,20,18,15,10 };
BOOL SelectTargetSpell3[10] = { FALSE,TRUE,FALSE,TRUE,FALSE,FALSE,TRUE };//0,1,3,4,6,7番目のスペルは対象を選ぶ

enum detailSpell4
{
	SPELL4_HYADO,
	SPELL4_IO,
	SPELL4_HYADARUKO,
	SPELL4_BAIKIRUTO,
	SPELL4_RUKANAN,
	SPELL4_IORA,
	SPELL4_MAHYADO,
	SPELL4_DORAGORAMU,
	SPELL4_IONAZUN,
	SPELL4_MAX
};
char detailSpell4[][8 * 2 + 1]=
{
	"　　 ヒャド(3)",		//0
	"　　　 イオ(5)",		//1
	" ヒャダルコ(5)",		//2
	" バイキルト(6)",		//3
	"　 ルカナン(4)",		//4
	"　　 イオラ(8)",		//5
	"　マヒャド(12)",		//6
	"ドラゴラム(18)",		//7
	"イオナズン(15)"		//8
};
int SpellMP4[10] = { 3,5,5,6,4,8,12,18,15 };
BOOL SelectTargetSpell4[10] = { FALSE,FALSE,FALSE,TRUE };//0,1,3,4,6,7番目のスペルは対象を選ぶ

enum spell_targetName
{
	NAME_PLAYER1,
	NAME_PLAYER2,
	NAME_PLAYER3,
	NAME_PLAYER4,
	NAME_MAX
};
char spell_targetName[][5 * 2 + 1] =
{
	"　主人公",
	"ビアンカ",
	"レックス",
	"　タバサ"
};








enum contentTool
{
	CONTENT_DORUM,
	CONTENT_MAX
};
char contentTool[][10 * 2 + 1] =
{
	"　たたかいのドラム"
};



void display()
{}



//力，素早さ，身の守り，maxHP，maxMP

void env_init() {
	srand((unsigned)time(NULL));
}

void init(Character* character)
{
	character[0].base_strength = 149;
	character[0].agility = 102;
	character[0].base_endurance = 45;
	character[0].maxHP = 340;
	character[0].maxMP = 170;

	character[1].base_strength = 55;
	character[1].agility = 120;
	character[1].base_endurance = 68;
	character[1].maxHP = 291;
	character[1].maxMP = 290;

	character[2].base_strength = 123;
	character[2].agility = 95;
	character[2].base_endurance = 50;
	character[2].maxHP = 324;
	character[2].maxMP = 180;


	character[3].base_strength = 50;
	character[3].agility = 115;
	character[3].base_endurance = 75;
	character[3].maxHP = 271;
	character[3].maxMP = 190;


	character[4].base_strength = 450;
	character[4].agility = 85;
	character[4].base_endurance = 250;
	character[4].maxHP = 9000;

	character[0].strength = character[0].base_strength;
	character[0].endurance = character[0].base_endurance;
	character[0].attack = character[0].strength + 130;
	character[0].defense = character[0].endurance + 235;
	character[0].HP = character[0].maxHP;
	character[0].MP = character[0].maxMP;
	SpellData spelldata = { detailSpell1,SpellMP1,SelectTargetSpell1,SPELL1_MAX };
	character[0].spells = spelldata;
	character[1].strength = character[1].base_strength;
	character[1].endurance = character[1].base_endurance;
	character[1].attack = character[1].strength + 100;
	character[1].defense = character[1].endurance + 157;
	character[1].HP = character[1].maxHP;
	character[1].MP = character[1].maxMP;
	SpellData spelldata2 = { detailSpell2,SpellMP2,SelectTargetSpell2,SPELL2_MAX };
	character[1].spells = spelldata2;
	character[2].strength = character[2].base_strength;
	character[2].endurance = character[2].base_endurance;
	character[2].attack = character[2].strength + 130;
	character[2].defense = character[2].endurance + 235;
	character[2].HP = character[2].maxHP;
	character[2].MP = character[2].maxMP;
	SpellData spelldata3 = { detailSpell3,SpellMP3,SelectTargetSpell3,SPELL3_MAX };
	character[2].spells = spelldata3;
	character[3].strength = character[3].base_strength;
	character[3].endurance = character[3].base_endurance;
	character[3].attack = character[3].strength + 100;
	character[3].defense = character[3].endurance + 180;
	character[3].HP = character[3].maxHP;
	character[3].MP = character[3].maxMP;
	SpellData spelldata4 = { detailSpell4,SpellMP4,SelectTargetSpell4,SPELL4_MAX };
	character[3].spells = spelldata4;
	character[4].HP = character[4].maxHP;
	character[4].can_action = TRUE;


}






void status_poison(Character *character)
{
	for (int i = 0; i < 4; i++)
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
	for (int i = 0; i < 4; i++) {
		if (character[i].HP == 0 || character[i].sleep || character[i].paralysis) {
			character[i].action = 0;
			character[i].can_action = FALSE;
		}
		else
			character[i].can_action = TRUE;
	}
}




void spell_hoimi(int playerId,Character* character) {
	int cureMin = 30;
	int cureMax = 40;
	int cure = cureMin + rand() % (cureMax - cureMin);
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはホイミをとなえた　　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	character[playerId].MP -= 3;
	character[character[playerId].action_spell_target].HP += cure;
	if (character[character[playerId].action_spell_target].HP > character[character[playerId].action_spell_target].maxHP)
		character[character[playerId].action_spell_target].HP = character[character[playerId].action_spell_target].maxHP;
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはHPが%dかいふくした　｜\n", playerName[character[playerId].action_spell_target], cure);
	printf("＋―――――――――――――――――＋\n");
}


void spell_kiarii(int playerId,Character* character) {
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはキアリーをとなえた　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	character[playerId].MP -= 2;
	character[character[playerId].action_spell_target].poison = 0;
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sのドクをけしさった　　　｜\n", playerName[character[0].action_spell_target]);
	printf("＋―――――――――――――――――＋\n");
}


void spell_bagi(int playerId,Character* character) {
	int m_damageMin = 8;
	int m_damageMax = 24;
	int m_damage = m_damageMin + rand() % (m_damageMax - m_damageMin);
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはバギをとなえた　　　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	character[playerId].MP -= 2;
	character[4].HP -= m_damage;
	printf("＋―――――――――――――――――――――――――＋\n");
	printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[playerId], enemyName[0], m_damage);
	printf("＋―――――――――――――――――――――――――＋\n");

}

void spell_sukara(int playerId,Character* character) {
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはスカラをとなえた　　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	character[playerId].MP -= 2;
	if (character[character[playerId].action_spell_target].endurance >= character[character[playerId].action_spell_target].base_endurance * 2)
		character[character[playerId].action_spell_target].endurance = character[character[playerId].action_spell_target].endurance;
	else
		character[character[playerId].action_spell_target].endurance += character[character[playerId].action_spell_target].base_endurance / 2;
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sのみのまもりがあがった　｜\n", playerName[character[playerId].action_spell_target]);
	printf("＋―――――――――――――――――＋\n");
}

void spell_behoimi(int playerId,Character* character) {
	int cureMin = 75;
	int cureMax = 95;
	int cure = cureMin + rand() % (cureMax - cureMin);
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはべホイミをとなえた　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	character[playerId].MP -= 5;
	character[character[playerId].action_spell_target].HP += cure;
	if (character[character[playerId].action_spell_target].HP > character[character[playerId].action_spell_target].maxHP)
		character[character[playerId].action_spell_target].HP = character[character[playerId].action_spell_target].maxHP;
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはHPが%dかいふくした　｜\n", playerName[character[playerId].action_spell_target], cure);
	printf("＋―――――――――――――――――＋\n");
}

void spell_bagima(int playerId,Character* character) {
	int m_damageMin = 25;
	int m_damageMax = 55;
	int m_damage = m_damageMin + rand() % (m_damageMax - m_damageMin);
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはバギマをとなえた　　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	character[playerId].MP -= 4;
	character[4].HP -= m_damage;
	printf("＋―――――――――――――――――――――――――＋\n");
	printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[playerId], enemyName[0], m_damage);
	printf("＋―――――――――――――――――――――――――＋\n");
}

void spell_behoma(int playerId,Character* character) {
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはベホマをとなえた　　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	character[playerId].MP -= 7;
	character[character[playerId].action_spell_target].HP = character[character[playerId].action_spell_target].maxHP;
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはHPがぜんかいふくした　｜\n", playerName[character[playerId].action_spell_target]);
	printf("＋―――――――――――――――――＋\n");
}

void spell_zaoraru(int playerId,Character* character) {
	int keep;
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはザオラルをとなえた　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	character[playerId].MP -= 10;
	if (character[character[playerId].action_spell_target].HP == 0)
	{
		switch (keep = rand() % 2)
		{
		case 0: character[character[playerId].action_spell_target].HP = character[character[playerId].action_spell_target].maxHP / 2;
			break;
		case 1:
			break;
		}

		if (keep == 0)
		{
			printf("＋―――――――――――――――――＋\n");
			printf("｜%sはいきかえった　　　　　｜\n", playerName[character[playerId].action_spell_target]);
			printf("＋―――――――――――――――――＋\n");
		}
		else if (keep == 1)
		{
			printf("＋―――――――――――――――――＋\n");
			printf("｜しかし、失敗した　　　　　　　　　｜\n");
			printf("＋―――――――――――――――――＋\n");
		}

	}
	else if (character[character[playerId].action_spell_target].HP != 0)
	{
		printf("＋―――――――――――――――――＋\n");
		printf("｜しかし、%sはいきている　　｜\n", playerName[character[playerId].action_spell_target]);
		printf("＋―――――――――――――――――＋\n");
	}
}

void spell_megazaru(int playerId,Character* character) {
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはメガザルをとなえた　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	character[playerId].HP = 0;
	character[playerId].MP = 0;
	for (int i = 0; i < 4; i++) {
		if (i != playerId) {
			character[i].HP = character[i].maxHP;
		}
	}
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはMPが0になり死亡した　　｜\n", playerName[playerId]);
	printf("｜ぜんいんが、かんぜんかいふくした　｜\n");
	printf("＋―――――――――――――――――＋\n");
}

void spell_bagikurosu(int playerId,Character* character) {
	int m_damageMin = 80;
	int m_damageMax = 180;
	int m_damage = m_damageMin + rand() % (m_damageMax - m_damageMin);
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはバギクロスをとなえた　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	character[playerId].MP -= 8;
	character[4].HP -= m_damage;
	printf("＋―――――――――――――――――――――――――＋\n");
	printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[playerId], enemyName[0], m_damage);
	printf("＋―――――――――――――――――――――――――＋\n");
}

void spell_mera(int playerId,Character* character) {
	int m_damageMin = 12;
	int m_damageMax = 15;
	int m_damage = m_damageMin + rand() % (m_damageMax - m_damageMin);
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはメラをとなえた　　　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	character[playerId].MP -= 2;
	character[4].HP -= m_damage;
	printf("＋―――――――――――――――――――――――――＋\n");
	printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[playerId], enemyName[0], m_damage);
	printf("＋―――――――――――――――――――――――――＋\n");
}


void spell_gira(int playerId,Character* character) {
	int m_damageMin = 16;
	int m_damageMax = 24;
	int m_damage = m_damageMin + rand() % (m_damageMax - m_damageMin);
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはギラをとなえた　　　　｜\n", playerName[1]);
	printf("＋―――――――――――――――――＋\n");
	character[1].MP -= 4;
	character[4].HP -= m_damage;
	printf("＋―――――――――――――――――――――――――＋\n");
	printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[1], enemyName[0], m_damage);
	printf("＋―――――――――――――――――――――――――＋\n");

}

void spell_baikiruto(int playerId,Character* character) {
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

void spell_begirama(int playerId,Character* character) {
	int m_damageMin = 30;
	int m_damageMax = 42;
	int m_damage = m_damageMin + rand() % (m_damageMax - m_damageMin);
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはベギラマをとなえた　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	character[playerId].MP -= 6;
	character[4].HP -= m_damage;
	printf("＋―――――――――――――――――――――――――＋\n");
	printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[playerId], enemyName[0], m_damage);
	printf("＋―――――――――――――――――――――――――＋\n");
}

void spell_merami(int playerId,Character* character) {
	int m_damageMin = 70;
	int m_damageMax = 90;
	int m_damage = m_damageMin + rand() % (m_damageMax - m_damageMin);
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはメラミをとなえた　　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	character[playerId].MP -= 4;
	character[4].HP -= m_damage;
	printf("＋―――――――――――――――――――――――――＋\n");
	printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[playerId], enemyName[0], m_damage);
	printf("＋―――――――――――――――――――――――――＋\n");
}

void spell_begiragon(int playerId,Character* character) {
	int m_damageMin = 88;
	int m_damageMax = 112;
	int m_damage = m_damageMin + rand() % (m_damageMax - m_damageMin);
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはベギラゴンをとなえた　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	character[1].MP -= 10;
	character[4].HP -= m_damage;
	printf("＋―――――――――――――――――――――――――＋\n");
	printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[playerId], enemyName[0], m_damage);
	printf("＋―――――――――――――――――――――――――＋\n");
}


void spell_merazooma(int playerId,Character* character) {
	int m_damageMin = 180;
	int m_damageMax = 200;
	int m_damage = m_damageMin + rand() % (m_damageMax - m_damageMin);
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはメラゾーマをとなえた　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	character[playerId].MP -= 2;
	character[4].HP -= m_damage;
	printf("＋―――――――――――――――――――――――――＋\n");
	printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[playerId], enemyName[0], m_damage);
	printf("＋―――――――――――――――――――――――――＋\n");
}



void spell_sukuruto(int playerId,Character* character) {
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

void spell_kiariku(int playerId,Character* character) {
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはキアリクをとなえた　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	character[playerId].MP -= 2;
	for (int i = 0; i < 4; i++) {
		if (character[i].paralysis == 0)continue;
		character[i].paralysis = 0;
		printf("＋―――――――――――――――――＋\n");
		printf("｜%sのマヒをけしさった　　　｜\n", playerName[character[0].action_spell_target]);
		printf("＋―――――――――――――――――＋\n");
	}
}

void spell_hubaaha(int playerId,Character* character) {
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはフバーハをとなえた　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	character[playerId].MP -= 3;
	for(int i=0;i<4;i++)
		character[i].bless = 1.0 / 2;
	printf("＋―――――――――――――――――＋\n");
	printf("｜ぜんいんのブレスたいせいがあがった｜\n");
	printf("＋―――――――――――――――――＋\n");
}

void spell_raidein(int playerId,Character* character) {
	int m_damageMin = 70;
	int m_damageMax = 90;
	int m_damage = m_damageMin + rand() % (m_damageMax - m_damageMin);
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはライデインをとなえた　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	character[playerId].MP -= 6;
	character[4].HP -= m_damage;
	printf("＋―――――――――――――――――――――――――＋\n");
	printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[playerId], enemyName[0], m_damage);
	printf("＋―――――――――――――――――――――――――＋\n");
}

void spell_zaoriku(int playerId,Character* character) {
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはザオリクをとなえた　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	character[playerId].MP -= 20;
	if (character[character[playerId].action_spell_target].HP == 0)
	{
		character[character[playerId].action_spell_target].HP = character[character[playerId].action_spell_target].maxHP;
		printf("＋――――――――――――――――――――――――＋\n");
		printf("｜%sはいきかえって、かんぜんかいふくした　｜\n", playerName[character[playerId].action_spell_target]);
		printf("＋――――――――――――――――――――――――＋\n");
	}
	else if (character[character[playerId].action_spell_target].HP != 0)
	{
		printf("＋―――――――――――――――――＋\n");
		printf("｜しかし、%sはいきている　　｜\n", playerName[character[playerId].action_spell_target]);
		printf("＋―――――――――――――――――＋\n");
	}

}

void spell_behomaraa(int playerId,Character* character) {
	int cureMin = 100;
	int cureMax = 120;
	int cure = cureMin + rand() % (cureMax - cureMin);
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはベホマラーをとなえた　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	character[playerId].MP -= 18;
	for (int i = 0; i < 4; i++) {
		character[i].HP += cure;
		if (character[i].HP > character[i].maxHP)
			character[i].HP = character[i].maxHP;
	}
	printf("＋―――――――――――――――――＋\n");
	printf("｜ぜんいんのHPがかいふくした　　　　｜\n");
	printf("＋―――――――――――――――――＋\n");
}

void spell_gigadein(int playerId,Character* character) {
	int m_damageMin = 175;
	int m_damageMax = 225;
	int m_damage = m_damageMin + rand() % (m_damageMax - m_damageMin);
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはギガデインをとなえた　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	character[playerId].MP -= 15;
	character[playerId].HP -= m_damage;
	printf("＋―――――――――――――――――――――――――＋\n");
	printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[playerId], enemyName[0], m_damage);
	printf("＋―――――――――――――――――――――――――＋\n");
}

void spell_minadein(int playerId,Character* character) {
	int m_damageMin = 300;
	int m_damageMax = 350;
	int m_damage = m_damageMin + rand() % (m_damageMax - m_damageMin);

	for (int i = 0; i < 4; i++)character[i].MP -= 10;
	printf("＋―――――――――――――――――――＋\n");
	printf("｜%sはぜんいんからちからをあつめ｜\n", playerName[2]);
	printf("｜ミナデインをとなえた　　　　　　　　　｜\n");
	printf("＋―――――――――――――――――――＋\n");
	character[4].HP -= m_damage;
	printf("＋―――――――――――――――――――＋\n");
	printf("｜%sに%dのダメージをあたえた　｜\n", enemyName[0], m_damage);
	printf("＋―――――――――――――――――――＋\n");

}

void spell_hyado(int playerId,Character* character) {
	int m_damageMin = 25;
	int m_damageMax = 35;
	int m_damage = m_damageMin + rand() % (m_damageMax - m_damageMin);
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはヒャドをとなえた　　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	character[playerId].MP -= 3;
	character[4].HP -= m_damage;
	printf("＋―――――――――――――――――――――――――＋\n");
	printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[playerId], enemyName[0], m_damage);
	printf("＋―――――――――――――――――――――――――＋\n");
}

void spell_io(int playerId,Character* character) {
	int m_damageMin = 20;
	int m_damageMax = 30;
	int m_damage = m_damageMin + rand() % (m_damageMax - m_damageMin);
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはイオをとなえた　　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	character[playerId].MP -= 5;
	character[4].HP -= m_damage;
	printf("＋―――――――――――――――――――――――――＋\n");
	printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[playerId], enemyName[0], m_damage);
	printf("＋―――――――――――――――――――――――――＋\n");
}

void spell_hyadaruko(int playerId,Character* character) {
	int m_damageMin = 42;
	int m_damageMax = 58;
	int m_damage = m_damageMin + rand() % (m_damageMax - m_damageMin);
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはヒャダルコをとなえた　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	character[playerId].MP -= 5;
	character[4].HP -= m_damage;
	printf("＋―――――――――――――――――――――――――＋\n");
	printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[playerId], enemyName[0], m_damage);
	printf("＋―――――――――――――――――――――――――＋\n");
}

void spell_runakan(int playerId,Character* character) {
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはルカナンをとなえた　　｜\n", enemyName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	character[playerId].MP -= 4;
	if (character[4].base_endurance == 0)
	{
		printf("＋――――――――――――――――――――＋\n");
		printf("｜%sのみのまもりはもうさがらない｜\n", enemyName[4]);
		printf("＋――――――――――――――――――――＋\n");
	}
	else
	{
		character[4].base_endurance -= character[4].base_endurance / 2;
		printf("＋―――――――――――――――――＋\n");
		printf("｜%sのみのまもりがさがった｜\n", playerName[4]);
		printf("＋―――――――――――――――――＋\n");
	}
}
void spell_iora(int playerId,Character* character) {
	int m_damageMin = 52;
	int m_damageMax = 68;
	int m_damage = m_damageMin + rand() % (m_damageMax - m_damageMin);
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはイオラをとなえた　　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	character[playerId].MP -= 8;
	character[4].HP -= m_damage;
	printf("＋―――――――――――――――――――――――――＋\n");
	printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[playerId], enemyName[0], m_damage);
	printf("＋―――――――――――――――――――――――――＋\n");
}

void spell_mahyado(int playerId,Character* character) {
	int m_damageMin = 80;
	int m_damageMax = 104;
	int m_damage = m_damageMin + rand() % (m_damageMax - m_damageMin);
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはマヒャドをとなえた　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	character[playerId].MP -= 12;
	character[4].HP -= m_damage;
	printf("＋―――――――――――――――――――――――――＋\n");
	printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[playerId], enemyName[0], m_damage);
	printf("＋―――――――――――――――――――――――――＋\n");
}

void spell_doragoramu(int playerId,Character* character) {
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはドラゴラムをとなえた　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	character[playerId].MP -= 18;
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはドラゴンになった　　　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");

	character[playerId].dragon = 1;

	//ドラゴンのデフォルトアクション
	int damageBase;
	int damageMin;
	int damageMax;
	int damage;

	switch (rand() % 3)
	{
	case 0:
		damageBase = character[playerId].attack / 2 - character[4].base_endurance / 4;
		damageMin = damageBase * 7 / 8 + 60;
		damageMax = damageBase * 9 / 8 + 60;
		damage = damageMin + rand() % (damageMax - damageMin);
		printf("＋―――――――――――――――――――＋\n");
		printf("｜%sはするどいツメでこうげきした｜\n", playerName[playerId]);
		printf("＋―――――――――――――――――――＋\n");
		character[4].HP -= damage;
		printf("＋――――――――――――――――――＋\n");
		printf("｜%sは%dのダメージをうけた｜\n", enemyName[0], damage);
		printf("＋――――――――――――――――――＋\n");
		break;
	default:
		damageMin = 65;
		damageMax = 85;
		damage = damageMin + rand() % (damageMax - damageMin);
		printf("＋――――――――――――――＋\n");
		printf("｜%sはほのおをはいた　｜\n", playerName[playerId]);
		printf("＋――――――――――――――＋\n");
		character[4].HP -= damage;
		printf("＋――――――――――――――――――＋\n");
		printf("｜%sは%dのダメージをうけた｜\n", enemyName[0], damage);
		printf("＋――――――――――――――――――＋\n");
		break;
	}
}

void spell_ionazun(int playerId,Character* character) {
	int m_damageMin = 120;
	int m_damageMax = 160;
	int m_damage = m_damageMin + rand() % (m_damageMax - m_damageMin);
	printf("＋―――――――――――――――――＋\n");
	printf("｜%sはイオナズンをとなえた　｜\n", playerName[playerId]);
	printf("＋―――――――――――――――――＋\n");
	character[playerId].MP -= 15;
	character[4].HP -= m_damage;
	printf("＋―――――――――――――――――――――――――＋\n");
	printf("｜%sは%sに%dのダメージをあたえた　　｜\n", playerName[playerId], enemyName[0], m_damage);
	printf("＋―――――――――――――――――――――――――＋\n");
}




void tool_tatakainodoramu(int playerId,Character* character) {
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








void spell(int p_turn, BOOL wait, BOOL disp,Character* character)
{
	if (disp)display();

	if (p_turn == 0)
	{
		if (character[0].action == 1)
		{
			if (character[0].action_spell == 0)
			{
				spell_hoimi(0,character);
			}
			else if (character[0].action_spell == 1)
			{
				spell_kiarii(0,character);
			}
			else if (character[0].action_spell == 2)
			{
				spell_bagi(0, character);
			}
			else if (character[0].action_spell == 3)
			{
				spell_sukara(0, character);
			}
			else if (character[0].action_spell == 4)
			{
				spell_behoimi(0, character);
			}
			else if (character[0].action_spell == 5)
			{
				spell_bagima(0, character);
			}
			else if (character[0].action_spell == 6)
			{
				spell_behoma(0, character);
			}
			else if (character[0].action_spell == 7)
			{
				spell_zaoraru(0, character);
			}
			else if (character[0].action_spell == 8)
			{
				spell_megazaru(0, character);
			}
			else if (character[0].action_spell == 9)
			{
				spell_bagikurosu(0, character);
			}
		}
	}
	else if (p_turn == 1)
	{
		if (character[1].action == 1)
		{
			if (character[1].action_spell == 0)
			{
				spell_mera(1, character);
			}
			else if (character[1].action_spell == 1)
			{
				spell_gira(1, character);
			}
			else if (character[1].action_spell == 2)
			{
				spell_baikiruto(1, character);
			}
			else if (character[1].action_spell == 3)
			{
				spell_begirama(1, character);
			}
			else if (character[1].action_spell == 4)
			{
				spell_merami(1, character);
			}
			else if (character[1].action_spell == 5)
			{
				spell_begiragon(1, character);
			}
			else if (character[1].action_spell == 6)
			{
				spell_merazooma(1, character);
			}
		}
	}
	else if (p_turn == 2)
	{
		if (character[2].action == 1)
		{
			if (character[2].action_spell == 0)
			{
				spell_sukuruto(2, character);
			}
			else if (character[2].action_spell == 1)
			{
				spell_behoimi(2, character);
			}
			else if (character[2].action_spell == 2)
			{
				spell_kiariku(2, character);
			}
			else if (character[2].action_spell == 3)
			{
				spell_behoma(2, character);
			}
			else if (character[2].action_spell == 4)
			{
				spell_hubaaha(2, character);
			}
			else if (character[2].action_spell == 5)
			{
				spell_raidein(2, character);
			}
			else if (character[2].action_spell == 6)
			{
				spell_zaoriku(2, character);
			}
			else if (character[2].action_spell == 7)
			{
				spell_behomaraa(2, character);
			}
			else if (character[2].action_spell == 8)
			{
				spell_gigadein(2, character);
			}
			else if (character[2].action_spell == 9)
			{
				spell_minadein(2, character);
			}
		}
	}
	else if (p_turn == 3)
	{
		if (character[3].action == 1)
		{
			if (character[3].action_spell == 0)
			{
				spell_hyado(3, character);
			}
			else if (character[3].action_spell == 1)
			{
				spell_io(3, character);
			}
			else if (character[3].action_spell == 2)
			{
				spell_hyadaruko(3, character);
			}
			else if (character[3].action_spell == 3)
			{
				spell_baikiruto(3, character);
			}
			else if (character[3].action_spell == 4)
			{
				spell_runakan(3, character);
			}
			else if (character[3].action_spell == 5)
			{
				spell_iora(3, character);
			}
			else if (character[3].action_spell == 6)
			{
				spell_mahyado(3, character);
			}
			else if (character[3].action_spell == 7)
			{
				spell_doragoramu(3, character);
			}
			else if (character[3].action_spell == 8)
			{
				spell_ionazun(3, character);
			}
		}
	}
	if (wait)_getch();
}




// 道具
void tool(int playerId, BOOL wait, BOOL disp,Character* character)
{
	if (disp)display();
	if (character[playerId].action_tool == 0)
	{
		tool_tatakainodoramu(playerId,character);
	}
	if (wait)_getch();
}





void battle_main(Character* characters, BOOL wait, BOOL disp) {
	// すばやさの比較
	int agility[] =
	{
		characters[0].agility,
		characters[1].agility,
		characters[2].agility,
		characters[3].agility,
		characters[4].agility
	};



	//int agility[5];
	int action_players = 0;
	for (int i = 0; i < 5; i++)
		if (characters[i].can_action == TRUE)
		{
			agility[action_players] = characters[i].agility;
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
	int em_damageMin;
	int em_damageMax;
	int em_damage;
	int keep;
	int b_turn = 0;			// バトルターン
	int agility_count = 0;	// 行動カウント

							// バトル
	while (1)
	{
		int p_turn = -1;
		int e_turn = -1;
		for (int i = 0; i < 4; i++) {
			if (agility[agility_count] == characters[i].agility)p_turn = i;
		}
		if (agility[agility_count] == characters[4].agility)
			e_turn = 1;

		if (characters[p_turn].dragon == 1)
		{
			if (disp)display();
			switch (rand() % 3)
			{
			case 0:
				damageBase = characters[p_turn].attack / 2 - characters[4].base_endurance / 4;
				damageMin = damageBase * 7 / 8 + 60;
				damageMax = damageBase * 9 / 8 + 60;
				damage = damageMin + rand() % (damageMax - damageMin);
				printf("＋―――――――――――――――――――＋\n");
				printf("｜%sはするどいツメでこうげきした｜\n", playerName[p_turn]);
				printf("＋―――――――――――――――――――＋\n");
				characters[4].HP -= damage;
				printf("＋――――――――――――――――――＋\n");
				printf("｜%sは%dのダメージをうけた｜\n", enemyName[0], damage);
				printf("＋――――――――――――――――――＋\n");
				break;
			default:
				damageMin = 65;
				damageMax = 85;
				damage = damageMin + rand() % (damageMax - damageMin);
				printf("＋――――――――――――――＋\n");
				printf("｜%sはほのおをはいた　｜\n", playerName[p_turn]);
				printf("＋――――――――――――――＋\n");
				characters[4].HP -= damage;
				printf("＋――――――――――――――――――＋\n");
				printf("｜%sは%dのダメージをうけた｜\n", enemyName[0], damage);
				printf("＋――――――――――――――――――＋\n");
				break;
			}
			if (wait)_getch();
			agility_count++;
			if (agility_count == action_players)
				break;
			else
				continue;
		}

		if (e_turn == 1)
		{
			// 2回攻撃
			int attack_count = 0;
			while (1)
			{
				switch (rand() % 6)
				{
				case 0:
					if (characters[0].HP == 0 && characters[1].HP == 0 && characters[2].HP == 0 && characters[3].HP == 0)break;
					while (1) {
						keep = rand() % 4;
						if (characters[keep].HP != 0)break;
					}
					damageBase = characters[4].base_strength / 2 - characters[keep].defense / 4;
					damageMin = damageBase * 7 / 8;
					damageMax = damageBase * 9 / 8;
					damage = damageMin + rand() % (damageMax - damageMin);
					if (disp)display();
					printf("＋―――――――――――――――――＋\n");
					printf("｜%sのこうげき　　　　　　　｜\n", enemyName[0]);
					printf("＋―――――――――――――――――＋\n");
					characters[keep].HP -= damage;
					if (characters[keep].HP < 0)
						characters[keep].HP = 0;
					printf("＋―――――――――――――――――＋\n");
					printf("｜%sは%sに　　　　　｜\n", enemyName[0], playerName[keep]);
					printf("｜%dのダメージを与えた　　　　　　｜\n", damage);
					printf("＋―――――――――――――――――＋\n");
					if (wait)_getch();
					break;
				case 1:
					em_damageMin = 72;
					em_damageMax = 88;
					if (disp)display();
					printf("＋―――――――――――――――――＋\n");
					printf("｜%sはイオナズンをとなえた　｜\n", enemyName[0]);
					printf("＋―――――――――――――――――＋\n");
					for (int i = 0; i < 4; i++)
					{
						em_damage = em_damageMin + rand() % (em_damageMax - em_damageMin);
						characters[i].HP -= em_damage;
						if (characters[i].HP < 0)
							characters[i].HP = 0;
					}
					printf("＋―――――――――――――――――＋\n");
					printf("｜%sはプレイヤー全員に　　　｜\n", enemyName[0]);
					printf("｜%dのダメージを与えた　　　　　　      ｜\n", em_damage);//yamato
					printf("＋―――――――――――――――――＋\n");
					if (wait)_getch();
					break;
				case 2:
					em_damageMin = 150;
					em_damageMax = 170;
					if (disp)display();
					printf("＋―――――――――――――――――＋\n");
					printf("｜%sは灼熱の炎をとなえた　　｜\n", enemyName[0]);
					printf("＋―――――――――――――――――＋\n");
					for (int i = 0; i < 4; i++)
					{
						em_damage = em_damageMin + rand() % (em_damageMax - em_damageMin);
						characters[i].HP -= em_damage * characters[i].bless;
						if (characters[i].HP < 0)
							characters[i].HP = 0;
					}
					printf("＋―――――――――――――――――＋\n");
					printf("｜%sはプレイヤー全員に　　　｜\n", enemyName[0]);
					printf("｜%dのダメージを与えた　　　　　　　　　｜\n", em_damage);//yamato
					printf("＋―――――――――――――――――＋\n");
					if (wait)_getch();
					break;
				case 3:
					em_damageMin = 120;
					em_damageMax = 140;
					if (disp)display();
					printf("＋―――――――――――――――――＋\n");
					printf("｜%sは輝く息をとなえた　　　｜\n", enemyName[0]);
					printf("＋―――――――――――――――――＋\n");
					for (int i = 0; i < 4; i++)
					{
						em_damage = em_damageMin + rand() % (em_damageMax - em_damageMin);
						characters[i].HP -= em_damage * characters[i].bless;
						if (characters[i].HP < 0)
							characters[i].HP = 0;
					}
					printf("＋―――――――――――――――――＋\n");
					printf("｜%sはプレイヤー全員に　　　｜\n", enemyName[0]);
					printf("｜%dのダメージを与えた　　　　　　｜\n", em_damage);//yamato
					printf("＋―――――――――――――――――＋\n");
					if (wait)_getch();
					break;
				case 4:
					keep = rand() % 4;
					em_damageMin = 92;
					em_damageMax = 128;
					em_damage = em_damageMin + rand() % (em_damageMax - em_damageMin);
					if (disp)display();
					printf("＋―――――――――――――――――＋\n");
					printf("｜%sはメラゾーマをとなえた　｜\n", enemyName[0]);
					printf("＋―――――――――――――――――＋\n");
					characters[keep].HP -= em_damage;
					if (characters[keep].HP < 0)
						characters[keep].HP = 0;
					printf("＋―――――――――――――――――＋\n");
					printf("｜%sは%sに　　　　　｜\n", enemyName[0], playerName[keep]);
					printf("｜%dのダメージを与えた　　　　　　｜\n", em_damage);//yamato
					printf("＋―――――――――――――――――＋\n");
					if (wait)_getch();
					break;
				case 5:
					if (disp)display();
					printf("＋――――――――――――――――――＋\n");
					printf("｜%sは凍てつく波動をとなえた　｜\n", enemyName[0]);
					printf("＋――――――――――――――――――＋\n");
					for (int i = 0; i < 4; i++) {
						characters[i].strength = characters[i].base_strength;
						characters[i].endurance = characters[i].base_endurance;
						characters[i].bless = 1;
					}
					printf("＋――――――――――――――――――＋\n");
					printf("｜プレイヤー全員にかかっている　　　　｜\n");
					printf("｜良い効果が消えた　　　　　　　　　　｜\n");
					printf("＋――――――――――――――――――＋\n");
					if (wait)_getch();
					break;
				}


				attack_count++;
				if (attack_count == 2)
				{
					attack_count = 0;
					e_turn = 0;
					break;
				}
			}
		}

		else
		{
			if (characters[p_turn].action == 0)
			{
				damageBase = characters[p_turn].attack / 2 - characters[4].base_endurance / 4;
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
					characters[4].HP -= c_damage;
					if (characters[4].HP < 0)
						characters[4].HP = 0;
					printf("｜%sは%sに　　　　　｜\n", playerName[p_turn], enemyName[0]);
					printf("｜%dのダメージを与えた　　　　　　　｜\n", c_damage);
					printf("＋―――――――――――――――――＋\n");
					if (wait)_getch();
				}
				else
				{
					characters[4].HP -= damage;
					if (characters[4].HP < 0)
						characters[4].HP = 0;
					if (disp)display();
					printf("＋―――――――――――――――――＋\n");
					printf("｜%sは%sに　　　　　｜\n", playerName[p_turn], enemyName[0]);
					printf("｜%dのダメージを与えた　　　　　　　｜\n", damage);
					printf("＋―――――――――――――――――＋\n");
					if (wait)_getch();
				}
			}
			else if (characters[p_turn].action == 1)
				spell(p_turn, wait, disp,characters);
			if (characters[4].HP < 0)
				characters[4].HP = 0;
			else if (characters[p_turn].action == 2)
				tool(p_turn, wait, disp,characters);
		}

		b_turn++;
		agility_count++;

		if (characters[4].HP == 0)
			break;
		else if (characters[0].HP == 0 && characters[1].HP == 0 && characters[2].HP == 0 && characters[3].HP == 0)
			break;
		else if (characters[0].paralysis == 1 && characters[1].paralysis == 1 && characters[2].paralysis == 1 && characters[3].paralysis == 1)
			break;
		if (agility_count == action_players)
			break;
	}
}



void input_action() {
}







