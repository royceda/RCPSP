#include <ilcplex/ilocplex.h>
#include <iostream>

#include "ConfigInt.hpp"

ILOSTLBEGIN

typedef IloArray< IloArray<IloNumArray> > NumMatrix;

using namespace  std;




/**
*TODO
* chemin critique
* creation des intervalles de chaque noeud (plus tot, lus tard)
* Pour tout noeud
* Reduction d'espace de recherche pour la config
* creation de la config
*/
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
      for (int k = 0; k < p.nOfRes(); k++) {
        sprintf(name, "f %d %d %d", i, j, k);
      }
    }
  }
  cout<<"INIT DONE\n";
}






IloObjective ConfigInt::objective(){
  IloObjective obj(env, S[_n - 1], IloObjective::Minimize, "OBJ");
  return obj;
}


int ConfigInt::bigM(){
  return _bigM;
}


void ConfigInt::addConstraints(Parser &p){
  for(int i = 0; i < _n; i++){ 
    IloExpr e00(env);
    e00 = x[i][i];
    model.add(e00 == 0);
    e00.end();

    for (int j = 0; j < p.sucVector()[i].size(); j++) {
      IloExpr e0(env);
      e0 = x[i][p.sucVector()[i][j]];
      model.add(e0 == 1);
      e0.end();
    }
  }
  /*Les deux premiere*/
  for(int i = 0; i < _n; i++){
    IloExpr e2(env);
    for(int j =0; j < _n; j++){
      e2 =  x[i][j] + x[j][i] ;
      model.add(e2 <= 1);
      e2.end();


      IloExpr e3(env);
      for(int k = 0; k <_n; k++){
        e3 = x[i][j] + x[j][k] - x[i][k] ;
        model.add(e3 <= 1);
      }
      e3.end();
    }
  }


  for(int i = 0; i < _n; i++){
    IloExpr e4(env);
    for(int j = 0; j < _n; j++){
      e4 = S[j] - S[i] - (p.durationsVector()[i] + bigM())*x[i][j];
      model.add(e4 >= - bigM());
      e4.end();
    }
  }
}



void ConfigInt::addConfig(){
  //createConfig();
  /*
  for (size_t i = 0;  i< count; ++) {
    for (size_t j = 0; j < count; ++) {

      for(int k= 0; k < F.size(); k++){
      //        int i = F[k].x;
      //      int j = F[k].y;

        constraints.add(x[i][j] >= 1);
      }
    }
  }*/
  }



  void ConfigInt::solve(Parser& p){
    try{
     model.add(objective());
     cout << "objectif"<< endl;

     addConstraints(p);
     cout << "const"<< endl;

   /*premier solve*/

     IloCplex cplex(model);
     cplex.solve();
     cout<<"OK\n";

   //addConfig(p);
   /*second solve*/
   //IloCplex cplex(model);
   //cplex.solve();
     cout <<"\n\nSOL= " <<cplex.getObjValue()<<"\n\n";
     cout << cplex.getObjValue() << endl;



     cout << "\n\nSOL= " << cplex.getObjValue() << "\n\n";
     for (int i = 0; i < p.jobs(); i++) {
       cout << "S" << i << " = " << cplex.getValue(S[i]) << "\n";
     }

     cout << cplex.getObjValue() << endl;
   }
   catch (IloException& e) {
    cerr << "ERROR : " << e << "\n";
  }

}
