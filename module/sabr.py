
import os

class SabrObj:
	
	def __init__(self):
		self.sym = []
		self.board = []
		self.reqList = []
		self.desObjList = []
		self.allDifList = []
    	
	def setSym(self,arr):
		self.sym = arr;
		
	def setBoard(self,arr):
		self.board = arr;
		
	def addReqGroup(self,name,arr):
		self.reqList.append((name,arr))
		
	def addDesObjGroup(self,name,arr):
		self.desObjList.append((name,arr))
		
	def addAllDifGroup(self,arr):
		self.allDifList.append((None,arr))
		
	def outElem(self,arr):
		
		out = '{'
		if isinstance(arr[0],list):
			out += '\n\t'
			for line in arr:
				for elem in line:
					out += elem + ' '
				out = out[:-1] + ';\n\t'
			out = out[:-1]
			
		else:
			for elem in arr:
				out += ' ' + elem 
			out += ' '
		
		out += '}\n'	
		return out
	
	def outArray(self,type,arr):
		out = ''
		for (name,constList) in arr:
			for const in constList:
				out += type 
				if name != None:
					out += ' ' + name
				out += self.outElem(const)
			out += '\n'
		return out
	
	def toString(self):
		
		# sym
		out = 'Sym' + self.outElem(self.sym) + '\n'
		
		# board
		out += 'Board' + self.outElem(self.board) + '\n'
		
		# req
		out += self.outArray('Req',self.reqList)
		
		# desobj
		out += self.outArray('DesObj',self.desObjList)
		
		# alldif
		out += self.outArray('AllDif',self.allDifList)
		
		return out
		
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
		