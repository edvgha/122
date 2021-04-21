import roboschool
import gym

print("\n".join(['- ' + spec.id for spec in gym.envs.registry.all() if spec.id.startswith('Roboschool')]))

import torch 
print(torch.__version__)

