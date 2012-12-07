# top95.txt from http://norvig.com/sudoku.html

import sys, time, random, sudokurand
sys.path.append("..")
import sabr

def makeConstraints(boardStr):

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
	
	return sabrObj

# for each new line in file create new board req
def hardTests():
	probs = open('top95.txt','r')
	for line in probs:
		
		# process
		sabrObj = makeConstraints(line.strip().replace('.','?'))
		(out,stats) = sabrObj.process('../../sabr')
		
		print line,out,stats

# create random sudokus to solve
def randomTests():

	outFile = open('tests.txt','w')
	for _ in range(0,1000000):
		
		# random puzzle
		line = sudokurand.random_puzzle()
		
		# process
		sabrObj = makeConstraints(line.strip().replace('.','?'))
		(out,stats) = sabrObj.process('../../sabr')
		
		# get time
		part1 = stats.split('CPU time              : ')[1]
		strNum = part1.split('s')[0].strip()
		num = float(strNum)
		
		# output time to solve, then the puzzle
		outLine = str(num) + ' \t' + line
		print outLine
		outFile.write(outLine+'\n')

def pythonSolve():
	easy1 = '4.....8.5.3..........7......2.....6.....8.4......1.......6.3.7.5..2.....1.4......'
	sudokurand.solve_all([easy1])
	
	hard1 = '.....6....59.....82....8....45........3........6..3.54...325..6..................'
	sudokurand.solve_all([hard1])

randomTests()
