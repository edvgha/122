import numpy as np
import MDP
import collections

class RL2:
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

    def sampleSoftmaxPolicy(self,policyParams,state):
        '''Procedure to sample an action from stochastic policy
        pi(a|s) = exp(policyParams(a,s))/[sum_a' exp(policyParams(a',s))])
        This function should be called by reinforce() to selection actions

        Inputs:
        policyParams -- parameters of a softmax policy (|A|x|S| array)
        state -- current state

        Outputs: 
        action -- sampled action
        '''

        # temporary value to ensure that the code compiles until this
        # function is coded
        action = 0
        # TODO
        return action

    def selectEpsilonGreedyAction(self, T, R, V):
        for actionId in range(0, self.mdp.nActions):
            w = R[actionId] + self.mdp.discount * T[actionId].dot(V)
            if actionId != 0:
                M = np.vstack([M, w])
            else:
                M = w
        return np.argmax(M, axis=0)

    def valueIteration(self, T, R, V):
        newV = np.zeros(self.mdp.nStates)
        for actionId in range(0, self.mdp.nActions):
                newV = np.maximum(newV, R[actionId] + self.mdp.discount * T[actionId].dot(V))
        return newV

    def modelBasedRL(self,s0,defaultT,initialR,nEpisodes,nSteps,epsilon=0):
        '''Model-based Reinforcement Learning with epsilon greedy 
        exploration.  This function should use value iteration,
        policy iteration or modified policy iteration to update the policy at each step

        Inputs:
        s0 -- initial state
        defaultT -- default transition function when a state-action pair has not been vsited
        initialR -- initial estimate of the reward function
        nEpisodes -- # of episodes (one episode consists of a trajectory of nSteps that starts in s0
        nSteps -- # of steps per episode
        epsilon -- probability with which an action is chosen at random

        Outputs: 
        V -- final value function
        policy -- final policy
        '''
        T = defaultT
        R = initialR
        V = np.zeros(self.mdp.nStates)
        policy = np.zeros(self.mdp.nStates,int)
        sa = collections.defaultdict(float)
        sas = collections.defaultdict(float)
        avgR = collections.defaultdict(float)
        
        for s in range(nEpisodes):
            S = s0
            avg = 0.0
            for _ in range(nSteps):
                A = 0
                if np.random.rand(1) < epsilon:
                    A = np.random.randint(0, self.mdp.nActions)
                else:
                    A = self.selectEpsilonGreedyAction(T, R, V)[S]
                r, nS = self.sampleRewardAndNextState(S, A)
                sa[(S, A)] += 1.0
                avg += r
                sas[(S, A, nS)] += 1.0
                R[A, S] = (r + (sa[(S, A)] - 1) * R[A, S]) / sa[(S, A)]
                for Si in range(self.mdp.nStates):
                    T[A, S, Si] = sas[(S, A, Si)] / sa[(S, A)]
                V = self.valueIteration(T, R, V)
                S = nS
            avgR[s] = avg / (nSteps + 0.0)


        policy = self.selectEpsilonGreedyAction(T, R, V)
        return [V,policy,avgR]    

    def epsilonGreedyBandit(self,nIterations):
        '''Epsilon greedy algorithm for bandits (assume no discount factor)

        Inputs:
        nIterations -- # of arms that are pulled

        Outputs: 
        empiricalMeans -- empirical average of rewards for each arm (array of |A| entries)
        '''

        empiricalMeans = np.zeros(self.mdp.nActions)
        N = np.zeros(self.mdp.nActions)
        rewards = np.empty([nIterations], dtype = float)

        for i in range(nIterations):
            epsilon = 1 / float(i + 1)
            A = np.argmax(empiricalMeans) if np.random.rand(1) > epsilon else np.random.randint(0, self.mdp.nActions)
            R, _ = self.sampleRewardAndNextState(0, A)
            rewards[i] = R
            N[A] += 1
            empiricalMeans[A] = empiricalMeans[A] + (1 / float(N[A])) * (R - empiricalMeans[A])

        return empiricalMeans, rewards

    def thompsonSamplingBandit(self,prior,nIterations,k=1):
        '''Thompson sampling algorithm for Bernoulli bandits (assume no discount factor)

        Inputs:
        prior -- initial beta distribution over the average reward of each arm (|A|x2 matrix such that prior[a,0] is the alpha hyperparameter for arm a and prior[a,1] is the beta hyperparameter for arm a)  
        nIterations -- # of arms that are pulled
        k -- # of sampled average rewards

        Outputs: 
        empiricalMeans -- empirical average of rewards for each arm (array of |A| entries)
        '''

        empiricalMeans = np.zeros(self.mdp.nActions)
        rewards = np.empty([nIterations], dtype = float)
        for i in range(nIterations):
            for A in range(self.mdp.nActions):
                samples = np.empty([k])
                for K in range(k):
                    samples[K] = np.random.beta(prior[A, 0], prior[A, 1])
                empiricalMeans[A]= np.average(samples)
            action = np.argmax(empiricalMeans)
            R, _ = self.sampleRewardAndNextState(0, action)
            rewards[i] = R
            if R == 1:
                prior[action, 0] += 1
            else:
                prior[action, 1] += 1

        return empiricalMeans, rewards

    def UCBbandit(self,nIterations):
        '''Upper confidence bound algorithm for bandits (assume no discount factor)

        Inputs:
        nIterations -- # of arms that are pulled

        Outputs: 
        empiricalMeans -- empirical average of rewards for each arm (array of |A| entries)
        '''

        empiricalMeans = np.zeros(self.mdp.nActions)
        N = np.zeros(self.mdp.nActions)
        rewards = np.empty([nIterations], dtype = float)

        for i in range(nIterations):
            A = np.argmax(empiricalMeans + np.sqrt(2 * np.log(i + 0.01) / (N + 0.01))) 
            R, _ = self.sampleRewardAndNextState(0, A)
            rewards[i] = R
            empiricalMeans[A] = (N[A] * empiricalMeans[A] + R) / float(N[A] + 1)
            N[A] += 1

        return empiricalMeans, rewards

    def reinforce(self,s0,initialPolicyParams,nEpisodes,nSteps):
        '''reinforce algorithm.  Learn a stochastic policy of the form
        pi(a|s) = exp(policyParams(a,s))/[sum_a' exp(policyParams(a',s))]).
        This function should call the function sampleSoftmaxPolicy(policyParams,state) to select actions

        Inputs:
        s0 -- initial state
        initialPolicyParams -- parameters of the initial policy (array of |A|x|S| entries)
        nEpisodes -- # of episodes (one episode consists of a trajectory of nSteps that starts in s0)
        nSteps -- # of steps per episode

        Outputs: 
        policyParams -- parameters of the final policy (array of |A|x|S| entries)
        '''

        # temporary values to ensure that the code compiles until this
        # function is coded
        policyParams = np.zeros((self.mdp.nActions,self.mdp.nStates))
        # TODO
        return policyParams    
