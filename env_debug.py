from DQVdllload import DQVenv
from msvcrt import getch

#45レベ　主人公ビアンカレックスタバサの前提

env=DQVenv()
env.reset()


preset_spells=[["ホイミ","キアリー","バギ","スカラ","バギマ","ベホマ","ザオラル","メガザル","バイキルト"],
              ["メラ","バイキルト","ベギラマ","メラミ","ベギラゴン","メラゾーマ"],
              ["スクルト","ベホイミ","キアリク","ベホマ","フバーハ","ライデイン","ザオリク","ベホマラー","ギガデイン","ミナデイン"],
              ["ヒャド","イオ","ヒャダルコ","バイキルト","ルカナン","イオラ","マヒャド","ドラゴラム","イオナズン"]]

chara_names=["主人公","ビアンカ","レックス","タバサ","スライム"]

playernum=4
enemynum=1
print("入力はカーソルキーとエンターでします")

Enter=13

ext_key=224
left=75
right=77
Ctrl_C=3
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
    print("spells")
    try:
        for i in range(20):
            print(playerdata.spells[i].contents.name,"name")
            print(playerdata.spells[i].contents.mp,"mp")
            print(playerdata.spells[i].contents.isSelectTarget,"isSelectTarget")
            print(playerdata.spells[i].contents.main,"main")
    except:
        pass

while True:
    actions=[]
    targets=[]
    
    for i in range(4):
        action=select(["たたかう","どうぐ","じゅもん"])
        if action==2:
            action+=select(preset_spells[i])
        print("対象(対象選択意味ないやつでも表示してる)")
        target=select(chara_names)
        actions.append(action)
        targets.append(target)
    data,reward,end_flag,_=env.step(actions,targets)
    print("HP:",data[0].HP,data[1].HP,data[2].HP,data[3].HP,data[4].HP,"reward:",reward)
    if end_flag:
        break
