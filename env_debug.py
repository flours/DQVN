from DQVdllload import DQVenv

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


def select(actions):
    while True:
        for i,action in enumerate(actions):
            print(i,action,end=',')
        num=input("数字を入力してください")
        try:
            if int(num) < len(actions):
                return int(num)
        except:
            pass

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
env.step(actions,targets)

