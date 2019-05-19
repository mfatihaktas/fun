#ifndef _DEBUG_
#define _DEBUG_

#define log_(type, msg) \
  std::clog << #type " "<< __FILE__ << ":" << __LINE__ << "] " << __func__ << ":: " << msg << std::endl;
// std::cerr << #type " "<< __FILE__ << ":" << __LINE__ << "] " << __func__ << ":: " << msg << std::endl;

#endif // _DEBUG_