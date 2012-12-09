
import os

class SabrObj:
	
	def __init__(self):
		self.sym = []
		self.board = []
		self.reqList = []
		self.desObjList = []
    	
	def setSym(self,arr):
		self.sym = arr;
		
	def setBoard(self,arr):
		self.board = arr;
		
	def addReqGroup(self,name,arr):
		self.reqList.append((name,arr))
		
	def addAllDif(self,name,num):
		arr = [[' v' if x == y else '!v' for y in range(0,num)] for x in range(0,num)]
		self.addReqGroup(name,arr)
	
	def addDesObjGroup(self,name,arr):
		self.desObjList.append((name,arr))
	
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
				out += type + ' ' + name
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
		
		return out
	
	# source.tb
	def process(self,sabrPath):
	
		out = self.toString()
		sourceFile = open('source.tb','w')
		sourceFile.write(out)
		sourceFile.close()
		
		cmd = sabrPath + ' 1 source.tb > stats.txt'
		os.system(cmd)
		
		resultFile = open('result.txt','r')
		res = resultFile.read()
		resultFile.close()
		
		return res
		