#ifndef _PATCH_FUN_H_
#define _PATCH_FUN_H_

#include <vector>
#include <map>
#include <boost/lexical_cast.hpp>

namespace patch_fun {
  template<typename T>
  std::string vec_to_str(std::vector<T> v)
  {
    std::stringstream ss;
    for (typename std::vector<T>::iterator it = v.begin(); it != v.end(); it++) {
      ss << boost::lexical_cast<std::string>(*it);
      if (it != (v.end() - 1) )
        ss << ", ";
    }
    
    return ss.str();
  };
  
  template<typename T>
  std::string pvec_to_str(std::vector<T> v)
  {
    std::stringstream ss;
    for (typename std::vector<T>::iterator it = v.begin(); it != v.end(); it++)
      ss << "\t" << boost::lexical_cast<std::string>(it->first) << ", " << boost::lexical_cast<std::string>(it->second) << "\n";
    
    return ss.str();
  };
  
  template<typename Tk, typename Tv>
  std::string map_to_str(std::map<Tk, Tv> m)
  {
    std::stringstream ss;
    for (typename std::map<Tk, Tv>::iterator it = m.begin(); it != m.end(); it++)
      ss << "\t" << boost::lexical_cast<std::string>(it->first) << " : " << boost::lexical_cast<std::string>(it->second) << "\n";
    
    return ss.str();
  }
  
  template<typename Tk, typename Tv>
  std::string pmap_to_str(std::map<Tk, Tv> m)
  {
    std::stringstream ss;
    for (typename std::map<Tk, Tv>::iterator it = m.begin(); it != m.end(); it++)
      ss << "\t<" << boost::lexical_cast<std::string>((it->first).first) << ", " 
                  << boost::lexical_cast<std::string>((it->first).second) << "> "
         << " : " << boost::lexical_cast<std::string>(it->second) << "\n";
    
    return ss.str();
  }
  
  template<typename Tk, typename Tv>
  std::string ppmap_to_str(std::map<Tk, Tv> m)
  {
    std::stringstream ss;
    for (typename std::map<Tk, Tv>::iterator it = m.begin(); it != m.end(); it++)
      ss << "\t <" << boost::lexical_cast<std::string>((it->first).first) << ", " 
                   << boost::lexical_cast<std::string>((it->first).second) << "> "
         << " : <" << boost::lexical_cast<std::string>((it->second).first) << ", "
                   << boost::lexical_cast<std::string>((it->second).second) << "> \n";
    
    return ss.str();
  }
  
  template <typename T>
  std::string arr_to_str(size_t size, T* arr_)
  {
    std::stringstream ss;
    for (int i = 0; i < size; i++)
      ss << boost::lexical_cast<std::string>(arr_[i] ) << ", ";
    
    return ss.str();
  }
}

#endif // _PATCH_FUN_H_