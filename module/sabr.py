
class SabrObj:
	
	def __init__(self):
		self.sym = []
		self.board = []
		self.req = []
		self.desobj = []
    	
	def setSym(self,arr):
		self.sym = arr;
		
	def setBoard(self,arr):
		self.board = arr;
		
	def addReq(self,arr):
		self.req = arr;
		
	def addAllDif(self,arr):
		self.sym = arr;
		
	def addDesObj(self,arr):
		self.sym = arr;
		
	def process(self):
		print 'Start'
