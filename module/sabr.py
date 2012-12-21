
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
				if instanceof(stages,int):
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
				
				exit()
		
	def unrollTrans(self,trans1,trans2):
	
		((_,nameTransX,objX,_,startArrX,endArrX),(_,nameDesObjX,_,_,desObjX,_)) = trans1
		((_,nameTransY,objY,_,startArrY,endArrY),(_,nameDesObjY,_,_,desObjY,_)) = trans2
	
		####################
		
		# T1) v1 v2 => v2 v1
		# a b;

		# T2) w1 w2 => w2 w1
		# b c;
		
		# T1) a0:(v1) b0:(v2) => a1:(v2) b1:(v1)

		# T2) b1:(w1) c1:(w2) => b2:(w2) c2:(w1)
		
		t1_StartS = {0:'v1', 1:'v2'}
		t1_EndS = {0:'v2', 1:'v1'}
		t1_DesObjS = {0:'a', 1:'b'}
		
		t2_StartS = {0:'w1', 1:'w2'}
		t2_EndS = {0:'w2', 1:'w1'}
		t2_DesObjS = {0:'b', 1:'c'}
		
		####################
		
		t1_Start = {}
		t1_End = {}
		
		t2_Start = {}
		t2_End = {}
		
		# set T1-0
		for k,v in t1_DesObjS.items():
			t1_Start[k] = ((v,0),t1_StartS[k])
		
		# set T1-1
		for k,v in t1_DesObjS.items():
			t1_End[k] = ((v,1),t1_EndS[k])
		
		# set T2-1
		for k,v in t2_DesObjS.items():
			t2_Start[k] = ((v,1),t2_StartS[k])
		
		# set T2-2
		for k,v in t2_DesObjS.items():
			t2_End[k] = ((v,2),t2_EndS[k])
		
		allT1 = copy.deepcopy([t1_Start, t1_End])
		allT2 = copy.deepcopy([t2_Start, t2_End])
		
		####################
		
		def replace(all,x,y):
			for li in all:
				for k,(cell,var) in li.items():
					if var == x:
						li[k] = (cell,y)
			
		# match T1_End to T2_Start
		# note, symbol can't be bound to var
		
		numCellOverlaps = 0
		
		for k1,(cell1,var1) in t1_End.items():
				
			for k2,(cell2,var2) in t2_Start.items():
				
				if cell1 == cell2:
					numCellOverlaps += 1
					
					# confirm these are compatible
					if var1 in self.sym:
					
						if var2 in self.sym:
						
							if var1 != var2:
								print 'Cannot Unroll Due To Conflict'
								return
							else:
								continue
					
					# replace all var1 with var1-var2
					replace(allT1,var1,var1+'-'+var2)
					
					# replace all var2 with var1-var2
					replace(allT2,var2,var1+'-'+var2)
		
		if numCellOverlaps == 0:
			print 'Use TransSim Instead of Unroll'
			return
		
		####################
		# apply first based on what appears first
		# apply last based on what appears last
		
		t_Start = []
		t_End = []
		des = []
		
		# go through desobj
		firstDict = {}
		for k,v in t1_DesObjS.items():
			((name,stage),var) = allT1[0][k]
			t_Start.append(var)
			des.append(name)
			firstDict[name] = True
		
		for k,v in t2_DesObjS.items():
			((name,stage),var) = allT2[0][k]
			if not name in firstDict:
				t_Start.append(var)
				des.append(name)
		
		searchDes = copy.deepcopy(des)
		for desName in searchDes:
			
			def findIn(allList,found,desName):
			
				for k,((name,stage),var) in allList.items():
					if name == desName:
						if found == False:
							found = ((name,stage),var)
							t_End.append(var)
						elif found[0][1] == stage:
						
							# must add for additional constraint
							des.append(name)
							t_Start.append('?')
							t_End.append(var)
							
				return found
						
			found = False
			
			# try to find in last
			found = findIn(allT2[1],found,desName)
			
			# find in second to last
			found = findIn(allT1[1],found,desName)
			
		print t_Start
		print t_End
		print des
		
		####################
		
		exit()
		
		# names
		newObjId = objX + '-' + objY
		newTransId = nameTransX + '-' + nameTransY
		newDesObjId = nameDesObjX + '-' + nameDesObjY
		
		self.addTrans(newTransId,newObjId,newStartArr,newEndArr)
		self.addDesObj(newDesObjId,newObjId,newDesObj)
		self.addSpace()
				
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
		