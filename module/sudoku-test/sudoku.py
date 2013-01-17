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
	sabrObj.addReq(None,'Board',boardArr)
	sabrObj.addSpace()
	
	def addGroup(des):
		for elem in des:
			sabrObj.addAllDif(elem)
		sabrObj.addSpace()
	
	# row
	des = [cross(rows, c) for c in cols]
	addGroup(des)
	
	# column
	des = [cross(r, cols) for r in rows]
	addGroup(des)
	
	# block
	blen = int(math.sqrt(size)+0.5)
	rb = [rows[i:i+blen] for i in range(0,size,blen)]
	cb = [cols[i:i+blen] for i in range(0,size,blen)]
	
	des = [cross(rs, cs) for rs in rb for cs in cb]
	addGroup(des)
	
	return sabrObj.process('../../sabr',1)

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

# need to install swipl (swi-prolog)
def prologSolver(blockSize,line):

	boardStr = line.strip().replace('.','?')
	
	size = blockSize * blockSize
	nums = '123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMO'
	rows = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ123456789abcdefghijklmo'
	
	nums = list(nums[:size])
	rows = list(rows[:size])
	
	cols = nums
	
	def cross(A, B):
		return [a+b for a in A for b in B]
		
	board = [cross(rows, c) for c in cols]
	flatBoard = [item for sublist in board for item in sublist]
	
	outStr = ':- use_module(library(clpfd)).\n\n'
	
	# puzzle param
	outStr += 'puzzle(Cells):-\n'
	
	# vars
	outStr += 'Cells = '
	outStr += str(flatBoard).replace('\'','G') + ',\n'
	outStr += 'Cells ins 1..' + str(size) + ',\n'
	
	# alldif
	def addGroup(des):
		ret = ''
		for elem in des:
			ret += 'all_different(' + str(elem).replace('\'','G') + '),\n'
		return ret
	
	# row all dif
	des = [cross(rows, c) for c in cols]
	outStr += addGroup(des)
	
	# column all dif
	des = [cross(r, cols) for r in rows]
	outStr += addGroup(des)
	
	# block all dif
	blen = int(math.sqrt(size)+0.5)
	rb = [rows[i:i+blen] for i in range(0,size,blen)]
	cb = [cols[i:i+blen] for i in range(0,size,blen)]
	
	des = [cross(rs, cs) for rs in rb for cs in cb]
	outStr += addGroup(des)
	outStr = outStr[:-2] + ',\n'
	
	outStr += 'label(Cells).'
	
	# this puzzle board
	boardArr = [list(boardStr[i:i+size]) for i in range(0,len(boardStr),size)]
	for y in range(0,size):
		for x in range(0,size):
			if boardArr[y][x] == '?':
				boardArr[y][x] = 'G' + board[y][x] + 'G'
			else:
				boardArr[y][x] = str(nums.index(boardArr[y][x])+1)
	
	flatBoardArr = [item for sublist in boardArr for item in sublist]
	boardStr = 'puzzle(' + str(flatBoardArr).replace('\'','') + ').'
	
	source = open('puzzle.pl','w')
	source.write(outStr)
	source.close()
	
	cmd = 'echo \'' + boardStr + '\' | swipl -f puzzle.pl'
	os.system(cmd)
	
	exit()

# random
def randomTest(size,i):
	res = sudokurand.random_puzzle(size)
	return res

def regLineShower(line,res,tm):
	
	return str(tm) + '\t' + line + '\n'

# show sabr stats and regular
def statsLineShower(line,res,tm):
	
	statsFile = open('stats.txt','r')
	stats = statsFile.read()
	arr1 = stats.split('CPU time              : ')[1]
	numStr = arr1.split('s',)[0].strip();
	
	ret = str(tm) + '\t' + str(numStr) + '\t' + line + '\n'
	return ret

# closure
def fileTestGen(name):
	file = open(name,'r')
	lines = file.read().strip().split('\n')
	
	def fileTest(size,i):
		if i >= len(lines):
			return None
		return lines[i]
		
	return fileTest


