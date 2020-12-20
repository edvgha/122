import numpy as np
import MDP
import collections

class RL:
    def __init__(self,mdp,sampleReward):
        '''Constructor for the RL class

        Inputs:
        mdp -- Markov decision process (T, R, discount)
        sampleReward -- Function to sample rewards (e.g., bernoulli, Gaussian).
        This function takes one argument: the mean of the distributon and 
        returns a sample from the distribution.
        '''

        self.mdp = mdp
        self.sampleReward = sampleReward

    def sampleRewardAndNextState(self,state,action):
        '''Procedure to sample a reward and the next state
        reward ~ Pr(r)
        nextState ~ Pr(s'|s,a)

        Inputs:
        state -- current state
        action -- action to be executed

        Outputs: 
        reward -- sampled reward
        nextState -- sampled next state
        '''

        reward = self.sampleReward(self.mdp.R[action,state])
        cumProb = np.cumsum(self.mdp.T[action,state,:])
        nextState = np.where(cumProb >= np.random.rand(1))[0][0]
        return [reward,nextState]

    def selectEpsilonGreedyAction(self, state, epsilon, Q):
        '''
        Q - Q-values of (self.mdp.nActions, self.mdp.nStates) shape
        '''
        return np.argmax(Q[:, state],axis = 0) if np.random.rand(1) > epsilon else np.random.randint(0, self.mdp.nActions)

    def getBestActionValueFor(self, nextState, Q):
        '''
        Q - Q-values of (self.mdp.nActions, self.mdp.nStates) shape
        '''
        return np.amax(Q[:, nextState], axis=0)

    def qLearning(self,s0,initialQ,nEpisodes,nSteps,epsilon=0,temperature=0):
        '''qLearning algorithm.  Epsilon exploration and Boltzmann exploration
        are combined in one procedure by sampling a random action with 
        probabilty epsilon and performing Boltzmann exploration otherwise.  
        When epsilon and temperature are set to 0, there is no exploration.

        Inputs:
        s0 -- initial state
        initialQ -- initial Q function (|A|x|S| array)
        nEpisodes -- # of episodes (one episode consists of a trajectory of nSteps that starts in s0
        nSteps -- # of steps per episode
        epsilon -- probability with which an action is chosen at random
        temperature -- parameter that regulates Boltzmann exploration

        Outputs: 
        Q -- final Q function (|A|x|S| array)
        policy -- final policy
        '''

        Q = np.zeros([self.mdp.nActions,self.mdp.nStates])
        policy = np.zeros(self.mdp.nStates,int)
        counts = collections.defaultdict(int)
        avgR = collections.defaultdict(int)

        for s in range(nEpisodes):
            state = s0
            avg = 0.0
            for _ in range(nSteps):
                action = self.selectEpsilonGreedyAction(state, epsilon, Q)
                counts[(state, action)] += 1.0
                learningRate = 1 / counts[(state, action)] if counts[(state, action)] != 0 else 0
                reward, nextState = self.sampleRewardAndNextState(state, action)
                avg += reward
                bestActionValue = self.getBestActionValueFor(nextState, Q)
                Q[action, state] += learningRate * (reward + self.mdp.discount * bestActionValue - Q[action, state])
                state = nextState
            avgR[s] = avg / (nSteps + 0.0)

        for s in range(self.mdp.nStates):
            best_Q = 0
            best_A = 0
            for a in range(self.mdp.nActions):
                if Q[a, s] > best_Q:
                    best_Q = Q[a, s]
                    best_A = a
            policy[s] = best_A

        return [Q,policy, avgR]