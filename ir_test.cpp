#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "debug.h"
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
  Variable x("x");
  Variable y("y");
  std::vector<Variable*> var_v;
  var_v.push_back(&x);
  var_v.push_back(&y);
  Constant c("+");
  std::vector<int> varperm_pos_to_index_v;
  varperm_pos_to_index_v.push_back(0);
  varperm_pos_to_index_v.push_back(1);
  Definition d(var_v, &c, varperm_pos_to_index_v);
  log_(INFO, "d.to_ir_str= " << d.to_ir_str() )
}

void test_Definition_is_isomorphic() {
  Variable x("x");
  Variable y("y");
  std::vector<Variable*> var_v;
  var_v.push_back(&x);
  var_v.push_back(&y);
  Constant c1("+");
  std::vector<int> varperm_pos_to_index_v1;
  varperm_pos_to_index_v1.push_back(0);
  varperm_pos_to_index_v1.push_back(1);
  Definition d1(var_v, &c1, varperm_pos_to_index_v1);
  
  Variable a("a");
  Variable b("b");
  std::vector<Variable*> var_v2;
  var_v2.push_back(&a);
  var_v2.push_back(&b);
  Constant c2("+");
  std::vector<int> varperm_pos_to_index_v2;
  varperm_pos_to_index_v2.push_back(0);
  varperm_pos_to_index_v2.push_back(1);
  Definition d2(var_v2, &c2, varperm_pos_to_index_v2);
  
  log_(INFO, "\n" << \
    "d1= " << d1 << "\n" \
    "d2= " << d2 << "\n" \
    "d1.is_isomorphic(d2)= " << d1.is_isomorphic(&d2) )
}

int main(int argc , char **argv)
{
  // test_Application();
  // test_Definition();
  test_Definition_is_isomorphic();
  
  return 0;
}
