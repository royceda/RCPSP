/*
 * File:   Time_indexed.hpp
 * Author: Charlie Brown
 *
 * Created on 5 janvier 2016, 17:58
 */

#ifndef CONFIG_INT_HPP
#define	CONFIG_INT_HPP

#include "Parser.h"
#include <ilcplex/ilocplex.h>


struct conf{
  int x;
  int y;
};

typedef vector<conf> config;



class ConfigInt{
public:
  ConfigInt();
  ConfigInt(Parser &p);
  void solve(Parser& p);
  
  int bigM();
  
  
protected:
  IloObjective objective();
  void addConstraints(Parser &p);
  
  config createConfig();
  
private:
  IloEnv env;
  IloModel model;
  IloRangeArray constraints; 
  IloArray <IloArray<IloNumVar> > x;
  IloArray<IloNumVar> S;
  


  
  int _bigM;
  int _n; 
  int _T;
  int _r  ;
  
};



#endif	/* CONFIG_INT_HPP */
