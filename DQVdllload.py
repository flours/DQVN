import ctypes
import random
import numpy as np

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
        self.libc.env_init.restype=None
        self.libc.env_init.argtypes=None
        self.libc.env_init()

    def reset(self):
        self.libc.init(self.character_data)
        return self.character_data
    def step(self,actions):
        for i,action in enumerate(actions):
            self.setAction(action,i,4)
        self.libc.status_check(self.character_data)
        self.libc.battle_main(self.character_data,False,False)

        end_flag=False
        if (self.character_data[0].HP is self.character_data[1].HP is self.character_data[2].HP is self.character_data[3].HP is 0) or self.character_data[4].HP is 0:
            end_flag=True

        reward=0
        for i in range(4):
            #reward+=self.character_data[i].HP*(self.character_data[i].can_action*2)/self.character_data[i].maxHP/4
            if(self.character_data[i].HP==0):
                reward+=self.character_data[i].HP
            else:
                reward-=1000
        reward-=self.character_data[4].HP#/self.character_data[4].maxHP
#        print(self.character_data[i].can_action)
#        print(reward)

        return self.character_data, reward, end_flag, None

    def setAction(self,action,playerId,target):
        self.character_data[playerId].action_spell_target=target
        if action==0:
            self.character_data[playerId].action=0
        elif action==self.character_data[playerId].spells.size+1:
            self.character_data[playerId].action=2
            self.character_data[playerId].action_tool=0
        else:
            self.character_data[playerId].action=1
            self.character_data[playerId].action_spell=action-1
    def printInfo(self,actions):
        for i,action in enumerate(actions):
            if action==0:
                print("こうげき,",end='')
            elif action==self.character_data[i].spells.size+1:
                print("たたかいのどらむ,",end='')
            else:
                print(self.character_data[i].spells.mp[action-1],',',end='')
        print()
    def setRandomAction(self):
        for i in range(4):
            self.character_data[i].action = random.randint(0, 2);
            self.character_data[i].action_spell = random.randint(0, self.character_data[i].spells.size-1);
            self.character_data[i].action_spell_target = random.randint(0,3);
            self.character_data[i].action_tool = 0;
    def getRandomActions(self):

        return np.random.randint(0,self.character_data[0].spells.size+2),np.random.randint(0,self.character_data[1].spells.size+2),np.random.randint(0,self.character_data[2].spells.size+2),np.random.randint(0,self.character_data[3].spells.size+2)
