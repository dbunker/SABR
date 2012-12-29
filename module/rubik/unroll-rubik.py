# shell game

print 'start'

import sys, os, re, time, random, math
sys.path.append("..")
import sabr

def sabrUnroll():
	
	sabrObj = sabr.SabrObj()
	
	sabrObj.readFromFile('10-solve.tb')
			
	sabrObj.unroll()
	sabrObj.removeUseless()
	
	sabrObj.source('unroll.tb')
	
	# sabrObj.process('../../sabr',6)

sabrUnroll()

