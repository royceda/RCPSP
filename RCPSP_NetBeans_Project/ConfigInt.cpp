#include <ilcplex/ilocplex.h>
#include <iostream>

#include "ConfigInt.hpp"

ILOSTLBEGIN

typedef IloArray< IloArray<IloNumArray> > NumMatrix;

using namespace  std;





ConfigInt::ConfigInt(){}

ConfigInt::ConfigInt(Parser &p): _n(p.jobs()),_bigM(1000000), _T(p.getHorizon()), _r(p.nOfRes()), model(env),  S(env, p.jobs()), constraints(env), x(env, p.jobs()){

 
  for (int i = 0; i < _n; i++) {
    x[i] = IloArray<IloNumVar> (env, _n);
    char name1[256];
    sprintf(name1, "S %d ", i);
    S[i] = IloNumVar(env, 0, p.getHorizon() - p.durationsVector()[i], ILOINT, name1);
    //f[i] = IloArray <IloArray <IloNumVar> > (env, _n);
    
    for (int j = 0; j < _n; j++) {
      char name[256];
      sprintf(name, "X %d %d", i, j);
      x[i][j] = IloNumVar(env, 0, 1, ILOBOOL, name);
      //f[i][j] = IloArray<IloNumVar>(env, p.nOfRes());
      for (int k = 0; k < p.nOfRes(); k++) {
	sprintf(name, "f %d %d %d", i, j, k);
	//f[i][j][k] = IloNumVar(env, 0, p.resAvail()[k], ILOINT, name);
      }
    }
  }
}


IloObjective ConfigInt::objective(){
  IloObjective obj(env, S[_n - 1], IloObjective::Minimize, "OBJ");
  return obj;
}


void ConfigInt::addConstraints(Parser &p){

  /*Les deux premiere*/
  for(int i = 0; i < _n; i++){
    for(int j =0; j < _n; j++){
      constraints.add(x[i][j] == 1);
      constraints.add(  x[i][j] + x[i][j] <= 1);

      for(int k = 0; k <_n; k++){	
	constraints.add( 1 >=  x[i][j] + x[j][k] - x[i][k] );       
      }
    }
  }


  for(int i = 0; i < _n; i++){
    for(int j = 0; j < _n; j++){
      constraints.add(S[j] - S[i] - (p.durationsVector()[i] + bigM())*x[i][j] >= -bigM());
    }
  }
  


}

