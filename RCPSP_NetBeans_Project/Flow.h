/* 
 * File:   Flow.h
 * Author: yoannjvr
 *
 * Created on 11 décembre 2015, 09:58
 */

#ifndef FLOW_H
#define	FLOW_H

#include "Parser.h"
#include <ilcplex/ilocplex.h>

class Flow{
public:
    Flow();
    Flow(int M);
    
    int getBigM();
    
    void solve(Parser& p);
    
    void heurSolve(Parser& p);
    
private:
    int _bigM;
    
};



#endif	/* FLOW_H */

