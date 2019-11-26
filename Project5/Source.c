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
	if (character[target].HP == 0)return -1;//�̗͂��Ȃ�
	int cure = cureMin + rand() % (cureMax - cureMin);

	character[target].HP += cure;
	if (character[target].HP > character[target].maxHP) {
		cure = character[target].HP - character[target].maxHP;
		character[target].HP = character[target].maxHP;
	}
	return cure;//����ɉ�
}

int base_spell_attack_single_target(int playerId, int target, Character* character, int damageMin, int damageMax) {
	if (character[target].HP == 0)return -1;//�̗͂��Ȃ�
	int damage = damageMin + rand() % (damageMax - damageMin);

	character[target].HP -= damage;
	if (character[target].HP < 0) {
		character[target].HP = 0;
	}

	return damage;//����ɉ�
}


//0�Ő����Ԃ���,1�Ŏ��s,2�͂܂������Ă���rand()%p==0�ŕ���
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
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�̓z�C�~���ƂȂ����@�@�@�b\n", playerName[playerId]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s��HP��%d�����ӂ������@�b\n",playerName[target], cure);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
}
Spell hoimi = { L"�z�C�~",3,TRUE,spell_hoimi};

void spell_kiarii(int playerId, Character* character, int target) {
	character[playerId].MP -= 2;
	character[target].poison = 0;
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�̓L�A���[���ƂȂ����@�@�b\n", playerName[playerId]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�̃h�N�������������@�@�@�b\n",playerName[target]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
}
Spell kiarii = { L"�L�A���[",2,TRUE,spell_kiarii};


void spell_bagi(int playerId, Character* character, int target) {
	int damage = base_spell_attack_single_target(playerId, target, character, 8, 24);
	character[playerId].MP -= 2;
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�̓o�M���ƂȂ����@�@�@�@�b\n", playerName[playerId]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s��%s��%d�̃_���[�W�����������@�@�b\n", playerName[playerId], playerName[target], damage);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
}
Spell bagi = { L"�o�M",2,TRUE,spell_bagi };


void spell_sukara(int playerId, Character* character, int target) {
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�̓X�J�����ƂȂ����@�@�@�b\n", playerName[playerId]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	character[playerId].MP -= 2;
	endurance_up(playerId, target, character);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�݂̂̂܂��肪���������@�b\n", playerName[target]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
}
Spell sukara = { L"�X�J��",2,TRUE,spell_sukara };

void spell_behoimi(int playerId, Character* character, int target) {
	int cure = base_spell_cure_single_target(playerId, target, character, 75, 95);
	character[playerId].MP -= 5;
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�͂׃z�C�~���ƂȂ����@�@�b\n", playerName[playerId]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s��HP��%d�����ӂ������@�b\n", playerName[target], cure);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
}
Spell behoimi = { L"�x�z�C�~",5,TRUE,spell_behoimi };

void spell_bagima(int playerId, Character* character, int target) {
	int damage = base_spell_attack_single_target(playerId, target, character, 25, 55);
	character[playerId].MP -= 4;
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�̓o�M�}���ƂȂ����@�@�@�b\n", playerName[playerId]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s��%s��%d�̃_���[�W�����������@�@�b\n", playerName[playerId], playerName[target], damage);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
}
Spell bagima = { L"�o�M�}",4,TRUE,spell_bagima };

void spell_behoma(int playerId, Character* character, int target) {
	character[playerId].MP -= 7;
	character[target].HP = character[target].maxHP;
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�̓x�z�}���ƂȂ����@�@�@�b\n", playerName[playerId]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s��HP�����񂩂��ӂ������@�b\n", playerName[target]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
}
Spell behoma = { L"�x�z�}",4,TRUE,spell_behoma };

void spell_zaoraru(int playerId, Character* character, int target) {
	int keep = revive(playerId, target, character, 2);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�̓U�I�������ƂȂ����@�@�b\n", playerName[playerId]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	character[playerId].MP -= 10;
	if (keep == 0) {
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
		printf("�b%s�͂������������@�@�@�@�@�b\n", playerName[target]);
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	}
	if (keep == -1) {
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
		printf("�b�������A���s�����@�@�@�@�@�@�@�@�@�b\n");
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	}
	if (keep == -2)
	{
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
		printf("�b�������A%s�͂����Ă���@�@�b\n", playerName[target]);
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	}
}
Spell zaoraru = { L"�U�I����",10,TRUE,spell_zaoraru };

void spell_megazaru(int playerId, Character* character, int target) {
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�̓��K�U�����ƂȂ����@�@�b\n", playerName[playerId]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	character[playerId].HP = 0;
	character[playerId].MP = 0;
	for (int i = 0; i < fielddata.playernum; i++) {
		if (i != playerId) {
			character[i].HP = character[i].maxHP;
		}
	}
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s��MP��0�ɂȂ莀�S�����@�@�b\n", playerName[playerId]);
	printf("�b���񂢂񂪁A���񂺂񂩂��ӂ������@�b\n");
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
}
Spell megazaru = { L"���K�U��",0,TRUE,spell_megazaru };

void spell_bagikurosu(int playerId, Character* character, int target) {
	int m_damage = base_spell_attack_single_target(playerId, target, character, 80, 180);
	character[playerId].MP -= 8;
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�̓o�M�N���X���ƂȂ����@�b\n", playerName[playerId]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s��%s��%d�̃_���[�W�����������@�@�b\n", playerName[playerId], playerName[target], m_damage);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
}
Spell bagikurosu = { L"�o�M�N���X",8,TRUE,spell_bagikurosu };

void spell_mera(int playerId, Character* character, int target) {
	int m_damage = base_spell_attack_single_target(playerId, target, character, 12, 15);
	character[playerId].MP -= 2;
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�̓������ƂȂ����@�@�@�@�b\n", playerName[playerId]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s��%s��%d�̃_���[�W�����������@�@�b\n", playerName[playerId], playerName[target], m_damage);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
}
Spell mera = { L"����",2,TRUE,spell_mera };


void spell_gira(int playerId, Character* character, int target) {
	int m_damage = base_spell_attack_single_target(playerId, target, character, 16, 24);
	character[playerId].MP -= 4;
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�̓M�����ƂȂ����@�@�@�@�b\n", playerName[playerId]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s��%s��%d�̃_���[�W�����������@�@�b\n", playerName[playerId], playerName[target], m_damage);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
}
Spell gira = { L"�M��",4,TRUE,spell_gira };


void spell_baikiruto(int playerId, Character* character, int target) {
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�̓o�C�L���g���ƂȂ����@�b\n", playerName[playerId]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	character[playerId].MP -= 6;
	if (character[character[playerId].action_spell_target].strength >= character[character[playerId].action_spell_target].base_strength * 2)
	{
		character[character[playerId].action_spell_target].strength = character[character[playerId].action_spell_target].strength;
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
		printf("�b�������A%s�̂�����͂���������Ȃ��@�b\n", playerName[character[playerId].action_spell_target]);
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	}
	else
	{
		character[character[playerId].action_spell_target].strength *= 2;
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
		printf("�b%s�͂����炪�΂��ɂȂ����@�b\n", playerName[character[playerId].action_spell_target]);
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	}
}
Spell baikiruto = { L"�o�C�L���g",6,TRUE,spell_baikiruto };

void spell_begirama(int playerId, Character* character, int target) {
	int m_damage = base_spell_attack_single_target(playerId, target, character, 30, 42);
	character[playerId].MP -= 6;
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�̓x�M���}���ƂȂ����@�@�b\n", playerName[playerId]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s��%s��%d�̃_���[�W�����������@�@�b\n", playerName[playerId], playerName[target], m_damage);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
}
Spell begirama = { L"�x�M���}",6,TRUE,spell_begirama };

void spell_merami(int playerId, Character* character, int target) {
	int m_damage = base_spell_attack_single_target(playerId, target, character, 70, 90);
	character[playerId].MP -= 4;
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�̓����~���ƂȂ����@�@�@�b\n", playerName[playerId]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s��%s��%d�̃_���[�W�����������@�@�b\n", playerName[playerId], playerName[target], m_damage);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
}
Spell merami = { L"�����~",4,TRUE,spell_merami };

void spell_begiragon(int playerId, Character* character, int target) {
	int m_damage = base_spell_attack_single_target(playerId, target, character, 88, 112);
	character[playerId].MP -= 10;
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�̓x�M���S�����ƂȂ����@�b\n", playerName[playerId]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s��%s��%d�̃_���[�W�����������@�@�b\n", playerName[playerId], playerName[target], m_damage);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
}
Spell begiragon = { L"�x�M���S��",10,TRUE,spell_begiragon };


void spell_merazooma(int playerId, Character* character, int target) {
	int m_damage = base_spell_attack_single_target(playerId, target, character, 180, 200);
	character[playerId].MP -= 2;
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�̓����]�[�}���ƂȂ����@�b\n", playerName[playerId]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s��%s��%d�̃_���[�W�����������@�@�b\n", playerName[playerId], playerName[target], m_damage);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
}
Spell merazooma = { L"�����]�[�}",2,TRUE,spell_merazooma };



void spell_sukuruto(int playerId, Character* character, int target) {
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�̓X�N���g���ƂȂ����@�@�b\n", playerName[playerId]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	character[playerId].MP -= 3;
	int start, end;
	ally_loop(playerId, &start, &end);
	

	for (int i = start; i < end; i++) {
		if (character[i].endurance >= character[i].base_endurance * 2)
		{
			character[i].endurance = character[i].endurance;
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			printf("�b�������A%s�݂̂̂܂���͂���������Ȃ��@�b\n", playerName[i]);
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
		}
		else
		{
			character[i].endurance *= 6 / 5;
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			printf("�b%s�݂̂̂܂��肪���������@�b\n", playerName[i]);
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
		}
	}
}
Spell sukuruto = { L"�X�N���g",3,TRUE,spell_sukuruto };


void spell_kiariku(int playerId, Character* character, int target) {
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�̓L�A���N���ƂȂ����@�@�b\n", playerName[playerId]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	character[playerId].MP -= 2;

	int start, end;
	ally_loop(playerId, &start, &end);
	for (int i = start; i < end; i++) {
		if (character[i].paralysis == 0)continue;
		character[i].paralysis = 0;
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
		printf("�b%s�̃}�q�������������@�@�@�b\n", playerName[i]);
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	}
}
Spell kiariku = { L"�L�A���N",2,TRUE,spell_kiariku };

void spell_hubaaha(int playerId, Character* character, int target) {
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�̓t�o�[�n���ƂȂ����@�@�b\n", playerName[playerId]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	character[playerId].MP -= 3;
	int start, end;
	ally_loop(playerId, &start, &end);
	for (int i = start; i < end; i++)
		character[i].bless = 1.0 / 2;
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b���񂢂�̃u���X�������������������b\n");
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
}
Spell hubaaha = { L"�t�o�[�n",3,FALSE,spell_hubaaha };


void spell_raidein(int playerId, Character* character, int target) {
	int m_damage = base_spell_attack_single_target(playerId, target, character, 70, 90);
	character[playerId].MP -= 6;
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�̓��C�f�C�����ƂȂ����@�b\n", playerName[playerId]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s��%s��%d�̃_���[�W�����������@�@�b\n", playerName[playerId], playerName[target], m_damage);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
}
Spell raidein = { L"���C�f�C��",6,TRUE,spell_raidein };

