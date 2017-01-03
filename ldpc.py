#!/cac/u01/mfa51/Desktop/Python-3.5.1/install/python3
# import math
import pprint, itertools, random, functools, math, numpy, copy
import matplotlib.pyplot as plot

def _gen_biregular_graph(d_t, d_b, n_b):
  n_b = int(n_b/d_t)*d_t
  n_t = int(n_b*d_b/d_t)
  
  n_v, n_c = n_t, n_b
  d_v, d_c = d_t, d_b
  adj_matrix = numpy.zeros(shape=(n_c, n_v) )
  for k in range(int(n_c*d_c/n_v) ):
    for i in range(int(n_v/d_c) ):
      c_i = int(k*n_v/d_c + i)
      adj_matrix[c_i, i*d_c:(i+1)*d_c] = numpy.ones(shape=(1, d_c) )
  
  def shuffle_by_col(matrix, n_col):
    def swap_cols(i, j):
      col_i = copy.copy(matrix[:, i] )
      matrix[:, i] = copy.copy(matrix[:, j] )
      matrix[:, j] = col_i
    # for i in range(n_col):
    #   # print("before swap; matrix= \n{}".format(matrix) )
    #   swap_cols(i, col_perm_l[i] )
    #   # print("after swap i= {}, j= {}; matrix= \n{}".format(i, col_perm_l[i], matrix) )
    #   # break
    for c in range(10):
      col_perm_l = numpy.random.permutation(n_col)
      matrix_ = copy.copy(matrix)
      for i in range(n_col):
        matrix_[:, i] = copy.copy(matrix[:, col_perm_l[i] ] )
      matrix = matrix_
    
    return matrix
  # print("before shuffle_by_col; adj_matrix= \n{}".format(adj_matrix) )
  adj_matrix = shuffle_by_col(adj_matrix, n_v)
  # print("after shuffle_by_col; adj_matrix= \n{}".format(adj_matrix) )
  
  t_adj_l = [[] for i in range(n_t) ]
  b_adj_l = [[] for i in range(n_b) ]
  for i in range(n_c):
    for j in range(n_v):
      if adj_matrix[i, j] == 1:
        b_adj_l[i].append(j)
        t_adj_l[j].append(i)
  # check if the graph has cycles of length 4
  def rows_overlap(matrix, i_1, i_2):
    counter = 0
    for j in range(n_v):
      if (matrix[i_1, j] == 1) and (matrix[i_1, j] == matrix[i_2, j] ):
        counter = counter + 1
    return counter >= d_b
  
  def num_cycle(matrix):
    num = 0
    for i in range(n_c):
      for i_ in range(i, n_c):
        if rows_overlap(matrix, i, i_):
          num = num + 1
    return num
  # num_cycle = num_cycle(adj_matrix)
  # print("num_cycle= {}".format(num_cycle) )
  
  # print("n_b= {}, b_adj_l= \n{}".format(n_b, pprint.pformat(b_adj_l) ) )
  # print("n_t= {}, t_adj_l= \n{}".format(n_t, pprint.pformat(t_adj_l) ) )
  # return (num_cycle == 0, t_adj_l, b_adj_l)
  return (True, t_adj_l, b_adj_l)

