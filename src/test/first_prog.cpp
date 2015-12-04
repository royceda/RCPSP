#include <ilcplex/ilocplex.h>
 
ILOSTLBEGIN

int main(int argc, char **argv) {
   //déclaration des trois classes principales
  IloEnv env; // environnement : permet d utiliser les fonctions de Concert Technology
  IloModel model(env); // modèle : représente le programme linéaire
  IloCplex cplex (model); // classe Cplex : permet d 'accéder aux fonctions d'optimisation
  // ----------------------- VARIABLES -----------------------
  //déclaration de 2 variables
  IloNumVar x1 (env, 0.0, 40.0, ILOFLOAT, "X1");
  IloNumVar x2 (env, -10, 20, ILOINT, "X2");
  //ajout des variables au modèle
  model.add(x1);
  model.add(x2);
  // ----------------------- OBJECTIF -----------------------
  //déclaration de la fct objectif
  IloObjective obj (env, x1 + x2, IloObjective::Minimize, "OBJ");
   //ajout de la fct objectif au modèle
  model.add(obj);
  // ----------------------- CONTRAINTES -----------------------
  //déclaration de deux contraintes
  IloRange ctr1 ( env, 2, 2.5 * x1 + x2, IloInfinity, "C1"); IloRange ctr2 ( env, -IloInfinity, x1 - 3 * x2, 10, "C2");
  //ajout des contraintes au modèle
  model.add(ctr1);
  model.add(ctr2);
  // ------------------ AFFICHAGE ET OPTIMISATION ----------------
  // export du PL créé dans un fichier .lp
  cplex.exportModel("test.lp");
  // résolution
  cplex.solve();
  // export de la solution dans un fichier texte
  cplex.writeSolution("sol.txt");
  // récupère la solution et l'affiche à l'écran
  cout << " objectif = " << cplex.getObjValue() << endl;
  cout << " X1 = " << cplex.getValue(x1) << endl;
  cout << " X2 = " << cplex.getValue(x2) << endl;
  env.end();
  return 0;
}