void spell_zaoriku(int playerId, Character* character, int target) {
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�̓U�I���N���ƂȂ����@�@�b\n", playerName[playerId]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	character[playerId].MP -= 20;
	int keep = revive(playerId, target, character, 1);
	if (keep == 0) {
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
		printf("�b%s�͂����������āA���񂺂񂩂��ӂ������@�b\n", playerName[character[playerId].action_spell_target]);
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	}
	else if (keep == -2)
	{
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
		printf("�b�������A%s�͂����Ă���@�@�b\n", playerName[character[playerId].action_spell_target]);
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	}

}
Spell zaoriku = { L"�U�I���N",20,TRUE,spell_zaoriku };


void spell_behomaraa(int playerId, Character* character, int target) {
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�̓x�z�}���[���ƂȂ����@�b\n", playerName[playerId]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	character[playerId].MP -= 18;
	int start, end;
	ally_loop(playerId, &start, &end);
	for (int i = start; i < end; i++) {
		base_spell_cure_single_target(playerId, i, character, 100, 120);
	}
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b���񂢂��HP�������ӂ������@�@�@�@�b\n");
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
}
Spell behomaraa = { L"�x�z�}���[",18,FALSE,spell_behomaraa };


void spell_gigadein(int playerId, Character* character, int target) {
	int m_damage = base_spell_attack_single_target(playerId, target, character, 175, 225);
	character[playerId].MP -= 15;
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�̓M�K�f�C�����ƂȂ����@�b\n", playerName[playerId]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s��%s��%d�̃_���[�W�����������@�@�b\n", playerName[playerId], playerName[target], m_damage);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
}
Spell gigadein = { L"�M�K�f�C��",15,TRUE,spell_gigadein};

void spell_minadein(int playerId, Character* character, int target) {
	int m_damage = base_spell_attack_single_target(playerId, target, character, 300, 350);
	for (int i = 0; i < fielddata.playernum; i++)character[i].MP -= 10;

	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�͂��񂢂񂩂炿��������߁b\n", playerName[playerId]);
	printf("�b�~�i�f�C�����ƂȂ����@�@�@�@�@�@�@�@�@�b\n");
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s��%d�̃_���[�W�����������@�b\n", playerName[target], m_damage);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");

}
Spell minadein = { L"�~�i�f�C��",10,TRUE,spell_minadein };

void spell_hyado(int playerId, Character* character, int target) {
	int m_damage = base_spell_attack_single_target(playerId, target, character, 25, 35);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�̓q���h���ƂȂ����@�@�@�b\n", playerName[playerId]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	character[playerId].MP -= 3;
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s��%s��%d�̃_���[�W�����������@�@�b\n", playerName[playerId], playerName[target], m_damage);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
}
Spell hyado = { L"�q���h",3,TRUE,spell_hyado };

void spell_io(int playerId, Character* character, int target) {
	int m_damage = base_spell_attack_single_target(playerId, target, character, 20, 30);
	character[playerId].MP -= 5;
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�̓C�I���ƂȂ����@�@�@�b\n", playerName[playerId]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s��%s��%d�̃_���[�W�����������@�@�b\n", playerName[playerId], playerName[target], m_damage);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
}
Spell io = { L"�q���h",5,TRUE,spell_io };

void spell_hyadaruko(int playerId, Character* character, int target) {
	int m_damage = base_spell_attack_single_target(playerId, target, character, 42, 58);
	character[playerId].MP -= 5;
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�̓q���_���R���ƂȂ����@�b\n", playerName[playerId]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s��%s��%d�̃_���[�W�����������@�@�b\n", playerName[playerId], playerName[target], m_damage);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
}
Spell hyadaruko = { L"�q���_���R",5,TRUE,spell_hyadaruko };


void spell_rukanan(int playerId, Character* character, int target) {
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�̓��J�i�����ƂȂ����@�@�b\n", playerName[playerId]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	character[playerId].MP -= 4;
	int start, end;
	enemy_loop(playerId,&start,&end);
	for (int i = start; i < end; i++) {
		if (character[i].base_endurance == 0)
		{
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			printf("�b%s�݂̂̂܂���͂���������Ȃ��b\n", playerName[i]);
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
		}
		else
		{
			character[i].base_endurance -= character[i].base_endurance / 2;
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			printf("�b%s�݂̂̂܂��肪���������b\n", playerName[i]);
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
		}
	}
}
Spell rukanan = { L"���J�i��",4,TRUE,spell_rukanan };


void spell_iora(int playerId, Character* character, int target) {
	int m_damage = base_spell_attack_single_target(playerId, target, character, 52, 68);
	character[playerId].MP -= 8;
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�̓C�I�����ƂȂ����@�@�@�b\n", playerName[playerId]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s��%s��%d�̃_���[�W�����������@�@�b\n", playerName[playerId], playerName[target], m_damage);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
}
Spell iora = { L"�C�I��",8,TRUE,spell_iora };


void spell_mahyado(int playerId, Character* character, int target) {
	int m_damage = base_spell_attack_single_target(playerId, target, character, 80, 104);
	character[playerId].MP -= 12;
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�̓}�q���h���ƂȂ����@�@�b\n", playerName[playerId]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s��%s��%d�̃_���[�W�����������@�@�b\n", playerName[playerId], playerName[target], m_damage);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
}
Spell mahyado = { L"�}�q���h",12,TRUE,spell_mahyado };

void spell_doragoramu(int playerId, Character* character, int target) {
	character[playerId].MP -= 18;
	character[playerId].dragon = 1;
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�̓h���S�������ƂȂ����@�b\n", playerName[playerId]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�̓h���S���ɂȂ����@�@�@�b\n", playerName[playerId]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");


	//�h���S���̃f�t�H���g�A�N�V����
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
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
		printf("�b%s�͂���ǂ��c���ł������������b\n", playerName[playerId]);
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
		character[target].HP -= damage;
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
		printf("�b%s��%d�̃_���[�W���������b\n", playerName[target], damage);
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
		break;
	default:
		damageMin = 65;
		damageMax = 85;
		damage = damageMin + rand() % (damageMax - damageMin);
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
		printf("�b%s�͂ق̂����͂����@�b\n", playerName[playerId]);
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
		character[target].HP -= damage;
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
		printf("�b%s��%d�̃_���[�W���������b\n", playerName[target], damage);
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
		break;
	}
}
Spell doragoramu = { L"�h���S����",18,TRUE,spell_doragoramu };


void spell_ionazun(int playerId, Character* character, int target) {
	int m_damage = base_spell_attack_single_target(playerId, target, character, 120, 160);
	character[playerId].MP -= 15;
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�̓C�I�i�Y�����ƂȂ����@�b\n", playerName[playerId]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s��%s��%d�̃_���[�W�����������@�@�b\n", playerName[playerId], playerName[target], m_damage);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
}
Spell ionazun = { L"�C�I�i�Y��",15,TRUE,spell_ionazun };

void spell_rukani(int playerId, Character* character, int target) {
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�̓��J�j���ƂȂ����@�@�b\n", playerName[playerId]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	character[playerId].MP -= 3;
	if (character[target].base_endurance == 0)
	{
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
		printf("�b%s�݂̂̂܂���͂���������Ȃ��b\n", playerName[target]);
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	}
	else
	{
		character[target].base_endurance -= character[target].base_endurance / 2;
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
		printf("�b%s�݂̂̂܂��肪���������b\n", playerName[target]);
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	}
}
Spell rukani = { L"���J�j",3,TRUE,spell_rukani };

void spell_mahotora(int playerId, Character* character, int target) {
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�̓}�z�g�����ƂȂ����@�@�b\n", playerName[playerId]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	character[playerId].MP -= 4;
	if (character[target].MP == 0)
	{
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
		printf("�b%s��MP�͂���������Ȃ��b\n", playerName[target]);
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	}
	else
	{
		int down_MP = (rand() % 6) + 5;
		character[target].MP -= down_MP;
		if(character[target].MP < 0)
			character[target].MP = 0;

		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
		printf("�b%s��MP�������Ƃ����b\n", playerName[target]);
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	}
}
Spell mahotora = { L"�}�z�g��",4,TRUE,spell_mahotora };


