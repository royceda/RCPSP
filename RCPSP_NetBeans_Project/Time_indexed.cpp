#include <ilcplex/ilocplex.h>
#include <iostream>

#include "Time_indexed.hpp"

ILOSTLBEGIN

typedef IloArray< IloArray<IloNumArray> > NumMatrix;

using namespace  std;


Time_indexed::Time_indexed(){}

Time_indexed::Time_indexed(Parser &p): _n(p.jobs()), _T(p.getHorizon()), _r(p.nOfRes()), model(env), y(env, _n){

  for( int i = 0; i <_n; i++){
    y[i] = IloArray<IloNumVar> (env, _T);
    for(int t = 0; t < _T; t++){
      y[i][t] = IloNumVar (env, 0,1, ILOBOOL);
    }
  }
}


IloObjective Time_indexed::objective(IloEnv &env){

  IloExpr e0(env);
  for( int t = 0; t < _T; t++){
    e0 +=  y[(_n)-1][t] * t;
  }

  cout << "obj : DONE !!!!" << endl;  
  IloObjective obj(env, e0, IloObjective::Minimize, "OBJ"); //sum

  model.add(obj);
  return obj;   
}




void Time_indexed::addConstraints(Parser &p){
  /*Ordonancé le job i qu'une fois*/

 for(int i = 0; i < _n; i++){
   IloExpr e1(env);
   for(int t = 0; t < _T; t++){
     e1 += y[i][t];
   }
   model.add(e1 == 1);
   e1.end();
 }
 cout << "ct1 : DONE !!!!"<<endl;  


  /*Precedence*/
 for(int i = 0; i < _n; i++){
      //parcours des successeur de i
  for(int j = 0; j < p.sucVector()[i].size(); j++){ 
    int succ = p.sucVector()[i][j];
      IloExpr e2(env);
          for( int t = 1; t < _T; t++){ // sur le poly ca commence à 1
              e2 += ((y[succ][t] - y[i][t]) * t); 
          }
          model.add(e2 >= p.durationsVector()[i]); //on a parfois 0 >= 5
          e2.end(); 
        } 
    }
 cout << "ct2 : DONE !!!!" << endl;  
 
 /*Ressources*/    
 
 for(int k = 0; k < _r; k++){ //forall k and t          
     for(int t = 0; t < _T; t++){
         
         IloExpr e4(env);
         
         for(int i = 0; i < _n; i++){
             IloExpr e3(env);
             int init = t - p.durationsVector()[i] + 1;
             
             if(init < 0){
                 init = 0;
             }
             for(int r = init; r <= t;  r++){
                 e3 +=  y[i][r];
             }
             e4 += p.reqJobsMach()[i][k] * e3;
             e3.end();
         }
         model.add(e4 <= p.resAvail()[k]);  
         e4.end();        
     }
 }
 cout << "ct3 : DONE !!!!" << endl; 
 
    /*def y*/
    //done !!
}


vector<int> Time_indexed::createFeasibleConfig(Parser &p, int j){
    //Parcours des jobs
    //test 1:  test de ressource
    //test 2: verif de chemin dans le graphe
    
}


/*
vector<int> Time_indexed::createFeasibleConfig(Parser &p){
    vector<int> vect;
    return vect;
}
*/

void Time_indexed::addFeasibleConstraints(Parser &p){
    //init xi
    for( int i = 0; i < feasibleConfig.size(); i++){
        xi[i] = IloArray<IloNumVar> (env, _T);
        for(int t = 0; t < _T; t++){
            xi[i][t] = IloNumVar (env, 0,1, ILOBOOL);
        }
    }
    
    /*Contrainte 1*/
    for(int i; i < _n; i++){
        IloExpr e1(env);
        vector<int> feasibleConf(createFeasibleConfig(p, i));
        for(int l = 0; l <   feasibleConf.size(); l++){
            for(int t = 0; t < _T; t++){
                e1 += xi[l][t] ;
            }
        }
        model.add(e1 == p.durationsVector()[i]);
        e1.end();        
    }
    
    
    /*Contrainte 2*/
        for(int t = 0; t < _T; t++){
            IloExpr e2(env);

            for(int l = 0; l <   feasibleConfig.size(); l++){
                e2 += xi[l][t];
            }
            model.add(e2 <= 1);
            e2.end();
        }
    
    /*Contrainte 3*/
    for(int t = 0; t < _T; t++){
        for(int i = 0; i < _n; i++){
            IloExpr e3(env);
            vector<int> feasibleConf(createFeasibleConfig(p,i));
            
            for(int l = 0; l<feasibleConf.size(); l++){
                e3 = xi[i][t] - xi[l][t-1];
            }
            
            model.add(e3 <= y[i][t]);
            e3.end();
        }
    }
    
    
}



/****, Solve          */
void Time_indexed::solve(Parser& p) {

  try{      
    cout << "\ninit : DONE !!!!" << endl;  

    /**Objectives**/
    objective(env);


    /**Contraintes**/
    addConstraints(p);

    /**Config realisable**/
    //addFeasibleConstraints(p);

    cout << "solve: " << endl;
    /**Solve it*/

    IloCplex cplex(model);
    cplex.solve();
    
    cout <<"\n\nSOL= " <<cplex.getObjValue()<<"\n\n";
    cout << cplex.getObjValue() << endl;
    
    for (int i = 0; i < _n; i++) {
      for(int t = 0; t<_T; t++){
        cout << "y[" << i << "]["<<t<<"] = " << cplex.getValue(y[i][t]) << "\n";
      }
    }

    cplex.exportModel("test.lp");
    env.end();
    
  } catch (IloException& e){       
    cerr << "ERROR : "<< e<<"\n";
  }
  
}
