#ifndef _DP_H_
#define _DP_H_

#include <vector>
#include <map>
#include <algorithm>
#include <limits>

// From https://www.topcoder.com/community/data-science/data-science-tutorials/dynamic-programming-from-novice-to-advanced/
int min_num_coins_for_sum(std::vector<int> coin_v, int sum,
                          std::map<int, int>& sum__num_coins_map);

// From https://www.topcoder.com/community/data-science/data-science-tutorials/dynamic-programming-from-novice-to-advanced/
// lns: longest_nondecing_seq
void sizeof_lns(int upto_i, int seq_size, int* seq_,
                std::map<int, int>& upto_i__sizeof_lns_map);

// From http://web.mit.edu/15.053/www/AMP-Chapter-11.pdf
// lcs: longest_common_subseq
typedef std::pair<int, int> i_j_pair;
int sizeof_lcs(int i, const char* s1_, int j, const char* s2_,
               std::map<i_j_pair, char>& branch_i_j__common_char_map,
               std::map<i_j_pair, i_j_pair>& i_j__lower_i_j_map,
               std::map<i_j_pair, int>& i_j__sizeof_lcs_map);

#endif // _DP_H_