void spell_firebress(int playerId, Character* character, int target) {
	int damage = 0;
	int damageMin = 40;
	int damageMax = 60;
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�͂ق̂����͂����@�@�@�b\n", playerName[playerId]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	int start, end;
	enemy_loop(playerId, &start, &end);
	
	for (int i = start; i < end; i++)
	{
		damage = damageMin + rand() % (damageMax - damageMin);
		character[i].HP -= damage;
		if (character[i].HP < 0)
			character[i].HP = 0;
	}
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�̓v���C���[�S���Ɂ@�@�@�b\n", playerName[playerId]);
	printf("�b%d�̃_���[�W��^�����@�@�@�@�@�@�b\n", damage);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
}
Spell firebress = { L"������̂���",0,TRUE,spell_firebress };

void spell_mahokanta(int playerId, Character* character, int target) {
	//�����𒵂˕Ԃ��o���A�𒣂�E�ł��ĂȂ�
}Spell mahokanta = { L"�}�z�J���^",4,TRUE,spell_mahokanta };

void spell_yaketukuiki(int playerId, Character* character, int target) {
	for (int i = 0; i < fielddata.playernum; i++) {
		character[i].paralysis = 5+rand()%5;//5~9�^�[��
	}
}
Spell yaketukuiki = { L"�₯������",4,TRUE,spell_yaketukuiki };

void spell_shinybress(int playerId, Character* character, int target) {
	int damageMin = 120;
	int damageMax = 140;
	int damage = damageMin + rand() % (damageMax - damageMin);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�͂����₭�������͂����@�b\n", playerName[playerId]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	int start, end;
	enemy_loop(playerId, &start, &end);
	for (int i = start; i < end; i++) {
		character[i].HP -= damage;
		if (character[i].HP < 0)
			character[i].HP = 0;
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
		printf("�b%s��%s�Ɂ@�@�@�@�@�b\n", playerName[playerId], playerName[i]);
		printf("�b%d�̃_���[�W��^�����@�@�@�@�@�@�b\n", damage);
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");

	}
}
Spell shinybress = { L"�����₭����",0,TRUE,spell_shinybress };

void spell_itetukuhado(int playerId, Character* character, int target) {
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�͓��Ă��g�����ƂȂ����@�b\n", playerName[playerId]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	int start, end;
	enemy_loop(playerId, &start, &end);
	for (int i = start; i < end; i++) {
		character[i].strength = character[i].base_strength;
		character[i].endurance = character[i].base_endurance;
		character[i].bless = 1;
	}
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b�v���C���[�S���ɂ������Ă���@�@�@�@�b\n");
	printf("�b�ǂ����ʂ��������@�@�@�@�@�@�@�@�@�@�b\n");
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
}
Spell itetukuhado = { L"���Ă��͂ǂ�",0,TRUE,spell_itetukuhado };

void spell_syakunetuhono(int playerId, Character* character, int target) {
	int damageMin = 150;
	int damageMax = 170;
	int damage = damageMin + rand() % (damageMax - damageMin);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�͂��Ⴍ�˂ق̂����͂����@�b\n", playerName[playerId]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	int start, end;
	enemy_loop(playerId, &start, &end);
	for (int i = start; i < end; i++) {
		character[i].HP -= damage;
		if (character[i].HP < 0)
			character[i].HP = 0;
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
		printf("�b%s��%s�Ɂ@�@�@�@�@�b\n", playerName[playerId], playerName[i]);
		printf("�b%d�̃_���[�W��^�����@�@�@�@�@�@�b\n", damage);
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	}

}
Spell syakunetuhono = { L"���Ⴍ�˂ق̂�",0,TRUE,spell_syakunetuhono };

void spell_sweetbress(int playerId, Character* character, int target) {
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�͂��܂��������͂����@�b\n", playerName[playerId]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	int start, end;
	enemy_loop(playerId, &start, &end);
	for (int i = start; i < end; i++) {
		if (0 == character[i].sleep) {
			character[i].sleep = 2 + rand() % 4;
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			printf("�b%s�͖������@�@�@�@�@�b\n", playerName[i]);
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
		}
	}
}

Spell sweetbress = { L"���܂�����",0,TRUE,spell_sweetbress };

void spell_poisonattack(int playerId, Character* character, int target) {
	int damage = enemy_dyrect_attack(playerId, character, target);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�̂ǂ����������@�b\n", playerName[playerId]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	character[target].HP -= damage;
	character[target].poison = TRUE;
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s��%s�Ɂ@�@�@�@�@�b\n", playerName[playerId], playerName[target]);
	printf("�b%d�̃_���[�W��^�����@�@�@�@�@�@�b\n", damage);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�͂ǂ��ɂȂ���     �b\n",playerName[target]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
}
Spell poisonattack = { L"�ǂ���������",0,TRUE,spell_poisonattack };

void spell_rarihoo(int playerId, Character* character, int target) {

	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�̓����z�[���������@�b\n", playerName[playerId]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	int start, end;
	enemy_loop(playerId, &start, &end);
	for (int i = start; i < end; i++) {
		if (0 == character[i].sleep) {
			character[i].sleep = 2 + rand() % 4;
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			printf("�b%s�͖������@�@�@�@�@�b\n", playerName[i]);
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
		}
	}
}
Spell rarihoo = { L"�����z�[",3,TRUE,spell_rarihoo };

void spell_bukiminahikari(int playerId, Character* character, int target) {
	//�G�O���[�v�ɑ΂��Ď�������Z�������₷���Ȃ�E�ł��ĂȂ�
}
Spell bukiminahikari = { L"�Ԃ��݂ȂЂ���",0,TRUE,spell_bukiminahikari };

void spell_manuusa(int playerId, Character* character, int target) {
	//�G�O���[�v�ɑ΂��Ēʏ�U���̖�������������E�ł��ĂȂ�
}
Spell manuusa = { L"�}�k�[�T",4,TRUE,spell_manuusa };

void spell_hardfire(int playerId, Character* character, int target) {
	int damageMin = 65;
	int damageMax = 85;
	int damage = damageMin + rand() % (damageMax - damageMin);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�͂͂������ق̂����͂����@�b\n", playerName[playerId]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	int start, end;
	enemy_loop(playerId, &start, &end);
	for (int i = start; i < end; i++) {
		character[i].HP -= damage;
		if (character[i].HP < 0)
			character[i].HP = 0;
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
		printf("�b%s��%s�Ɂ@�@�@�@�@�b\n", playerName[playerId], playerName[i]);
		printf("�b%d�̃_���[�W��^�����@�@�@�@�@�@�b\n", damage);
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	}
}
Spell hardfire = { L"�͂������ق���",0,TRUE,spell_hardfire };

void spell_kogoeruhubuki(int playerId, Character* character, int target) {
	int damageMin = 50;
	int damageMax = 60;
	int damage = damageMin + rand() % (damageMax - damageMin);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�͂�������ӂԂ����������@�b\n", playerName[playerId]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	int start, end;
	enemy_loop(playerId, &start, &end);
	for (int i = start; i < end; i++) {
		character[i].HP -= damage;
		if (character[i].HP < 0)
			character[i].HP = 0;
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
		printf("�b%s��%s�Ɂ@�@�@�@�@�b\n", playerName[playerId], playerName[i]);
		printf("�b%d�̃_���[�W��^�����@�@�@�@�@�@�b\n", damage);
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	}
}
Spell kogoeruhubuki = { L"��������ӂԂ�",0,TRUE,spell_kogoeruhubuki };

void spell_medapani(int playerId, Character* character, int target) {
	//(�G���g�����ꍇ)�G�P�̂�������Ԃɂ���E�ł��ĂȂ�(6-9�^�[��)
}
Spell medapani = { L"���_�p�j",5,TRUE,spell_medapani };

void spell_mahotoon(int playerId, Character* character, int target) {
	//�G�O���[�v�ɑ΂��Ď������g�p�s�ɂ���E�ł��ĂȂ�(7-10�^�[��)
}
Spell mahotoon = { L"�}�z�g�[��",3,TRUE,spell_mahotoon };

void spell_namemawasi(int playerId, Character* character, int target) {
	//�G�P�̂�1�^�[���x�݁E�ł��ĂȂ�
}
Spell namemawasi = { L"�Ȃ߂܂킵",0,TRUE,spell_namemawasi };



void tool_tatakainodoramu(int playerId, Character* character, int target) {
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�͂��������̃h�������g�����@�@�@�@�b\n", playerName[playerId]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	int start, end;
	ally_loop(playerId, &start, &end);
	for (int i = start; i < end; i++) {
		if (character[i].strength >= character[i].base_strength * 2)
		{
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			printf("�b�������A%s�̂�����͂���������Ȃ��@�@�@�b\n", playerName[i]);
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
		}
		else
		{
			character[i].strength *= 2;
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			printf("�b%s�̂����炪���������@�@�@�b\n", playerName[i]);
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
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

//���x���ƃL�������w�肵��basestatus������
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
	if (level != target_level)printf("�Y������X�e�[�^�X������܂���:%s,���x��%d",name,target_level);

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

//�����i�̃X�e�[�^�X�𔽉f������
void set_Character_equip_status(int id, Character *character, char *wepon_name, char *armar_name, char *helmet_name, char *shield_name)
{
	FILE *fp;
	char filename[128];
	char* sep[128];
	char line[128];


	sprintf(filename, "character_datas/����.csv");
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
	if (strcmp(sep[0], wepon_name))printf("�Y�����镐�킪����܂���:%s", wepon_name);
	fclose(fp);

	sprintf(filename, "character_datas/��낢.csv");
	fp = fopen(filename, "r");
	int endurance = 0;
	while (fscanf(fp, "%s", line) != EOF) {
		int count = split(sep, line, ',');
		if (!strcmp(sep[0], armar_name)) {
			endurance = atoi(sep[3]);
			break;
		}
	}
	if (strcmp(sep[0], armar_name))printf("�Y�����镐�킪����܂���:%s", armar_name);
	fclose(fp);


	sprintf(filename, "character_datas/���Ԃ�.csv");
	fp = fopen(filename, "r");
	while (fscanf(fp, "%s", line) != EOF) {
		int count = split(sep, line, ',');
		if (!strcmp(sep[0], helmet_name)) {
			endurance += atoi(sep[3]);
			break;
		}
	}
	if (strcmp(sep[0], helmet_name))printf("�Y�����镐�킪����܂���:%s", helmet_name);
	fclose(fp);


	sprintf(filename, "character_datas/����.csv");
	fp = fopen(filename, "r");
	while (fscanf(fp, "%s", line) != EOF) {
		int count = split(sep, line, ',');
		if (strcmp(sep[0], shield_name)) {
			endurance += atoi(sep[3]);
			break;
		}
	}
	if (!strcmp(sep[0], shield_name))printf("�Y�����镐�킪����܂���:%s", shield_name);

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
	strcpy(character[id].name,L"�G�X�^�[�N");
}

void estark_action(int id,Character *characters) {
	// 2��U��
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
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			printf("�b%s�̂��������@�@�@�@�@�@�@�b\n", playerName[id]);
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			characters[target].HP -= damage;
			if (characters[target].HP < 0)
				characters[target].HP = 0;
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			printf("�b%s��%s�Ɂ@�@�@�@�@�b\n", playerName[id], playerName[target]);
			printf("�b%d�̃_���[�W��^�����@�@�@�@�@�@�b\n", damage);
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			break;
		case 1:
			damageMin = 72;
			damageMax = 88;
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			printf("�b%s�̓C�I�i�Y�����ƂȂ����@�b\n", playerName[id]);
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			for (int i = 0; i < fielddata.playernum; i++)
			{
				damage = damageMin + rand() % (damageMax - damageMin);
				characters[i].HP -= damage;
				if (characters[i].HP < 0)
					characters[i].HP = 0;
			}
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			printf("�b%s�̓v���C���[�S���Ɂ@�@�@�b\n", playerName[id]);
			printf("�b%d�̃_���[�W��^�����@�@�@�@�@�@      �b\n", damage);
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			break;
		case 2:
			damageMin = 150;
			damageMax = 170;
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			printf("�b%s�͎ܔM�̉����ƂȂ����@�@�b\n", playerName[id]);
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			for (int i = 0; i < fielddata.playernum; i++)
			{
				damage = damageMin + rand() % (damageMax - damageMin);
				characters[i].HP -= damage * characters[i].bless;
				if (characters[i].HP < 0)
					characters[i].HP = 0;
			}
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			printf("�b%s�̓v���C���[�S���Ɂ@�@�@�b\n", playerName[id]);
			printf("�b%d�̃_���[�W��^�����@�@�@�@�@�@�@�@�@�b\n", damage);
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			break;
		case 3:
			damageMin = 120;
			damageMax = 140;
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			printf("�b%s�͋P�������ƂȂ����@�@�@�b\n", playerName[id]);
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			for (int i = 0; i < 4; i++)
			{
				damage = damageMin + rand() % (damageMax - damageMin);
				characters[i].HP -= damage * characters[i].bless;
				if (characters[i].HP < 0)
					characters[i].HP = 0;
			}
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			printf("�b%s�̓v���C���[�S���Ɂ@�@�@�b\n", playerName[id]);
			printf("�b%d�̃_���[�W��^�����@�@�@�@�@�@�b\n", damage);
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			break;
		case 4:
			target = rand() % 4;
			damageMin = 92;
			damageMax = 128;
			damage = damageMin + rand() % (damageMax - damageMin);
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			printf("�b%s�̓����]�[�}���ƂȂ����@�b\n", playerName[id]);
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			characters[target].HP -= damage;
			if (characters[target].HP < 0)
				characters[target].HP = 0;
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			printf("�b%s��%s�Ɂ@�@�@�@�@�b\n", playerName[id], playerName[target]);
			printf("�b%d�̃_���[�W��^�����@�@�@�@�@�@�b\n", damage);
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			break;
		case 5:
			spell_itetukuhado(id, characters, target);
			break;
		}
	}
}


void message_disp(int id,int target,int damage) {
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s�̂��������@�@�@�@�@�@�@�b\n", playerName[id]);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
	printf("�b%s��%s�Ɂ@�@�@�@�@�b\n", playerName[id], playerName[target]);
	printf("�b%d�̃_���[�W��^�����@�@�@�@�@�@�b\n", damage);
	printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
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
}//�X���C��

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
}//���тȂ��C�^�`

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
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
		printf("�b%s�͗l�q���݂��@�@�@�@�@�@�@�b\n", playerName[id]);
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
		break;
	case 2:spell_hyado(id, character, target);
		break;
	default:break;
	}
}//�v���Y�j����

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
}//�o�u���X���C��

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
	int damage = enemy_dyrect_attack(id, character, target);//�ʏ�̂�
	message_disp(id, target, damage);
}//�S�[�X�g

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
}//���΂��L�����h��

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
	int damage = 0;//��^�[���c�ʏ�B�����^�[���c�ʏ�E�����E�M���E���J�j
	if (turn_count_oyabun % 2 == 1) {//��^�[��
		damage = enemy_dyrect_attack(id, character, target);
		message_disp(id, target, damage);
	}
	else
		switch(rand() % 4) {//�����^�[��
	    case 0:damage = enemy_dyrect_attack(id, character, target);
			message_disp(id, target, damage); break;
		case 1:spell_mera(id, character, target); break;
		case 2:spell_gira(id, character, target); break;
		case 3:spell_rukani; break;
		default: break;
	}
	turn_count_oyabun++;
}//����Ԃ�S�[�X�g


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
	case 1://���Ԃ��Ă�(�z�C�~�X���C��)�E�ł��ĂȂ�
		break;
	default:break;
	}
}//����炵

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
}//�������U�[�h

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
}//�i�C�g�E�C�v�X

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
}//�K�b�v����

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
}//�T�{�e���{�[��

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
	case 2:spell_mahotoon(id, character, target);//�}�z�g�[���E�ł��ĂȂ�
		break;
	case 3:spell_sukuruto(id, character,target);
		break;
	default:break;
	}
}//�܂ق�����

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
}//�U�C��

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
	if (turn_count_snowqueen%3==1) {//1�^�[���ځE4�^�[����
		switch (rand() % 2) {
		case 0:
			damage = enemy_dyrect_attack(id, character, target);
			message_disp(id, target, damage);
			character[id].strength= character[id].base_strength;//�U���͂����ɖ߂�
			break;
		case 1:
		{
			int damageMin = 13;
			int damageMax = 16;
			damage = damageMin + rand() % (damageMax - damageMin);
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			printf("�b%s�͂�������������͂����@�b\n", playerName[id]);
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			for (int i = 0; i < fielddata.playernum; i++) {
				character[i].HP -= damage;
				if (character[i].HP < 0)
					character[i].HP = 0;
				printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
				printf("�b%s��%s�Ɂ@�@�@�@�@�b\n", playerName[id], playerName[i]);
				printf("�b%d�̃_���[�W��^�����@�@�@�@�@�@�b\n", damage);
				printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			}
			character[id].strength = character[id].base_strength;//�U���͂����ɖ߂�
		}break;
		default:break;
		}
	}
	else if (turn_count_snowqueen % 3 == 2) {//2�^�[���ځE5�^�[����
		switch (rand() % 2) {
		case 0:damage = enemy_dyrect_attack(id, character, target); 
			message_disp(id, target, damage); 
			break;
		case 1:spell_hyado(id, character, target); break;
		default:break;
		}
	}
	else {//3�^�[���ځE6�^�[����...
		switch (rand() % 2){
		case 0:spell_hoimi(id, character, id); break;
		case 1://�����z������
			character[id].strength = character[id].base_strength * 2;//�U���͂�2�{
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			printf("�b%s�͂��������������������񂾁@�b\n", playerName[id]);
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			break;
		default:break;
		}
	}
	turn_count_snowqueen++;
}//�䂫�̂��傤����


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
}//���΂��L�m�R

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
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
		printf("�b%s�͏΂��Ă���@�@�@�@�@�@�@�b\n", playerName[id]);
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
		break;
	default:break;
	}
}//�G�r���A�b�v��

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
	case 2:spell_mahotoon(id, character, target);//�}�z�g�[���E�ł��ĂȂ�
		break;
	case 3:spell_medapani(id, character, target);//���_�p�j�E�ł��ĂȂ�
		break;
	//case 4://���Ԃ��Ă�(�z�C�~�X���C��)�E�ł��ĂȂ�
	//	break;
	default:break;
	}
}//��炢�Ԃ���

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

}//�z�C�~�X���C��

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
}//�������ւ�

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
	if (turn_count_falsetaiko % 3 == 1) {//1�^�[���E4�^�[��
		switch (rand() % 1) {
		case 0:damage = enemy_dyrect_attack(id, character, target);
			message_disp(id, target, damage); break;
		//case 1://��炢�Ԃ�����ĂԁE�ł��ĂȂ�
		//	break;
		default:break;
		}
	}
	else if(turn_count_falsetaiko % 3 == 2){//2�^�[���E5�^�[��
		switch(rand() % 2) {
		case 0:
			character[id].strength = character[id].base_strength * 2;//�U���͂��{�ɂ���
			break;
		case 1:spell_firebress(id, character, target);
			break;
		default:break;
		}
	}
	else {
		switch (rand() % 1) {//3�^�[���E6�^�[��
		case 0:damage = enemy_dyrect_attack(id, character, target);
			message_disp(id, target, damage);
			character[id].strength = character[id].base_strength;//�U���͂����ɖ߂�
			break;
		//case 1://�����������ĂԁE�ł��ĂȂ�
		//	character[id].strength = character[id].base_strength;//�U���͂����ɖ߂�
		//	break;
		default: break;
		}
	}
	turn_count_falsetaiko++;
}//�j�Z��������

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
}//�x�z�}�X���C��

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
}//�}�h���[�p�[

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
	case 1:spell_yaketukuiki(id, character, target);//�₯������
		break;
	}
}//�ւт�������

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
		break;//��S�̈ꌂ
	}
	case 2:spell_behoimi(id, character, id);
		break;
	default:break;
	}
}//�J���_�^

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
		character[id].endurance= character[id].base_endurance*2;//�h��
		break;
	}
}//�V�[���h�q�b�|

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
}//�I�[�NLv20

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
	for (int attack_num = rand() % 2; 0 <= attack_num; attack_num--) {//1�`2��U��
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
}//�L���[��Lv35

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
	case 1: {//��������ӂԂ�
		int damageMin = 50;
		int damageMax = 60;
		damage = damageMin + rand() % (damageMax - damageMin);
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
		printf("�b%s�͂������邢�Ԃ����͂Ȃ����@�b\n", playerName[id]);
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
		for (int i = 0; i < fielddata.playernum; i++) {
			character[i].HP -= damage;
			if (character[i].HP < 0)
				character[i].HP = 0;
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			printf("�b%s��%s�Ɂ@�@�@�@�@�b\n", playerName[id], playerName[i]);
			printf("�b%d�̃_���[�W��^�����@�@�@�@�@�@�b\n", damage);
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
		}
		break;
	}
	case 2:spell_bagikurosu(id, character, target);
		break;
	case 3:spell_merami(id, character, target);
		break;
	default:break;
	}
}//�W���~

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
	case 0:damage = enemy_dyrect_attack(id, character, target);//���ڍU��
		message_disp(id, target, damage); break;
	case 1:damage = enemy_dyrect_attack(id, character, target);//�_�t�̃c�o
		break;
	//case 2:spell_namemawasi(id, character, target);//�Ȃ߂܂킵�E�ł��ĂȂ�
	//	break;
	default:break;
	}
}//�x���S�����[�h

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
	case 0:damage = enemy_dyrect_attack(id, character, target);//���ڍU��
		message_disp(id, target, damage); break;
	case 1:spell_hoimi(id, character, target);
		break;
	case 2:spell_gira(id, character, target);
		break;
	case 3:spell_hyado(id, character, target);
		break;
	//case 4:spell_manuusa(id, character, target);//�}�k�[�T�E�ł��ĂȂ�
	//	break;
	default:break;
	}
}//���C�W�L����

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
	case 0:damage = enemy_dyrect_attack(id, character, target);//���ڍU��
		message_disp(id, target, damage); break;
	case 1:spell_merami(id, character, target);
		break;
	case 2:
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
		printf("�b%s�̓C�I�i�Y�����������@�b\n", playerName[id]);
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
		printf("�b������MP������Ȃ��@              �b\n");
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
		break;
	default:break;
	}
}//�~�j�f�[����

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
	case 0:damage = enemy_dyrect_attack(id, character, target);//���ڍU��
		message_disp(id, target, damage); break;
	//case 1:spell_mahotoon(id, character, target);//�}�z�g�[���E�ł��ĂȂ�
	//	break;
	//case 2:spell_bukiminahikari(id, character, target);//�Ԃ��݂ȂЂ���E�ł��ĂȂ�
	//	break;
	default:break;
	}
}//���b�T�[��

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
		damage = (int)(enemy_dyrect_attack(id, character, target)*1.25);//�����U��񂷁E1.25�{
	}
	message_disp(id, target, damage);
}//�S���Y

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
	for (int attack_num = rand() % 2; 0 <= attack_num; attack_num--) {//1�`2��U��
		switch (rand() % 4) {
		case 0:damage = enemy_dyrect_attack(id, character, target);
			message_disp(id, target, damage); break;
		case 1: {//�͂������ق̂�
			int damageMin = 65;
			int damageMax = 85;
			damage = damageMin + rand() % (damageMax - damageMin);
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			printf("�b%s�͂͂������ق̂����͂Ȃ����@�b\n", playerName[id]);
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			for (int i = 0; i < fielddata.playernum; i++) {
				character[i].HP -= damage;
				if (character[i].HP < 0)
					character[i].HP = 0;
				printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
				printf("�b%s��%s�Ɂ@�@�@�@�@�b\n", playerName[id], playerName[i]);
				printf("�b%d�̃_���[�W��^�����@�@�@�@�@�@�b\n", damage);
				printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			}
			break;
		}
		case 2:spell_merazooma(id, character, target);
			break;
		case 3:spell_mahokanta(id, character, target);//�}�z�J���^�E�ł��ĂȂ�
			break;
		default:break;
		}
	}
}//�Q�}

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
	for (int attack_num = rand() % 2; 0 <= attack_num; attack_num--) {//1�`2��U��
		switch (rand() % 5) {
		case 0:damage = enemy_dyrect_attack(id, character, target);
			message_disp(id, target, damage); break;
		case 1: {//�͂������ق̂�
			int damageMin = 65;
			int damageMax = 85;
			damage = damageMin + rand() % (damageMax - damageMin);
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			printf("�b%s�͂͂������ق̂����͂Ȃ����@�b\n", playerName[id]);
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			for (int i = 0; i < fielddata.playernum; i++) {
				character[i].HP -= damage;
				if (character[i].HP < 0)
					character[i].HP = 0;
				printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
				printf("�b%s��%s�Ɂ@�@�@�@�@�b\n", playerName[id], playerName[i]);
				printf("�b%d�̃_���[�W��^�����@�@�@�@�@�@�b\n", damage);
				printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			}
			break;
		}
		case 2: {//���Ȃ���
			int damageMin = 50;
			int damageMax = 70;
			damage = damageMin + rand() % (damageMax - damageMin);
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			printf("�b%s�͂��Ȃ��܂��͂Ȃ����@�b\n", playerName[id]);
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			for (int i = 0; i < fielddata.playernum; i++) {
				character[i].HP -= damage;
				if (character[i].HP < 0)
					character[i].HP = 0;
				printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
				printf("�b%s��%s�Ɂ@�@�@�@�@�b\n", playerName[id], playerName[i]);
				printf("�b%d�̃_���[�W��^�����@�@�@�@�@�@�b\n", damage);
				printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
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
}//�u�I�[��

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
	case 0:damage = enemy_dyrect_attack(id, character, target);//���ڍU��
		message_disp(id, target, damage); break;
	case 1:spell_behomaraa(id, character, target);//�x�z�}���[
		break;
	case 2:spell_firebress(id, character, target);//������̂���
		break;
	default:break;
	}
}//�C�Y���C�[��

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
	case 1: {//�͂������ق̂�
		int damageMin = 65;
		int damageMax = 85;
		damage = damageMin + rand() % (damageMax - damageMin);
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
		printf("�b%s�͂͂������ق̂����͂Ȃ����@�b\n", playerName[id]);
		printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
		for (int i = 0; i < fielddata.playernum; i++) {
			character[i].HP -= damage;
			if (character[i].HP < 0)
				character[i].HP = 0;
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			printf("�b%s��%s�Ɂ@�@�@�@�@�b\n", playerName[id], playerName[i]);
			printf("�b%d�̃_���[�W��^�����@�@�@�@�@�@�b\n", damage);
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
		}
		break;
	}
	case 2:spell_begiragon(id, character, target);
		break;
	case 3:spell_mahyado(id, character, target);
		break;
	default:break;
	}
}//���}�_

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
	if (turn_count_snowqueen % 3 == 1) {//1�^�[���ځE4�^�[����
		switch (rand() % 2) {
		case 0: spell_shinybress(id, character, target);
			break;
		case 1:
			spell_mahokanta(id, character, target);
		default:break;
		}
	}
	else if (turn_count_snowqueen % 3 == 2) {//2�^�[���ځE5�^�[����
		switch (rand() % 2) {
		case 0:			
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			printf("�b%s��%s�ɂ�����Ȃ��������@�b\n", playerName[id], playerName[target]);
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n"); 
			character[target].HP -= 105;
			break;
		case 1:character[id].endurance = character[id].base_endurance * 5;//�ڂ�����E5����1�Ɍy��
			break;
		default:break;
		}
	}
	else {//3�^�[���ځE6�^�[����...
		switch (rand() % 2) {
		case 0:character[id].endurance = character[id].base_endurance;//�ڂ����匳�ɖ߂�
			spell_ionazun(id, character, target);
			break;
		case 1:character[id].endurance = character[id].base_endurance;//�ڂ����匳�ɖ߂�
			spell_itetukuhado(id, character, target);//���Ă��͂ǂ�
			break;
		default:break;
		}
	}
	turn_count_snowqueen++;
}//�C�[�u��

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
}//�G�r���X�v���b�c

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
	case 1://�a����E�ʏ�Ɠ����_���[�W
		damage = enemy_dyrect_attack(id, character, target);
		message_disp(id, target, damage);
		break;
	case 2:spell_rukanan(id, character, target);
		break;
	case 3:spell_sukara(id, character, target);
		break;
	default:break;
	}
}//�V���v�����K�[

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
	for (int attack_num = rand() % 2; 0 <= attack_num; attack_num--) {//1�`2��U��
		switch (rand() % 5) {
		case 0:damage = enemy_dyrect_attack(id, character, target);
			message_disp(id, target, damage); break;
		case 1: {//�͂������ق̂�
			int damageMin = 65;
			int damageMax = 85;
			damage = damageMin + rand() % (damageMax - damageMin);
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			printf("�b%s�͂͂������ق̂����͂Ȃ����@�b\n", playerName[id]);
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			for (int i = 0; i < fielddata.playernum; i++) {
				character[i].HP -= damage;
				if (character[i].HP < 0)
					character[i].HP = 0;
				printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
				printf("�b%s��%s�Ɂ@�@�@�@�@�b\n", playerName[id], playerName[i]);
				printf("�b%d�̃_���[�W��^�����@�@�@�@�@�@�b\n", damage);
				printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
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
}//�Q�}(2���)

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
}//�X�J���h��

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
	case 1:spell_hardfire(id, character, target);//�͂������ق̂�
		break;
	case 2:spell_yaketukuiki(id, character, target);
		break;
	default:break;
	}
}//�t���A�h���S��

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
	case 1:spell_bagikurosu (id, character, target);//�o�M�N���X
		break;
	case 2:spell_mahotoon(id, character, target);//�}�z�g�[���E�ł��ĂȂ�
		break;
	default:break;
	}
}//���C�g�L���O

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
	//�~���h���[�X���`��
	if (7000 < character[id].HP) {
		switch (rand() % 5) {
		case 0:damage = enemy_dyrect_attack(id, character, target);
			message_disp(id, target, damage); break;
		case 1:spell_shinybress(id, character, target);
			break;
		case 2:
			spell_itetukuhado(id, character, target);//���Ă��͂ǂ�
			break;
		case 3:spell_merazooma(id, character, target);
			break;
		case 4://�����艺��2�C���Ȃ������炠���܂��񂩂��2�C�ĂԁE�ł��ĂȂ�
			break;
		case 5://�����艺��2�C���Ȃ������炫��[�܂����2�C�ĂԁE�ł��ĂȂ�
			break;
		default:break;
		}
		if (character[id].HP < 7000){
			character[id].HP = 7000;
			trun_count_mildrous = 0;
		}
	}
	else if (4500 < character[id].HP) {//�~���h���[�X�ŏI�`�ԁE7000�`4500
		for (int attack_num = rand() % 2; 0 <= attack_num; attack_num--) {//1�`2��s��
			if (trun_count_mildrous % 3 == 1) {//1�^�[���E4�^�[��
				switch (rand() % 2) {
				case 0:damage = enemy_dyrect_attack(id, character, target);
					message_disp(id, target, damage); break;
				case 1:spell_syakunetuhono(id, character, target);//���Ⴍ�˂�
					break;
				default:break;
				}
			}
			else if (trun_count_mildrous % 3 == 2) {//2�^�[���E5�^�[��
				switch (rand() % 2) {
				case 0:spell_itetukuhado(id, character, target);//���Ă��͂ǂ�
					break;
				case 1:spell_ionazun(id, character,target);//�C�I�i�Y��
					break;
				default:break;
				}
			}
			else {//3�^�[���E6�^�[��
				switch (rand() % 2) {
				case 0:spell_rukanan(id, character, target);//���J�i��
					break;
				case 1:spell_mahokanta(id, character, target);//�}�z�J���^
					break;
				default: break;
				}
			}
		}
	}
	else if (2500 < character[id].HP) {//�~���h���[�X�ŏI�`�ԁE4500�`2500
		for (int attack_num = rand() % 2; 0 <= attack_num; attack_num--) {//1�`2��s��
			if (trun_count_mildrous % 3 == 1) {//1�^�[���E4�^�[��
				switch (rand() % 2) {
				case 0:damage = enemy_dyrect_attack(id, character, target);
					message_disp(id, target, damage); break;
				case 1:spell_syakunetuhono(id, character, target);//���Ⴍ�˂�
					break;
				default:break;
				}
			}
			else if (trun_count_mildrous % 3 == 2) {//2�^�[���E5�^�[��
				switch (rand() % 2) {
				case 0:spell_itetukuhado(id, character, target);//���Ă��͂ǂ�
					break;
				case 1:character[id].HP += 500;//�߂�����(HP500��)
					break;
				default:break;
				}
			}
			else {//3�^�[���E6�^�[��
				switch (rand() % 2) {
				case 0:spell_rukanan(id, character, target);//���J�i��
					break;
				case 1:spell_merazooma(id, character, target);//�����]�[�}
					break;
				default: break;
				}
			}
		}
	}
	else {//�~���h���[�X�ŏI�`�ԁE2500�`0
		for (int attack_num = rand() % 2; 0 <= attack_num; attack_num--) {//1�`2��s��
			if (trun_count_mildrous % 3 == 1) {//1�^�[���E4�^�[��
				switch (rand() % 2) {
				case 0://�ɍ��Ȉꌂ
					printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
					printf("�b%s��%s�ɂ�����Ȃ��������@�b\n", playerName[id], playerName[target]);
					printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
					character[target].HP -= 215; break;
				case 1:spell_syakunetuhono(id, character, target);//���Ⴍ�˂�
					break;
				default:break;
				}
			}
			else if (trun_count_mildrous % 3 == 2) {//2�^�[���E5�^�[��
				switch (rand() % 2) {
				case 0:spell_itetukuhado(id, character, target);//���Ă��͂ǂ�
					break;
				case 1:spell_ionazun(id, character, target);//�C�I�i�Y��
					break;
				default:break;
				}
			}
			else {//3�^�[���E6�^�[��
				switch (rand() % 2) {
				case 0:spell_rukanan(id, character, target);//���J�i��
					break;
				case 1:spell_merazooma(id, character, target);//�����]�[�}
					break;
				default: break;
				}
			}
		}
	}

	trun_count_mildrous++;
	
}//�~���h���[�X


