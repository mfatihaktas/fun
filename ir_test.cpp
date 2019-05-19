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
  std::vector<Term*> term_v;
  term_v.push_back(&c);
  term_v.push_back(&x);
  term_v.push_back(&y);
  Application a(term_v);
  Definition d(var_v, &a);
  log_(INFO, "d.to_ir_str= " << d.to_ir_str() )
}

int main(int argc , char **argv)
{
  // test_Application();
  test_Definition();
  
  return 0;
}
