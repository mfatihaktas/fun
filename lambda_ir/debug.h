#ifndef _DEBUG_
#define _DEBUG_

#include <string>
#include <sstream>
#include <vector>

#define log_(type, msg) \
  std::clog << #type " "<< __FILE__ << ":" << __LINE__ << "] " << __func__ << ":: " << msg << std::endl;
// std::cerr << #type " "<< __FILE__ << ":" << __LINE__ << "] " << __func__ << ":: " << msg << std::endl;


template<typename T>
std::string vec_to_str(std::vector<T> v) {
  std::stringstream ss;
  for (typename std::vector<T>::iterator it = v.begin(); it != v.end(); it++) {
    ss << *it;
    if (it != (v.end() - 1) )
      ss << ", ";
  }
  
  return ss.str();
};

#endif // _DEBUG_