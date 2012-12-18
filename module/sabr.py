
import os

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
				if isinstance(startArr[0],list):
					out += '=>'
				else:
					out += '=>'
				out += self.outLines(endArr)
			
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
		
			((_,nameTransX,objX,_,startArrX,endArrX),(_,nameDesObjX,_,_,desObjX,_)) = x
			
			for y in transDesObjList:
				
				((_,nameTransY,objY,_,startArrY,endArrY),(_,nameDesObjY,_,_,desObjY,_)) = y
				
				def embedList(arr):
					if isinstance(arr[0],list):
						return arr
					return [arr]
				
				def makeList(arr1,arr2):
				
					arr1 = embedList(arr1)
					arr2 = embedList(arr2)
					return arr1 + arr2
					
				newStartArr = makeList(startArrX,startArrY)
				newEndArr = makeList(endArrX,endArrY)
				newDesObj = makeList(desObjX,desObjY)
				
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
		