# -*- coding: utf-8 -*-


#https://qiita.com/ReoNagai/items/4c5c2c2b1175f898c0d6のほぼコピペ

import numpy as np
#import gym
import random
import sys

from collections import deque
from keras.layers import Input, Activation, Dense, Flatten, RepeatVector, Reshape
from keras.layers.convolutional import Conv2D
from keras.models import Model
from keras import backend as K

import cv2
from skimage.color import rgb2gray
from skimage.transform import resize
# rmsprop
import keras

from DQVdllload import DQVenv

partyid=sys.argv[1]

np.set_printoptions(suppress=True)

file_history = open("history.txt", "w")
file_history.close()

import random
class Agent:
    def __init__(self, env):
        self.env = env

        self.q_network,self.q_network2,self.q_network3,self.q_network4 = self.ModelCreate()
        self.t_network,self.t_network2,self.t_network3,self.t_network4 = self.ModelCreate()

        self.q_network.summary()
        self.max_q = [0,0,0,0]
        self.ave_q = [0,0,0,0]

    def ModelCreate(self):
        ip = Input(shape=(30,))
        h = Dense(64, activation='relu')(ip)
        last = Dense(128, activation='relu')(h)
        last2 = Dense(128, activation='relu')(h)
        last3 = Dense(128, activation='relu')(h)
        last4 = Dense(128, activation='relu')(h)
        #(攻撃1+道具1+スペル10)*対象8
        out = Dense(12*11)(last)
        out2 = Dense(12*11)(last2)
        out3 = Dense(12*11)(last3)
        out4 = Dense(12*11)(last4)
        model = Model(ip, output=out)
        model2 = Model(ip, output=out2)
        model3 = Model(ip, output=out3)
        model4 = Model(ip, output=out4)

        rmsprop = keras.optimizers.RMSprop(lr=0.00025, rho=0.95, epsilon=0.01, decay=0.0)
        model.compile(rmsprop, 'mse')
        model2.compile(rmsprop, 'mse')
        model3.compile(rmsprop, 'mse')
        model4.compile(rmsprop, 'mse')
        return model,model2,model3,model4

    def getAction(self, state, epsilon):
        # epsilon-greedy
        if np.random.rand() < epsilon:
            return [random.randint(0,2)*8+random.randint(0,self.env.allnum-1) for i in range(self.env.playernum)]

        q_value = self.Predict(state)
        actions=[]
        for i in range(self.env.playernum):
            actions.append(np.argmax(q_value[i]))
        
        #print(actions[0]//8,actions[0]%8,actions[1]//8,actions[1]%8)
        #for i in range(self.env.playernum):
        #    if actions[i]//8==0:
        #        print('攻撃',end=' ')
        #    elif actions[i]//8==1:
        #        print('道具',end=' ')
        #    else:
        #        try:
        #            print(self.env.character_data[i].spells[actions[i]//8-2].contents.name,end=' ')
        #        except:
        #            print("NULLSPELL",end=' ')
        #    print(self.env.character_data[actions[i]%8].name,end=' ')
        #print(self.env.character_data[0].HP,self.env.character_data[1].HP,self.env.character_data[2].HP,self.env.character_data[3].HP,self.env.character_data[4].HP,'HPs',end=' ')

        return actions

    def Train(self, x_batch, y_batch,i):
        if i ==0:
            return self.q_network.train_on_batch(x_batch.reshape(32,30), y_batch)
        if i==1:
            self.q_network2.train_on_batch(x_batch.reshape(32,30), y_batch)
        if i==2:
            self.q_network3.train_on_batch(x_batch.reshape(32,30), y_batch)
        if i==3:            
            self.q_network4.train_on_batch(x_batch.reshape(32,30), y_batch)

    def Predict(self, x_batch):
        return self.t_network.predict_on_batch(x_batch),self.t_network2.predict_on_batch(x_batch),self.t_network3.predict_on_batch(x_batch),self.t_network4.predict_on_batch(x_batch)

    def WeightCopy(self):
        for i in range(4):
            self.t_network.layers[i].set_weights(self.q_network.layers[i].get_weights())
            self.t_network2.layers[i].set_weights(self.q_network2.layers[i].get_weights())
            self.t_network3.layers[i].set_weights(self.q_network3.layers[i].get_weights())
            self.t_network4.layers[i].set_weights(self.q_network4.layers[i].get_weights())

    # 学習の結果を保存しておく
    def SaveHistory(self, episode, reward, epsilon, next_state):
        msg = "[{reward:" + str(reward) + "} {epsilon:" + str(epsilon) + "}]\n"
        # 保存
        file_history = open("history.txt", "a")
        file_history.write(msg)
        file_history.close()


