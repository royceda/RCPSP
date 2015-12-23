#include <ilcplex/ilocplex.h>
#include "Parser.h"
#include "Flow.h"
#include "Time_indexed.hpp"


int main(int argc, char **argv){
  //Parser* p = new Parser("perso.sm");
  Parser* p = new Parser("j120.sm/j1201_2.sm");
  //Parser* p = new Parser("perso.sm");
  
  Flow* fl = new Flow();
  //fl->heurSolve(*p);
  //fl->solve(*p);
  
  /*
    for(int i = 0; i< p->jobs(); i++)
    for(int j =0; j< p->jobs(); j++)
    cout << p->sucVector()[i][j] << endl;
  */
  Time_indexed *t = new Time_indexed(*p);
  t->solve(*p);
  
  return 0;
}
