# shell game
# unroll: transition by 2 steps instead of 1

import sys, os, re, time, random, math
relFold = '../../../'
sys.path.append(relFold+'module')
import sabr

def sabrUnroll():
	
	sabrObj = sabr.SabrObj()
	
	sabrObj.readFromFile('6-solve.tb')
			
	sabrObj.unroll()
	sabrObj.removeUseless()
	
	sabrObj.source('unroll.tb')
	
	res = sabrObj.process(relFold+'/sabr',4)
	if res != None:
		(board,trans) = res
		print trans
	else:
		print None
		
sabrUnroll()

