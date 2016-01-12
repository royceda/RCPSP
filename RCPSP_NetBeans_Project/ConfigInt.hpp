/*
 * File:   ConfigInt.hpp
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


typedef vector<vector<int> > Config;



class ConfigInt{
public:
  ConfigInt();
  ConfigInt(Parser &p);
  void solve(Parser &p);

  int bigM();

  vector<int> Slate();

protected:
  IloObjective objective();
  void addConstraints(Parser &p);

  void createConfig();
  void addConfig();

private:
  IloEnv env;
  IloModel model;
  IloRangeArray constraints;
  IloArray <IloArray<IloNumVar> > x;
  IloArray<IloNumVar> S;

  vector<int> _Slate;

  Config F;
  int _bigM;
  int _n;
  int _T;
  int _r  ;

};



#endif	/* CONFIG_INT_HPP */
