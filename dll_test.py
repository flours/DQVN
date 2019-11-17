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

    def __init__(self,num_enemy=2,num_party_members=1):
        self.num_party_members=num_party_members
        self.num_enemy=num_enemy


        self.libc=ctypes.CDLL("DQV_Dll_2.dll")
        self.libc.init.restype=None
        self.libc.init.argtypes=(Character*(self.num_party_members+self.num_enemy),)

        self.libc.status_check.restype=None
        self.libc.status_check.argtypes=(Character*(self.num_party_members+self.num_enemy),)

        self.libc.battle_main.restype=None
        self.libc.battle_main.argtypes=(Character*(self.num_party_members+self.num_enemy),ctypes.c_bool,ctypes.c_bool)
        self.character_data=(Character*(self.num_party_members+self.num_enemy))()


    def reset(self):
        self.libc.init(self.character_data)
        return self.character_data
        
    def step(self,action,playerId,targetId):
        self.setAction(action,playerId,targetId)
        self.libc.status_check(self.character_data)
        self.libc.battle_main(self.character_data,True,True)

        end_flag=True
        for i in range(self.num_party_members):
            if self.character_data[i].HP is not 0:
                end_flag=False
        for i in range(self.num_enemy,self.num_party_members):
            if self.character_data[i].HP is not 0:
                end_flag=False

        reward=0
        for i in range(self.num_party_members):
            reward+=self.character_data[i].HP
        for i in range(self.num_enemy,self.num_party_members):
            reward-=self.character_data[i].HP

        return self.character_data, reward, end_flag, None

    def setAction(self,action,playerId,target):
        self.character_data[playerId].action_spell_target=target
        if action==0:
            self.character_data[playerId].action=0
        elif action==self.character_data[playerId].spell_num+1:
            self.character_data[playerId].action=2
            self.character_data[playerId].action_tool=0
        else:
            self.character_data[playerId].action=1
            self.character_data[playerId].action_spell=action-1

    def setRandomAction(self):
        for i in range(self.num_party_members):
            self.character_data[i].action = random.randint(0, 2);
#            self.character_data[i].action_spell = random.randint(0, self.character_data[i].spells.size-1);
            self.character_data[i].action_spell_target = random.randint(0,2);
            self.character_data[i].action_tool = 0;

#env=DQVenv()
#env.reset()


#while True:
#    input("waiting..")
#    print(env.character_data[0].HP,env.character_data[1].HP,env.character_data[2].HP)
#    env.step(0,0,random.randint(1,2))