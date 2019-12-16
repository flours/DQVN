import ctypes
import random


class Spell(ctypes.Structure):
    _fields_=[
        ("name",ctypes.c_wchar*(8*2+1)),
        ("mp",ctypes.c_int32),
        ("isSelectTarget",ctypes.c_int32),
        ("main",ctypes.CFUNCTYPE(None,ctypes.c_int,ctypes.c_int))
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
        ("spells",ctypes.POINTER(Spell)*20),
        ("name",ctypes.c_wchar*(10*2+1)),
    ]


class FieldData(ctypes.Structure):
    _fields=[
        ("playernum",ctypes.c_int32),
        ("enemynum",ctypes.c_int32),
        ("fullcharacters",ctypes.c_int32)
    ]




class DQVenv:

    def __init__(self):
        
        self.prevhp=[]
        self.playernum= 0
        self.enemynum = 0
        self.allnum=0
        self.maxcharacternum = 12
        
        self.libc=ctypes.CDLL("Project5.dll")
        self.libc.init.restype=None
        self.libc.init.argtypes=(Character*self.maxcharacternum,)

        self.libc.status_check.restype=None

        self.libc.status_check.argtypes=(Character*self.maxcharacternum,)
        

        self.libc.battle_main.restype=None
        self.libc.battle_main.argtypes=(Character*self.maxcharacternum,ctypes.c_bool,ctypes.c_bool)
        self.libc.get_fielddata.restype=None
        self.libc.get_fielddata.argtypes=(ctypes.POINTER(ctypes.c_uint32),ctypes.POINTER(ctypes.c_uint32))
        self.libc.get_damages.restype=None
        self.libc.get_damages.argtypes=(ctypes.POINTER(ctypes.c_int32),ctypes.POINTER(ctypes.c_int32),ctypes.POINTER(ctypes.c_int32),ctypes.POINTER(ctypes.c_int32))
        self.character_data=(Character*self.maxcharacternum)()
        

    def reset(self,id):
        self.libc.init(self.character_data,id)
        i = ctypes.c_uint32()
        i2 = ctypes.c_uint32()
        self.libc.get_fielddata(i,i2)
        self.playernum=i.value
        self.enemynum=i2.value
        self.allnum=self.playernum+self.enemynum
        self.prevhp=[0]*self.allnum
        for i in range(self.enemynum):
            self.prevhp[self.playernum+i]=self.character_data[self.playernum+i].HP
        return self.character_data
            
    def step(self,action):
        for i in range(len(action)):
            self.setAction(action[i]//12,i,action[i]%12)
        self.libc.status_check(self.character_data)
        self.libc.battle_main(self.character_data,False,False)

        end_flag=False
        for i in range(self.playernum):
            if (self.character_data[i].HP is 0):
                if(i != self.playernum-1):
                    continue
                else:
                    end_flag=True
            else:
                break
        for i in range(self.enemynum):
            i+=self.playernum
            if (self.character_data[i].HP is 0):
                if(i != self.playernum+self.enemynum-1):
                    continue
                else:
                    print('win')
                    end_flag=True
            else:
                break

        reward=0
        d0 = ctypes.c_int32(0)
        d1 = ctypes.c_int32(0)
        d2 = ctypes.c_int32(0)
        d3 = ctypes.c_int32(0)
        
        self.libc.get_damages(d0,d1,d2,d3)
        damages=[d0.value,d1.value,d2.value,d3.value]

        return self.character_data, reward, end_flag, damages

    def setAction(self,action,id,target):
        self.character_data[id].action_spell_target=target
        if action==0:
            self.character_data[id].action=0
        else:
            self.character_data[id].action=1
            self.character_data[id].action_spell=action-1

    def setRandomAction(self):
        for i in range(self.playernum):
            self.character_data[i].action = random.randint(0, 2);
            self.character_data[i].action_spell = random.randint(0, self.character_data[i].spells.size-1);
            self.character_data[i].action_spell_target = random.randint(0,3);
            self.character_data[i].action_tool = 0;

if __name__=='__main__':
    env=DQVenv()
    env.reset()
