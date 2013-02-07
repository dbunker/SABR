# shell game
# show it is possible to get multiple solutions

import sys, os, time, random, math
relFold = "../../../"
sys.path.append(relFold+'module')
import sabr

def sabrMulti():
	
	sabrObj = sabr.SabrObj()
	
	# sym
	sabrObj.setSym(['0','1','2'])
	
	# board
	sabrObj.setBoard([['a','b'],['c']])
	
	# start
	sabrObj.setStart([['2','0'],['0']])
	
	# end
	sabrObj.setEnd([['0','0'],['2']])
	
	# trans
	sabrObj.addTransSim('T1','O1',['v1','v2'],['v2','v1'])
	
	sabrObj.addDesObj('D1','O1',['a','b'])
	sabrObj.addDesObj('D2','O1',['b','c'])
	
	for i in range(5):
	
		# (board,trans)
		res = sabrObj.multiProcess(relFold + 'sabr',4)
		print res
		print ''

sabrMulti()