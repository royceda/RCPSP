/*
 * File:   Time_indexed.hpp
 * Author: Charlie Brown
 *
 * Created on 15 décembre 2015, 11:58
 */

#ifndef TIME_INDEXED_HPP
#define	TIME_INDEXED_HPP

#include "Parser.h"
#include <ilcplex/ilocplex.h>

class Time_indexed{
public:
    Time_indexed();
    Time_indexed(Parser &p);
    void solve(Parser& p);
    
 
    
    
protected:
    IloObjective objective(IloEnv &env);
    void addConstraints(Parser &p);
  
    /**
     * Penser a supp la contrainte de ressouce
     * @param p
     */
    void addFeasibleConstraints(Parser &p);
  
    /**
   * creation d'une config realisable contenant j
   * @param p
   * @param j
   */
    vector<int> createFeasibleConfig(Parser &p,  int j);
  
    /**
     * creation de toute les config realisable
     * @param p
     * @return 
     */
    void createFeasibleConfig(Parser &p);
    
private:
  IloEnv env;
  IloModel model;
  IloRangeArray constraints; 
  IloArray <IloArray<IloNumVar> > y;
  IloArray <IloArray<IloNumVar> > xi;
   
    //all feasible config
    vector<int> feasibleConfig;
    
    int _n; 
    int _T;
    int _r  ;

};



#endif	/* TIME_INDEXED_HPP */
