import ctypes
import random


class SpellData(ctypes.Structure):
    _fields_=[
        ("name",ctypes.POINTER(ctypes.c_char_p*17)),
        ("mp",ctypes.POINTER(ctypes.c_int32)),
        ("isSelectTarget",ctypes.POINTER(ctypes.c_bool)),
        ("size",ctypes.c_int32)
    ]

class Character(ctypes.Structure):
    _fields_=[
        ("base_strength",ctypes.c_int32),
        ("agility",ctypes.c_int32),
        ("base_endurance",ctypes.c_int32),
        ("maxHP",ctypes.c_int32),
        ("maxMP",ctypes.c_int32),

        ("poison",ctypes.c_int32),
        ("paralysis",ctypes.c_int32),
        ("sleep",ctypes.c_int32),
        ("can_action",ctypes.c_int32),
        ("dragon",ctypes.c_int32),

        ("bless",ctypes.c_double),

        ("strength",ctypes.c_int32),
        ("endurance",ctypes.c_int32),
        ("attack",ctypes.c_int32),
        ("defense",ctypes.c_int32),
        ("HP",ctypes.c_int32),
        ("MP",ctypes.c_int32),
        ("action",ctypes.c_int32),
        ("action_spell",ctypes.c_int32),
        ("action_spell_target",ctypes.c_int32),
        ("action_tool",ctypes.c_int32),
        ("spells",SpellData)
    ]





class DQVenv:

    def __init__(self):
        self.libc=ctypes.CDLL("Project5.dll")
        self.libc.init.restype=None
        self.libc.init.argtypes=(Character*5,)

        self.libc.status_check.restype=None
        self.libc.status_check.argtypes=(Character*5,)

        self.libc.battle_main.restype=None
        self.libc.battle_main.argtypes=(Character*5,ctypes.c_bool,ctypes.c_bool)
        self.character_data=(Character*5)()

    def reset(self):
        self.libc.init(self.character_data)
        return self.character_data
    def step(self,action):
        self.setAction(action)
        self.libc.status_check(self.character_data)
        self.libc.battle_main(self.character_data,False,False)

        end_flag=False
        if (self.character_data[0].HP is self.character_data[1].HP is self.character_data[2].HP is self.character_data[3].HP is 0) or self.character_data[4].HP is 0:
            end_flag=True

        reward=0
        #for i in range(4):
        #    reward+=self.character_data[i].HP
        reward=self.character_data[4].maxHP-self.character_data[4].HP

        return self.character_data, reward, end_flag, None

    def setAction(self,action):
        if action==0:
            self.character_data[0].action=0
        elif action==12:
            self.character_data[0].action=2
            self.character_data[0].action_tool=0
        else:
            self.character_data[0].action=1
            self.character_data[0].action_spell=action-1

    def setRandomAction(self):
        for i in range(4):
            self.character_data[i].action = random.randint(0, 2);
            self.character_data[i].action_spell = random.randint(0, self.character_data[i].spells.size-1);
            self.character_data[i].action_spell_target = random.randint(0,3);
            self.character_data[i].action_tool = 0;
