#include "dp.h"

int min_num_coins_for_sum(std::vector<int> coin_v, int sum,
                          std::map<int, int>& sum__num_coins_map)
{
  if (sum == 0)
    return 0;
  
  std::vector<int> coin_to_use_v;
  for (std::vector<int>::iterator it = coin_v.begin(); it != coin_v.end(); it++) {
    if (*it <= sum)
      coin_to_use_v.push_back(*it);
  }
  
  if (sum != 0 && coin_to_use_v.empty() )
    return std::numeric_limits<int>::max();
  
  std::vector<int> next_sum_v;  
  for (std::vector<int>::iterator it = coin_to_use_v.begin(); it != coin_to_use_v.end(); it++)
    next_sum_v.push_back(min_num_coins_for_sum(coin_v, sum - *it, sum__num_coins_map) );
  
  if (sum__num_coins_map.count(sum) != 0)
    return sum__num_coins_map[sum];
  
  int result = 1 + *std::min_element(next_sum_v.begin(), next_sum_v.end() );
  
  sum__num_coins_map[sum] = result;
  return result;
}

void sizeof_lns(int upto_i, int seq_size, int* seq_,
                std::map<int, int>& upto_i__sizeof_lns_map)
{
  int _sizeof_lns = 1;
  
  for (int i = upto_i - 1; i >= 0; i--) {
    if (seq_[i] <= seq_[upto_i] ) {
      if (upto_i__sizeof_lns_map[i] + 1 > _sizeof_lns)
        _sizeof_lns = upto_i__sizeof_lns_map[i] + 1;
    }
  }
  upto_i__sizeof_lns_map[upto_i] = _sizeof_lns;
  
  if (upto_i == seq_size - 1)
    return;
  else
    sizeof_lns(upto_i + 1, seq_size, seq_, upto_i__sizeof_lns_map);
}

int sizeof_lcs(int i, const char* s1_, int j, const char* s2_,
               std::map<i_j_pair, char>& i_j__common_char_map,
               std::map<i_j_pair, i_j_pair>& i_j__lower_i_j_map,
               std::map<i_j_pair, int>& i_j__sizeof_lcs_map)
{
  i_j_pair p = std::make_pair(i, j);
  
  if (i_j__sizeof_lcs_map.count(p) != 0)
    return i_j__sizeof_lcs_map[p];
  
  if (i == 0) {
    for (int j_ = 0; j_ < j; j_++) {
      if (s1_[i] == s2_[j_] ) {
        i_j__lower_i_j_map[p] = std::make_pair(i, j_);
        i_j__common_char_map[std::make_pair(i, j_) ] = s1_[i];
        return 1;
      }
    }
    return 0;
  }
  else if (j == 0) {
    for (int i_ = 0; i_ < i; i_++) {
      if (s1_[i_] == s2_[j] ) {
        i_j__lower_i_j_map[p] = std::make_pair(i_, j);
        i_j__common_char_map[std::make_pair(i_, j) ] = s2_[j];
        return 1;
      }
    }
    return 0;
  }
  
  int result;
  if (s1_[i] == s2_[j] ) {
    i_j__lower_i_j_map[p] = std::make_pair(i - 1, j - 1);
    i_j__common_char_map[p] = s1_[i];
    result = 1 + sizeof_lcs(i - 1, s1_, j - 1, s2_,
                                i_j__common_char_map,
                                i_j__lower_i_j_map,
                                i_j__sizeof_lcs_map);
  }
  else {
    int right_result = sizeof_lcs(i, s1_, j - 1, s2_,
                                      i_j__common_char_map,
                                      i_j__lower_i_j_map,
                                      i_j__sizeof_lcs_map);
    int left_result = sizeof_lcs(i - 1, s1_, j, s2_, 
                                     i_j__common_char_map,
                                     i_j__lower_i_j_map,
                                     i_j__sizeof_lcs_map);
    
    if (right_result > left_result)
      i_j__lower_i_j_map[p] = std::make_pair(i, j - 1);
    else
      i_j__lower_i_j_map[p] = std::make_pair(i - 1, j);
    
    result = std::max(left_result, right_result);
  }
  
  i_j__sizeof_lcs_map[p] = result;
  return result;
}
