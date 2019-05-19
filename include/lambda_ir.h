#ifndef _LAMBDA_RI_H_
#define _LAMBDA_RI_H_

#include <vector>
#include <map>
#include <algorithm>
#include <limits>
// #include <iostream>
#include <string>
#include <sstream>

#include "debug.h"

/**********************************************  Term  ******************************************/
class Term {
  protected:
    /* 'v': <variable>, "identifiers"
     * 'c': <constant>, "predeﬁned objects"
     * 'a': (<term> <term>*), "applications (function calls)"
     * 'd': `<variable>{, <variable>}*`<term>, "abstractions (function definitions)"
     */
    char type;
  public:
    Term(char type): type(type) {}
    ~Term() {}
    virtual std::string to_ir_str() { return "Should'nt have been called!"; }
    virtual std::string to_str() { return "Should'nt have been called!"; }
};

/*
template <typename T>
class Variable : public Term {
  public:
    T v;
    
    Variable(T v)
    : Term('v'), v(v)
    {
      log_(INFO, "constructed; \n\t" << to_str() )
    }
    
    ~Variable() {}
    
    std::string v_to_str(float v) {
      return std::to_string(v);
    }
    
    std::string v_to_str(std::string v) {
      return v;
    }
    
    std::string to_ir_str() {
      return v_to_str(this->v);
    }
    
    std::string to_str() {
      return "Variable(name= " + v_to_str(this->v) + ")";
    }
};
*/
class Variable : public Term {
  public:
    std::string name;
    
    Variable(std::string name)
    : Term('v'), name(name)
    {
      log_(INFO, "constructed; \n\t" << to_str() )
    }
    
    ~Variable() {}
    
    std::string to_ir_str() {
      return this->name;
    }
    
    std::string to_str() {
      return "Variable(name= " + this->name + ")";
    }
};

class Value : public Term {
  public:
    float val;
    
    Value(float val)
    : Term('v'), val(val)
    {
      log_(INFO, "constructed; \n\t" << to_str() )
    }
    
    ~Value() {}
    
    std::string to_ir_str() {
      return std::to_string(this->val);
    }
    
    std::string to_str() {
      return "Value(val= " + std::to_string(this->val) + ")";
    }
};

class Constant : public Term {
  public:
    std::string name;
    
    Constant(std::string name)
    : Term('c'), name(name)
    {
      log_(INFO, "constructed; \n\t" << to_str() )
    }
    
    ~Constant() {}
    
    std::string to_ir_str() {
      return name;
    }
    
    std::string to_str() {
      return "Constant(name= " + this->name + ")";
    }
};

class Application : public Term {
  public:
    // (<term> <term>*)
    std::vector<Term*> term_v;
    
    Application(std::vector<Term*>& term_v)
    : Term('a'), term_v(term_v)
    {
      log_(INFO, "constructed; \n" << to_str() )
    }
    
    ~Application() {}
    
    std::string to_ir_str() {
      std::stringstream ss;
      ss << "(";
      for (std::vector<Term*>::iterator it = this->term_v.begin(); it != this->term_v.end(); it++) {
        ss << (*it)->to_ir_str();
        if (it != this->term_v.end() - 1)
          ss << " ";
      }
      ss << ")";
      
      return ss.str();
    }
    
    std::string to_str() {
      std::stringstream ss;
      ss << "Application(\n\tterm_v= [\n";
      for (std::vector<Term*>::iterator it = this->term_v.begin(); it != this->term_v.end(); it++)
        ss << "\t " << (*it)->to_str() << ",\n";
      ss << "\t]\n)";
      
      return ss.str();
    }
};

class Definition : public Term {
  // `<variable>{, <variable>}*`<term>
  public:
    std::vector<Variable*> var_v;
    Term* t_;
    
    Definition(std::vector<Variable*>& var_v, Term* t_)
    : Term('d'), var_v(var_v), t_(t_)
    {
      log_(INFO, "constructed; \n" << to_str() )
    }
    
    ~Definition() {}
    
    std::string to_ir_str() {
      std::stringstream ss;
      ss << "`";
      for (std::vector<Variable*>::iterator it = this->var_v.begin(); it != this->var_v.end(); it++) {
        ss << (*it)->to_ir_str();
        if (it != this->var_v.end() - 1)
          ss << ", ";
      }
      ss << "`" << t_->to_ir_str();
      
      return ss.str();
    }
    
    std::string to_str() {
      std::stringstream ss;
      ss << "Definition(\n\tvar_v= [\n";
      for (std::vector<Variable*>::iterator it = this->var_v.begin(); it != this->var_v.end(); it++)
        ss << "\t " << (*it)->to_str() << ",\n";
      ss << "\t]\n";
      ss << "\t" << "Term=\n" << t_->to_str() << "\n)";
      
      return ss.str();
    }
};

#endif // _LAMBDA_RI_H_