SABR
================================
 
General
-------------------------

SABR (Spatial and Action Based Resolver) is a constraint programming language designed with an emphasis on spatial and temporal logic. 

Programs compile to CNF (Conjunctive Normal Form), which is then solved by a CNF solver. 

The goal of the language is to make representing operations research problems not just possible, but also intuitive and the solving of these problems efficient. 

From a theoretical perspective, the language can also be used to prove a problem is NP-Easy and can be used to verify properties about automata and systems that can be modeled as automata such as circuits and programs.

website: sabrlang.org

Install
-------------------------

SABR is installed using setup.py

python setup.py build  
	Will build SABR and the CNF solver
	
python setup.py help  
	For more commands

Run
-------------------------

To run SABR, provide the number of stages to use, an optional flag, and the input code.

Example:  
./sabr 20 test/Simple/simple.tb

./sabr --help  
	For more commands

Testing
-------------------------

Testing is done with test.py. For more documentation check /doc/LANGUAGE.

python test.py all  
	Runs all tests

python test.py help  
	For more commands
