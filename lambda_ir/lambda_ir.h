#ifndef _LAMBDA_RI_H_
#define _LAMBDA_RI_H_

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <limits>
#include <string>
#include <sstream>

#define log_(type, msg) \
  std::clog << #type " "<< __FILE__ << ":" << __LINE__ << "] " << __func__ << ":: " << msg << std::endl;

/**********************************************  Term  ******************************************/
#define VARIABLE 'v'
#define VALUE 'w'
#define CONSTANT 'c'
#define DEFINITION 'd'
#define APPLICATION 'a'
class Term {
  // protected:
  public:
    /* 'v': <variable>, "identifiers"
     * 'c': <constant>, "predeﬁned objects"
     * 'd': `<variable>{, <variable>}*`<term>, "abstractions (function definitions)"
     * 'a': (<term> <term>*), "applications (function calls)"
     */
    char type;
    
    Term(char type): type(type) {}
    ~Term() {}
    virtual std::string to_ir_str() { return "Should'nt have been called!"; }
    virtual std::string to_str() { return "Should'nt have been called!"; }
    
    virtual bool is_isomorphic(Term* t_) {
      return (this->type == t_->type);
    }
};

std::ostream & operator<< (std::ostream &os, Term &t) {
  return os << t.to_ir_str();
}

class Variable : public Term {
  public:
    std::string name;
    
    Variable(std::string name)
    : Term(VARIABLE), name(name)
    {
      // log_(DEBUG, "constructed; \n\t" << to_str() )
    }
    
    ~Variable() {}
    
    std::string to_ir_str() {
      return this->name;
    }
    
    std::string to_str() {
      return "Variable(name= " + this->name + ")";
    }
    
    bool is_isomorphic(Term* t_) {
      return Term::is_isomorphic(t_);
    }
};

class Value : public Term {
  public:
    float val;
    
    Value(float val)
    : Term(VALUE), val(val)
    {
      // log_(DEBUG, "constructed; \n\t" << to_str() )
    }
    
    ~Value() {}
    
    std::string to_ir_str() {
      return std::to_string(this->val);
    }
    
    std::string to_str() {
      return "Value(val= " + std::to_string(this->val) + ")";
    }
    
    bool is_isomorphic(Term* t_) {
      if (!Term::is_isomorphic(t_) )
        return false;
      
      return (this->val == ((Value*) t_)->val);
    }
};

class Constant : public Term {
  public:
    std::string name;
    
    Constant(std::string name)
    : Term(CONSTANT), name(name)
    {
      // log_(DEBUG, "constructed; \n\t" << to_str() )
    }
    
    ~Constant() {}
    
    std::string to_ir_str() {
      return name;
    }
    
    std::string to_str() {
      return "Constant(name= " + this->name + ")";
    }
    
    bool is_isomorphic(Term* t_) {
      if (!Term::is_isomorphic(t_))
        return false;
      
      return (this->name.compare(((Variable*) t_)->name) == 0);
    }
};

class Definition : public Term {
  // `<variable>{, <variable>}*`<term>
  private:
    std::map<int, int> i_in_var_v__i_in_term_v__m;
  public:
    std::vector<Variable*> var_v;
    Constant* c_;
    std::vector<Term*> term_v;
    
    Definition(std::vector<Variable*>& var_v, Constant* c_, std::vector<Term*>& term_v)
    : Term(DEFINITION), var_v(var_v), c_(c_), term_v(term_v)
    {
      std::map<std::string, int> i_in_var_v_m;
      
      int i = 0;
      for (std::vector<Variable*>::iterator it = this->var_v.begin(); it != this->var_v.end(); it++) {
        i_in_var_v_m[(*it)->name] = i;
        i++;
      }
      
      i = 0;
      for (std::vector<Term*>::iterator it = this->term_v.begin(); it != this->term_v.end(); it++) {
        if ((*it)->type == VARIABLE) {
          if (i_in_var_v_m.find(((Variable*) *it)->name) == i_in_var_v_m.end() ) {
            log_(ERROR, "Varname is in term_v but not in var_v; term= " << **it << "\n")
            exit(1);
          }
          // i_in_term_v_m[it->name] = i
          i_in_var_v__i_in_term_v__m[i_in_var_v_m[((Variable*) *it)->name] ] = i;
        }
        else if ((*it)->type == VALUE) {
          i++;
          continue;
        }
        else {
          log_(ERROR, "Unexpected term in term_v; term= " << **it << "\n")
          exit(1);
        }
        i++;
      }
      
      // log_(DEBUG, "constructed; \n" << to_str() )
    }
    
