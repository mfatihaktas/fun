#!/cac/u01/mfa51/Desktop/Python-3.5.1/install/python3
# import math

import matplotlib.pyplot  as plt
import queueing_tool as qt
import numpy as np

# Queueing parameters
a, b = 158, 50
h  = 13.0
nc = 8
mu = 30.0

# Data collection variables and parameters
N  = 10 # 500
w0 = np.array([] )
s0 = np.zeros(N)

# Queueing process functions
rate = lambda t: a + b - b * np.cos(2 * np.pi * t / h)
arr = lambda t: qt.poisson_random_measure(t, rate, a + 2 * b)
ser = lambda t: t + np.random.exponential(1 / mu)

# The Queue
q = qt.QueueServer(nServers=nc, deactive_t=h,
                   arrival_f=arr, service_f=ser)
for k in range(N):
  q.collect_data = True
  q.set_active()
  q.simulate(t=h+5)
  
  data  = q.fetch_data()
  s0[k] = np.std(data[:,1] - data[:, 0] )
  w0 = np.hstack((w0, data[:,1] - data[:, 0] ) )
  
  q.clear()

# """
# The queueing network definition
adjacency = {
  0: {1: {'edge_type': 1} },
  1: {k: {'edge_type': 2} for k in range(2, 2 + nc) }
}

# edge_type = {0: {1: 1}, 1: {k: 2 for k in range(2, 22)}}
g = qt.adjacency2graph(adjacency)

qclass = {1: qt.QueueServer, 2: qt.QueueServer }
qargs  = {1: {'nServers': 1, 'deactive_t': h,
              'arrival_f': arr, 
              'service_f': lambda t: t,
              'AgentClass': qt.GreedyAgent},
          2: {'nServers': 1,
              'service_f': ser} }

qn = qt.QueueNetwork(adjacency, q_classes=qclass, q_args=qargs)
w1 = np.array([] )
s1 = np.zeros(N)

for k in range(N) :
  qn.start_collecting_data(eType=2)
  qn.initialize(eType=1)
  qn.simulate(t=h+5)
  
  data  = qn.data_queues(eType=2)
  good  = data[:,1] > 0
  s1[k] = np.std(data[good, 1] - data[good, 0] )
  w1 = np.hstack((w1, data[good,1] - data[good, 0] ) )
  qn.clear()
# """
# Transform from hours to minutes
w0 = w0 * 60
s0 = s0 * 60
w1 = w1 * 60
s1 = s1 * 60

plt.style.use('ggplot')

## Waiting time plots
fig, ax = plt.subplots(2, 1, dpi=80, figsize=(10,14) )
n, bins, patches = ax[1].hist(w1, bins=50, range=(0, 40), normed=True)
n, bins, patches = ax[0].hist(w0, bins=bins, normed=True)

ylim = max(ax[0].get_ylim()[1], ax[1].get_ylim()[1] )

out = ax[1].axvline(np.mean(w1), linestyle='--')
out = ax[1].set_title('Traditional checkout')
out = ax[1].set_xlabel('Waiting times (in minutes)')
out = ax[1].set_ylabel('Percentage of customers')
out = ax[1].set_ylim((0, ylim) )
out = ax[1].text(np.mean(w1) + max(w1) / 100.0, 0.5 * ylim,
                 'Mean of {0}'.format(round(np.mean(w1), 1) ) )

out = ax[0].axvline(np.mean(w0), linestyle='--')
out = ax[0].set_title("Trader Joe's checkout")
out = ax[0].set_xlabel('Waiting times (in minutes)')
out = ax[0].set_ylabel('Percentage of customers')
out = ax[0].set_ylim((0, ylim) )
out = ax[0].text(np.mean(w0) + max(w0) / 100.0, 0.5 * ylim, 
                 'Mean of {0}'.format(round(np.mean(w0), 1) ) )

plt.savefig('waiting_times_both_systems.png', dpi=80,
            bbox_inches='tight', transparent=True)
#plt.show()


## Waiting time standard deviation plots
fig, ax = plt.subplots(2, 1, dpi=80, figsize=(10,14) )
n, bins, patches = ax[1].hist(s1, bins=35, normed=True)
n, bins, patches = ax[0].hist(s0, bins=bins, normed=True)

ylim = max(ax[0].get_ylim()[1], ax[1].get_ylim()[1] )

out = ax[1].axvline(np.mean(s1), linestyle='--')
out = ax[1].set_title('Traditional checkout')
out = ax[1].set_xlabel('Standard deviations of waiting times')
out = ax[1].set_ylabel('Percentage of observations')
out = ax[1].set_ylim((0, ylim) )
out = ax[1].text(np.mean(s1) + max(s1) / 100.0, 0.95 * ylim,
                 'Mean of {0}'.format(round(np.mean(s1), 1) ) )

out = ax[0].axvline(np.mean(s0), linestyle='--')
out = ax[0].set_title("Trader Joe's checkout")
out = ax[0].set_xlabel('Standard deviation of waiting times')
out = ax[0].set_ylabel('Percentage of observations')
out = ax[0].set_ylim((0, ylim) )
out = ax[0].text(np.mean(s0) + max(s0) / 100.0, 0.95 * ylim, 
                 'Mean of {0}'.format(round(np.mean(s0), 1) ) )

plt.savefig('waiting_time_std_both_systems.png', dpi=80, 
            bbox_inches='tight', transparent=True)
#plt.show()

# For better display purposes
qn.g.new_vertex_property('pos')
pos = {}
for v in qn.g.nodes():
  if v == 0 :
    pos[v] = [0, 1]
  elif v == 1 :
    pos[v] = [0, 0.5]
  else :
    pos[v] = [-3.5 + (v - 2.0), 0]

qn.draw(fname="store.png", figsize=(16, 3.5), pos=pos)

# if __name__ == "__main__":
  