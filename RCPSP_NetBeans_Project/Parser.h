/* 
 * File:   Parser.h
 * Author: yoannjvr
 *
 * Created on 9 décembre 2015, 16:49
 */

#ifndef PARSER_H
#define	PARSER_H

#include <fstream>
#include <vector>

using namespace std;

class Parser{
public:
    
    Parser();
    
    Parser(const string & filename);
    
    /**
     * 
     * @return the number of projects
     */
    int projects();
    
    /**
     * 
     * @return horizon
     */
    int getHorizon();
    
    /**
     * 
     * @return the number of jobs
     */
    int jobs();
    
    /**
     * 
     * @return the release dates
     */
    int rDate();
    
    /**
     * 
     * @return the due date
     */
    int dueDate();
    
    /**
     * 
     * @return Cost of tardness
     */
    int tardCost();
    
    /**
     * 
     * @return 
     */
    int MPMTime();
    
    /**
    * 
    * @return the succersors vector per jobs
    */
    vector<vector<int> > sucVector();

    /**
     * 
     * @return the duration vector per jobs
     */
    vector<int> durationsVector();

    /**
     * 
     * @return the requests of the jobs per machine
     */
    vector<vector<int> > reqJobsMach();
    
    /**
     * 
     * @return the number of ressources
     */
    int nOfRes();
    
    /**
     * 
     * @return the availibilities per ressource
     */
    vector<int> resAvail();
    
    
private:
    /*
     * number Of Projects
     */
    int _projects;
    
    /*
     * Horizon
     */
    int _horizon;
    
    /*
     * number Of jobs
     */
    int _jobs;
    
    /*
     * releaseDate
     */
    int _rDate; 
    
    /*
     * Due Date
     */
    int _dDate;
    
    /*
     * Cost of tardness
     */
    int _tardCost;
    int _MPM_time;
    
    /*
     * successors vector per job
     */
    vector<vector<int> > _sucVector;
    
    /*
     * Duration of the jobs
     */
    vector<int> _durationsVector;
    
    /*
     * Requests of the jobs per machine
     */
    vector<vector<int> > _reqJobsMach;
    
    /*
     * number Of ressouces
     */
    int _nOfRes;
    
    /*
     *ressources availibilities
     */
    vector<int> _resAvail;
    

};


#endif	/* PARSER_H */

