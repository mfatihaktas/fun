#!/cac/u01/mfa51/Desktop/Python-3.5.1/install/python3
import pprint, itertools, random
import matplotlib.pyplot as plot
import numpy as np
from math import factorial as fac

def binomial(x, y):
  try:
    binom = fac(x) // fac(y) // fac(x - y)
  except ValueError:
    binom = 0
  return binom
    
def plot_hamming_P_u__P_e():
  num_p_samples = 100
  p_list = [i/num_p_samples for i in range(num_p_samples)]
  def P_u(p):
    return p**7 + 7*p**4*(1-p)**3 + 7*p**3*(1-p)**4
  def P_e(p):
    n = 7
    P_e = 0
    for w in range(2, n+1):
      P_e += binomial(n, w) * p**w * (1-p)**(n-w)
    return P_e
  P_u_list = [P_u(p) for p in p_list]
  P_e_list = [P_e(p) for p in p_list]
  
  plot.figure(1)
  plot.subplot(211)
  plot.grid(True)
  plot.plot(p_list, P_u_list, 'k-')
  plot.xlabel(r'$p$')
  plot.ylabel(r'$P_u$')
  plot.subplot(212)
  plot.grid(True)
  plot.plot(p_list, P_e_list, 'b-')
  plot.xlabel(r'$p$')
  plot.ylabel(r'$P_e$')
  plot.tight_layout()
  # ax = plot.gca()
  # ax.grid(True)
  plot.savefig("plot_hamming_P_u__P_e.png")
  # plot.show()

if __name__ == "__main__":
  plot_hamming_P_u__P_e()