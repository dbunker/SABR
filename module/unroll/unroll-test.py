
print 'start'

import sys, os, time, random, math
sys.path.append("..")
import sabr

def sabrUnroll():
	
	sabrObj = sabr.SabrObj()

	# sym
	sabrObj.setSym(['0','1'])
	
	# board
	sabrObj.setBoard(['a','b','c'])
	
	# start
	sabrObj.setStart(['1','0','0'])
	
	# end
	sabrObj.setEnd(['0','0','1'])
	
	# trans
	sabrObj.addTrans('D1','D1',['1','0'],['0','1'])
	sabrObj.addDesObj('D1','D1',['a','b'])
	sabrObj.addSpace()
	
	sabrObj.addTrans('D2','D2',['1','0'],['0','1'])
	sabrObj.addDesObj('D2','D2',['b','c'])
	
	sabrObj.unroll()
	
	sabrObj.source('unroll.tb')
	
	# sabrObj.process('../../sabr')

sabrUnroll()