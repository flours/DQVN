# gymの環境としてのDQV_envを作成しました

プログラムを実行するフォルダにDQV_envフォルダをコピーしてください
DQV_env/__init__.pyでimport DQV_envされたときにdqv-v0を登録します

```
import gym
import DQV_env
env=gym.make('dqv-v0')
```
こんな感じでenvを作れます一応DQN.pyの変更を確認すればどんなふうにかえれば動くのかわかるかと
githubならファイル名の右の方にあるコミットコメントみたいなやつをクリックすれば差分が表示できるのでそれでみましょう
(文字コードとかかわると全部変更になるから意味ないことあるけど)



