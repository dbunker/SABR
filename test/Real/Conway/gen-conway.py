# plays conway game of life, showing a set of initial boards
# that will lead to the provided end board

import os

##############################

# create combination of characters
# construct recursively
def combSimp(val,numVal,soFar,left,acc):
	
	# go through each val
	if len(left) == 0 or numVal == 0:
		acc.append(soFar + ([val]*numVal) + left)
		return
	
	# pick number to place now and later
	for i in range(numVal,-1,-1):
		
		newSoFar = soFar + ([val]*i) + [left[0]]
		newLeft = left[1:]
		newNum = numVal - i
		
		combSimp(val,newNum,newSoFar,newLeft,acc)

# this will give a list of every combination of each of these number of characters
# combMany([('A',4),('B',4)])
def combMany(li):
	li.reverse()
	
	newLeftListGroup = [[]]
	for (val,numVal) in li:
		
		leftListGroup = newLeftListGroup
		newLeftListGroup = []
		
		for leftList in leftListGroup:
			combSimp(val,numVal,[],leftList,newLeftListGroup)

	return newLeftListGroup

def createBoard(xSize,ySize,zSize):

    outStr = ''
    outStr += 'Sym { 0 1 }\n\n'
    outStr += 'Board {\n'

    # cell-z-y-x
    for z in range(0,zSize):
        for y in range(0,ySize):
            outStr += '\t'
            
            for x in range(0,xSize):
                outStr += 'cell-' + str(z) + '-' + str(y) + '-' + str(x) + ' '
            outStr = outStr[:-1] + ';\n'
        outStr += '\n'
    outStr = outStr[:-1] + '}\n\n'
    
    return outStr
                
def createBoardSet(reqBoard,z):
    
    outStr = 'DesObj ReqFinalBoard {\n'
    ySize = len(reqBoard)
    xSize = len(reqBoard[0])
    
    # cell-z-y-x
    for y in range(0,ySize):
        outStr += '\t'
        
        for x in range(0,xSize):
            outStr += 'cell-' + str(z) + '-' + str(y) + '-' + str(x) + ' '
        outStr = outStr[:-1] + ';\n'
    
    outStr += '}\n\n'
    
    outStr += 'Req ReqFinalBoard {\n'
    
    # cell-z-y-x
    for y in range(0,ySize):
        outStr += '\t'
        
        for x in range(0,xSize):
            outStr += str(reqBoard[y][x]) + ' '
        outStr = outStr[:-1] + ';\n'
    
    outStr += '}\n\n'
    
    return outStr

def createOpt(startVal, endVal, groupName, toGroup):
    
    group = combMany(toGroup)
    
    outStr = ''
    for item in group:
        
        newStr = ''
        for v in item:
            newStr += str(v) + ' '
        
        outStr += 'Opt ' + groupName + ' { ' + startVal + ' ' + endVal + ' ' + newStr + '}\n'
        
    return outStr

##############################
# Rules

# Any live cell with fewer than two live neighbors dies, as if caused by under-population.
# Any live cell with two or three live neighbors lives on to the next generation.
# Any live cell with more than three live neighbors dies, as if by overcrowding.
# Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.

# live 2-or-3 =>          live
# Opt { 1   1     1 1 0 0 0 0 0 0 }
# Opt { 1   1     1 1 0 0 0       }
# Opt { 1   1     1 1 0           }

# dead exactly-3 =>       live
# Opt { ?   1     1 1 1 0 0 0 0 0 }
# Opt { ?   1     1 1 1 0 0       }
# Opt { ?   1     1 1 1           }

# live fewer-than-2 =>    dead
# Opt { ?   0     ? 0 0 0 0 0 0 0 }
# Opt { ?   0     ? 0 0 0 0       }
# Opt { ?   0     ? 0 0           }

# Opt { 0   0     ? ? 0 0 0 0 0 0 }
# Opt { 0   0     ? ? 0 0 0       }
# Opt { 0   0     ? ? 0           }

# live more-than-3 =>     dead
# Opt { ?   0     1 1 1 1 ? ? ? ? }
# Opt { ?   0     1 1 1 1 ?       }

##################

