# top95.txt from http://norvig.com/sudoku.html

import sys, time, random, sudokurand
sys.path.append("..")
import sabr

def sabrSolver(boardStr):
	boardStr = boardStr.strip().replace('.','?')

	rows = 'ABCDEFGHI'
	nums = '123456789'
	cols = nums
	sabrObj = sabr.SabrObj()
	
	def cross(A, B):
		return [a+b for a in A for b in B]
	
	# sym
	sabrObj.setSym(list(nums))
	
	# board
	board = [cross(rows, c) for c in cols]
	sabrObj.setBoard(board)
	
	# req board
	boardArr = [list(boardStr[i:i+9]) for i in range(0,len(boardStr),9)]
	sabrObj.addReqGroup('Board',[boardArr])
	
	# all different
	sabrObj.addAllDif('RowColBlock',9)
	
	# desobj row
	des = [cross(rows, c) for c in cols]
	sabrObj.addDesObjGroup('RowColBlock',des)
	
	# desobj column
	des = [cross(r, cols) for r in rows]
	sabrObj.addDesObjGroup('RowColBlock',des)
	
	# desobj block
	des = [cross(rs, cs) for rs in ('ABC','DEF','GHI') for cs in ('123','456','789')]
	sabrObj.addDesObjGroup('RowColBlock',des)
	
	return sabrObj.process('../../sabr')

# generateTest takes an integer argument for test number
def runTests(generateTest,solver,numTests=100,outFile='tests.txt',threshold=-1.0):
	
	file = open(outFile,'w')
	for i in range(numTests):
	
		line = generateTest(i)
		start = time.clock()
		solver(line)
		tm = time.clock()-start
		
		outLine = str(tm) + '\t' + line
		file.write(outLine)
		
		if tm > threshold:
			print outLine

# closure
def fileTestGen(name):
	file = open(name,'r')
	lines = file.read().split('\n')
	
	return lambda i: lines[i]

# random
def randomTest(_):
	return sudokurand.random_puzzle()

runTests(randomTest,sabrSolver,100)
#runTests(randomTest,sudokurand.solve,100)
