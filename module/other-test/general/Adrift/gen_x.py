# adrift game

import sys, time, os, json, random
relFold = "../../../../"
sys.path.append(relFold+'module')
import sabr

# ../../../../sabr 1 source.tb

def createPuz(numSide,colorEnds,Xs=[]):

	sabrObj = sabr.SabrObj()

	colors = []
	for (color,arr) in colorEnds:
		colors.append(color)
	colors.append('X')

	sabrObj.setSym(colors)

	overallBoard = []
	for sideName in ['z', 'x', 'y' ]:
		for y in range(0,numSide):
			tempSide = []
			
			for x in range(0,numSide):
				name = sideName + str(y) + str(x)
				tempSide.append(name)
				
			overallBoard.append(tempSide)

	sabrObj.setBoard(overallBoard)

	# req board
	reqBoard = []
	for sideName in ['z', 'x', 'y' ]:
		for y in range(0,numSide):
			tempSide = []
			for x in range(0,numSide):
				name = sideName + str(y) + str(x)
				
				toAdd = '?'
				if name in Xs:
					toAdd = 'X'
					
				for (color,arr) in colorEnds:
					if name in arr:
						toAdd = color
				
				tempSide.append(toAdd)
				
			reqBoard.append(tempSide)

	sabrObj.addReq(None,'Board',reqBoard)

	# opt groups
	optGroups = [
		('link2',[ 'v',  'v',  'v', ]),
		('link3',[ 'v', '!v',  'v',  'v', ]),
		('link3',[ 'v',  'v', '!v',  'v', ]),
		('link3',[ 'v',  'v',  'v', '!v', ]),
		('link4',[ 'v',  'v',  'v', '!v', '!v', ]),
		('link4',[ 'v',  'v', '!v',  'v', '!v', ]),
		('link4',[ 'v',  'v', '!v', '!v',  'v', ]),
		('link4',[ 'v', '!v',  'v',  'v', '!v', ]),
		('link4',[ 'v', '!v',  'v', '!v',  'v', ]),
		('link4',[ 'v', '!v', '!v',  'v',  'v', ]),
		('end2' ,[ 'v',  'v', '!v', ]),
		('end2' ,[ 'v', '!v',  'v', ]),
		('end3' ,[ 'v',  'v', '!v', '!v', ]),
		('end3' ,[ 'v', '!v',  'v', '!v', ]),
		('end3' ,[ 'v', '!v', '!v',  'v', ]),
		('end4' ,[ 'v',  'v', '!v', '!v', '!v', ]),
		('end4' ,[ 'v', '!v',  'v', '!v', '!v', ]),
		('end4' ,[ 'v', '!v', '!v',  'v', '!v', ]),
		('end4' ,[ 'v', '!v', '!v', '!v',  'v', ]),
		('link2',[ 'X',  '?',  '?', ]),
		('link3',[ 'X',  '?',  '?',  '?', ]),
		('link4',[ 'X',  '?',  '?',  '?', '?', ]),
	]
	
	sabrObj.addSpace()
	
	# opt
	for (obj,arr) in optGroups:
		sabrObj.addOpt(None,obj,arr)

	sabrObj.addSpace()
	
	vectorDict = {}
	
	# vectors in squares
	for sideName in ['z', 'x', 'y' ]:
		for y in range(0,numSide):
			for x in range(0,numSide):
				name = sideName + str(y) + str(x)
				vectorDict[name] = []
				
				# left
				if x > 0:
					vectorDict[name].append(sideName + str(y) + str(x-1))
				
				# right
				if x < numSide-1:
					vectorDict[name].append(sideName + str(y) + str(x+1))
					
				# up
				if y > 0:
					vectorDict[name].append(sideName + str(y-1) + str(x))
				
				# down
				if y < numSide-1:
					vectorDict[name].append(sideName + str(y+1) + str(x))
		
	# vectors z-x
	for i in range(0,numSide):
		n1 = 'z' + str(numSide-1) + str(i)
		n2 = 'x0' + str(i)
		
		vectorDict[n1].append(n2)
		vectorDict[n2].append(n1)
	
	# vectors z-y
	for i in range(0,numSide):
		n1 = 'z' + str(numSide-1-i) + str(numSide-1)
		n2 = 'y0' + str(i)
		
		vectorDict[n1].append(n2)
		vectorDict[n2].append(n1)
	
	# vectors x-y
	for i in range(0,numSide):
		n1 = 'x' + str(i) + str(numSide-1)
		n2 = 'y' + str(i) + '0'
		
		vectorDict[n1].append(n2)
		vectorDict[n2].append(n1)
	
	toSort = vectorDict.keys()
	toSort.sort()
	
	for key in toSort:
		
		val = vectorDict[key]
		
		useEnd = False
		for (color,arr) in colorEnds:
			if key in arr:
				useEnd = True
				
		obj = 'link'
		if useEnd:
			obj = 'end'
		obj = obj + str(len(val))
		
		sabrObj.addDesObj(None,obj,[key] + val)
	
	sabrObj.source('source.tb')
	return sabrObj

