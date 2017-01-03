#!/usr/bin/python
import math

# l: arrival rate, m: service rate
def m_d_1_avg_system_time(l, m):
  ro = l/m
  return 1/m + ro/(2*m*(1 - ro) )


# l: arrival rate, m: service rate of a single server, c: # of servers
def m_d_c_approx_avg_system_time(l, m, c):
  ro = l/m
  pi_0 = math.pow(sum([math.pow(ro, n)/math.factorial(n) for n in range(0, c) ] ) \
                  + math.pow(ro, c)/(math.factorial(c)*(1 - ro/c) ), -1)
  N_q_M = pi_0*math.pow(ro, c + 1)/(c*math.factorial(c)*math.pow(1 - ro/c, 2) )
  N_q_D = 0.5*N_q_M
  return 1/m + N_q_D/l;

if __name__ == "__main__":
  