# top95.txt from http://norvig.com/sudoku.html

import sys, time, random, math, sudokurand
sys.path.append("..")
import sabr

def sabrSolver(boardStr):
	boardStr = boardStr.strip().replace('.','?')

	# rows = 'ABCDEFGHI'
	# nums = '123456789'
	
	rows = 'ABCDEFGHIJKLMNOP' 
	nums = '123456789abcdefg'
	
	cols = nums
	size = len(rows)
	sabrObj = sabr.SabrObj()
	
	def cross(A, B):
		return [a+b for a in A for b in B]
	
	# sym
	sabrObj.setSym(list(nums))
	
	# board
	board = [cross(rows, c) for c in cols]
	sabrObj.setBoard(board)
	
	# req board
	boardArr = [list(boardStr[i:i+size]) for i in range(0,len(boardStr),size)]
	sabrObj.addReqGroup('Board',[boardArr])
	
	# all different
	sabrObj.addAllDif('RowColBlock',size)
	
	# desobj row
	des = [cross(rows, c) for c in cols]
	sabrObj.addDesObjGroup('RowColBlock',des)
	
	# desobj column
	des = [cross(r, cols) for r in rows]
	sabrObj.addDesObjGroup('RowColBlock',des)
	
	# desobj block
	blen = int(math.sqrt(size)+0.5)
	rb = [rows[i:i+blen] for i in range(0,size,blen)]
	cb = [cols[i:i+blen] for i in range(0,size,blen)]
	
	des = [cross(rs, cs) for rs in rb for cs in cb]
	sabrObj.addDesObjGroup('RowColBlock',des)
	
	return sabrObj.process('../../sabr')

# generateTest takes an integer argument for test number
def runTests(generateTest,solver,numTests=100,outFile='tests.txt',threshold=-1.0):
	
	file = open(outFile,'w')
	for i in range(numTests):
	
		line = generateTest(i)
		if line == None:
			return
		
		start = time.time()
		solver(line)
		tm = time.time()-start
		
		rows = 'ABCDEFGHIJKLMNOP' 
		nums = '123456789abcdefg'
		
		outLine = str(tm) + '\t' + line
		file.write(outLine)
		
		if tm > threshold:
			print outLine

# closure
def fileTestGen(name):
	file = open(name,'r')
	lines = file.read().strip().split('\n')
	
	def fileTest(i):
		if i >= len(lines):
			return None
		return lines[i]
		
	return fileTest

# random
def randomTest(_):
	return sudokurand.random_puzzle()

fileTest = fileTestGen('top95.txt')

#runTests(fileTest,sabrSolver,1)
#runTests(randomTest,sabrSolver,1)

#runTests(fileTest,sudokurand.solve,1)
#runTests(randomTest,sudokurand.solve,1)
