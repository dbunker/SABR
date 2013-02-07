# shell game

import sys, os, time, random, math
relFold = '../../../'
sys.path.append(relFold+'module')
import sabr

def sabrUnroll():
	
	sabrObj = sabr.SabrObj()
	
	# sym
	sabrObj.setSym(['0','1','2'])
	
	# board
	sabrObj.setBoard(['a','b','c'])
	
	# start
	sabrObj.setStart(['2','0','1'])
	
	# end
	sabrObj.setEnd(['0','1','2'])
	
	# trans
	sabrObj.addTransSim('T1','O1',['v1','v2'],['v2','v1'])
	sabrObj.addTransSim('T2','O2',['w1','w2'],['w2','w1'])
	
	
	sabrObj.addDesObj('D1','O1',['a','b'])
	sabrObj.addDesObj('D2','O2',['b','c'])
	sabrObj.addDesObj('D3','O1',['b','c'])
	
	sabrObj.unroll()
	sabrObj.removeUseless()
	
	sabrObj.source('unroll.tb')
	
	res = sabrObj.process(relFold+'sabr',2)
	print res

sabrUnroll()