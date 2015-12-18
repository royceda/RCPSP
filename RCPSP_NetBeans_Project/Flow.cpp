#include <ilcplex/ilocplex.h>
#include <iostream>
#include <sstream>
#include <limits>

#include "Flow.h"

ILOSTLBEGIN


typedef IloArray < IloArray <IloNumVarArray> > NumMatrix;

using namespace std;

Flow::Flow() {
}

Flow::Flow(int M) : _bigM(M) {
}

int Flow::getBigM() {
    return _bigM;
}

void Flow::heurSolve(Parser& p) {
    int m = p.getHorizon();
    _bigM = m;
}

void Flow::solve(Parser& p) {
    /**Main Classes**/
    IloEnv env;
    try {
        IloModel model(env);

        /**Variables**/
        IloArray<IloArray<IloNumVar> > x(env, p.jobs());
        //vector<vector<int> > x;
        IloArray<IloNumVar> S(env, p.jobs());
        IloArray<IloArray <IloArray<IloNumVar> > > f(env, p.jobs());

        //NumMatrix f(env, p.jobs());

        for (int i = 0; i < p.jobs(); i++) {
            x[i] = IloArray<IloNumVar> (env, p.jobs());
            char name1[256];
            sprintf(name1, "S %d ", i);
            S[i] = IloNumVar(env, 0, p.getHorizon() - p.durationsVector()[i], ILOINT, name1);
            f[i] = IloArray <IloArray <IloNumVar> > (env, p.jobs());
            for (int j = 0; j < p.jobs(); j++) {
                char name[256];
                sprintf(name, "X %d %d", i, j);
                x[i][j] = IloNumVar(env, 0, 1, ILOBOOL, name);
                f[i][j] = IloArray<IloNumVar>(env, p.nOfRes());
                for (int k = 0; k < p.nOfRes(); k++) {
                    sprintf(name, "f %d %d %d", i, j, k);
                    f[i][j][k] = IloNumVar(env, 0, p.resAvail()[k], ILOINT, name);
                }
            }
        }

        //model.add(S);
        //model.add(x);
        //model.add(f);

        /**Objectif**/
        IloObjective obj(env, S[p.jobs() - 1], IloObjective::Minimize, "OBJ");
        model.add(obj);
        /**Contraintes**/

        for (unsigned int i = 0; i < p.jobs(); i++) {
            //vector<int> tmpX;

            IloExpr e00(env);
            e00 = x[i][i];
            model.add(e00 == 0);
            e00.end();

            for (int j = 0; j < p.sucVector()[i].size(); j++) {
                IloExpr e0(env);
                e0 = x[i][p.sucVector()[i][j]];
                model.add(e0 == 1);
                e0.end();
            }
            //tmpX.clear();


            for (unsigned int j = i + 1; j < p.jobs(); j++) {
                IloExpr e1(env);
                e1 = x[i][j] + x[j][i];
                model.add(e1 <= 1);
                e1.end();
            }

            /* transitivité */
            for (unsigned int j = 0; j < p.jobs(); j++) {
                for (unsigned int k = 0; k < p.jobs(); k++) {
                    IloExpr e2(env);
                    e2 = x[i][j] + x[j][k] - x[i][k];
                    model.add(e2 <= 1);
                    e2.end();
                }
                int bound;
                bound = p.durationsVector()[i];
                IloExpr e3(env);
                e3 = S[j] - S[i];
                IloExpr e4(env);
                e4 = ((-getBigM() + (x[i][j] * getBigM())) + (x[i][j] * bound));
                model.add(e3 >= e4);
                e3.end();
                e4.end();
            }
        }

        /*flow sum*/
        for (unsigned int k = 0; k < p.nOfRes(); k++) {
            for (unsigned int i = 0; i < p.jobs() - 1; i++) {
                IloExpr e(env);

                for (int j = 1; j < p.jobs(); j++) {
                    e += f[i][j][k];
                }
                model.add(e == p.reqJobsMach()[i][k]);
                e.end();
            }
            for (unsigned int i = 1; i < p.jobs(); i++) {
                IloExpr ee(env);

                for (int j = 0; j < p.jobs()-1; j++) {
                    ee += f[j][i][k];
                }
                model.add(ee == p.reqJobsMach()[i][k]);
                ee.end();

            }
            
            IloExpr ex(env);
            for(unsigned int i = 1; i<p.jobs(); i++){
                ex += f[0][i][k];
            }
            model.add(ex == p.resAvail()[k]);
            ex.end();
            
            IloExpr en(env);
            for(unsigned int i = 1; i<p.jobs()-1; i++){
                en += f[i][p.jobs()-1][k];
            }
            model.add(en == p.resAvail()[k]);
            en.end();            
        }


        /*flow min*/
        for (unsigned int i = 0; i < p.jobs() - 1; i++) {
            for (unsigned int j = 1; j < p.jobs(); j++) {
                for (unsigned int k = 0; k < p.nOfRes(); k++) {
                    if (p.reqJobsMach()[i][k] < p.reqJobsMach()[j][k])
                        model.add(f[i][j][k] <= (x[i][j] * p.reqJobsMach()[i][k]));
                    else
                        model.add(f[i][j][k] <= (x[i][j] * p.reqJobsMach()[j][k]));
                }
            }
        }

        IloCplex cplex(model);
        cplex.exportModel("test.lp");
        cplex.solve();

        cout << "\n\nSOL= " << cplex.getObjValue() << "\n\n";
        for (int i = 0; i < p.jobs(); i++) {
            cout << "S" << i << " = " << cplex.getValue(S[i]) << "\n";
        }

        cout << cplex.getObjValue() << endl;


        env.end();

    } catch (IloException& e) {
        cerr << "ERROR : " << e << "\n";
    }

}
