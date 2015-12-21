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
    
    
private:
    IloEnv env;
    IloModel model;
    IloArray <IloNumVarArray> y;
    
 
    
    int _n; 
    int _T;
    int _r  ;

};



#endif	/* TIME_INDEXED_HPP */
