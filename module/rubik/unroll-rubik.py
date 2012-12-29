# shell game

import sys, os, re, time, random, math
sys.path.append("..")
import sabr

def sabrUnroll():
	
	sabrObj = sabr.SabrObj()
	
	sabrObj.readFromFile('6-solve.tb')
			
	sabrObj.unroll()
	sabrObj.removeUseless()
	
	sabrObj.source('unroll.tb')
	
	res = sabrObj.process('../../sabr',4)
	if res != None:
		(board,trans) = res
		print trans
	else:
		print None
		
sabrUnroll()