    ~Definition() {
      delete c_;
      for (std::vector<Variable*>::iterator it = this->var_v.begin(); it != this->var_v.end(); it++)
        delete *it;
      for (std::vector<Term*>::iterator it = this->term_v.begin(); it != this->term_v.end(); it++)
        delete *it;
    }
    
    std::string to_ir_str() {
      std::stringstream ss;
      ss << "`";
      for (std::vector<Variable*>::iterator it = this->var_v.begin(); it != this->var_v.end(); it++) {
        ss << (*it)->to_ir_str();
        if (it != this->var_v.end() - 1)
          ss << ",";
      }
      ss << "`(" << this->c_->to_ir_str() << " ";
      
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
      ss << "Definition(\n\tvar_v= [\n";
      for (std::vector<Variable*>::iterator it = this->var_v.begin(); it != this->var_v.end(); it++)
        ss << "\t " << (*it)->to_str() << ",\n";
      ss << "\t]\n" \
         << "\t" << "Constant=" << this->c_->to_str() << "\n" \
         << "\t" << "Parameters=\n";
      for (std::vector<Term*>::iterator it = this->term_v.begin(); it != this->term_v.end(); it++) {
        ss << (*it)->to_str();
        if (it != this->term_v.end() - 1)
          ss << ",\n";
      }
      
      return ss.str();
    }
    
    bool is_isomorphic(Term* t_) {
      if (!Term::is_isomorphic(t_) ) {
        // log_(WARNING, "Term::is_isomorphic returned false!\n" \
        //   << "this= " << *this << "\n" \
        //   << "target= " << *t_ << "\n")
        return false;
      }
      
      Definition* d_ = ((Definition*) t_);
      if (var_v.size() != d_->var_v.size() )
        return false;
      if (term_v.size() != d_->term_v.size() )
        return false;
      if (!c_->is_isomorphic(d_->c_) )
        return false;
      
      for (int i = 0; i < term_v.size(); i++) {
        // std::cout << "i= " << i << ", *term_v[i]= " << *term_v[i] << ", *(d_->term_v)[i]= " << *(d_->term_v)[i] << "\n";
        if (!term_v[i]->is_isomorphic(d_->term_v[i] ) )
          return false;
      }
      
      for (std::map<int, int>::iterator it = i_in_var_v__i_in_term_v__m.begin(); it != i_in_var_v__i_in_term_v__m.end(); it++) {
        if (it->second != d_->i_in_var_v__i_in_term_v__m[it->first] )
          return false;
      }
      
      return true;
    }
};

class Application : public Term {
  public:
    // (<term> <term>*)
    std::vector<Term*> term_v;
    
    Application(std::vector<Term*>& term_v)
    : Term(APPLICATION), term_v(term_v)
    {
      // log_(DEBUG, "constructed; \n" << to_str() )
    }
    
    ~Application() {
      for (std::vector<Term*>::iterator it = this->term_v.begin(); it != this->term_v.end(); it++)
        delete *it;
    }
    
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
    
    bool is_isomorphic(Term* t_) {
      if (!Term::is_isomorphic(t_) )
        return false;
      
      Application* a_ = ((Application*) t_);
      if (term_v.size() != a_->term_v.size() )
        return false;
      
      for (int i = 0; i < term_v.size(); i++) {
        if (!term_v[i]->is_isomorphic(a_->term_v[i] ) )
          return false;
      }
      
      return true;
    }
};

#endif // _LAMBDA_RI_H_