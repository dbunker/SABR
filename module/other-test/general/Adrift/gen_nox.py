# adrift game
# gen_nox can quiken the search for a puzzle without an X by having
# sabr decide where the start and end points of each strand is
# still may have cycles

import sys, time, os, random
relFold = "../../../../"
sys.path.append(relFold+'module')
import sabr

# ../../../../sabr 1 source.tb

def createPuz(numSide,oldColors,declareEnds=[],Xs=[],restrict=False):

	sabrObj = sabr.SabrObj()

	colors = oldColors[:]
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

	for sideName in ['z', 'x', 'y' ]:
		for y in range(0,numSide):
			tempSide = []
			
			for x in range(0,numSide):
				name = 'e' + sideName + str(y) + str(x)
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
				toAdd = '!X'
				if name in Xs:
					toAdd = 'X'
				tempSide.append(toAdd)
			reqBoard.append(tempSide)
	
	for sideName in ['z', 'x', 'y' ]:
		for y in range(0,numSide):
			tempSide = []
			for x in range(0,numSide):
				name = sideName + str(y) + str(x)
				toAdd = '?'
				if name in Xs:
					toAdd = 'X'
					
				for (col,arr) in declareEnds:
					if name in arr:
						toAdd = col
				
				tempSide.append(toAdd)
			reqBoard.append(tempSide)

	sabrObj.addReq(None,'Board',reqBoard)

	# to force exactly two of each end, does not prevent cycles
	if restrict:
		for col in oldColors:
			li = sabr.combMany([(col,2),('!'+col,3*numSide*numSide-2)])
			for arr in li:
				sabrObj.addOpt('end-'+col,'end',arr)
		
		desEnd = []
		for sideName in ['z', 'x', 'y' ]:
			for y in range(0,numSide):
				for x in range(0,numSide):
					name = 'e' + sideName + str(y) + str(x)
					desEnd.append(name)
	
		sabrObj.addDesObj(None,'end',desEnd)
	
	# opt groups
	optGroups = [
		('link2',[ 'X', 'v',  'v',  'v', ]),
		('link3',[ 'X', 'v', '!v',  'v',  'v', ]),
		('link3',[ 'X', 'v',  'v', '!v',  'v', ]),
		('link3',[ 'X', 'v',  'v',  'v', '!v', ]),
		('link4',[ 'X', 'v',  'v',  'v', '!v', '!v', ]),
		('link4',[ 'X', 'v',  'v', '!v',  'v', '!v', ]),
		('link4',[ 'X', 'v',  'v', '!v', '!v',  'v', ]),
		('link4',[ 'X', 'v', '!v',  'v',  'v', '!v', ]),
		('link4',[ 'X', 'v', '!v',  'v', '!v',  'v', ]),
		('link4',[ 'X', 'v', '!v', '!v',  'v',  'v', ]),
		
		('link2',[ 'v', 'v',  'v', '!v', ]),
		('link2',[ 'v', 'v', '!v',  'v', ]),
		('link3',[ 'v', 'v',  'v', '!v', '!v', ]),
		('link3',[ 'v', 'v', '!v',  'v', '!v', ]),
		('link3',[ 'v', 'v', '!v', '!v',  'v', ]),
		('link4',[ 'v', 'v',  'v', '!v', '!v', '!v', ]),
		('link4',[ 'v', 'v', '!v',  'v', '!v', '!v', ]),
		('link4',[ 'v', 'v', '!v', '!v',  'v', '!v', ]),
		('link4',[ 'v', 'v', '!v', '!v', '!v',  'v', ]),
		
		('link2',[ 'X', 'X',  '?',  '?', ]),
		('link3',[ 'X', 'X',  '?',  '?',  '?', ]),
		('link4',[ 'X', 'X',  '?',  '?',  '?', '?', ]),
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
				
		obj = 'link'
		obj = obj + str(len(val))
		
		sabrObj.addDesObj(None,obj,['e'+key] + [key] + val)
	
	sabrObj.source('source.tb')
	return sabrObj
	
def randomPoint(sideNum):
	z = ['z','x','y'][random.randint(0,2)]
	x = str(random.randint(0,sideNum-1))
	y = str(random.randint(0,sideNum-1))
	return z+x+y

def simpleTest():

	sideNum = 5
	colors = [ 'R','B','G','O','Y' ][:sideNum]

	mainSabrObj = createPuz(sideNum,colors)
	doPrint = True
	
	for i in range(3):
		mainSabrObj.multiProcess(relFold + 'sabr')
		fi = open('result.txt')
		res = fi.read()
		os.system('rm debug.txt stats.txt cnf.txt vars.txt result.txt 2> /dev/null')
	
		print str(i) + ' Done'
		if doPrint:
			print res

def makePuz():

	sideNum = 5
	colors = [ 'R','B','G','O','Y' ][:sideNum]

	mainSabrObj = createPuz(sideNum,colors)
	
	# find right one
	for i in range(100):
		
		mainSabrObj.multiProcess(relFold + 'sabr')
		
		fi = open('result.txt')
		res = fi.read()
		
		if res != 'UNSATISFIABLE':
		
			endsDict = {}
			nextSect = 0
			faces = ['z','x','y']
			faceNum = 0
			curLineNum = 0
			num = 0
			
			# find start/end
			for val in res.split():
			
				if nextSect == 1:
					name = faces[faceNum] + str(curLineNum) + str(num)
					
					if not val in endsDict:
						endsDict[val] = []
					endsDict[val].append(name)
				
				num += 1
				if num == sideNum:
					num = 0
					curLineNum += 1
			
					if curLineNum == sideNum:
						curLineNum = 0
						faceNum += 1
						
						if faceNum == 3:
							faceNum = 0
							nextSect += 1
			
			declareEnds = endsDict.items()
			
			# assume these start/end, make sure no other way to make it
			tempSabrObj = createPuz(sideNum,colors,declareEnds)
			tempSabrObj.multiProcess(relFold + 'sabr')
			
			# test that it is only solution
			tempSabrObj.multiProcess(relFold + 'sabr')
			
			fi = open('result.txt')
			secondRes = fi.read()
			
			if secondRes == 'UNSATISFIABLE':
				print res
			else:
				print 'Many Solutions'
		
		else:
			print 'Not Possible'

makePuz()

