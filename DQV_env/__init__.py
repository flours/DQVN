from gym.envs.registration import register

register(
    id='dqv-v0',
    entry_point='DQV_env.DQVdllload:DQVenv'
)