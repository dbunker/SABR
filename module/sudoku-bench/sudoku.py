# test sudoku using various solvers
# top95.txt from http://norvig.com/sudoku.html

import sys, os, time, random, math, numpy, sudokurand
relFold = '../../'
sys.path.append(relFold + 'module')
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
	
	cmd = sabrObj.getCmd(relFold+'sabr',1)
	return cmd

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
	return cmd

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
	return cmd

def cvc4Solver(blockSize,line):

	def select(list):
		return ' '.join('(select a {0})'.format(l) for l in list)
	
	nums = '123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMO'
	
	lineSize = blockSize * blockSize
	boardSize = lineSize * lineSize
	
	lines = []
	lines.append('(set-logic AUFLIRA)')
	lines.append('(set-option :produce-models true)')
	lines.append('(declare-fun a () (Array Int Int))')
	
	index = numpy.arange(boardSize).reshape(lineSize,lineSize)
	for i in xrange(lineSize):
		lines.append('(assert (distinct {}))'.format(select(index[:,i])))
		lines.append('(assert (distinct {}))'.format(select(index[i,:])))
	
		r0 = (i % blockSize) * blockSize
		c0 = (i // blockSize) * blockSize
		lines.append('(assert (distinct {}))'.format(
			select(index[r0:r0+blockSize,c0:c0+blockSize].ravel())
		))
	
	for i in xrange(boardSize):
		lines.append('(assert (< 0 (select a {0})))'.format(i))
		lines.append('(assert (> ' + str(lineSize+1) + ' (select a {0})))'.format(i))
	
	for i, n in zip(xrange(boardSize), line):
		if n != '.':
			outN = str(nums.index(n)+1)
			lines.append('(assert (= {0} (select a {1})))'.format(outN, i))
	
	lines.append('(check-sat)')
	lines.append('(get-value ({}))'.format(select(xrange(boardSize))))
	
	out = open('puzzle.smt', 'w')
	outStr = '\n'.join(lines)
	out.write(outStr)
	out.write('\n')
	out.close()
	
	# cvc4 must be added to project path
	# downloadable from http://cvc4.cs.nyu.edu/web/#Downloads
	cmd = 'cvc4 --lang smt puzzle.smt > cvc4-result.txt'
	return cmd

def pythonSolver(blockSize,line):

	cmd = 'python pythonsolver.py ' + str(blockSize) + ' ' + line
	return cmd