//Enemy  = {_init,_attack};
Enemy suraimu = { suraimu_init,suraimu_attack ,L"�X���C��"};//�X���C��

Enemy kubinagaweasel = { kubinagaweasel_init,kubinagaweasel_attack ,L"���тȂ��C�^�`" };//���тȂ��C�^�`
Enemy prisoncat = { prisoncat_init,prisoncat_attack ,L"�v���Y�j����" };//�v���Y�j�����E����1lv�̃X�e�[�^�X
Enemy bubbleslime = { bubbleslime_init,bubbleslime_attack ,L"�o�u���X���C��" };//�o�u���X���C��
Enemy ghost = { ghost_init,ghost_attack, L"�S�[�X�g" };//�S�[�X�g
Enemy obakevcandle = { obakevcandle_init,obakevcandle_attack, L"���΂��L�����h��" };//���΂��L�����h��
Enemy oyabunghost = { oyabunghost_init,oyabunghost_attack, L"����Ԃ�S�[�X�g" };//BOSS����Ԃ�S�[�X�g

Enemy soilchild= { soilchild_init,soilchild_attack, L"����炵" };//����炵
Enemy meralizard= { meralizard_init,meralizard_attack, L"�������U�[�h" };//�������U�[�h
Enemy nightsplit = { nightsplit_init,nightsplit_attack, L"�i�C�g�E�B�b�v�X" };//�i�C�g�E�B�b�v�X
Enemy gappurin= { gappurin_init,gappurin_attack, L"�K�b�v����" };//�K�b�v����
Enemy sabotenball= { sabotenball_init,sabotenball_attack , L"�T�{�e���{�[��" };//�T�{�e���{�[��
Enemy witch= { witch_init,witch_attack, L"�܂ق�����" };//�܂ق�����
Enemy zairu = { zairu_init,zairu_attack , L"�U�C��" };//�U�C��
Enemy snowqueen= { snowqueen_init,snowqueen_attack , L"�䂫�̂��傤����" };//�䂫�̂��傤����

