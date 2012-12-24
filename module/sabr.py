
import os, copy

class SabrObj:
	
	def __init__(self):
		self.sym = []
		self.board = []
		self.start = []
		self.end = []
		
		# AllDif, Req, Opt, Trans, TransSim, DesObj
		self.constraints = []
    	
    # [<symbols>]
	def setSym(self,arr):
		self.sym = arr
	
	# [<board array>]
	def setBoard(self,arr):
		self.board = arr
	
	# [<start req var>]
	def setStart(self,arr):
		self.start = arr
	
	# [<end req var>]
	def setEnd(self,arr):
		self.end = arr
	
	# all constraints are: 
	# ('<type>','<name>','<obj>',(stagesStart,stagesEnd),[<start array>],[end array])
	
	def addAllDif(self,arr,stages=None):
		self.constraints.append(('AllDif',None,None,stages,arr,None))
	
	def addReq(self,name,obj,arr,stages=None):
		self.constraints.append(('Req',name,obj,stages,arr,None))
	
	def addOpt(self,name,obj,arr,stages=None):
		self.constraints.append(('Opt',name,obj,stages,arr,None))
	
	def addTrans(self,name,obj,arrStart,arrEnd,stages=None):
		self.constraints.append(('Trans',name,obj,stages,arrStart,arrEnd))
	
	def addTransSim(self,name,obj,arrStart,arrEnd,stages=None):
		self.constraints.append(('TransSim',name,obj,stages,arrStart,arrEnd))
	
	def addDesObj(self,name,obj,arr):
		self.constraints.append(('DesObj',name,obj,None,arr,None))
		
	def addSpace(self):
		self.constraints.append(None)
	
	def outLines(self,arr):
		
		out = ''
		
		if isinstance(arr[0],list):
			for line in arr:
				out += '\n\t'
				for var in line:
					out += var + ' '
				out = out[:-1] + ';'
			out += '\n'
			
		else:
			out += ' '
			for var in arr:
				out += var + ' '	
			out = out[:-1] + ' '
			
		return out
		
	def singleWrap(self,name,arr):
	
		return name + ' {' + self.outLines(arr) + '}\n\n'
	
	def toString(self):
		
		# sym
		out = self.singleWrap('Sym',self.sym)
		
		# board
		out +=  self.singleWrap('Board',self.board)
		
		# start, end
		if self.start != [] and self.end != []:
			out += self.singleWrap('Start',self.start)
			out += self.singleWrap('End',self.end)
			
		# constraints: AllDif, Req, Opt, Trans, TransSim, DesObj
		for const in self.constraints:
			
			if const == None:
				out += '\n'
				continue
			
			(type,name,obj,stages,startArr,endArr) = const
			out += type + ' '
			
			if name != None and name != '':
				out += name + ':'
			
			if obj != None and obj != '':
				out += obj
			else:
				out = out[:-1]
			
			if stages != None and stages != ():
				if isinstance(stages,int):
					out += '(' + str(stages) + ')'
				else:
					(startStage,endStage) = stages
					out += '(' + str(startStage) + ':' + str(endStage) + ')'
			
			out += ' {'
			out += self.outLines(startArr)
			
			if type == 'Trans' or type == 'TransSim':
				out += '=>' + self.outLines(endArr)
			
			out += '}\n'
		
		return out
	
	def unroll(self):
		
		self.addSpace()
		
		# we take a cross of all trans-desobj
		# (trans,desobj)
		transDesObjList = []
		
		for constTrans in self.constraints:
			if constTrans == None:
				continue
			
			(type,name,objTrans,stages,startArr,endArr) = constTrans
			
			if type != 'Trans' and type != 'TransSim':
				continue
			
			for constDesObj in self.constraints:
				if constDesObj == None:
					continue
				
				(type,name,objDesObj,stages,startArr,endArr) = constDesObj
				
				if type != 'DesObj':
					continue
				
				if objTrans == objDesObj:
					transDesObjList.append((constTrans,constDesObj))
	
		for x in transDesObjList:
			
			for y in transDesObjList:
		
				self.unrollTrans(x,y)

	def unrollTrans(self,trans1,trans2):
	
		((_,nameTransX,objX,_,startArrX,endArrX),(_,nameDesObjX,_,_,desObjX,_)) = trans1
		((_,nameTransY,objY,_,startArrY,endArrY),(_,nameDesObjY,_,_,desObjY,_)) = trans2
	
		####################
		
		# <place> : ([<name> list of all names it has],
		#				[[(varName,isNeg,isSym) OR ...] AND ...]) 
		
		# convert to dict
		# turn the string 'v1:(!0,v2)' to 
		# (set(['v1']),set([set([('0',True,True),('v2',False,False)])]))
		
		# consolidate duplicate cells
		# regardless of placement, unrolling puts all on single line, original order
		
		# if a cell does not have a name, it is given the name of its cell *<cell>*<stage>*
		# the * cannot normally appear in valid programs, these are removed at end
		
		# example:
		# T1) a0:(v1) b0:(v2) => a1:(v2) b1:(v1)
		# T2) b1:(w1) c1:(w2) => b2:(w2) c2:(w1)
		
		# T1)	a0:(v1-w1)	b0:(v2) => 
		# 		a1:(v2)		b1:(v1-w1) 
		
		# T2) 	b1:(v1-w1)	c1:(w2) => 
		# 		b2:(w2)		c2:(v1-w1)
		
		# a0:(v1-w1) 	b0:(v2) => 
		# a1:(v2) 		b1:(v1-w1) 		c1:(w2) => 
		# 				b2:(w2) 		c2:(v1-w1)
		
		# a			b		c
		# v1-w1		v2		w2
		# v2		w2		v1-w1
		
		# t1_StartS = {		(0,0):(set([('v1',1)]),set([])),	(0,1):(set([('v2',1)]),set([]))}
		# t1_EndS = {		(0,0):(set([('v2',1)]),set([])),	(0,1):(set([('v1',1)]),set([]))}
		# t1_DesObjS = {	(0,0):'a',							(0,1):'b'}
		
		# t2_StartS = {		(0,0):(set([('w1',2)]),set([])),	(0,1):(set([('w2',2)]),set([]))}
		# t2_EndS = {		(0,0):(set([('w2',2)]),set([])),	(0,1):(set([('w1',2)]),set([]))}
		# t2_DesObjS = {	(0,0):'b', 							(0,1):'c'}
		
		def remake(startS,endS,desObjS,tVal):
		
			def flatten(arr):
				return [elem for li in arr for elem in li]
			
			startS = flatten(startS)
			endS = flatten(endS)
			desObjS = flatten(desObjS)
			
			startSRet = {}
			for i in range(len(startS)):
				v = startS[i]
				startSRet[(0,i)] = (set([(v,tVal)]),set([]))
				
			endSRet = {}
			for i in range(len(endS)):
				v = endS[i]
				endSRet[(0,i)] = (set([(v,tVal)]),set([]))
			
			desObjSRet = {}
			for i in range(len(desObjS)):
				v = desObjS[i]
				desObjSRet[(0,i)] = v
			
			return (startSRet,endSRet,desObjSRet)
		
		(t1_StartS,t1_EndS,t1_DesObjS) = remake(startArrX,endArrX,desObjX,1)
		(t2_StartS,t2_EndS,t2_DesObjS) = remake(startArrY,endArrY,desObjY,2)
		
		####################
		# produce:
		# (cellName,stage) : (<name or None>,[[(varName,isNeg,isSym) OR ...] AND ...])
		
		t1_Start = {}
		t1_End = {}
		
		t2_Start = {}
		t2_End = {}
		
		# set T1-0
		for k,v in t1_DesObjS.items():
			t1_Start[(v,0)] = t1_StartS[k]
		
		# set T1-1
		for k,v in t1_DesObjS.items():
			t1_End[(v,1)] = t1_EndS[k]
		
		# set T2-1
		for k,v in t2_DesObjS.items():
			t2_Start[(v,1)] = t2_StartS[k]
		
		# set T2-2
		for k,v in t2_DesObjS.items():
			t2_End[(v,2)] = t2_EndS[k]
		
		allT = copy.deepcopy([t1_Start, t1_End, t2_Start, t2_End])
		
		####################
		# match T1_End to T2_Start
		# note, symbol can't be bound to var
		
		def addTo(all,varNameFind,varNameAdd,varListAdd):
		
			for li in all:
				for cell,(varNames,varList) in li.items():
				
					# add varName, and items that get AND added
					if len(varNameFind & varNames) > 0:
						varNames |= varNameAdd
						varList |= varListAdd
						
					for orList in varList:
						for elem in orList:
							(storeVarNames,isNeg,isSym) = elem
							if len(varNameFind & storeVarNames) > 0:
								storeVarNames |= varNameAdd
								
		numCellOverlaps = 0
		
		# stage1 and stage2 will both be 1
		for (cell1,stage1),(varName1,varList1) in t1_End.items():
				
			for (cell2,stage2),(varName2,varList2) in t2_Start.items():
				
				if cell1 == cell2:
					numCellOverlaps += 1
					
					# replace all var1 with var1,var2
					addTo(allT,varName1,varName2,varList2)
					
					# replace all var2 with var1,var2
					addTo(allT,varName2,varName1,varList2)
		
		# these cells don't overlap
		# Use TransSim Instead of Unroll
		if numCellOverlaps == 0:
			return
		
		####################
		# apply first based on what appears first
		# apply last based on what appears last
		
		allDict = {}
		for t in allT:
			for k,v in t.items():
				allDict[k] = v
		
		desObjOrder = []
		des = sorted(t1_DesObjS.items()) + sorted(t2_DesObjS.items())
		for k,v in des:
			if not v in desObjOrder:
				desObjOrder.append(v)
		
		t_Start = []
		t_End = []
		
		def toStr(var):
			
			(varNames,varList) = var
			ret = ''
			for name in varNames:
				(v,tv) = name
				ret += v + '_' + str(tv) + '-'
			return ret[:-1]
		
		for elem in desObjOrder:
			if (elem,0) in allDict:
				t_Start.append(toStr(allDict[(elem,0)]))
			elif (elem,1) in allDict:
				t_Start.append(toStr(allDict[(elem,1)]))
			else:
				print 'Failed'
				exit()
				
		for elem in desObjOrder:
			if (elem,2) in allDict:
				t_End.append(toStr(allDict[(elem,2)]))
			elif (elem,1) in allDict:
				t_End.append(toStr(allDict[(elem,1)]))
			else:
				print 'Failed'
				exit()
		
		####################
		
		# names
		newTransId = nameTransX + '-' + nameTransY
		newDesObjId = nameDesObjX + '-' + nameDesObjY
		newObjId = newTransId + '-' + newDesObjId + '-' + objX + '-' + objY
		
		self.addTrans(newTransId,newObjId,t_Start,t_End)
		self.addDesObj(newDesObjId,newObjId,desObjOrder)
		self.addSpace()
		
	def readFromFile(self,fileName):
		
		# read from file
		progFi = open(fileName,'r')
		prog = progFi.read()
		
		# return (type,name,obj,arr1,arr2,remainingStr)
		def getInfo(remStr):
			
			type = remStr.split(None,1)[0].replace('{','')
			
			stages = None
			stagesArr = remStr.split('{',1)[0].split('(',1)
			if len(stagesArr) > 1:
				stagesArr = stagesArr[1].split(')',1)
				stagesArr = stagesArr[0].split(':')
				
				if len(stagesArr) > 1:
					stages = (int(stagesArr[0]),int(stagesArr[1]))
				else:
					stages = (int(stagesArr[0]),int(stagesArr[0]))
			
			nameArr = remStr.split('{',1)[0].split(None,1)
			
			name = None
			obj = None
			
			arr1 = None
			arr2 = None
			
			# has name or obj
			if len(nameArr) > 1:
				
				nameSplit = nameArr[1].split(':',1)
				obj = nameSplit[0].strip()
				
				if len(nameSplit) > 1:
					
					name = nameSplit[0].strip()
					obj = nameSplit[1].strip()
			
			arrSplit = remStr.split('{',1)[1].split('}',1)[0]
			
			transSplit = arrSplit.split('=>',1)
			
			def procArr(arrStr):
				
				arr = arrStr.split(';')
				
				ret = []
				for li in arr:
				
					liSplit = li.split()
					if len(liSplit) > 0:
						ret.append(liSplit)
				
				if len(ret) == 1:
					ret = ret[0]
				
				return ret
				
			arr1 = procArr(transSplit[0])
			
			if len(transSplit) > 1:
				arr2 = procArr(transSplit[1])
			
			rem = remStr.split('}',1)
			rem = rem[1]
			
			return 	(type,name,obj,arr1,arr2,stages,rem)
		
		# split file
		rem = prog
		
		# Sym Board Start End AllDif Req Opt Trans TransSim DesObj
		while(rem.strip() != ''):
			
			(type,name,obj,arr1,arr2,stages,rem) = getInfo(rem)
			
			if type == 'Sym':
				self.setSym(arr1)
		
			elif type == 'Board':
				self.setBoard(arr1)
	
			elif type == 'Start':
				self.setStart(arr1)
		
			elif type == 'End':
				self.setEnd(arr1)
		
			else:
			
				if type == 'AllDif':
					self.addAllDif(arr1,stages)
				
				elif type == 'Req':
					self.addReq(name,obj,arr1,stages)
				
				elif type == 'Opt':
					self.addOpt(name,obj,arr1,stages)
				
				elif type == 'Trans':
					self.addTrans(name,obj,arr1,arr2,stages)
				
				elif type == 'TransSim':
					self.addTransSim(name,obj,arr1,arr2,stages)
					
				elif type == 'DesObj':
					self.addDesObj(name,obj,arr1)
				
				self.addSpace()
				
	def removeUseless(self):
		
		def flatten(arr):
			return [elem for li in arr for elem in li]
			
		transList = [ const for const in self.constraints 
			if const != None and (const[0] == 'Trans' or const[0] == 'TransSim') ]
			
		# remove transitions that don't create change 
		constraints = copy.copy(transList)
		for const in constraints:
			(type,name,obj,stages,startArr,endArr) = const
			
			startArr = flatten(startArr)
			endArr = flatten(endArr)
			
			unchanged = True
			for i in range(len(startArr)):
				if startArr[i] != endArr[i]:
					unchanged = False
					break
			
			if unchanged and const in self.constraints:
				self.constraints.remove(const)
		
		# remove redundant transitions, values may not have exact same names
		constraints = copy.copy(transList)
		for i in range(0,len(constraints)):
			compConst = constraints[i]
			(compType,compName,compObj,compStages,compStartArr,compEndArr) = compConst
				
			compFullArr = flatten(compStartArr) + flatten(compEndArr)
			
			for n in range(i+1,len(constraints)):
				curConst = constraints[n]
				(curType,curName,curObj,curStages,curStartArr,curEndArr) = curConst
	
				curFullArr = flatten(curStartArr) + flatten(curEndArr)
				
				if len(compFullArr) != len(curFullArr):
					continue
				
				# check indexes compFullArr matches indexes curFullArr 
				isDup = True
				for k in range(len(compFullArr)):
						
					# all indexes where arr is v
					def getIndexes(v,arr):
						return [ x for x in range(len(arr)) if arr[v] == arr[x] ]
					
					compIndexes = getIndexes(k,compFullArr)
					curIndexes = getIndexes(k,curFullArr)
					
					if compIndexes != curIndexes:
						isDup = False
						break
				
				if isDup:
					
					if curConst in self.constraints:
						self.constraints.remove(curConst)
					
					# reset all des-obj to this
					for constInd in range(len(self.constraints)):
						
						if self.constraints[constInd] == None:
							continue
						
						(type,name,obj,stages,startArr,endArr) = self.constraints[constInd]
						
						if type == 'DesObj' and obj == curObj:
							self.constraints[constInd] = (type,name,compObj,stages,startArr,endArr)
	
		def isGenConst(type):
			return (type == 'Req' or type == 'Opt' or type == 'Trans' or type == 'TransSim')
		
		def isDesObj(type):
			return (type == 'DesObj')
		
		# remove any redundant sets (ex. DesObj)
		constraints = copy.copy(self.constraints)
		for i in range(0,len(constraints)):
			const1 = constraints[i]
			if const1 == None:
				continue
			
			(type1,name1,obj1,stages1,startArr1,endArr1) = const1
			check1 = (type1,None,obj1,stages1,startArr1,endArr1)
			
			for n in range(i+1,len(constraints)):
				const2 = constraints[n]
				if const2 == None:
					continue
				
				(type2,name2,obj2,stages2,startArr2,endArr2) = const2
				check2 = (type2,None,obj2,stages2,startArr2,endArr2)
						
				if check1 == check2 and const2 in self.constraints:
					self.constraints.remove(const2)
		
		# remove desobj without constraint and constraint without desobj		
		constraints = copy.copy(self.constraints)
		for i in range(0,len(constraints)):
			const1 = constraints[i]
			if const1 == None:
				continue
			
			(type1,name1,obj1,stages1,startArr1,endArr1) = const1
			check1 = (type1,None,obj1,stages1,startArr1,endArr1)
			
			desObjMatch = False
			genConstMatch = False
			
			for n in range(0,len(constraints)):
				const2 = constraints[n]
				if const2 == None:
					continue
				
				(type2,name2,obj2,stages2,startArr2,endArr2) = const2
				check2 = (type2,None,obj2,stages2,startArr2,endArr2)
				
				if obj1 == obj2:
					
					if isGenConst(type2):
						genConstMatch = True
						
					if isDesObj(type2):
						desObjMatch = True

			if ((isDesObj(type1) and not genConstMatch) or 
				(isGenConst(type1) and not desObjMatch)) and (const1 in self.constraints):
				
				self.constraints.remove(const1)

	def source(self,fileName):
	
		out = self.toString()
		sourceFile = open(fileName,'w')
		sourceFile.write(out)
		sourceFile.close()
		
	def cnf(self,sabrPath):
	
		self.source('source.tb')
	
		cmd = sabrPath + ' --cnf 1 source.tb > stats.txt'
		os.system(cmd)
	
	# source.tb
	def process(self,sabrPath):
	
		self.source('source.tb')
		
		cmd = sabrPath + ' 1 source.tb > stats.txt'
		os.system(cmd)
		
		resultFile = open('result.txt','r')
		res = resultFile.read()
		resultFile.close()
		
		return res
		