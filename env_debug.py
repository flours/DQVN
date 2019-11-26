from DQVdllload import DQVenv
from msvcrt import getch
import sys



#45レベ　主人公ビアンカレックスタバサの前提
env=DQVenv()
if len(sys.argv)==2:
    data=env.reset(int(sys.argv[1]))
else:
    data=env.reset(0)

print("入力はカーソルキーとエンターでします")

Enter=13

ext_key=224
left=75
right=77
Ctrl_C=3
esc_key=27

import sys
def select(actions):
    print()
    selected=0
    while True:
        print('\r',end='')
        for i,action in enumerate(actions):
            ch="  "
            if i==selected:ch="→"
            print(ch,action,end=',',flush=True)

        key = ord(getch())

        if key==Enter:
            print()
            return selected
        if key==esc_key:
            print()
            return -1
        if key==Ctrl_C:
            exit()
        if key==ext_key:
            key = ord(getch())
            if key==left:
                selected-=1
            if key==right:
                selected+=1
        
        if selected<0:selected=0
        if selected>=len(actions):selected=len(actions)-1
        
def dispAll(playerdata):
    print(playerdata.base_strength,"base_strength")
    print(playerdata.base_endurance,"endurance")
    print(playerdata.maxHP,"maxHP")
    print(playerdata.maxMP,"maxMP")
    print(playerdata.poison,"poison")
    print(playerdata.paralysis,"paralysis")
    print(playerdata.sleep,"sleep")
    print(playerdata.can_action,"can_action")
    print(playerdata.dragon,"dragon")
    print(playerdata.bless,"bless")
    print(playerdata.strength,"strength")
    print(playerdata.endurance,"endurance")
    print(playerdata.attack,"attack")
    print(playerdata.defense,"defence")
    print(playerdata.HP,"HP")
    print(playerdata.MP,"MP")
    print(playerdata.action,"action")
    print(playerdata.action_spell,"action_spell")
    print(playerdata.action_tool,"action_tool")
    print(playerdata.name,"name")
    print("spells")
    try:
        for i in range(20):
            print(playerdata.spells[i].contents.name,"name")
            print(playerdata.spells[i].contents.mp,"mp")
            print(playerdata.spells[i].contents.isSelectTarget,"isSelectTarget")
            print(playerdata.spells[i].contents.main,"main")
    except:
        pass

def get_spell_list(playerdata):
    names=[]
    try:
        for i in range(20):
            names.append(playerdata.spells[i].contents.name)
    except:
        pass
    return names
    
def get_name_list(playerdatas,env):
    names=[]
    try:
        for i in range(env.allnum):
            names.append(playerdatas[i].name)
    except:
        pass
    return names
    
for i in range(env.playernum+env.enemynum):
    dispAll(data[i])
    
while True:
    actions=[]
    targets=[]


    for i in range(env.playernum):
        print("-------------------------------"+data[i].name+"の行動選択--------------------------------")
        action=select(["たたかう","どうぐ","じゅもん"])
        if action==2:
            action+=select(get_spell_list(data[i]))
        print("対象(対象選択意味ないやつでも表示してる),")
        name_list=get_name_list(data,env)
        name_list.reverse()
        
        target=len(name_list)-select(name_list)-1
        actions.append(action)
        targets.append(target)
    data,reward,end_flag,_=env.step(actions,targets)
    print("名前:HP:MP",)
    for i in range(env.allnum):
        print(data[i].name,data[i].HP,data[i].MP,)
    if end_flag:
        break
