# adrift game

import sys, time, os, random
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
	
# R = ('R',[ 'z00', 'y22' ])
# B = ('B',[ 'z20', 'x20' ])
# colorEnds = [ R, B ]
# Xs = [ 'z01', 'z02', 'x00', 'x01', 'x10', 'x11', 'y00', 'y10', 'y20', 'y02', 'y12' ]

def randomPoint(sideNum):
	z = ['z','x','y'][random.randint(0,2)]
	x = str(random.randint(0,sideNum-1))
	y = str(random.randint(0,sideNum-1))
	return z+x+y

sideNum = 5
colors = [ 'R','B','G','O','Y' ]

for i in range(0,10000):

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
		for val in res.split():
		
			name = faces[faceNum] + str(curLineNum) + str(num)
			
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
				print res
				print secRes
				print ''
			
			