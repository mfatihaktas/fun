#!/cac/u01/mfa51/Desktop/Python-3.5.1/install/python3
# import math
import pprint, itertools, random, functools
import matplotlib.pyplot as plot
import numpy as np

def simplex_7_3_codewords_l():
  # base vectors
  v_0 = np.array([0, 0, 0, 1, 1, 1, 1] )
  v_1 = np.array([0, 1, 1, 0, 0, 1, 1] )
  v_2 = np.array([1, 0, 1, 0, 1, 0, 1] )
  
  cw_l = []
  for d in range(8):
    c_l = [int(c) for c in "{0:03b}".format(d) ]
    cw = c_l[0]*v_0 + c_l[1]*v_1 + c_l[2]*v_2
    cw_l.append(np.array([b%2 for b in cw] ) )
  return cw_l

def standart_arr_simplex_7_3():
  cw_l = simplex_7_3_codewords_l()
  print("cw_l= \n{}".format(pprint.pformat(cw_l) ) )
  not_covered_word_l = ["{0:07b}".format(i) for i in range(2**7) ]
  def weight_compare(w_1, w_2):
    w_1 = [int(c) for c in w_1]
    w_2 = [int(c) for c in w_2]
    if sum(w_1) < sum(w_2):
      return -1
    elif sum(w_1) > sum(w_2):
      return 1
    else:
      return 0
  not_covered_word_l.sort(key=functools.cmp_to_key(weight_compare) )
  
  coset_leader_l = []
  while len(not_covered_word_l) > 0:
    # coset_leader = not_covered_word_l.pop(0)
    coset_leader = not_covered_word_l[0]
    # print("coset_leader= {}".format(coset_leader) )
    coset_leader_l.append(coset_leader)
    for c in cw_l:
      coset_leader_ = np.array([int(b) for b in coset_leader] )
      # print("coset_leader_+c= {}".format(''.join([str(b%2) for b in coset_leader_+c] ) ) )
      not_covered_word_l.remove(''.join([str(b%2) for b in coset_leader_+c] ) )
    # cw_l.append(coset_leader)
    # cw_in_arr_l.append(int(''.join([str(b) for b in coset_leader] ), 2) )
    # print("size= {}, cw_in_arr_l= \n{}".format(len(cw_in_arr_l), cw_in_arr_l) )
  print("size= {}, coset_leader_l= \n{}".format(len(coset_leader_l), pprint.pformat(coset_leader_l) ) )
  # print("size= {}, cw_in_arr_l= \n{}".format(len(cw_in_arr_l), cw_in_arr_l) )
  for cl in coset_leader_l:
    print("coset {}".format(''.join([str(b) for b in cl] ) ) )
    for cw in cw_l:
      cl_ = np.array([int(b) for b in cl] )
      print("{}".format(''.join([str(b%2) for b in cl_+cw] ) ) )

def hamming_7_4_codewords_l():
  # base vectors
  v_0 = np.array([1, 1, 1, 0, 0, 0, 0] )
  v_1 = np.array([1, 0, 0, 1, 1, 0, 0] )
  v_2 = np.array([0, 1, 0, 1, 0, 1, 0] )
  v_3 = np.array([1, 1, 0, 1, 0, 0, 1] )
  
  cw_l = []
  for d in range(16):
    c_l = [float(c) for c in "{0:04b}".format(d) ]
    cw = c_l[0]*v_0 + c_l[1]*v_1 + c_l[2]*v_2 + c_l[3]*v_3
    cw_l.append(np.array([b%2 for b in cw] ) )
  return cw_l

def write_hist_pairwise_distance_between_codewords():
  cw_l = hamming_7_4_codewords_l()
  
  # distance_num_map = {}
  distance_l = []
  for comb in itertools.combinations(cw_l, 2):
    distance_l.append(np.count_nonzero(comb[0] != comb[1] ) )
    # d = np.count_nonzero(comb[0] != comb[1] )
    # if not d in distance_num_map:
    #   distance_num_map[d] = 0
    # distance_num_map[d] += 1
  # print("distance_num_map= \n{}".format(pprint.pformat(distance_num_map) ) )
  
  print("distance_l= {}".format(distance_l) )
  # plot.hist(distance_l, normed=1, color='g', bins=(np.arange(8) - 0.5) )
  plot.hist(distance_l, normed=1, color='g', rwidth=0.6, bins=np.arange(9)-0.5)
  plot.xlabel('Hamming distance')
  plot.ylabel('Frequency')
  plot.title('Histogram of pairwise distances between codewords\nfor [7, 4, 3] code')
  plot.grid(True)
  plot.savefig("hist_pairwise_distance_between_codewords.png")
  # plot.show()

def write_hist_codeword_weights():
  cw_l = hamming_7_4_codewords_l()
  
  weight_l = []
  for cw in cw_l:
    weight_l.append(np.count_nonzero(cw != np.zeros(len(cw) ) ) )
  
  print("weight_l= {}".format(weight_l) )
  plot.hist(weight_l, normed=1, color='g', rwidth=0.6, bins=np.arange(9)-0.5)
  plot.xlabel('Weight')
  plot.ylabel('Frequency')
  plot.title('Histogram of codeword weights\nfor [7, 4, 3] code')
  plot.grid(True)
  plot.savefig("hist_codeword_weights.png")
  # plot.show()

def write_hist_distance_from_rand_codeword_to_others():
  cw_l = hamming_7_4_codewords_l()
  
  distance_l = []
  rand_cw = cw_l[random.randrange(0, len(cw_l) ) ]
  for cw in cw_l:
    d = np.count_nonzero(cw != rand_cw)
    if d != 0:
      distance_l.append(d)
    
  print("distance_l= {}".format(distance_l) )
  plot.hist(distance_l, normed=1, color='g', rwidth=0.6, bins=np.arange(9)-0.5)
  plot.xlabel('Hamming distance')
  plot.ylabel('Frequency')
  plot.title('Histogram of the distances between a non-zero random codeword\nand all the others for [7, 4, 3] code')
  plot.grid(True)
  plot.savefig("hist_distance_from_rand_codeword_to_others.png")
  # plot.show()

if __name__ == "__main__":
  # codewords_l = get hamming_7_4_codewords_l()
  # print("codewords_l= {}".format(pprint.pformat(codewords_l) ) )
  # write_hist_pairwise_distance_between_codewords()
  # write_hist_codeword_weights()
  # write_hist_distance_from_rand_codeword_to_others()
  standart_arr_simplex_7_3()