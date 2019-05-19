#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "debug.h"
#include "lambda_ir.h"

int main(int argc , char **argv)
{
  // log_(INFO, "deneme.")
  
  Variable var("x");
  log_(INFO, "var= " << var.to_str() )
  
  // std::cout << "Deneme!" << std::endl;
  
  // std::string str = "Mehmet";
  // std::cout << "str= " << str << std::endl;
  
  return 0;
}
