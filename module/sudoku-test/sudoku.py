# top95.txt from http://norvig.com/sudoku.html

import sys
sys.path.append("..")
import sabr

def makeConstraints(boardSet):

	letterArr = 'abcdefghi'
	sabrObj = sabr.SabrObj()
	
	# sym
	sabrObj.setSym(['1','2','3','4','5','6','7','8','9'])
	
	# board
	boardArr = [['.']*9 for x in xrange(9)]
	for y in range(0,9):
		for x in range(0,9):
			boardArr[y][x] = letterArr[y] + str(x)
			
	sabrObj.setBoard(boardArr)
	
	# req board
	boardArr = [['.']*9 for x in xrange(9)]
	for y in range(0,9):
		for x in range(0,9):
			val = boardSet[y*9+x]
			if val == '.':
				val = '?'
			boardArr[y][x] = val
			
	sabrObj.addReq('Board',boardArr)
	sabrObj.addReqSpace()
	
	# all different
	sabrObj.addAllDif('RowColBlock',9)
	
	# desobj row
	for y in range(0,9):
		desObjRow = []
		for x in range(0,9):
			desObjRow.append(letterArr[y] + str(x))
		sabrObj.addDesObj('RowColBlock',desObjRow)
		
	sabrObj.addDesObjSpace()
	
	# desobj column
	for y in range(0,9):
		desObjCol = []
		for x in range(0,9):
			desObjCol.append(letterArr[x] + str(y))
		sabrObj.addDesObj('RowColBlock',desObjCol)
		
	sabrObj.addDesObjSpace()
	
	# desobj block
	for blockY in range(0,3):
		for blockX in range(0,3):
		
			desObjBlock = []
			for y in range(0,3):
				for x in range(0,3):
					val = letterArr[blockY*3+y] + str(blockX*3+x)
					desObjBlock.append(val)
					
			sabrObj.addDesObj('RowColBlock',desObjBlock)
	
	return sabrObj

# for each new line in file create new board req
probs = open('top95.txt','r')
for line in probs:
	arr = list(line)
	
	sabrObj = makeConstraints(arr)
	
	# process
	(out,stats) = sabrObj.process('../../sabr')
	print line,out,stats

