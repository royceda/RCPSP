#include "Parser.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

Parser::Parser() {
}

Parser::Parser(const string & filename) {
    ifstream file(filename.c_str(), ios::in);
    if (file) {
        string line;
        istringstream ssline(line);
        int ite = 0;
        while (ite < 4) {
            getline(file, line);
            ite++;
        }
        std::string tmp;
        getline(file, line);
        ssline.clear();
        ssline.str(line);
        ssline >> tmp >> tmp >> _projects;
        std::cout << "projects : " << _projects << "\n";
        getline(file, line);
        ssline.clear();
        ssline.str(line);
        ssline >> tmp >> tmp >> tmp >> tmp >>_jobs;
        std::cout << "jobs : " << _jobs << "\n";
        getline(file, line);
        ssline.clear();
        ssline.str(line);
        ssline >> tmp >> tmp >> _horizon;
        std::cout << "horizon : " << _horizon << "\n";

        ite = 0;
        while (ite < 7) {
            getline(file, line);
            ite++;
        }
        getline(file, line);
        ssline.clear();
        ssline.str(line);
        ssline >> tmp >> tmp >> _rDate >> _dDate >> _tardCost>>_MPM_time;
        std::cout << "releaseDate = " << _rDate << " dueDate = " << _dDate << " tardCost = " << _tardCost << " MPMTIME = " << _MPM_time << "\n";
        ite = 0;
        while (ite < 3) {
            getline(file, line);
            ite++;
        }
        //Getting the successors of each job
        ite = 0;
        int tmpInt;
        int tmpSuc;
        vector<int> tmpVector;
        while (ite < jobs()) {
            getline(file, line);
            ssline.clear();
            ssline.str(line);
            ssline >> tmpInt>>tmpInt>>tmpInt;
            tmpVector.clear();
            while(ssline){
                ssline >> tmpSuc ;
                tmpVector.push_back(tmpSuc - 1);
            }
            tmpVector.pop_back();
            _sucVector.push_back(tmpVector);
            ite++;
        }
        int i =0;
        for(ite =0 ; ite<jobs(); ite++){
            cout <<ite<<" suc = ";
            for(i = 0; i< _sucVector[ite].size(); i++)
                cout <<_sucVector[ite][i]<<" ";
            cout<<"\n";
        }

        //Getting the durations and the requests of the jobs per machine
        ite=0;
        while(ite<4){
            getline(file, line);
            ite++;
        }
        int tmpDur;
        int tmpR;
        vector<int> tmpRequest;
        for(ite = 0; ite< jobs(); ite++){
            getline(file, line);
            ssline.clear();
            ssline.str(line);
            ssline>>tmpInt>>tmpInt;
            ssline >> tmpDur;
            _durationsVector.push_back(tmpDur);
            tmpRequest.clear();
            while(ssline){
                ssline>>tmpR;
                tmpRequest.push_back(tmpR);
            }
            tmpRequest.pop_back();
            _reqJobsMach.push_back(tmpRequest);	    
        }


	
        for(ite =0 ; ite<jobs(); ite++){
            cout <<ite<<" request = ";
            for(i = 0; i< _reqJobsMach[ite].size(); i++)
                cout <<_reqJobsMach[ite][i]<<" ";
            cout<<"\n";
        }


        ite = 0;
        while (ite<3){
            getline(file, line);
            ite++;
        }

        //Getting the number of ressources and their availibilities
        getline(file, line);
        ssline.clear();
        ssline.str(line);
        int tmpA;
        while(ssline){
            ssline>>tmpA;
            _resAvail.push_back(tmpA);
            _nOfRes ++;
        }
        _resAvail.pop_back();
        _nOfRes --;
        cout << _nOfRes <<"\n";
        for(int j =1; j<=_nOfRes; j++){
            cout<<"RESj : "<<resAvail()[j-1]<<"\n";
        }

	for(unsigned int i = 0; i < _nOfRes; i++){
	  _reqJobsMach[0] = _reqJobsMach[0] + resAvail()[i];
	  _reqJobsMach[jobs()-1] =  _reqJobsMach[jobs()-1] + resAvail()[i];


	}
	
        file.close();
    } else
        cerr << "Impossible to open the file\n";
}

/**
 *
 * @return the number of projects
 */
int Parser::projects() {
    return _projects;
}

/**
 *
 * @return horizon
 */
int Parser::getHorizon() {
    return _horizon;
}

/**
 *
 * @return the number of jobs
 */
int Parser::jobs() {
    return _jobs;
}

/**
 *
 * @return the release dates
 */
int Parser::rDate() {
    return _rDate;
}

/**
 *
 * @return the due date
 */
int Parser::dueDate() {
    return _dDate;
}

/**
 *
 * @return Cost of tardness
 */
int Parser::tardCost() {
    return _tardCost;
}

/**
 *
 * @return
 */
int Parser::MPMTime() {
    return _MPM_time;
}

/**
 *
 * @return the succersors vector per jobs
 */
vector<vector<int> > Parser::sucVector() {
    return _sucVector;
}

/**
 *
 * @return the duration vector per jobs
 */
vector<int> Parser::durationsVector() {
    return _durationsVector;
}

/**
 *
 * @return the requests of the jobs per machine
 */
vector<vector<int> > Parser::reqJobsMach() {
    return _reqJobsMach;
}

/**
 *
 * @return the number of ressources
 */
int Parser::nOfRes() {
    return _nOfRes;
}

/**
 *
 * @return the availibilities per ressource
 */
vector<int> Parser::resAvail() {
    return _resAvail;
}