Enemy obakekinoko= { obakekinoko_init,obakekinoko_attack ,L"���΂��L�m�R" };//���΂��L�m�R
Enemy evilapple= { evilapple_init,evilapple_attack ,L"�G�r���A�b�v��" };//�G�r���A�b�v��
Enemy waraibag= { waraibag_init,waraibag_attack ,L"��炢�Ԃ���" };//��炢�Ԃ���
Enemy hoimislime= { hoimislime_init,hoimislime_attack ,L"�z�C�~�X���C��" };//�z�C�~�X���C��
Enemy skelsoldier= { skelsoldier_init,skelsoldier_attack ,L"�������ւ�" };//�������ւ�
Enemy falsetaiko= { falsetaiko_init,falsetaiko_attack ,L"�j�Z��������" };//�j�Z��������
Enemy behomaslime= { behomaslime_init,behomaslime_attack ,L"�x�z�}�X�����[�h�C��" };//�x�z�}�X���C��
Enemy madolooper= { madolooper_init,madolooper_attack ,L"�}�h���[�p�[*2" };//�}�h���[�p�[*2
Enemy snakebat= { snakebat_init,snakebat_attack ,L"�ւт�������" };//�ւт�������
Enemy kandata= { kandata_init,kandata_attack ,L"�J���_�^" };//�J���_�^
Enemy shieldhipo = { shieldhipo_init,shieldhipo_attack ,L"�V�[���h�q�b�|" };//�V�[���h�q�b�|
Enemy oak = { oak_init,oak_attack ,L"�I�[�NLv20" };//�I�[�NLv20
Enemy kimeera= { kimeera_init,kimeera_attack ,L"�L���[��Lv35" };//�L���[��Lv35
Enemy jami= { jami_init,jami_attack ,L"�W���~" };//�W���~
Enemy berogonload= { berogonload_init,berogonload_attack ,L"�x���S�����[�h" };//�x���S�����[�h
Enemy magekimera= { magekimera_init,magekimera_attack ,L"���C�W�L����" };//���C�W�L����
Enemy minidaemon= { minidaemon_init,minidaemon_attack ,L"�~�j�f�[����" };//�~�j�f�[����
Enemy messaara= { messaara_init,messaara_attack ,L"���b�T�[��" };//���b�T�[��
Enemy gons= { gons_init,gons_attack ,L"�S���Y" };//�S���Y
Enemy gema= { gema_init,gema_attack ,L"�Q�}" };//�Q�}
Enemy buoon= { buoon_init,buoon_attack ,L"�u�I�[��" };//�u�I�[��
Enemy izrairu= { izrairu_init,izrairu_attack ,L"�C�Y���C�[��" };//�C�Y���C�[��
Enemy ramada= { ramada_init,ramada_attack ,L"���}�_" };//���}�_
Enemy iburu= { iburu_init,iburu_attack ,L"�C�[�u��" };//�C�[�u��
Enemy evilswplits= { evilswplits_init,evilswplits_attack ,L"�G�r���X�v���b�c" };//�G�r���X�v���b�c
Enemy springer= { springer_init,springer_attack ,L"�V���v�����K�[" };//�V���v�����K�[
Enemy gema2= { gema2_init,gema2_attack ,L"�Q�}(2���)" };//�Q�}(2���)
Enemy skaldon= { skaldon_init,skaldon_attack ,L"�X�J���h���S��" };//�X�J���h��
Enemy flaredoragon= { flaredoragon_init,flaredoragon_attack ,L"�t���A�h���S��" };//�t���A�h���S��
Enemy wightking= { wightking_init,wightking_attack ,L"���C�g�L���O" };//���C�g�L���O
Enemy mildrous= { mildrous_init,mildrous_attack ,L"�~���h���[�X" };//�~���h���[�X

