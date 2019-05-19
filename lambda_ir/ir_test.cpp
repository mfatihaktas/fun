#include "lambda_ir.h"

void test_Application() {
  Variable v1("x");
  log_(INFO, "v1= " << v1.to_str() )
  
  Value v2(12.1);
  log_(INFO, "v2= " << v2.to_str() )
  
  // Term* c_ = &c;
  // log_(INFO, "c_->to_str()= " << c_->to_str() )
  
  std::vector<Term*> term_v;
  term_v.push_back(&v1);
  term_v.push_back(&v2);
  Application a(term_v);
  log_(INFO, "a.to_str= " << a.to_str() << \
             "a.to_ir_str= " << a.to_ir_str() )
}

void test_Definition() {
  std::vector<Variable*> var_v;
  var_v.push_back(new Variable("x") );
  var_v.push_back(new Variable("y") );
  Constant* c_ = new Constant("+");
  std::vector<Term*> term_v;
  term_v.push_back(new Variable("x") );
  term_v.push_back(new Variable("y") );
  Definition d(var_v, c_, term_v);
  log_(INFO, "d.to_ir_str= " << d.to_ir_str() )
}

Definition* helper_create_Definition(std::string v1, std::string v2, 
                                     std::string c, std::string term_v1, std::string term_v2) {
  std::vector<Variable*> var_v;
  var_v.push_back(new Variable(v1) );
  var_v.push_back(new Variable(v2) );
  Constant* c_ = new Constant(c);
  std::vector<Term*> term_v;
  term_v.push_back(new Variable(term_v1) );
  term_v.push_back(new Variable(term_v2) );
  return new Definition(var_v, c_, term_v);
}

void test_Definition_is_isomorphic() {
  Definition *d1_, *d2_;
  // d1_ = helper_create_Definition("x", "y", "+", "x", "y");
  // d2_ = helper_create_Definition("a", "b", "-", "a", "b");
  // // d2_ = helper_create_Definition("a", "b", "-", "b", "a");
  
  {
    std::vector<Variable*> var_v;
    var_v.push_back(new Variable("x") );
    var_v.push_back(new Variable("y") );
    Constant* c_ = new Constant("+");
    std::vector<Term*> term_v;
    term_v.push_back(new Value(2) );
    term_v.push_back(new Variable("x") );
    term_v.push_back(new Variable("y") );
    d1_ = new Definition(var_v, c_, term_v);
  }
  {
    std::vector<Variable*> var_v;
    var_v.push_back(new Variable("a") );
    var_v.push_back(new Variable("b") );
    Constant* c_ = new Constant("+");
    std::vector<Term*> term_v;
    term_v.push_back(new Value(2) );
    term_v.push_back(new Variable("b") );
    term_v.push_back(new Variable("a") );
    d2_ = new Definition(var_v, c_, term_v);
  }
  
  log_(INFO, "\n" << \
    "d1= " << *d1_ << "\n" \
    "d2= " << *d2_ << "\n" \
    "d1_->is_isomorphic(d2_)= " << d1_->is_isomorphic(d2_) )
  
  delete d1_;
  delete d2_;
}

void test_Application_is_isomorphic() {
  Application *a1_, *a2_;
  {
    std::vector<Variable*> var_v1;
    var_v1.push_back(new Variable("x") );
    var_v1.push_back(new Variable("y") );
    Constant* c_ = new Constant("+");
    std::vector<Term*> term_v1;
    term_v1.push_back(new Variable("x") );
    term_v1.push_back(new Variable("y") );
    Definition* d1_ = new Definition(var_v1, c_, term_v1);
    
    std::vector<Variable*> var_v2;
    var_v2.push_back(new Variable("f") );
    std::vector<Term*> term_v2;
    term_v2.push_back(new Variable("f") );
    term_v2.push_back(new Value(1) );
    term_v2.push_back(new Value(2) );
    Definition* d2_ = new Definition(var_v2, c_, term_v2);
    
    std::vector<Term*> term_v;
    term_v.push_back(d2_);
    term_v.push_back(d1_);
    a1_ = new Application(term_v);
  }
  {
    std::vector<Variable*> var_v1;
    var_v1.push_back(new Variable("a") );
    var_v1.push_back(new Variable("b") );
    Constant* c_ = new Constant("+");
    std::vector<Term*> term_v1;
    term_v1.push_back(new Variable("b") );
    term_v1.push_back(new Variable("a") );
    Definition* d1_ = new Definition(var_v1, c_, term_v1);
    
    std::vector<Variable*> var_v2;
    var_v2.push_back(new Variable("g") );
    std::vector<Term*> term_v2;
    term_v2.push_back(new Variable("g") );
    term_v2.push_back(new Value(1) );
    term_v2.push_back(new Value(2) );
    Definition* d2_ = new Definition(var_v2, c_, term_v2);
    
    std::vector<Term*> term_v;
    term_v.push_back(d2_);
    term_v.push_back(d1_);
    a2_ = new Application(term_v);
  }
  
  log_(INFO, "\n" << \
    "a1= " << *a1_ << "\n" \
    "a2= " << *a2_ << "\n" \
    "a1_->is_isomorphic(a2_)= " << a1_->is_isomorphic(a2_) )
  
  delete a1_;
  delete a2_;
}

int main(int argc , char **argv) {
  // test_Application();
  // test_Definition();
  // test_Definition_is_isomorphic();
  test_Application_is_isomorphic();
  
  return 0;
}
