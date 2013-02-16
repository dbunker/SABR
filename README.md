SABR
================================

General
-------------------------

SABR (Spatial and Action Based Resolver) is a constraint programming language designed with an emphasis on spatial and temporal logic. 

Programs compile to CNF (Conjunctive Normal Form), which is then solved by a CNF solver. 

The goal of the language is to make representing operations research problems not just possible, but also intuitive and the solving of these problems efficient. 

From a theoretical perspective, the language can also be used to prove a problem is NP-Easy and to verify properties about automata and systems that can be modeled as automata such as circuits and programs.

Install
-------------------------

SABR is installed using setup.py

python setup.py build  
	Will build SABR and the CNF solver

python setup.py help  
	For more commands

Run
-------------------------

To run SABR, provide an optional flag, the number of stages to use, and the input source path.

Example:  
./sabr 20 test/Simple/simple.tb

./sabr --help  
	For more commands

Testing
-------------------------

Testing can be done with test.py. 

python test.py all  
	Runs all tests

python test.py help  
	For more commands

Example
-------------------------

Let's see what the traditional river crossing puzzle (http://wikipedia.org/wiki/river_crossing_puzzle) looks like in SABR.

	Sym { west east }
	
	# each cell on the board can be any symbol
	Board { cabbage goat wolf sailor }
	Start { west west west west }
	End { east east east east }
	
	# transitions for object Crew
	# sailor can take one passenger east or west
	Trans SailEast:Crew { west west => east east }
	Trans SailWest:Crew { east east => west west }
	
	# describe object Crew's cells
	DesObj Goat:Crew { sailor goat }
	DesObj Cabbage:Crew { sailor cabbage }
	DesObj Wolf:Crew { sailor wolf }
	DesObj Alone:Crew { sailor sailor }
	
	# options for object Watch, at least one must match
	# sailor needs to be watching these two if they are together
	Opt Watch { side side side }
	Opt Watch { !side !side side }
	Opt Watch { !side side !side }
	
	DesObj Watch { sailor goat cabbage }
	DesObj Watch { sailor wolf goat }

Running ./sabr 10 source.tb shows us the answer to the puzzle in result.txt (https://gist.github.com/dbunker/4966217).

Other
-------------------------

For more documentation check /doc/LANGUAGE.  
Simple python module can be found at /module/sabr.py  

Website: http://sabrlang.org  
Examples: http://sabrlang.org/river.html