Enemy estark = { estark_init,estark_action,L"�G�X�^�[�N"};//�G�X�^�[�N
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
	set_Character_base_status(id, character, "��l��", level);
	set_Character_equip_status(id, character, "���^���L���O�̂���", "���^���L���O��낢", "���^���L���O�w����","���^���L���O�̂���");
	spell_copy(character[id].spells ,presetspell1);
}
void bianka_init(int id, Character* character, int level) {
	set_Character_base_status(id, character, "�r�A���J", level);
	spell_copy(character[id].spells , presetspell2);
}
void rex_init(int id, Character* character, int level) {
	set_Character_base_status(id, character, "���b�N�X", level);
	spell_copy(character[id].spells, presetspell2);
}
void tabasa_init(int id, Character* character, int level) {
	set_Character_base_status(id, character, "�^�o�T", level);
	spell_copy(character[id].spells, presetspell2);
}

PresetCharacter hero = {L"��l��",0,hero_init};
PresetCharacter bianka = { L"�r�A���J",1,bianka_init };
PresetCharacter rex = { L"���b�N�X",2,rex_init };
PresetCharacter tabasa = { L"�^�o�T",3,tabasa_init };

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

//�L�����N�^�[�ݒ�


 
void party0_init(Character* character) {
	field_init();
	//addCharacter���ׂĂ��Ă���addEnemy
	add_character_from_name(character, "��l��", 3);
	add_character_from_name(character, "�r�A���J",3);
	add_Enemy(&suraimu, character);
	add_Enemy(&suraimu, character);
	add_Enemy(&suraimu, character);
}//�X���C��*3
void party1_init(Character* character) {
	field_init();
	//addCharacter���ׂĂ��Ă���addEnemy
	add_character_from_name_and_equip(character, "��l��", 8, "�u�[������", "���ттƂ̂ӂ�", "����̂���", "����̂ڂ���");
	add_character_from_name_and_equip(character, "�r�A���J",8, "�������̃i�C�t", "�Ă���̃P�[�v", "���Ȃׂ̂ӂ�", "����̂ڂ���");
	add_Enemy(&oyabunghost, character);
}//����Ԃ�S�[�X�g
void party2_init(Character* character) {
	field_init();
	//addCharacter���ׂĂ��Ă���addEnemy
	add_character_from_name(character, "��l��",8);
	add_character_from_name(character, "�x�r�[�p���T�[",2);
	add_character_from_name(character, "�x��",7);
	add_Enemy(&meralizard, character);
	add_Enemy(&soilchild, character);
	add_Enemy(&nightsplit, character);
}//�������U�[�h�E����炵�E�i�C�g�E�B�b�v�X
void party3_init(Character* character) {
	field_init();
	//addCharacter���ׂĂ��Ă���addEnemy
	add_character_from_name(character, "��l��", 10);
	add_character_from_name(character, "�x�r�[�p���T�[", 5);
	add_character_from_name(character, "�x��", 7);
	add_Enemy(&zairu, character);
}//�U�C��
void party4_init(Character* character) {
	field_init();
	//addCharacter���ׂĂ��Ă���addEnemy
	add_character_from_name_and_equip(character, "��l��", 10, "�u�[������", "���ттƂ̂ӂ�", "����̂���", "����̂ڂ���");
	add_character_from_name_and_equip(character, "�x�r�[�p���T�[", 10,"�Ƃ������z�l", "�Ă���̃P�[�u", "", "����̂ڂ���");
	add_character_from_name_and_equip(character, "�x��", 7,"�����̂�","���ʂ̃��[�u","����̂���","�w�A�o���h");
	add_Enemy(&snowqueen, character);
}//�䂫�̂��傤����
void party5_init(Character* character) {
	field_init();
	//addCharacter���ׂĂ��Ă���addEnemy
	add_character_from_name(character,"��l��", 10);
	add_character_from_name(character,"�w�����[", 3);
	add_Enemy(&obakekinoko, character);
	add_Enemy(&evilapple, character);
}//���΂��L�m�R*3�E�G�r���A�b�v��<��l���E�w�����[>
void party6_init(Character* character) {
	field_init();
	//addCharacter���ׂĂ��Ă���addEnemy
	add_character_from_name_and_equip(character,"��l��",10,"�`�F�[���N���X","���낱�̂�낢","�Ă̂���", "������̃t�[�h");
	add_character_from_name_and_equip(character,"�G�r���A�b�v��",5,"�͂��˂̃L�o", "�X���C���̂ӂ�","","");
	add_character_from_name_and_equip(character,"�w�����[",7,"�`�F�[���N���X", "�h���C�̂ӂ�", "���낱�̂���", "���̂ڂ���");
	add_character_from_name_and_equip(character,"�X���C���i�C�g",1,"�u�����Y�i�C�t","","���낱�̂���", "���̂ڂ���");
	add_Enemy(&suraimu, character);
	add_Enemy(&suraimu, character);
	add_Enemy(&suraimu, character);
	add_Enemy(&suraimu, character);
	add_Enemy(&suraimu, character);
	add_Enemy(&suraimu, character);
	add_Enemy(&suraimu, character);
	add_Enemy(&suraimu, character);
}//�X���C��*8<�G�r���A�b�v���E��l���E�w�����[�E�X���C���i�C�g2,10,7,1>
void party7_init(Character* character) {
	field_init();
	//addCharacter���ׂĂ��Ă���addEnemy
	add_character_from_name_and_equip(character,"��l��", 13,"�`�F�[���N���X", "���낱�̂�낢", "�Ă̂���", "������̃t�[�h");
	add_character_from_name_and_equip(character,"�G�r���A�b�v��",10,"�͂��˂̂邬", "","���낱�̂���", "���̂ڂ���");
	add_character_from_name_and_equip(character,"�w�����[",13,"�`�F�[���N���X", "�h���C�̂ӂ�", "���낱�̂���", "���̂ڂ���");
	add_character_from_name_and_equip(character,"�X���C���i�C�g",10,"�͂��˂̃L�o", "�X���C���̂ӂ�","","");
	add_Enemy(&waraibag, character);
	add_Enemy(&waraibag, character);
	add_Enemy(&hoimislime, character);
	add_Enemy(&hoimislime, character);
	add_Enemy(&hoimislime, character);
	add_Enemy(&skelsoldier, character);
}//��炢�Ԃ���*2�E�z�C�~�X���C��*3�E�������ւ�<�G�r���A�b�v���E��l���E�w�����[�E�X���C���i�C�g12,13,13,12>
void party8_init(Character* character) {
	field_init();
	//addCharacter���ׂĂ��Ă���addEnemy
	add_character_from_name_and_equip(character,"��l��", 16, "�`�F�[���N���X", "���낱�̂�낢", "�Ă̂���", "������̃t�[�h");
	add_character_from_name_and_equip(character,"�G�r���A�b�v��", 15, "�͂��˂̂邬", "", "���낱�̂���", "���̂ڂ���");
	add_character_from_name_and_equip(character,"�w�����[", 15, "�`�F�[���N���X", "�h���C�̂ӂ�", "���낱�̂���", "���̂ڂ���");
	add_character_from_name_and_equip(character,"�X���C���i�C�g", 15, "�͂��˂̃L�o", "�X���C���̂ӂ�", "", "");
	add_Enemy(&falsetaiko, character);
}//�j�Z��������<�G�r���A�b�v���E��l���E�w�����[�E�X���C���i�C�g12,13,13,12>
void party9_init(Character* character) {
	field_init();
	//addCharacter���ׂĂ��Ă���addEnemy
	add_character_from_name_and_equip(character,"��l��",19 , "�`�F�[���N���X", "���낱�̂�낢", "�Ă̂���", "������̃t�[�h");
	add_character_from_name_and_equip(character,"�X���C���i�C�g",20 , "�͂��˂̂邬","", "���낱�̂���", "���̂ڂ���");
	add_character_from_name_and_equip(character,"�G�r���A�b�v��",15, "�͂��˂̃L�o", "�X���C���̂ӂ�","","");
	add_Enemy(&behomaslime, character);
	add_Enemy(&behomaslime, character);
	add_Enemy(&madolooper, character);
	add_Enemy(&madolooper, character);
	add_Enemy(&snakebat, character);
}//�x�z�}�X���C��*2�E�}�h���[�p�[*2�E�ւт�������<��l���E�G�r���A�b�v���E�X���C���i�C�g,14,13,13>
void party10_init(Character* character) {
	field_init();
	//addCharacter���ׂĂ��Ă���addEnemy
	add_character_from_name_and_equip(character,"��l��",25 , "�p�p�X�̂邬", "�h���S�����C��", "�ӂ�����̂���", "�Ă����߂�");
	add_character_from_name_and_equip(character,"�X���C���i�C�g",25, "�͂��˂̂邬", "�͂��˂̂�낢", "�ӂ�����̂���", "�Ă��Ԃ�");
	add_character_from_name_and_equip(character,"�G�r���A�b�v��",20, "�͂��˂̃L�o", "�X���C���̂ӂ�","", "�V���N�n�b�g");
	add_character_from_name_and_equip(character,"�L���[�p���T�[",25 , "�ق̂��̃c��", "����̂ނ˂���","", "�Ă��Ԃ�");
	add_Enemy(&kandata, character);
	add_Enemy(&shieldhipo, character);
}//�J���_�^�E�V�[���h�q�b�|<��l���E�G�r���A�b�v���E�X���C���i�C�g,�L���[�p���T�[,14,13,13,15>
void party11_init(Character* character) {
	field_init();
	//addCharacter���ׂĂ��Ă���addEnemy
	add_character_from_name_and_equip(character,"��l��",25, "�p�p�X�̂邬", "�h���S�����C��", "�ӂ�����̂���", "�Ă����߂�");
	add_character_from_name_and_equip(character,"�X���C���i�C�g",25, "�͂��˂̂邬", "�͂��˂̂�낢", "�ӂ�����̂���", "�Ă��Ԃ�");
	add_character_from_name_and_equip(character,"�G�r���A�b�v��",20, "�͂��˂̃L�o", "�X���C���̂ӂ�","", "�V���N�n�b�g");
	add_character_from_name_and_equip(character,"�L���[�p���T�[",25, "�ق̂��̃c��", "����̂ނ˂���","", "�Ă��Ԃ�");
	add_Enemy(&oak, character);
}//�I�[�NLv20<��l���E�G�r���A�b�v���E�X���C���i�C�g,�L���[�p���T�[,14,14,14,15>
void party12_init(Character* character) {
	field_init();
	//addCharacter���ׂĂ��Ă���addEnemy
	add_character_from_name_and_equip(character,"��l��",25, "�p�p�X�̂邬", "�h���S�����C��", "�ӂ�����̂���", "�Ă����߂�i����Ă񂭂��̂��āj	");
	add_character_from_name_and_equip(character,"�X���C���i�C�g",25, "�͂��˂̂邬", "�͂��˂̂�낢", "�ӂ�����̂���", "�Ă��ԂƁi����Ă񂭂��̂邬�j");
	add_character_from_name_and_equip(character,"�G�r���A�b�v��",20, "�͂��˂̃L�o", "�X���C���̂ӂ�","", "�V���N�n�b�g");
	add_character_from_name_and_equip(character,"�L���[�p���T�[",25, "�ق̂��̃c��", "����̂ނ˂���","", "�Ă��Ԃ�");
	add_Enemy(&kimeera, character);
}//�L���[��Lv35<��l���E�G�r���A�b�v���E�X���C���i�C�g,�L���[�p���T�[,14,14,14,15>
void party13_init(Character* character) {
	field_init();
	//addCharacter���ׂĂ��Ă���addEnemy
	add_character_from_name_and_equip(character,"��l��",30, "�p�p�X�̂邬", "�h���S�����C��", "�ӂ�����̂���", "�Ă����߂�i����Ă񂭂��̂��āj	");
	add_character_from_name_and_equip(character,"�X���C���i�C�g",30, "�͂��˂̂邬", "�͂��˂̂�낢", "�ӂ�����̂���", "�Ă��ԂƁi����Ă񂭂��̂邬�j");
	add_character_from_name_and_equip(character,"�G�r���A�b�v��",20, "�͂��˂̃L�o", "�X���C���̂ӂ�","", "�V���N�n�b�g");
	add_character_from_name_and_equip(character,"�L���[�p���T�[",30, "�ق̂��̃c��", "����̂ނ˂���","", "�Ă��Ԃ�");
	add_Enemy(&jami, character);
}//�W���~<��l���E�G�r���A�b�v���E�X���C���i�C�g,�L���[�p���T�[,14,14,14,15>
void party14_init(Character* character) {
	field_init();
	//addCharacter���ׂĂ��Ă���addEnemy
	add_character_from_name_and_equip(character,"�T���`��",20, "�炢����̃���", "�܂ق��̂�낢", "�ӂ�����̂���", "�����킹�̂ڂ���");
	add_character_from_name_and_equip(character,"�G�r���A�b�v��",20, "�͂��˂̃L�o", "�X���C���̂ӂ�", "","�V���N�n�b�g");
	add_character_from_name_and_equip(character,"�j�̎q",10, "�Ă񂭂��̂邬", "�h���S�����C��", "�Ă񂭂��̂���", "�Ă񂭂��̂��Ԃ�");
	add_character_from_name_and_equip(character,"���̎q",10, "�悤�����̂���", "�v�����Z�X���[�u", "���낱�̂���", "��������̃e�B�A��");
	add_Enemy(&berogonload, character);
	add_Enemy(&magekimera, character);
	add_Enemy(&minidaemon, character);
	add_Enemy(&messaara, character);
}//�x���S�����[�h�E���C�W�L�����E�~�j�f�[�����E���b�T�[��<�T���`���E�G�r���A�b�v���E�j�̎q�E���̎q,20,15,5,5>
void party15_init(Character* character) {
	field_init();
	//addCharacter���ׂĂ��Ă���addEnemy
	add_character_from_name_and_equip(character,"��l��",31, "�h���S���̂�", "�ق̂��̂�낢", "������̂���", "����傭�̂��Ԃ�");
	add_character_from_name_and_equip(character,"�T���`��",30, "�炢����̃���", "�܂ق��̂�낢", "�ӂ�����̂���", "�����킹�̂ڂ���");
	add_character_from_name_and_equip(character,"�j�̎q",29, "�Ă񂭂��̂邬", "�h���S�����C��", "�Ă񂭂��̂���", "�Ă񂭂��̂��Ԃ�");
	add_character_from_name_and_equip(character,"���̎q",29, "�悤�����̂���", "�v�����Z�X���[�u", "���낱�̂���", "��������̃e�B�A��");
	add_Enemy(&gons, character);
}//�S���Y<�T���`���E�j�̎q�E���̎q�E��l��, 26, 23, 22, 22>
void party16_init(Character* character) {
	field_init();
	//addCharacter���ׂĂ��Ă���addEnemy
	add_character_from_name_and_equip(character,"��l��",33, "�h���S���̂�", "�ق̂��̂�낢", "������̂���", "����傭�̂��Ԃ�");
	add_character_from_name_and_equip(character,"�T���`��",31, "�炢����̃���", "�܂ق��̂�낢", "�ӂ�����̂���", "�����킹�̂ڂ���");
	add_character_from_name_and_equip(character,"�j�̎q",30, "�Ă񂭂��̂邬", "�h���S�����C��", "�Ă񂭂��̂���", "�Ă񂭂��̂��Ԃ�");
	add_character_from_name_and_equip(character,"���̎q",30, "�悤�����̂���", "�v�����Z�X���[�u", "���낱�̂���", "��������̃e�B�A��");
	add_Enemy(&gema, character);
}//�Q�}<�T���`���E�j�̎q�E���̎q�E��l��, 26, 23, 22, 22>
void party17_init(Character* character) {
	field_init();
	//addCharacter���ׂĂ��Ă���addEnemy
	add_character_from_name_and_equip(character,"��l��",33 , "�h���S���̂�", "�ق̂��̂�낢", "������̂���", "����傭�̂��Ԃ�");
	add_character_from_name_and_equip(character,"�T���`��",32 , "�炢����̃���", "�܂ق��̂�낢", "�ӂ�����̂���", "�����킹�̂ڂ���");
	add_character_from_name_and_equip(character,"�j�̎q",31 , "�Ă񂭂��̂邬", "�h���S�����C��", "�Ă񂭂��̂���", "�Ă񂭂��̂��Ԃ�");
	add_character_from_name_and_equip(character,"���̎q",31, "�悤�����̂���", "�v�����Z�X���[�u", "���낱�̂���", "��������̃e�B�A��");
	add_Enemy(&buoon, character);
}//�u�I�[��<�T���`���E�j�̎q�E���̎q�E��l��, 26, 23, 22, 22>
void party18_init(Character* character) {
	field_init();
	//addCharacter���ׂĂ��Ă���addEnemy
	add_character_from_name_and_equip(character,"��l��",33, "�h���S���̂�", "��������̃}���g", "������̂���", "����傭�̂��Ԃ�");
	add_character_from_name_and_equip(character,"�T���`��",32, "�炢����̃���", "�܂ق��̂�낢", "�ӂ�����̂���", "�����킹�̂ڂ���");
	add_character_from_name_and_equip(character,"�j�̎q",31, "�Ă񂭂��̂邬", "�Ă񂭂��̂�낢", "�Ă񂭂��̂���", "�Ă񂭂��̂��Ԃ�");
	add_character_from_name_and_equip(character,"���̎q",31, "�悤�����̂���", "�v�����Z�X���[�u", "���낱�̂���", "��������̃e�B�A��");
	add_Enemy(&izrairu, character);
	add_Enemy(&izrairu, character);
	add_Enemy(&izrairu, character);
}//�C�Y���C�[��*3<�T���`���E�j�̎q�E���̎q�E��l��,27,25,24,24>
void party19_init(Character* character) {
	field_init();
	//addCharacter���ׂĂ��Ă���addEnemy
	add_character_from_name_and_equip(character,"��l��",33, "�h���S���̂�", "��������̃}���g", "������̂���", "����傭�̂��Ԃ�");
	add_character_from_name_and_equip(character,"�T���`��",32, "�炢����̃���", "�܂ق��̂�낢", "�ӂ�����̂���", "�����킹�̂ڂ���");
	add_character_from_name_and_equip(character,"�j�̎q",31, "�Ă񂭂��̂邬", "�Ă񂭂��̂�낢", "�Ă񂭂��̂���", "�Ă񂭂��̂��Ԃ�");
	add_character_from_name_and_equip(character,"���̎q",31, "�悤�����̂���", "�v�����Z�X���[�u", "���낱�̂���", "��������̃e�B�A��");
	add_Enemy(&ramada, character);
}//���}�_<�T���`���E�j�̎q�E���̎q�E��l��,27,25,24,24>
void party20_init(Character* character) {
	field_init();
	//addCharacter���ׂĂ��Ă���addEnemy
	add_character_from_name_and_equip(character,"��l��",33, "�h���S���̂�", "��������̃}���g", "������̂���", "����傭�̂��Ԃ�");
	add_character_from_name_and_equip(character,"�T���`��",33, "�炢����̃���", "�܂ق��̂�낢", "�ӂ�����̂���", "�����킹�̂ڂ���");
	add_character_from_name_and_equip(character,"�j�̎q",32, "�Ă񂭂��̂邬", "�Ă񂭂��̂�낢", "�Ă񂭂��̂���", "�Ă񂭂��̂��Ԃ�");
	add_character_from_name_and_equip(character,"���̎q",32, "�悤�����̂���", "�v�����Z�X���[�u", "���낱�̂���", "��������̃e�B�A��");
	add_Enemy(&iburu, character);
}//�C�[�u��<�T���`���E�j�̎q�E���̎q�E��l��,28,25,25,24>
void party21_init(Character* character) {
	field_init();
	//addCharacter���ׂĂ��Ă���addEnemy
	add_character_from_name_and_equip(character,"��l��",36, "�h���S���̂�", "��������̃}���g", "�݂����݂̂���", "���^���L���O�w����");
	add_character_from_name_and_equip(character,"�T���`��",36, "�r�b�O�{�E�K��", "�܂ق��̂�낢", "�I�[�K�V�[���h", "�O���[�g�w����");
	add_character_from_name_and_equip(character,"�j�̎q",35, "�Ă񂭂��̂���", "�Ă񂭂��̂�낢", "�Ă񂭂��̂���", "�Ă񂭂��̂��Ԃ�");
	add_character_from_name_and_equip(character,"���̎q",35, "�悤�����̂���", "�v�����Z�X���[�u", "�݂����݂̂���", "��������̃e�B�A��");
	add_Enemy(&evilswplits, character);
	add_Enemy(&evilswplits, character);
	add_Enemy(&springer,character);
	add_Enemy(&springer, character);
}//�G�r���X�v���b�c*2�E�V���v�����K�[*2<�T���`���E�j�̎q�E���̎q�E��l��,29,27,26,26>
void party22_init(Character* character) {
	field_init();
	//addCharacter���ׂĂ��Ă���addEnemy
	add_character_from_name_and_equip(character,"��l��",36, "�h���S���̂�", "��������̃}���g", "�݂����݂̂���", "���^���L���O�w����");
	add_character_from_name_and_equip(character,"�T���`��",36, "�r�b�O�{�E�K��", "�܂ق��̂�낢", "�I�[�K�V�[���h", "�O���[�g�w����");
	add_character_from_name_and_equip(character,"�j�̎q",35, "�Ă񂭂��̂���", "�Ă񂭂��̂�낢", "�Ă񂭂��̂���", "�Ă񂭂��̂��Ԃ�");
	add_character_from_name_and_equip(character,"���̎q",35, "�悤�����̂���", "�v�����Z�X���[�u", "�݂����݂̂���", "��������̃e�B�A��");
	add_Enemy(&gema2, character);
}//�Q�}(2���)<�T���`���E�j�̎q�E���̎q�E��l��,29,27,26,26>
void party23_init(Character* character) {
	field_init();
	//addCharacter���ׂĂ��Ă���addEnemy
	add_character_from_name_and_equip(character,"��l��", 38, "�h���S���̂�", "��������̃}���g", "�݂����݂̂���", "���^���L���O�w����");
	add_character_from_name_and_equip(character,"�T���`��", 38, "�r�b�O�{�E�K��", "�܂ق��̂�낢", "�I�[�K�V�[���h", "�O���[�g�w����");
	add_character_from_name_and_equip(character,"�j�̎q",37, "�Ă񂭂��̂���", "�Ă񂭂��̂�낢", "�Ă񂭂��̂���", "�Ă񂭂��̂��Ԃ�");
	add_character_from_name_and_equip(character,"���̎q",37, "�悤�����̂���", "�v�����Z�X���[�u", "�݂����݂̂���", "��������̃e�B�A��");
	add_Enemy(&skaldon, character);
	add_Enemy(&flaredoragon, character);
	add_Enemy(&flaredoragon, character);
	add_Enemy(&flaredoragon, character);
	add_Enemy(&wightking, character);
}//�X�J���h���S���E�t���A�h���S�� * 3�E���C�g�L���O<�T���`���E�j�̎q�E���̎q�E��l��,29,27,27,26>
void party24_init(Character* character) {
	field_init();
	//addCharacter���ׂĂ��Ă���addEnemy
	add_character_from_name_and_equip(character,"��l��",40, "�h���S���̂�", "��������̃}���g", "�݂����݂̂���", "���^���L���O�w����");
	add_character_from_name_and_equip(character,"�T���`��",40, "�r�b�O�{�E�K��", "�܂ق��̂�낢", "�I�[�K�V�[���h", "�O���[�g�w����");
	add_character_from_name_and_equip(character,"�j�̎q",38, "�Ă񂭂��̂���", "�Ă񂭂��̂�낢", "�Ă񂭂��̂���", "�Ă񂭂��̂��Ԃ�");
	add_character_from_name_and_equip(character,"���̎q",38, "�悤�����̂���", "�v�����Z�X���[�u", "�݂����݂̂���", "��������̃e�B�A��");
	add_Enemy(&mildrous, character);
}//�~���h���[�X<�T���`���E�j�̎q�E���̎q�E��l��,29,27,27,26>

