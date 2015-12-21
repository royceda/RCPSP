#include <ilcplex/ilocplex.h>
#include <iostream>

#include "Time_indexed.hpp"

ILOSTLBEGIN

typedef IloArray< IloArray<IloNumArray> > NumMatrix;

using namespace  std;


Time_indexed::Time_indexed(){}

Time_indexed::Time_indexed(Parser &p, IloEnv & env): _n(p.jobs()), _T(p.getHorizon()), _r(p.nOfRes()), model(env), y(env, _n){
     
    for( int i = 0; i <_n; i++){
        y[i] = IloNumVarArray(env, _T, 0, 1, ILOBOOL);
    }
}


IloObjective Time_indexed::objective(IloEnv &env){
    
     IloExpr e0(env);
     for( int t = 0; t < 1; t++){
         e0 =  y[_n-1][t] * t;
     }
     
     cout << "obj : DONE !!!!" << endl;  
     IloObjective obj(env, e0, IloObjective::Minimize, "OBJ"); //sum
     
     return obj;   
}


void Time_indexed::solve(Parser& p) {

  try{

      /**Main Classes**/
      IloEnv env;
      //IloModel model(env);
      
      /*
    int n = p.jobs(); // number of jobs
    int T = p.getHorizon(); //discret time
    int r  = p.nOfRes(); //number of sources
    */
    
    
    /**Variables**/
   /*IloArray <IloNumVarArray> y(env, _n); //decision ( n x T)
    
    /**initialization */
   /* for( int i = 0; i <_n; i++){
      y[i] = IloNumVarArray(env, _T, 0, 1, ILOBOOL);
    }
    */
      
      
      
    cout << "\ninit : DONE !!!!" << endl;  
    /**Objectives**/
    IloObjective obj = objective(env);
    model.add(obj);
    
    /**Contraintes**/
    /*Ordonancé le job i qu'une fois*/
    IloExpr e1(env);
    for(unsigned int i = 0; i < _n; i++){
        for(unsigned int t = 0; t < _T; t++){
            e1 += y[i][t];
        }
        model.add(e1 == 1);
    }
    cout << "ct1 : DONE !!!!" << endl;  
    
    /*Precedence*/
    for(unsigned int i = 0; i < _n; i++){
        IloExpr e2(env);
        //cout << "ct2 : creating i = "  << i << endl;
        //parcours des successeur de i
        for(unsigned int j = 0; j < p.sucVector()[i].size(); j++){
            int succ = p.sucVector()[i][j];
            //cout << "ct2 : succ = "  << succ << endl;
            for( int t = 0; t < _T; t++){
                e2 += (y[succ][t] - y[i][t]) * t; 
            }
        }
        model.add(e2 >= p.durationsVector()[i]); 
    }
    cout << "ct2 : DONE !!!!" << endl;  
    
    
    /*Ressources*/    
    for(int t = 0; t < _T; t++){
        for(int k = 0; k < _r; k++){ //forall k and t          
            IloExpr e3(env);
            IloExpr e4(env);
            for(int i = 0; i < _n; i++){
                //cout << "ct3 : creating i = "  << i<< endl;  
                int init = t - p.durationsVector()[i] + 1;
                if( init >= 0){
                    for(int r = init; r < t;  r++){
                        //expr de somme en r
                        e3 +=  y[i][r];
                    }
                    e4 += p.reqJobsMach()[i][k] * e3;
                }
            }
            model.add(e4 <= p.resAvail()[k]);
        }
    }
    cout << "ct3 : DONE !!!!\n" << endl;  
    
    
    /*def y*/
    //done !!
    
    /**************************/
    /* Configuration realisables*/
    /**************************/
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    cout << "solve: " << endl;
    /**Solve it*/

    IloCplex cplex(model);
    cplex.solve();
    
    cout <<"\n\nSOL= " <<cplex.getObjValue()<<"\n\n";
    
    
    cout << cplex.getObjValue() << endl;
    
    cplex.exportModel("test.lp");
    env.end();
    
  } catch (IloException& e){       
    //cerr << "ERROR : "<< e<<"\n";
  }
  
}