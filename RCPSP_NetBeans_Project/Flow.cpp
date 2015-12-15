#include <ilcplex/ilocplex.h>
#include <iostream>
#include <limits>

#include "Flow.h"

ILOSTLBEGIN


typedef IloArray < IloArray <IloNumVarArray> > NumMatrix;

using namespace  std;

Flow::Flow() {
}


Flow::Flow(int M) : _bigM(M) {
}


int Flow::getBigM() {
    return _bigM;
}

void Flow::heurSolve(Parser& p) {
    int m = 1000000;
    _bigM = m;
}

void Flow::solve(Parser& p) {
    /**Main Classes**/
    IloEnv env;
    try {
        IloModel model(env);

        /**Variables**/
        IloArray<IloNumVarArray> x(env, p.jobs());
        IloNumVarArray S(env, p.jobs());
        //    IloArray<IloArray <IloNumVarArray> > f(env, p.jobs());

        NumMatrix f(env, p.jobs());

        for (int i = 0; i < p.jobs(); i++) {
            x[i] = IloNumVarArray(env, p.jobs(), 0, 1, ILOBOOL);
            S[i] = IloNumVar(env, 0, p.getHorizon() - p.durationsVector()[i], ILOINT);
            f[i] = IloArray <IloNumVarArray> (env, p.jobs());
            for (int j = 0; j < p.jobs(); j++) {
                f[i][j] = IloNumVarArray(env, p.nOfRes(), 0, IloInfinity, ILOINT);
            }
        }

        //model.add(S);
        //model.add(x);
        //model.add(f);

        /**Objectif**/
        IloObjective obj(env, S[p.jobs() - 1], IloObjective::Minimize, "OBJ");

        /**Contraintes**/
        for (int i = 0; i < p.jobs(); i++) {
            if (p.sucVector()[i].size() > 0) {
                for (int j = 0; j < p.sucVector()[i].size(); j++) {
                    IloExpr e0 = x[i][p.sucVector()[i][j]];
                    model.add(e0 == 1);
                }
            }

            for (int j = i + 1; j < p.jobs(); j++) {
                IloExpr e1 = x[i][j] + x[j][i];
                model.add(e1 <= 1);
            }
            for (int j = 0; j < p.jobs(); j++) {
                for (int k = 0; k < p.jobs(); k++) {
                    IloExpr e2 = x[i][j] + x[j][k] - x[i][k];
                    model.add(e2 <= 1);
                }
                int bound;
                bound = p.durationsVector()[i];
                IloExpr e3 = S[j] - S[i];
                model.add(e3 >= ((-getBigM() + (getBigM()*x[i][j])) + x[i][j]*bound));
            }
        }
        for (int k = 0; k < p.nOfRes(); k++) {
            for (int i = 0; i < p.jobs(); i++) {
                IloExpr e(env);
                IloExpr ee(env);
                for (int j = 0; j < p.jobs(); j++) {
                    e += f[i][j][k];
                    ee += f[j][i][k];
                }

                model.add(e == p.reqJobsMach()[i][k]);
                model.add(ee == p.reqJobsMach()[i][k]);
                e.end();
                ee.end();
            }
        }
        for (int i = 0; i < p.jobs(); i++) {
            for (int j = 0; j < p.jobs(); j++) {
                for (int k = 0; k < p.nOfRes(); k++) {
                    if (p.reqJobsMach()[i][k] < p.reqJobsMach()[j][k])
                        model.add(f[i][j][k] <= (p.reqJobsMach()[i][k] * x[i][j]));
                    else
                        model.add(f[i][j][k] <= (p.reqJobsMach()[j][k] * x[i][j]));
                }
            }
        }

        cout << "ALL SET UP\n";


        IloCplex cplex(model);
        cplex.solve();
        cout << "obj = " << cplex.getObjValue() << "\n";

        cplex.exportModel("test.lp");
    }    catch (IloException& e) {
        cerr << "ERROR = " << e << "\n";
    }

    env.end();
    NumMatrix f(env, p.jobs());

    for (int i = 0; i < p.jobs(); i++) {
        x[i] = IloNumVarArray(env, p.jobs(), 0, 1, ILOBOOL);
        S[i] = IloNumVar(env, 0, p.getHorizon() - p.durationsVector()[i], ILOINT);
        for (int j = 0; j < p.jobs(); j++) {
	  f[i][j] = IloNumVarArray(env, p.nOfRes(), 0, IloInfinity, ILOINT);
        }
    }

    //model.add(S);
    //model.add(x);
    //model.add(f);

    /**Objectif**/
    IloObjective obj(env, S[p.jobs() - 1], IloObjective::Minimize, "OBJ");



    /**Contraintes**/
    for (int i = 0; i < p.jobs(); i++) {
      for (int j = 0; j < p.sucVector()[i].size(); j++) {
        IloExpr e0 = x[i][p.sucVector()[i][j]];
	model.add(e0 == 1);
}

for (int j = 0; j < p.jobs(); j++) {
	IloExpr e1 = x[i][j] + x[j][i];
  model.add(e1 <= 1);
	for (int k = 0; k < p.jobs(); k++) {
    IloExpr e2 = x[i][j] + x[j][k] - 1;
	  model.add(x[i][k] >= e2);
  }
	IloExpr e3 = -getBigM() + (p.durationsVector()[i] + getBigM()) * x[i][j];
  model.add(S[j] - S[i] >= e3);
      }
    }

    for (int k = 0; k < p.nOfRes(); k++) {
	for(int i = 0; i < p.jobs(); i++){
    IloExpr e;
	  IloExpr ee;
    for(int j = 0; j < p.jobs(); j++){
	    e += f[i][j][k];
      ee += f[j][i][k];
	  }
	  model.add(e == p.reqJobsMach()[i][k]);
	  model.add(ee == p.reqJobsMach()[i][k]);
	}
      }

      for(int i = 0; i<p.jobs(); i++){
	for(int j = 0; j< p.jobs(); j++){
	  for(int k = 0; k < p.nOfRes(); k++){
	    if (p.reqJobsMach()[i][k] < p.reqJobsMach()[j][k])
	      model.add(f[i][j][k] <= p.reqJobsMach()[i][k]*x[i][j]);
	    else
	      model.add(f[i][j][k] <= p.reqJobsMach()[j][k]*x[i][j]);
	  }
	}
      }

    IloCplex cplex(model);
    cplex.exportModel("test.lp");
>>>>>>> 423babadd53938b0cb677b434b950534bb5efac1

}
