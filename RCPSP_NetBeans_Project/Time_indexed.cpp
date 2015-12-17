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
    
    
    int n = p.jobs(); // number of jobs
    int T = p.getHorizon(); //discret time
    int r = p.nOfRes(); //number of sources
    
    
    /**Variables**/
    IloArray <IloNumVarArray> y(env, p.getHorizon()); //decision ( n x T)
   
    
    /**initialization */
    for(unsigned int i = 0; i <n; i++){
      y[i] = IloNumVarArray(env, T, 0, 1, ILOBOOL);

    }


  
    /**Objectives**/
    IloExpr e0(env);
    for( int t = 0; t < T; t++){
      e0 =  y[n+1][t] * t;
    }
    
    IloObjective obj(env, e0, IloObjective::Minimize, "OBJ"); //sum
    
    
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
      model.add(e2 >= p.durationsVector()[j]); 
    }
    

    /*Ressources*/    
    for(int t = 0; t < T; t++){
      for(int k = 0; k < r; k++){
	IloExpr e3(env);
	for(int i = 0; i < n; i++){
	  for(int j = 0; j < t; j++){
		e3 += p.reqJobsMach()[i][k] * y[i][j];
	  }
	  model.add(e3 <= p.resAvail()[k]);
	}
      }
    }
    
    
    
    /*def y*/
    //done !!
    
    
    
    
    /**Solve it*/

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
