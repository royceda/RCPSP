#include <ilcplex/ilocplex.h>
#include <iostream>

#include "Time_indexed.hpp"



ILOSTLBEGIN

typedef IloArray< IloArray<IloNumArray> > NumMatrix;

using namespace  std;


Time_indexed::Time_indexed(){}


void Time_indexed::solve(Parser& p) {

  try{

  /**Main Classes**/
  IloEnv env;
  IloModel model(env);
  
  
  /**Variables**/
  IloArray <IloNumVarArray> y(env, p.getHorizon());    

  int n = p.jobs(); // n jobs
  int T = p.getHorizon(); //discret time

  IloNumVarArray P(env, p.jobs()); //time
  IloNumVarArray S(env, p.jobs()); 
  IloNumVarArray B(env, p.resAvail()); //res Available
  IloNumVarArray b(env, p.reqJobsMach()); //required ressource
  
  
  /**Objectives**/
  IloExpr eO(env);
  for(unsigned int t = 0; t < T; t++){
    eO += t *  y[n+1][t] ;
  }
  
  IloObjective obj(env, eO, IloObjective::Minimize, "OBJ"); //sum
  
  
  /**Contraintes**/
  IloExpr e1(env);
  for(unsigned int i = 0; i < n; i++){
    for(unsigned int t = 0; t < T; t++){
      e1 += y[i][t];
    }
    model.add(e1 == 1);
  }


  /*Precedence*/
  for(unsigned int i = 0; i < n; i++){
    IloExpr e2(env);
    for(unsigned int j = 0; j < n; j++){
      for(unsigned int t = 0; t < T; t++){
	e2 += y[i][t] - y[j][t];
      }
    }
    model.add(e2 >= P[i]); 
  }
  
  /*Ressources*/

  /*def y*/





  IloCplex cplex(model);
  
  cplex.solve();
  
  cout <<"\n\nSOL= " <<cplex.getObjValue()<<"\n\n";
  
  
  cout << cplex.getObjValue() << endl;
  
  cplex.exportModel("test.lp");
  env.end();
  
  } catch (IloException& e){       
   cerr << "ERROR : "<< e<<"\n";
  }

}
