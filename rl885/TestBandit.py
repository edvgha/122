import numpy as np
import MDP
import RL2


def sampleBernoulli(mean):
    ''' function to obtain a sample from a Bernoulli distribution

    Input:
    mean -- mean of the Bernoulli
    
    Output:
    sample -- sample (0 or 1)
    '''

    if np.random.rand(1) < mean: return 1
    else: return 0


# Multi-arm bandit problems (3 arms with probabilities 0.3, 0.5 and 0.7)
T = np.array([[[1]],[[1]],[[1]]])
R = np.array([[0.3],[0.5],[0.7]])
discount = 0.999
mdp = MDP.MDP(T,R,discount)
banditProblem = RL2.RL2(mdp,sampleBernoulli)

# Test epsilon greedy strategy
egb = np.zeros([200], dtype=float)
for i in range(1000):
    empiricalMeans, rewards = banditProblem.epsilonGreedyBandit(nIterations=200)
    egb += rewards
egb = egb / float(1000)

# Test UCB strategy
ucb = np.zeros([200], dtype=float)
for i in range(1000):
    empiricalMeans, rewards = banditProblem.UCBbandit(nIterations=200)
    ucb += rewards
ucb = ucb / float(1000)

# Test Thompson sampling strategy
thompson = np.zeros([200], dtype=float)
for i in range(1000):
    empiricalMeans, rewards = banditProblem.thompsonSamplingBandit(prior=np.ones([mdp.nActions,2]),nIterations=200)
    thompson += rewards
thompson = thompson / float(1000)


import matplotlib.pyplot as plt
fig, ax = plt.subplots()
ax.plot(range(0, 200),egb.tolist())
ax.plot(range(0, 200),ucb.tolist())
ax.plot(range(0, 200),thompson.tolist())
ax.legend(['Epsilon greedy bandit', 'UCB', 'Thompson sampling'])
plt.show()