def gen_biregular_graph(d_t, d_b, n_b):
  n_t = int(n_b*d_b/d_t)
  t_adj_l = [[] for i in range(n_t) ]
  b_adj_l = [[] for i in range(n_b) ]
  # """
  # t_adj_l, b_adj_l = [n_t*[]], [n_b*[]]
  # print("n_t= {}, t_adj_l= {}".format(n_t, pprint.pformat(t_adj_l) ) )
  # print("n_b= {}, b_adj_l= {}".format(n_b, pprint.pformat(b_adj_l) ) )
  # for t_i in range(n_t):
  #   for i in range(d_t):
  #     c = 0
  #     while 1:
  #       c = c + 1
  #       if c > 20:
  #         print("c= {}, still could not finish!".format(c) )
  #         break
  #       adj_i = random.randrange(0, n_b)
  #       print("adj_i= {}".format(adj_i) )
  #       if (len(b_adj_l[adj_i] ) < d_b) and (adj_i not in t_adj_l[t_i] ):
  #         t_adj_l[t_i].append(adj_i)
  #         b_adj_l[adj_i].append(t_i)
  #         break
  def get_rand_adj_i_l(top, c_i):
    i_l = None
    if top:
      if len(t_adj_l[c_i] ) == d_t:
        return []
      i_l = [i for i in range(n_b) if (i not in t_adj_l[c_i] ) and (len(b_adj_l[i]) < d_b) ]
    else:
      if len(b_adj_l[c_i] ) == d_b:
        return []
      i_l = [i for i in range(n_t) if (i not in b_adj_l[c_i] ) and (len(t_adj_l[i]) < d_t) ]
    # print("top= {}, c_i= {}, i_l= {}".format(top, c_i, i_l) )
    # print("n_b= {}, b_adj_l= \n{}".format(n_b, pprint.pformat(b_adj_l) ) )
    # print("n_t= {}, t_adj_l= \n{}".format(n_t, pprint.pformat(t_adj_l) ) )
    return i_l
  
  counter = 0
  top = True # Top
  from_i = random.randrange(0, n_t)
  terminate = False
  while not terminate:
    to_i_l = None
    _counter = 0
    while 1:
      if _counter > 10:
        terminate = True
        break
      _counter = _counter + 1
      to_i_l = get_rand_adj_i_l(top, from_i)
      if len(to_i_l) == 0:
        if top:
          from_i = random.choice([i for i in range(n_t) if len(t_adj_l[i] ) < d_t] )
        else:
          from_i = random.choice([i for i in range(n_b) if len(b_adj_l[i] ) < d_b] )
        # from_i = random.randrange(0, top*n_t + (not top)*n_b)
      else:
        break
    if not terminate:
      to_i = random.choice(to_i_l)
      if top:
        t_adj_l[from_i].append(to_i)
        b_adj_l[to_i].append(from_i)
      else:
        b_adj_l[from_i].append(to_i)
        t_adj_l[to_i].append(from_i)
      top = not top
      from_i = to_i
      counter = counter + 1
      if counter == n_t*d_t:
        break
  # print("terminate= {}".format(terminate) )
  # print("n_t= {}, t_adj_l= \n{}".format(n_t, pprint.pformat(t_adj_l) ) )
  # print("n_b= {}, b_adj_l= \n{}".format(n_b, pprint.pformat(b_adj_l) ) )
  return (not terminate, t_adj_l, b_adj_l)
  # """
  # n_row, n_col = n_b, n_t

def try_to_decode(err_frac, t_adj_l, b_adj_l, d_t, d_b):
  # print("try_to_decode:: started; err_frac= {}".format(err_frac) )
  n_t, n_b = len(t_adj_l), len(b_adj_l)
  # n_err_t = math.floor(err_frac*n_t)
  t_conf_l, b_conf_l = n_t*[1], n_b*[0]
  err_i_l = []
  # while len(err_i_l) < n_err_t:
  #   err_i = random.randrange(0, n_t)
  #   if err_i not in err_i_l:
  #     err_i_l.append(err_i)
  for i in range(n_t):
    if float(random.randrange(100)/100) <= err_frac:
      err_i_l.append(i)
  # print("err_i_l= {}".format(err_i_l) )
  for i in err_i_l:
    t_conf_l[i] = 0
  # print("t_conf_l= {}".format(t_conf_l) )
  
  terminate = False
  counter = 0
  while not terminate:
    terminate = True
    counter = counter + 1
    fixed_t_i_l = []
    for t_i in err_i_l:
      for b_i in t_adj_l[t_i]:
        if sum([t_conf_l[t_adj_i] for t_adj_i in b_adj_l[b_i] ] ) >= d_b-1:
          t_conf_l[t_i] = 1
          fixed_t_i_l.append(t_i)
          terminate = False
          break
    for fixed_t_i in fixed_t_i_l:
      err_i_l.remove(fixed_t_i)
    # print("counter= {}, err_i_l= {}".format(counter, err_i_l) )
    if len(err_i_l) == 0:
      break
  # if len(err_i_l) > 0:
  #   print("failed with err_i_l= {}".format(err_i_l) )
  #   print("t_conf_l= {}".format({i:conf for i,conf in enumerate(t_conf_l) } ) )
  #   print("n_t= {}, t_adj_l= \n{}".format(n_t, pprint.pformat({i:l for i,l in enumerate(t_adj_l) } ) ) )
  #   print("n_b= {}, b_adj_l= \n{}".format(n_b, pprint.pformat({i:l for i,l in enumerate(b_adj_l) } ) ) )
  return len(err_i_l) == 0

