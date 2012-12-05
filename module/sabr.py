
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
		
	def addReq(self,name,arr):
		self.reqList.append((name,arr))
	
	def addAllDif(self,name,num):
		
		for y in range(0,num):
			req = []
			for x in range(0,num):
				val = '!v'
				if x == y:
					val = ' v'
				req.append(val)
			
			self.addReq(name,req)
	
	def addDesObj(self,name,arr):
		self.desObjList.append((name,arr))
		
	def addReqSpace(self):
		self.reqList.append((None,None))

	def addDesObjSpace(self):
		self.desObjList.append((None,None))
	
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
		for (name,req) in arr:
			if name == None:
				out += '\n'
			else:
				out += type + ' ' + name
				out += self.outElem(req)
		return out
	
	def toString(self):
		
		# sym
		out = 'Sym' + self.outElem(self.sym) + '\n'
		
		# board
		out += 'Board' + self.outElem(self.board) + '\n'
		
		# req
		out += self.outArray('Req',self.reqList) + '\n'
		
		# desobj
		out += self.outArray('DesObj',self.desObjList) + '\n'
		
		return out
	
	# source.tb
	def process(self,sabrPath):
	
		out = self.toString()
		sourceFile = open('source.tb','w')
		sourceFile.write(out)
		sourceFile.close()
		
		os.system(sabrPath + ' 1 source.tb > stats.txt')
		
		resultFile = open('result.txt','r')
		res = resultFile.read()
		resultFile.close()
		
		statsFile = open('stats.txt','r')
		stat = statsFile.read()
		statsFile.close()
		
		return (res,stat)
		