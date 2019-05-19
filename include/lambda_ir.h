#ifndef _LAMBDA_RI_H_
#define _LAMBDA_RI_H_

#include <vector>
#include <map>
#include <algorithm>
#include <limits>
#include <iostream>
#include <string>

#include "debug.h"

/**********************************************  Term  ******************************************/
class Term {
  public:
    /* 'v': <variable>, "identifiers"
     * 'c': <constant>, "predeﬁned objects"
     * 'a': (<term> <term>*), "applications (function calls)"
     * 'd': `<variable>{, <variable>}*`<term>, "abstractions (function definitions)"
     */
    char type;
    
    Term(char type): type(type) {}
    ~Term() {}
};

class Variable : public Term {
  public:
    std::string name;
    
    Variable(std::string name)
    : Term('v'), name(name)
    {
      log_(INFO, "constructed; \n" << to_str() )
    }
    
    ~Variable() {}
    
    std::string to_str() {
      return "Variable(name= " + name + ")";
      // std::stringstream ss;
      // ss << "\t total_dur_sec= " << total_dur_sec << ", avg_dur_sec= " << total_dur_sec / num_dur << "\n";
      // return ss.str();
    }
};

/*
class Constant : public Term {
  public:
    float val;
    
    Constant(float val)
    : Term('v'), val(val)
    {
      log_(INFO, "constructed; \n" << to_str() )
    }
    
    ~Constant() {}
    
    std::string to_str() {
      return "Constant(val= " + std::to_string(val) + ")";
    }
};
*/

#endif // _LAMBDA_RI_H_