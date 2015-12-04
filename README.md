# RCPSP
implementation of RCPSP in C++ by using concert lib by IBM


15 RÉFÉRENCES
[1] IBM Knowledge Center, Manuel de référence en ligne
http://www-01.ibm.com/support/knowledgecenter/SSSA5P_12.6.0/ilog.odms.cplex.help/refcppcplex/html/overview.html?cp=SSSA5P_12.6.0%2F2-8&lang=fr

[2] IBM, IBM ILOG CPLEX Optimization Studio Getting Started with CPLEX, Version 12 Release 4 http://cedric.cnam.fr/~lamberta/MPRO/ECMA/doc/Interface.pdf

[3] IBM Knowledge Center, Anatomie d'une application C++ Concert Technology
http://www-01.ibm.com/support/knowledgecenter/SSSA5P_12.6.0/ilog.odms.cplex.help/CPLEX/GettingStarted/topics/tutorials/Cplusplus/appliAnatomy_synopsis.html?lang=fr

[4] IBM Knowledge Center, La classe IloCplex
http://www-01.ibm.com/support/knowledgecenter/SSSA5P_12.6.0/ilog.odms.cplex.help/refcppcplex/html/classes/IloCplex.html?lang=fr


How use it:

create a directory named lib in trunk directory with your directories concert and cplex.

Problems:

<h3>I.Easy formulation<h3>
<ul>
<li>1. Flow ressources problem</li>
<li>2. Time-indexed</li>
</ul>


<h3>II. Hard Formulation</h3> 
<ul>
<li>1. Not allowed configurations (cut generation)</li>
<li>2. Allowed configurations (row generation)</li>
</ul>
