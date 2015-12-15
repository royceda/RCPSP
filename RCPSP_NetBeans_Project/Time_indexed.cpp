#include <ilcplex/ilocplex.h>
#include <iostream>

#include "Flow.h"

ILOSTLBEGIN

typedef IloArray< IloArray<IloNumArray> > NumMatrix;

using namespace  std;


Time_indexed::Time_indexed(){}


void Time_indexed::solve(Parser& p) {
    /**Main Classes**/
    IloEnv env;
    IloModel model(env);


		/**Variables**/
		IloArray <IloNumVarArray> y(env, p.jobs());

		IloNumVarArray S(env, p.jobs());

		IloNumVarArray B(env, p.resAvail());



	}
