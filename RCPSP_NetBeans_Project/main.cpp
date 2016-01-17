#include <ilcplex/ilocplex.h>
#include "Parser.h"
#include "Flow.h"
#include "Time_indexed.hpp"
#include "ConfigInt.hpp"


int main(int argc, char **argv){

  //Parser* p = new Parser("perso.sm");
  //Parser* p = new Parser("j30.sm/j301_1.sm");
  cout<<"##########PARSING##########\n";
  Parser* p = new Parser("j120.sm/perso.sm");
  
  //Parser* p = new Parser("perso.sm");
  
  cout<<"##########FLOW##########\n";
  Flow* fl = new Flow();
  fl->heurSolve(*p);
  fl->solve(*p);
  fl->writeSolution(*p, "solFlow.txt");
  /*
    for(int i = 0; i< p->jobs(); i++)
    for(int j =0; j< p->jobs(); j++)
    cout << p->sucVector()[i][j] << endl;
  */
  cout<<"##########TIMEIND##########\n";
  Parser* p1 = new Parser("j120.sm/perso.sm");
  Time_indexed *t = new Time_indexed(*p1);
  t->solve(*p1);
  //t->writeSolution("solTime.txt");

  cout<<"##########CONFIGINT##########\n";
  Parser* p2 = new Parser("j120.sm/perso.sm");
  ConfigInt * conf = new ConfigInt(*p2);
  conf->solve(*p2);
  conf->writeSolution("solConfInt.txt");

  return 0;
}
