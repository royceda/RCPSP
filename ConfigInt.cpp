#include <ilcplex/ilocplex.h>
#include <iostream>

#include "ConfigInt.hpp"

ILOSTLBEGIN

typedef IloArray< IloArray<IloNumArray> > NumMatrix;

using namespace  std;




/**
*TODO
* chemin critique
* creation des intervalles de chaque noeud (plus tot, lus tard)
* Pour tout noeud
* Reduction d'espace de recherche pour la config
* creation de la config
*/
ConfigInt::ConfigInt(){}






ConfigInt::ConfigInt(Parser &p):
_n(p.jobs()),_bigM(1000000), _T(p.getHorizon()),
_r(p.nOfRes()), model(env),  S(env, p.jobs()), constraints(env), x(env, p.jobs()),
_b(p.reqJobsMach()), _p(p.durationsVector()), _B(p.resAvail()){
  for (int i = 0; i < _n; i++) {
    x[i] = IloArray<IloNumVar> (env, _n);
    char name1[256];
    sprintf(name1, "S %d ", i);
    S[i] = IloNumVar(env, 0, p.getHorizon() - p.durationsVector()[i], ILOINT, name1);
    //f[i] = IloArray <IloArray <IloNumVar> > (env, _n);

    for (int j = 0; j < _n; j++) {
      char name[256];
      sprintf(name, "X %d %d", i, j);
      x[i][j] = IloNumVar(env, 0, 1, ILOBOOL, name);
      for (int k = 0; k < p.nOfRes(); k++) {
        sprintf(name, "f %d %d %d", i, j, k);
      }
    }
  }
  cout<<"INIT DONE\n";
}






IloObjective ConfigInt::objective(){
  IloObjective obj(env, S[_n - 1], IloObjective::Minimize, "OBJ");
  return obj;
}


int ConfigInt::bigM(){
  return _bigM;
}

IloNumArray ConfigInt::v(){
  return _v;
}

vector<int> ConfigInt::Slate(){
  return _Slate;
}

void ConfigInt::addConstraints(Parser &p){
  for(int i = 0; i < _n; i++){
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
  }
  /*Les deux premiere*/
  for(int i = 0; i < _n; i++){
    IloExpr e2(env);
    for(int j =0; j < _n; j++){
      e2 =  x[i][j] + x[j][i] ;
      model.add(e2 <= 1);
      e2.end();


      IloExpr e3(env);
      for(int k = 0; k <_n; k++){
        e3 = x[i][j] + x[j][k] - x[i][k] ;
        model.add(e3 <= 1);
      }
      e3.end();
    }
  }


  for(int i = 0; i < _n; i++){
    IloExpr e4(env);
    for(int j = 0; j < _n; j++){
      e4 = S[j] - S[i] - (p.durationsVector()[i] + bigM())*x[i][j];
      model.add(e4 >= - bigM());
      e4.end();
    }
  }
}



bool ConfigInt::createConfig(IloNumArray v){
  bool boolNewConf = false;
  //cout<<"......\n";
  vector< vector <int> > tmp;
  vector< vector <int> > conf2;
  for(int i = 1; i< _n-1; i++){
    vector<int> tmpI;
    tmpI.push_back(i);
    for(int j = 1; j<_n-1; j++){
      if(i != j){
        if(v[j] <= v[i]){
          if ((v[j] + _p[j]) > v[i]){
            tmpI.push_back(j);
          }
        }
      }
    }
    tmp.push_back(tmpI);
    tmpI.clear();
  }


  for(int j = 0; j<tmp.size(); j++){
    for(int k =0; k < _r; k++){
      int sum = 0;

      for(int i = 0; i < tmp[j].size(); i++){
        int index = tmp[j][i];
        sum += _b[index][k];
      }

      if(sum > _B[k]){
        boolNewConf = true;
        conf2.push_back(tmp[j]);
      }
    }
  }
  for(int a = 0; a < conf2.size(); a++){
    IloExpr e(env);
    for(int b = 0; b < conf2[a].size(); b++){
      for(int c = 0; c < conf2[a].size(); c++){
        if(b != c){
          e += x[conf2[a][b]][conf2[a][c]];
        }
      }
    }
    //cout << "e = "<<e<<"\n";
    model.add(e >= 1);
    e.end();
  }


  if(!conf2.empty()){
    for(int k =0; k<conf2.size(); k++){
      F.push_back(conf2[k]);
    }
  }
  return boolNewConf;
}





void ConfigInt::solve(Parser& p){
  try{
   model.add(objective());
   //cout << "objectif"<< endl;

   addConstraints(p);
   //cout << "const"<< endl;
   /*premier solve*/

   IloCplex cplex(model);
   cplex.solve();



   cout<<"OK\n";

   //addConfig(p);
   /*second solve*/
   //IloCplex cplex(model);
   //cplex.solve();
   cout <<"\n\nSOL= " <<cplex.getObjValue()<<"\n\n";
   cout << cplex.getObjValue() << endl;

   bool finished= false;
   while(!finished){
     IloNumArray _v(env);
     //cout <<"OK\n";
     cplex.getValues(_v, S);
     //cout<<"OK2\n";

     finished = !createConfig(_v);
     _v.end();
     //cout<<"OK2\n";

     cplex.solve();


     cout << "\n\nSOL= " << cplex.getObjValue() << "\n\n";
     for (int i = 0; i < p.jobs(); i++) {
       cout << "S" << i << " = " << cplex.getValue(S[i]) << "\n";
     }

     cout << cplex.getObjValue() << endl;
   }
   IloNumArray _v(env);
   cplex.getValues(_v, S);
   //cout<<"v NULL?? "<<_v<<" and _n = "<<_n<<"\n";
   for(int i = 0; i < _n; i++){
      _vSol.push_back(_v[i]);
   }
 }
 catch (IloException& e) {
  cerr << "ERROR : " << e << "\n";
  }

}



//line1 n r
//line2 R1 R2 ...
//line3 B1 B2 ...
//line4 j1 j2 ..
//line5 S1 S2 ...
//line6 p1 p2 ...
//line7 to r  b11 b12 ...

void ConfigInt::writeSolution(string fileName){
  //string fname = "sol.txt";
  ofstream file(fileName.c_str(), ios::out);
  //cout<<"file OKKK\n";
  if(file){
    file << _n << " "<< _r << "\n";

    //line2
    for(int i = 0; i<_r; i++){
      file << i << " ";
    }
    file << "\n";

    //line3
    for(int i = 0; i<_r; i++){
      file << _B[i] << " ";
    }
    file << "\n";

    //line4
    for(int i = 0; i<_n; i++){
      file << i << " ";
    }
    file << "\n";

    //line 5
    for(int i =0; i< _n; i++){
      file << _vSol.front() << " ";
      //cout << i<< " : "<<_vSol.front()<<"\n";
      _vSol.pop_front();
    }

    //line6
    for(int i = 0; i<_n; i++){
      file << _p[i] << " ";
    }
    file << "\n";

    //from line7
    for(int i= 0; i<_r; i++){
      for(int j = 0; j<_n; j++){
        file << _b[i][j] << " ";
      }
      file << "\n";
    }


   file.close();
 }
 else
  cerr << "Error while trying to write the file\n";

}