def randomPoint(sideNum):
	z = ['z','x','y'][random.randint(0,2)]
	x = str(random.randint(0,sideNum-1))
	y = str(random.randint(0,sideNum-1))
	return z+x+y

def makeNewPuz():
	sideNum = 5
	colors = [ 'R','B','G','O','Y' ]
	outJson = []

	for i in range(1000):

		colorEnds = []
		for color in colors:
			colorEnds.append((color,[randomPoint(sideNum),randomPoint(sideNum)]))

		# pass 5 tuples of random (z,y,x)
		sabrObj = createPuz(sideNum,colorEnds)
		sabrObj.process(relFold + 'sabr')

		fi = open('result.txt')
		res = fi.read()
	
		if res != 'UNSATISFIABLE':
	
			faces = ['z','x','y']
			faceNum = 0
			curLineNum = 0
			num = 0
		
			# get Xs
			Xs = []
			solution = []
			for val in res.split():
		
				name = faces[faceNum] + str(curLineNum) + str(num)
				solution.append( { 'color':val, 'side':name[0], 'y':name[1], 'x':name[2] } )
				
				if val == 'X':
					Xs.append(name)
				num += 1

				if num == sideNum:
					num = 0		
					curLineNum += 1
			
					if curLineNum == sideNum:
						curLineNum = 0
						faceNum += 1
		
			if len(Xs) < 10:
		
				sabrObj = createPuz(sideNum,colorEnds,Xs)
				sabrObj.multiProcess(relFold + 'sabr')
				sabrObj.multiProcess(relFold + 'sabr')
		
				fi = open('result.txt')
				secRes = fi.read()
			
				if secRes == 'UNSATISFIABLE':
					print '\n' + res
					print colorEnds
					
					start = []
					for (color,[A,B]) in colorEnds:
						start.append( { 'color':color, 'side':A[0], 'y':A[1], 'x':A[2] } )
						start.append( { 'color':color, 'side':B[0], 'y':B[1], 'x':B[2] } )
					
					for X in Xs:
						start.append( { 'color':'X', 'side':X[0], 'y':X[1], 'x':X[2] } )
					
					outJson.append( { 'start':start, 'solution':solution } )
	
	outFile = open('out.json','w')
	outFile.write(json.dumps(outJson))
	outFile.close()

def genTest(sideNum,colorEnds,Xs=[]):

	# pass 5 tuples of random (z,y,x)
	sabrObj = createPuz(sideNum,colorEnds,Xs)
	sabrObj.multiProcess(relFold + 'sabr')

	fi = open('result.txt')
	res = fi.read()
	print res

	sabrObj.multiProcess(relFold + 'sabr')

	fi = open('result.txt')
	res = fi.read()
	
	if res != 'UNSATISFIABLE':
		print res
	else:
		print 'Only Soultion'

def test1():
	sideNum = 4
	colorEnds = [ 
		('R',[ 'z00', 'x03' ]), 
		('B',[ 'y02', 'x12' ]),  
		('P',[ 'z11', 'y22' ]), 
		('Y',[ 'x20', 'y23' ]), 
		('G',[ 'z30', 'z23' ]), 
	]	
	genTest(sideNum,colorEnds)

def test2():
	sideNum = 5
	colorEnds = [ 
		('O',[ 'z02', 'x12' ]),
		('G',[ 'z11', 'y44' ]),
		('P',[ 'z14', 'x21' ]),
		('B',[ 'z44', 'x40' ]),
		('R',[ 'z31', 'x04' ]),
	]
	Xs = [ 'z23','z41','x01','x11','x24','y20','y21' ]
	genTest(sideNum,colorEnds,Xs)
	
makeNewPuz()