void party25_init(Character* character) {
	field_init();
	//addCharacter���ׂĂ��Ă���addEnemy
	add_character_from_name_and_equip(character,"��l��",45,"���^���L���O�̂���","���^���L���O��낢","���^���L���O�̂���","���^���L���O�w����");
	add_character_from_name_and_equip(character,"�r�A���J",45, "�O�����K���̃��`", "�v�����Z�X���[�u", "���낱�̂���", "���^���L���O�w����");
	add_character_from_name_and_equip(character, "�j�̎q",45, "���^���L���O�̂���", "���^���L���O��낢", "���^���L���O�̂���", "���^���L���O�w����");
	add_character_from_name_and_equip(character, "���̎q",45, "�O�����K���̃��`", "�v�����Z�X���[�u", "�݂����݂̂���", "��������̃e�B�A��");
	add_Enemy(&estark, character);
}//�G�X�^�[�N<��l���E�r�A���J�E�j�̎q�E���̎q,45,45,45,45>

void (*party_inits[26])(Character* character) = { party0_init,party1_init,party2_init,party3_init,party4_init,party5_init,party6_init,party7_init,party8_init,party9_init,party10_init,party11_init,party12_init,party13_init,party14_init,party15_init,party16_init,party17_init,party18_init,party19_init,party20_init,party21_init,party22_init,party23_init,party24_init,party25_init };


