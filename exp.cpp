#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "patch_fun.h"
#include "dp.h"

std::map<char*, char*> parse_opts(int argc, char** argv)
{
  std::map<char*, char*> opt_map;
  // 
  int c;
  
  static struct option long_options[] = {
    {"type", optional_argument, NULL, 0},
    {0, 0, 0, 0}
  };
  
  while (1) {
    int option_index = 0;
    c = getopt_long (argc, argv, "s", long_options, &option_index);

    if (c == -1) // Detect the end of the options.
      break;
    
    switch (c) {
      case 0:
        opt_map[(char*)"type"] = optarg;
        break;
      default:
        break;
    }
  }
  if (optind < argc) {
    printf ("non-option ARGV-elements: ");
    while (optind < argc)
      printf ("%s ", argv[optind++]);
    putchar ('\n');
  }
  // 
  std::cout << "opt_map= \n";
  for (std::map<char*, char*>::iterator it = opt_map.begin(); it != opt_map.end(); ++it)
    std::cout << it->first << " : " << it->second << '\n';
  return opt_map;
}

void test_min_num_coins_for_sum()
{
  int coin_[] = {1, 2, 3, 4, 5};
  std::vector<int> coin_v(coin_, coin_ + sizeof(coin_)/sizeof(*coin_) );
  std::map<int, int> sum__num_coins_map;
  int min_num_coins = min_num_coins_for_sum(coin_v, 20,
                                            sum__num_coins_map);

  std::cout << "test_min_num_coins_for_sum:: min_num_coins= " << min_num_coins << "\n"
            << "sum__num_coins_map= \n" << patch_fun::map_to_str<>(sum__num_coins_map) << "\n";
}

void test_sizeof_lns() {
  srand(time(NULL) );
  
  // int seq_[] = {5, 3, 4, 8, 6, 7};
  int seq_size = 10; //sizeof(seq_)/sizeof(*seq_);
  int* seq_ = (int*)malloc(sizeof(int)*seq_size);
  for (int i = 0; i < seq_size; i++)
    seq_[i] = rand() % 4;
  
  std::cout << "seq_= \n" << patch_fun::arr_to_str<int>(seq_size, seq_) << "\n";
  std::map<int, int> upto_i__sizeof_lns_map;
  sizeof_lns(0, seq_size, seq_, upto_i__sizeof_lns_map);
  std::cout << "upto_i__sizeof_lns_map= \n" << patch_fun::map_to_str<int, int>(upto_i__sizeof_lns_map) << "\n";
  
  free(seq_);
}

void test_sizeof_lcs() {
  std::string s1 = "abazdc"; // "xyzxasdy";
  std::string s2 = "bacbad"; // "xayzxsd";
  
  std::map<i_j_pair, char> i_j__common_char_map;
  std::map<i_j_pair, i_j_pair> i_j__lower_i_j_map;
  std::map<i_j_pair, int> i_j__sizeof_lcs_map;
  int lcs = sizeof_lcs(s1.size() - 1, s1.c_str(), s2.size() - 1, s2.c_str(),
                       i_j__common_char_map,
                       i_j__lower_i_j_map,
                       i_j__sizeof_lcs_map);
  std::cout << "lcs = " << lcs << "\n"
            << "i_j__common_char_map= \n" << patch_fun::pmap_to_str<i_j_pair, char>(i_j__common_char_map) << "\n"
            << "i_j__lower_i_j_map= \n" << patch_fun::ppmap_to_str<i_j_pair, i_j_pair>(i_j__lower_i_j_map) << "\n"
            << "i_j__sizeof_lcs_map= \n" << patch_fun::pmap_to_str<i_j_pair, int>(i_j__sizeof_lcs_map) << "\n";
  // Construct lcs
  std::vector<char> lcs_v;
  i_j_pair p = std::make_pair(s1.size() - 1, s2.size() - 1);
  while (1) {
    if (i_j__common_char_map.count(p) != 0)
      lcs_v.push_back(i_j__common_char_map[p] );
    
    if (i_j__lower_i_j_map.count(p) != 0)
      p = i_j__lower_i_j_map[p];
    else
      break;
  }
  std::cout << "lcs_v= " << patch_fun::vec_to_str<char>(lcs_v) << "\n";
}

int main(int argc , char **argv)
{
  std::map<char*, char*> opt_map = parse_opts(argc, argv);
  // 
  if (strcmp(opt_map[(char*)"type"], (char*)"dp") == 0) {
    test_min_num_coins_for_sum();
    // test_sizeof_lns();
    // test_sizeof_lcs();
  }
}
