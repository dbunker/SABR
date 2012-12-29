# generate dodecahedron 4 color model, and offer brute force solution
# as opposed to constraint propagation or SAT

#    0       6 7
#  1 2 3    8 9 10
#   4 5       11

import sys, time
sys.path.append("../../../module/")
import sabr

# possible colors
colors = ['yellow','green','blue','red']
colors = ['y','g','b','r']

# sides
sides = [0,1,2,3,4,5,6,7,8,9,10,11]

# connections
conn = {}
conn[2] = [0,3,5,4,1]
conn[0] = [1,2,3,7,6]
conn[3] = [0,2,5,6,8]
conn[5] = [4,2,3,8,11]
conn[4] = [1,2,5,11,10]
conn[1] = [0,2,4,10,7]
conn[9] = [6,7,10,11,8]
conn[6] = [8,9,7,3,0]
conn[7] = [6,9,10,0,1]
conn[10] = [7,9,11,1,4]
conn[11] = [8,9,10,4,5]
conn[8] = [6,9,11,5,3]

def gen():

	sabrObj = sabr.SabrObj()
	sabrObj.setSym(colors)
	sabrObj.setBoard(sides)

	for cell,link in conn.items():
		for linkCell in link:
			sabrObj.addAllDif([cell,linkCell])
		sabrObj.addSpace()
	
	return sabrObj.process('../../../sabr')

def bruteForce():
	
	def isValid(sidesSet,newCol,oldColsInds):
	
		for ind in oldColsInds:
			if newCol == sidesSet[ind]:
				return False
		return True
	
	def setValue(sidesSet,curInd):
	
		if curInd >= len(sides):
			return sidesSet
	
		for col in colors:
		
			if isValid(sidesSet,col,conn[curInd]):
			
				newSidesSet = sidesSet[:]
				newSidesSet[curInd] = col
				res = setValue(newSidesSet,curInd+1)
				
				if res != None:
					return res
		
		return None

	empty = [None] * len(sides)
	return setValue(empty,0)

def checkResult():
	for i in range(len(res)):
		print res[i],
		
		for sideInd in conn[i]:
			print res[sideInd],
			
		print ''

options = [gen,bruteForce]

res = options[0]()
print res
