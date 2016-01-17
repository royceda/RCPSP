#include <ilcplex/ilocplex.h>
#include "Parser.h"
#include "Flow.h"
#include "Time_indexed.hpp"
#include "ConfigInt.hpp"
#include "myClock.h"

int main(int argc, char **argv){

  //Parser* p = new Parser("perso.sm");
  //Parser* p = new Parser("j30.sm/j301_1.sm");
  cout<<"##########PARSING##########\n";
  Parser* p = new Parser("j120.sm/perso.sm");
  
  //Parser* p = new Parser("perso.sm");
  
  cout<<"##########FLOW##########\n";
  MyClock flowC;
  flowC.start();
  Flow* fl = new Flow();
  fl->heurSolve(*p);
  fl->solve(*p);
  flowC.end();
  cout << "ELAPSED TIME IN FLOW : "<<flowC.elapsedTime()<<"\n";
  fl->writeSolution(*p, "solFlow.txt");
  /*
    for(int i = 0; i< p->jobs(); i++)
    for(int j =0; j< p->jobs(); j++)
    cout << p->sucVector()[i][j] << endl;
  */
  /* cout<<"##########TIMEIND##########\n";
  Parser* p1 = new Parser("j120.sm/perso.sm");
  MyClock timeC;
  timeC.start();
  Time_indexed *t = new Time_indexed(*p1);
  t->solve(*p1);
  timeC.end();
  cout << "ELAPSED TIME IN TIME_INDEXED : "<<timeC.elapsedTime()<<"\n";
  //t->writeSolution("solTime.txt");
  */
  cout<<"##########CONFIGINT##########\n";
  Parser* p2 = new Parser("j120.sm/perso.sm");
  MyClock confC;
  confC.start();
  ConfigInt * conf = new ConfigInt(*p2);
  conf->solve(*p2);
  confC.end();
  conf->writeSolution("solConfInt.txt");
  cout << "ELAPSED TIME IN CONFINT : "<<confC.elapsedTime()<<"\n";


  system("java -jar ./JavaGantt/Gantt.jar")
  return 0;
}
