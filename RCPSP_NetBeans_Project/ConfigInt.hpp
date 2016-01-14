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
#include <fstream>
#include <string>
#include <list>

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
  IloNumArray v();

  vector<int> Slate();

  void writeSolution(string fileName);

protected:
  IloObjective objective();
  void addConstraints(Parser &p);

  bool createConfig(IloNumArray v);
  void addConfig();


private:
  IloEnv env;
  IloModel model;
  IloRangeArray constraints;
  IloArray <IloArray<IloNumVar> > x;
  IloNumVarArray S;
  IloNumArray _v;
  list<int> _vSol; 

  vector<int> _Slate;

  Config F;
  vector<int> _p;
  vector<int> _B;
  vector< vector<int > > _b;
  int _bigM;
  int _n;
  int _T;
  int _r  ;

};



#endif	/* CONFIG_INT_HPP */