void init(Character* character,int partyid)
{
	setlocale(LC_ALL, "Japanese");
	field_init();
	//addCharacter���ׂĂ��Ă���addEnemy
	party_inits[partyid](character);

}//�X���C��


void status_poison(Character *character)
{
	for (int i = 0; i < fielddata.playernum; i++)
	{
		if (character[i].poison)
		{
			character[i].HP -= (character[i].maxHP / 6);
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			printf("�b%s�͓łɂ��_���[�W���󂯂��@�@�@�@�@�@�b\n", playerName[i]);
			printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
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
				printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
				printf("�b%s�͖ڂ��o�܂����@�@�@�@�@�b\n", playerName[i]);
				printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			}
			else {
				printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
				printf("�b%s�͂��₷�▰���Ă���@�@�@�@�@�b\n", playerName[i]);
				printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
			}
		}
	}

}


void status_check(Character* character) {
	// �Ŕ���
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


// ����
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
	// ���΂₳�̔�r
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

	// agility[] ���o�u���\�[�g
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
	int b_turn = 0;			// �o�g���^�[��

							// �o�g��
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
				printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
				printf("�b%s�͂���ǂ��c���ł������������b\n", playerName[p_turn]);
				printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
				characters[target].HP -= damage;
				printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
				printf("�b%s��%d�̃_���[�W���������b\n", playerName[target], damage);
				printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
				break;
			default:
				damageMin = 65;
				damageMax = 85;
				damage = damageMin + rand() % (damageMax - damageMin);
				printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
				printf("�b%s�͂ق̂����͂����@�b\n", playerName[p_turn]);
				printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
				characters[target].HP -= damage;
				printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
				printf("�b%s��%d�̃_���[�W���������b\n", playerName[target], damage);
				printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
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
					printf("�s���ȃ^�[�Q�b�g");
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
				printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
				printf("�b%s�̂��������@�@�@�@�@�@�@�@�b\n", playerName[p_turn]);
				printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{");
				if (wait)_getch();
				if (keep == 0)
				{
					if (disp)display();
					printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
					printf("�b��S�̈ꌂ�I�@�@�@�@�@�@�@�@�@�@�@�b\n");
					characters[target].HP -= c_damage;
					if (characters[target].HP < 0)
						characters[target].HP = 0;
					printf("�b%s��%s�Ɂ@�@�@�@�@�b\n", playerName[p_turn], playerName[target]);
					printf("�b%d�̃_���[�W��^�����@�@�@�@�@�@�@�b\n", c_damage);
					printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
					if (wait)_getch();
				}
				else
				{
					characters[target].HP -= damage;
					if (characters[target].HP < 0)
						characters[target].HP = 0;
					if (disp)display();
					printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
					printf("�b%s��%s�Ɂ@�@�@�@�@�b\n", playerName[p_turn], playerName[target]);
					printf("�b%d�̃_���[�W��^�����@�@�@�@�@�@�@�b\n", damage);
					printf("�{�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�{\n");
					if (wait)_getch();
				}
			}
			else if (characters[p_turn].action == 1) {
				int target = characters[p_turn].action_spell_target;
				if (target < 0 || target >= fielddata.fullcharacters) {
					printf("�s���ȃ^�[�Q�b�g");
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