def addOpt():

    outStr = ''
    
    # live 2-or-3 =>          live
    # Opt { 1   1     1 1 0 0 0 0 0 0 }
    outStr += createOpt('1', '1', 'Group8', [('1',2),('0',6)]) + '\n'
    
    # Opt { 1   1     1 1 0 0 0       }
    outStr += createOpt('1', '1', 'Group5', [('1',2),('0',3)]) + '\n'
    
    # Opt { 1   1     1 1 0           }
    outStr += createOpt('1', '1', 'Group3', [('1',2),('0',1)]) + '\n'
    
    
    # dead exactly-3 =>       live
    # Opt { ?   1     1 1 1 0 0 0 0 0 }
    outStr += createOpt('?', '1', 'Group8', [('1',3),('0',5)]) + '\n'
    
    # Opt { ?   1     1 1 1 0 0       }
    outStr += createOpt('?', '1', 'Group5', [('1',3),('0',2)]) + '\n'
    
    # Opt { ?   1     1 1 1           }
    outStr += createOpt('?', '1', 'Group3', [('1',3)]) + '\n'
    
    
    # live fewer-than-2 =>    dead
    # Opt { ?   0     ? 0 0 0 0 0 0 0 }
    outStr += createOpt('?', '0', 'Group8', [('?',1),('0',7)]) + '\n'
    
    # Opt { ?   0     ? 0 0 0 0       }
    outStr += createOpt('?', '0', 'Group5', [('?',1),('0',4)]) + '\n'
    
    # Opt { ?   0     ? 0 0           }
    outStr += createOpt('?', '0', 'Group3', [('?',1),('0',2)]) + '\n'
    
    
    # Opt { 0   0     ? ? 0 0 0 0 0 0 }
    outStr += createOpt('0', '0', 'Group8', [('?',2),('0',6)]) + '\n'
    
    # Opt { 0   0     ? ? 0 0 0       }
    outStr += createOpt('0', '0', 'Group5', [('?',2),('0',3)]) + '\n'
    
    # Opt { 0   0     ? ? 0           }
    outStr += createOpt('0', '0', 'Group3', [('?',2),('0',1)]) + '\n'
    
    
    # live more-than-3 =>     dead
    # Opt { ?   0     1 1 1 1 ? ? ? ? }
    outStr += createOpt('?', '0', 'Group8', [('1',4),('?',4)]) + '\n'
    
    # Opt { ?   0     1 1 1 1 ?       }
    outStr += createOpt('?', '0', 'Group5', [('1',4),('?',1)]) + '\n'
    
    return outStr

def addOptDesObj(xSize,ySize,zSize):
    
    outStr = ''
    
    # cell-z-y-x
    for z in range(0,zSize-1):
        
        for y in range(0,ySize):
            for x in range(0,xSize):
                
                surroundList = ''
                num = 0
                for subY in range(max(y-1,0),min(y+2,ySize)):
                    
                    for subX in range(max(x-1,0),min(x+2,xSize)):
                        
                        if not (subX == x and subY == y):
                            surroundList += 'cell-' + str(z) + '-' + str(subY) + '-' + str(subX) + ' '
                            num += 1
                
                currentCell = 'cell-' + str(z) + '-' + str(y) + '-' + str(x)
                nextCell = 'cell-' + str(z+1) + '-' + str(y) + '-' + str(x)
                outStr += 'DesObj Group' + str(num) + ' { ' + currentCell + ' ' + nextCell + ' ' + surroundList + '}\n'
                
            outStr = outStr[:-1] + '\n'
            
    return outStr

def writeConway(endBoard,steps):
    
    xSize = len(endBoard)
    ySize = len(endBoard[0])
    zSize = steps

    outStr = ''
    outStr += createBoard(xSize,ySize,zSize)
    outStr += createBoardSet(endBoard,zSize-1)
    outStr += addOpt()
    outStr += addOptDesObj(xSize,ySize,zSize)

    outFi = open('conway.tb','w')
    outFi.write(outStr)
    outFi.close()
    
def processGame(sabrCmd,ySize):
    
    cmd = sabrCmd + ' 1 conway.tb'
    os.system(cmd)
    
    inFi = open('result.txt','r')
    outFi = open('final.txt','w')
    
    num = 0
    for line in inFi:
        
        if num == ySize:
            outFi.write('\n')
            num = 0
        num += 1
        
        outFi.write(line)
    
    outFi.close()
    inFi.close()

def testExample():
    
    endBoard = [
        [ 0, 0, 0, 0 ],
        [ 0, 1, 0, 1 ],
        [ 0, 1, 0, 1 ],
        [ 0, 0, 1, 0 ]
    ]
    
    writeConway(endBoard,2)

testExample()
