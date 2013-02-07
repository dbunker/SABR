
# 12 marbles, 1 light/heavy, 3 weighs

import sys, os, time, copy
sys.path.append("../../../../module/")
import sabr

def gen():

	sabrObj = sabr.SabrObj()
	sabrObj.setSym(['A','B','N'])
	
	sabrObj.addSym('Num',[str(i) for i in range(1,7)])
	
	def getBoard(rName):
		boardVar = []
		for start in ['f','a','b','g','aa','ab','ag','ba','bb','bg','ga','gb','gg']:
			tempVar = [start + rName]
			for i in range(12):
				tempVar.append(start + str(i))
			boardVar.append(tempVar)
		return boardVar
	
	sabrObj.setBoard(getBoard('r:Num'))
	
	# A must match B	
	def setNumInfo(char):
		comb  = []
		for i in range(1,7):
			comb += [ [str(i)] + li for li in sabr.combMany([(char,i),('!'+char,12-i)]) ]
		
		for elem in comb:
			sabrObj.addOpt('SetSame'+char,'Weigh',elem)
		sabrObj.addSpace()
	
	setNumInfo('A')
	setNumInfo('B')
	
	# boardvar for desobj
	boardVar = getBoard('r')
	
	for elem in boardVar:
		sabrObj.addDesObj(None,'Weigh',elem)
	
	sabrObj.addSpace()
	
	# must end with all excluded but 1 of the 24
    # exclude if both light and heavy side
	# exclude if excluded from imbalance
	# exclude if included in balance
	# deduction must at one point be weighed
	
	for set1 in ['A','B','N']:
		for set2 in ['A','B','N']:
			for set3 in ['A','B','N']:
			
				obj = set1+'-'+set2+'-'+set3
				
				# must eliminate all y
				# opt group for single DesObj
				
				# escape if not current one examining
				sabrObj.addOpt(None,obj,['!'+set1,'?','?','?','?','?'])
				sabrObj.addOpt(None,obj,['?','!'+set2,'?','?','?','?'])
				sabrObj.addOpt(None,obj,['?','?','!'+set3,'?','?','?'])
				
				start = [set1,set2,set3]
				
				def same(s1,s2):
					return (s1 == s2 and s1 != 'N' and s2 != 'N')
					
				def diff(s1,s2):
					return (s1 != s2 and s1 != 'N' and s2 != 'N')
				
				# conditional list
				cl = []
				
				# both light and heavy side
				cl.append((same(set1,set2),['val','!val','?']))
				cl.append((same(set1,set3),['val','?','!val']))
				cl.append((same(set2,set3),['?','val','!val']))
				
				cl.append((diff(set1,set2),['val','val','?']))
				cl.append((diff(set1,set3),['val','?','val']))
				cl.append((diff(set2,set3),['?','val','val']))
				
				# excluded from imbalance
				cl.append(((set1 != 'N'),['N','?','?']))
				cl.append(((set2 != 'N'),['?','N','?']))
				cl.append(((set3 != 'N'),['?','?','N']))
				
				# included in balance
				cl.append(((set1 == 'N'),['!N','?','?']))
				cl.append(((set2 == 'N'),['?','!N','?']))
				cl.append(((set3 == 'N'),['?','?','!N']))
				
				# deduction must at one point be weighed
				if start != ['N','N','N']:
					for (cond,toAdd) in cl:
						if cond:
							sabrObj.addOpt(None,obj,start+toAdd)
							
				sabrObj.addSpace()
	
				matchHeavy = { 'A':'a', 'B':'b', 'N':'g' }
				matchLight = { 'A':'b', 'B':'a', 'N':'g' }
				
				for xNum in range(12):
					for yNum in range(12):
						if xNum != yNum:
							
							x = str(xNum)
							y = str(yNum)
							
							for prop in ['heavy','light']:
							
								# 24 possibilites, can be placed anywhere
								
								match = matchLight
								if prop == 'heavy':
									match = matchHeavy
								
								sn1 = 'f'
								sn2 = match[set1]
								sn3 = match[set1] + match[set2]
								
								# ex. f0 a0 aa0 fX aX aaX
								desObjLi = [sn1+y,sn2+y,sn3+y,sn1+x,sn2+x,sn3+x]
								
								sabrObj.addDesObj(None,obj,desObjLi)
					
					sabrObj.addSpace()
				
	sabrObj.source('out.tb')
	os.system('../../../../sabr 1 out.tb')

# process result.txt
def output():
	
	matchHeavy = { 'A':'a', 'B':'b', 'N':'g' }
	matchLight = { 'A':'b', 'B':'a', 'N':'g' }
	
	res = open('result.txt','r')
	
	dict = {}
	dict[''] = res.readline().split()[1:]
	
	for v1 in ['a','b','g']:
		
		line = res.readline().split()[1:]
		dict[v1] = line
	
	infoMatch = {'a':'A heavy','b':'B heavy','g':'balanced'}
	
	def getWeigh(li):
		ret = ''
		for n in range(len(li)):
			ret += str(n) + ':' + li[n] + ' '
		return 'Weigh: ' + ret + '\n'
		
	print '\n' + getWeigh(dict[''])
	for v1 in ['a','b','g']:
		print 'If ' + infoMatch[v1] + ', ' + getWeigh(dict[v1])
	
		for v2 in ['a','b','g']:

			line = res.readline().split()[1:]
			dict[v1+v2] = line
			
			print '\tIf ' +infoMatch[v2] + ', ' + getWeigh(dict[v1+v2])
			
			for n in range(12):
			
				set1 = dict[''][n]
				set2 = dict[v1][n]
				set3 = dict[v1+v2][n]
				
				# exactly one is N or always light/heavy
				
				def addDict(match,name):
					if match[set1] == v1 and match[set2] == v2:
						dict[v1+v2+match[set3]] = (str(n),name)
				
				addDict(matchHeavy,'heavy')
				addDict(matchLight,'light')
				
			for v3 in ['a','b','g']:
				if v1+v2+v3 in dict:
					print '\t\tIf ' + infoMatch[v3] + ', ' + dict[v1+v2+v3][0] + ' is ' + dict[v1+v2+v3][1]
			print ''

output()


