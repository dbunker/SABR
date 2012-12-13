# test sudoku using various solvers
# top95.txt from http://norvig.com/sudoku.html

import sys, os, time, random, math, sudokurand, cvc4sudo
sys.path.append("..")
import sabr

def sabrSolver(blockSize,boardStr):
	boardStr = boardStr.strip().replace('.','?')
	
	size = blockSize * blockSize
	nums = '123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMO'
	rows = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ123456789abcdefghijklmo'
	
	nums = nums[:size]
	rows = rows[:size]
	
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
	boardArr = [list(boardStr[i:i+size]) for i in range(0,len(boardStr),size)]
	sabrObj.addReqGroup('Board',[boardArr])
	
	# row
	des = [cross(rows, c) for c in cols]
	sabrObj.addAllDifGroup(des)
	
	# column
	des = [cross(r, cols) for r in rows]
	sabrObj.addAllDifGroup(des)
	
	# block
	blen = int(math.sqrt(size)+0.5)
	rb = [rows[i:i+blen] for i in range(0,size,blen)]
	cb = [cols[i:i+blen] for i in range(0,size,blen)]
	
	des = [cross(rs, cs) for rs in rb for cs in cb]
	sabrObj.addAllDifGroup(des)
	
	return sabrObj.process('../../sabr')

# generateTest takes an integer argument for test number as well as 
# blockSize which is block width
def runTests(blockSize,generateTest,solver,shower,numTests=100,
				outFile='tests.txt',threshold=-1.0):
	
	file = open(outFile,'w')
	for i in range(numTests):
	
		line = generateTest(blockSize,i)
		
		if line == None:
			return
		line = line.strip()
		
		start = time.time()
		res = solver(blockSize,line)
		tm = time.time()-start
		
		outLine = shower(line,res,tm)
		file.write(outLine)
		
		if tm > threshold:
			print outLine

# need to install minizinc from http://www.g12.csse.unimelb.edu.au/minizinc/download.html
# and place in system path to run this test
def minizincSolver(blockSize,line):

	# to get the number associated with the char
	nums = '123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMO'

	size = blockSize * blockSize
	
	outStr = 'include "sudokusolve.mzn";\n\n'
	outStr += 'S=' + str(blockSize) + ';\n'
	outStr += 'puzzle=[|\n'
	
	for y in range(size):
		for x in range(size):
			elem = line[y*size+x]
			newElem = elem
			
			if elem == '.':
				newElem = '_'
			else:
				newElem = str(nums.index(elem)+1)
				
			outStr += newElem + ', '
		outStr = outStr[:-2] + '|\n'
	outStr += '|];'
	
	source = open('puzzle.mzn','w')
	source.write(outStr)
	source.close()
	
	cmd = 'minizinc puzzle.mzn > puzzle-out.txt'
	os.system(cmd)

# random
def randomTest(size,i):
	res = sudokurand.random_puzzle(size)
	return res

def regLineShower(line,res,tm):
	
	return str(tm) + '\t' + line + '\n'

# show sabr stats
def statsLineShower(line,res,tm):
	
	statsFile = open('stats.txt','r')
	stats = statsFile.read()
	arr1 = stats.split('CPU time              : ')[1]
	numStr = arr1.split('s',)[0].strip();
	
	return regShower(line,res,numStr)

# closure
def fileTestGen(name):
	file = open(name,'r')
	lines = file.read().strip().split('\n')
	
	def fileTest(size,i):
		if i >= len(lines):
			return None
		return lines[i]
		
	return fileTest

file95Test = fileTestGen('top95.txt')

testOptions = [ randomTest, file95Test ]
tester = testOptions[0]

solverOptions = [ sabrSolver, minizincSolver, sudokurand.solve, cvc4sudo.solve ]
solver = solverOptions[0]

timeShowOptions = [ regLineShower, statsLineShower ]
shower = timeShowOptions[0]

boardSize = 6
numTests = 1

runTests(boardSize,tester,solver,shower,numTests)