def try_to_decode_(err_frac, v_adj_l, c_adj_l, d_v, d_c):
  n_v, n_c = len(v_adj_l), len(c_adj_l)
  n_err_t = math.floor(err_frac*n_v)
  v_nerr_l, c_nerr_l = n_v*[0], n_c*[0]
  err_i_l = []
  while len(err_i_l) < n_err_t:
    err_i = random.randrange(0, n_v)
    if err_i not in err_i_l:
      err_i_l.append(err_i)
  # for i in range(n_v):
  #   if float(random.randrange(100)/100) <= err_frac:
  #     err_i_l.append(i)
  # print("err_i_l= {}".format(err_i_l) )
  for i in err_i_l:
    v_nerr_l[i] = 1
  print("v_nerr_l= {}".format(v_nerr_l) )
  for c, c_adj in enumerate(c_adj_l):
    nerr = 0
    for v in c_adj:
      if v_nerr_l[v] == 1:
        nerr = nerr + 1
    c_nerr_l[c] = nerr
  print("c_nerr_l= {}".format(c_nerr_l) )
  
  done = False
  while not done:
    done = True
    
    to_be_fixed_v = None
    for c, c_nerr in enumerate(c_nerr_l):
      if to_be_fixed_v == None:
        if c_nerr == 1:
          for v in c_adj_l[c]:
            if v_nerr_l[v] == 1:
              to_be_fixed_v = v
              done = False
              break
      else:
        break
    _c_nerr_l = copy.copy(c_nerr_l)
    if to_be_fixed_v != None:
      v_nerr_l[to_be_fixed_v] = 0
      for c in v_adj_l[to_be_fixed_v]:
        c_nerr_l[c] = c_nerr_l[c] - 1
      print("before/after fixing v= {}, \n\t _c_nerr_l= {}, \n\t c_nerr_l= {}".format(to_be_fixed_v, _c_nerr_l, c_nerr_l) )
  print("after decoding trial; \n v_nerr_l= {}, \n c_nerr_l= {}".format(v_nerr_l, c_nerr_l) )
  return sum(c_nerr_l) == 0

def ldpc_sim():
  d_t, d_b = 3, 6
  n_b = 20
  num_graph_gen_trial = 1 # 100
  num_decode_trial = 1 # 2 # 10
  num_success = 0
  
  err_frac__decode_success_l_m = {}
  for i in range(num_graph_gen_trial):
    (success, t_adj_l, b_adj_l) = _gen_biregular_graph(d_t, d_b, n_b)
    if success:
      # num_success = num_success + 1
      # print("len(t_adj_l)= {}, t_adj_l= \n{} \n len(b_adj_l)= {}, b_adj_l= \n{}".format(len(t_adj_l), t_adj_l, len(b_adj_l), b_adj_l) )
      # for err_frac in numpy.arange(0, 0.3, 0.1):
      for err_frac in numpy.arange(0.1, 0.3, 0.1):
        if err_frac not in err_frac__decode_success_l_m:
          err_frac__decode_success_l_m[err_frac] = []
        success_decode_l = [try_to_decode_(err_frac, t_adj_l, b_adj_l, d_t, d_b) for j in range(num_decode_trial) ]
        success_decode = sum(success_decode_l)/num_decode_trial
        print("err_frac= {}, success_decode= {}".format(err_frac, success_decode) )
        err_frac__decode_success_l_m[err_frac].append(success_decode)
      # break
    else:
      print("gen_biregular_graph failed!")
  # print("success_frac= {}".format(num_success/num_graph_gen_trial) )
  # print("err_frac__decode_success_l_m= {}".format(pprint.pformat(err_frac__decode_success_l_m) ) )
  
  err_frac__decode_success_frac_m = {}
  for err_frac,decode_success_l in err_frac__decode_success_l_m.items():
    err_frac__decode_success_frac_m[err_frac] = float(sum(decode_success_l)/len(decode_success_l) )
  print("err_frac__decode_success_frac_m= {}".format(pprint.pformat(err_frac__decode_success_frac_m) ) )

if __name__ == "__main__":
  ldpc_sim()
  
  # _gen_biregular_graph(d_t=3, d_b=6, n_b=10)
  