def CreateBatch(agent, replay_memory, batch_size, discount_rate,idx):
    minibatch = random.sample(replay_memory, batch_size)
    state, action, reward, state2, end_flag =  map(np.array, zip(*minibatch))

    x_batch = state.reshape(batch_size,30)
    # この状態の時に各行動をした場合のQ値(y_batch変数はactionそれぞれに対するQ値)を，現在のネットワークで推定
    y_batch = agent.Predict(x_batch)[idx]
    # 今のQ値よりももっと高かったら更新
    agent.max_q[idx] = y_batch[idx].max() # 保存用
    
    #Q値のアベレージ
    agent.ave_q[idx] =y_batch[idx].mean() # 保存用
    
    # 1つ未来における各行動に対するそれぞれのQ値
    next_q_values = agent.Predict(state2.reshape(batch_size,30))[idx]

    for i in range(batch_size):
    # ベルマン方程式 Q(s,a) = r + gamma * max_a Q(s', a')
        y_batch[i, action[i]] = reward[i] + discount_rate * np.max(next_q_values[i]) * (1 - end_flag[i])

    return x_batch, y_batch


def PrintInfo(episode, reward, epsilon):
    msg = "[episode:" + str(episode) + " } {reward:" + str(reward) + "} {epsilon:" + str(epsilon) + "}]"
    #print(msg)


def RewardClipping(reward):
    return np.sign(reward)

def Preprocess(character_data,playernum,enemynum):
    max_playernum=4
    max_enemynum=8
    
    input_chara=[]
    
    for i in range(playernum):
        input_chara.extend([character_data[i].HP,character_data[i].strength,character_data[i].endurance,character_data[i].attack,character_data[i].defense])
    for i in range(max_playernum - playernum):
        input_chara.extend([0,0,0,0,0])
    for i in range(enemynum):
        input_chara.extend([character_data[i+playernum].HP])
    for i in range(max_enemynum - enemynum):
        input_chara.extend([0])
    input_chara.extend([playernum,enemynum])
    return np.array(input_chara).reshape(1,30)

def main():
    n_episode = 12000
    discount_rate = 0.99
    max_memory = 20000
    batch_size = 32
    epsilon = 1.0
    min_epsilon = 0.1
    reduction_epsilon = (1. - min_epsilon) / n_episode

    #env_name = 'CartPole-v0'
    #env_name = 'Breakout-v0'
    #env = gym.make(env_name)
    env=DQVenv()
    agent = Agent(env)
    replay_memory = [deque(),deque(),deque(),deque()]
    

    # ゲーム再スタート
    episode=0
    step_num=0
    while episode>=-1:
        episode+=1
        episode_reward = 0
        end_flag = False

        state = env.reset(int(partyid))#-------------------------------------------------------------reset
        state = Preprocess(state,env.playernum,env.enemynum)

        epsilon = min_epsilon + (1. - min_epsilon) * (n_episode - episode) / n_episode
        if min_epsilon>=epsilon:
            epsilon = min_epsilon
        # ボールが落ちるまで
        while not end_flag:
            action = agent.getAction(state, epsilon)
            state2, reward, end_flag, damages = env.step(action)
            step_num+=1
            # 前処理
            state2 = Preprocess(state2,env.playernum,env.enemynum)
            episode_reward += reward
            # 報酬のクリッピング
            #reward = RewardClipping(reward)
            # リプレイメモリに保存
            for i in range(4):
                reward=0
                for j in range(4):
                    reward+=damages[j]*0.5
                reward+=damages[i]*0.5
                #print('reward:',reward)
                #episode_reward+=reward
                replay_memory[i].append([state, action, reward, state2, end_flag])
                # リプレイメモリが溢れたら前から削除
                if len(replay_memory[i]) > max_memory:
                    replay_memory[i].popleft()
                # リプレイメモリが溜まったら学習
                #if len(replay_memory[i]) > batch_size*2:
                if len(replay_memory[i]) > max_memory/2 :
                    x_batch, y_batch = CreateBatch(agent, replay_memory[i], batch_size, discount_rate,i)
                    #print(y_batch)
                    agent.Train(x_batch, y_batch,i)
            print('step',str(step_num),*agent.max_q,*agent.ave_q)

            state = state2
            
            enemyHPnum=0
            for i in range(env.enemynum):
                enemyHPnum += env.character_data[env.playernum+i].maxHP-env.character_data[env.playernum+i].HP
            # 可視化
            #env.render()
        print(str(episode)+","+str(enemyHPnum))
        # Q-networkの重みをTarget-networkにコピー
        agent.WeightCopy()
        if episode != 0 and episode % 1000 == 0:
            agent.t_network.save_weights("weight.h5")
            #print(episode)

        #PrintInfo(episode, episode_reward, epsilon)
        #if episode % 10 ==0:
        #    print()
        #    print("episode:",episode,":epsilon:",epsilon)
        #    print()

        
        agent.SaveHistory(episode, episode_reward, epsilon, state2)

    env.close()



if __name__ == '__main__':
    main()