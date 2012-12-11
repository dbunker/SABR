# see license at project root

import os, sys

def checkFile(elem,cmdExec,toCheck):

	if os.path.isfile('test/' + elem + '-' + toCheck):
	
		cmdDif = 'diff -B -w ' + toCheck + ' test/' + elem + '-' + toCheck
		ans = os.system(cmdDif)
		
		if ans != 0:
			print 'Error ' + toCheck + ' ' + cmdExec
			exit()

def checkRun(ans,cmdExec):
	if ans != 0:
		print 'Failed Run: ' + cmdExec
		exit()

# just test, don't write
def proc(newList,size):
	
	for elem in newList:
		
		# example: ./sabr 20 test/Simple/simple.tb
		cmdExec = './sabr ' + str(size) + ' test/' + elem + '.tb'
		ans = os.system(cmdExec)
		checkRun(ans,cmdExec)
		
		# compare if possible
		checkFile(elem,cmdExec,'cnf.txt')
		checkFile(elem,cmdExec,'vars.txt')
		
		# create debug and compare if possible
		if os.path.isfile('test/' + elem + '-debug.txt'):
		
			cmdExec = './sabr --debug ' + str(size) + ' test/' + elem + '.tb'
			ans = os.system(cmdExec)
			checkRun(ans,cmdExec)
			checkFile(elem,cmdExec,'debug.txt')
		
		# check expected results
		cmdDif = 'diff -B -w result.txt test/' + elem + '-expected.txt'
		ans = os.system(cmdDif)
		
		if ans != 0:
			print 'Error Res ' + cmdExec
			exit()
		
		print 'Passed ' + elem

# run tests, and write out results
# use with caution
def procWrite(newList,size):

	for elem in newList:

		# main results
		cmdExec = './sabr ' + str(size) + ' test/' + elem + '.tb > stats.txt'
		ans = os.system(cmdExec)
		checkRun(ans,cmdExec)

		# debug results
		cmdExec = './sabr --debug ' + str(size) + ' test/' + elem + '.tb'
		ans = os.system(cmdExec)
		checkRun(ans,cmdExec)
		
		# these can be used when it is known the preliminary results correct
		cmd = 'cp cnf.txt test/' + elem + '-cnf.txt'
		os.system(cmd)
		
		cmd = 'cp vars.txt test/' + elem + '-vars.txt'
		os.system(cmd)

		cmd = 'cp debug.txt test/' + elem + '-debug.txt'
		os.system(cmd)
		
		cmd = 'cp stats.txt test/' + elem + '-stats.txt'
		os.system(cmd)

		# this can be used when it is known the final results are correct
		# cmd = 'cp result.txt test/' + elem + '-expected.txt'
		# ans = os.system(cmd)

		print 'Wrote ' + elem

# test post process debugger
def debug(newList):

	for elem in newList:

		cmdExec = './sabr 1 test/Debug/' + elem + '/debug.tb > full.txt'
		ans = os.system(cmdExec)
		checkRun(ans,cmdExec)

		# this can be used when it is known the debug results are correct
		# cmd = 'cp full.txt test/Debug/' + elem + '/full.txt'
		# ans = os.system(cmd)

		cmdDif = 'diff -B -w full.txt test/Debug/' + elem + '/full.txt'
		ans = os.system(cmdDif)
	
		if ans != 0:
			print 'Error Diff ' + cmdExec
			exit()

		print 'Passed ' + elem

def clear(newList,size):
	for elem in newList:
		cmd = 'rm test/' + elem + '-cnf.txt'
		os.system(cmd)
		cmd = 'rm test/' + elem + '-vars.txt'
		os.system(cmd)
		cmd = 'rm test/' + elem + '-debug.txt'
		os.system(cmd)

debugList = [	'1-Sym/1-MultiName', '1-Sym/2-DupGenList', '1-Sym/3-DupSym',
		'2-Board/1-NoSym', '2-Board/2-NoGenSym', '2-Board/3-DupCellName',
		'3-Obj/1-MultiNameObj', '3-Obj/2-MultiNameDesObj', '3-Obj/3-ObjCreate', '3-Obj/4-DesObj',
		'4-Elab/1-Req/1-MultiNameReq', '4-Elab/1-Req/2-StageReq', '4-Elab/1-Req/3-Obj/1-BadObj',
		'4-Elab/1-Req/3-Obj/2-MatchObj', '4-Elab/1-Req/4-Temp/1-Paren', '4-Elab/1-Req/4-Temp/2-SymName',
		'4-Elab/1-Req/4-Temp/3-Connect', '4-Elab/2-Rest/1-MultiNameTrans','4-Elab/2-Rest/2-StageOpt',
		'4-Elab/2-Rest/3-StageTrans', '4-Elab/2-Rest/4-TransObj', '4-Elab/2-Rest/5-StartEnd',
		'5-LexYacc/1-Lex','5-LexYacc/2-Yacc/1-Root'	]

simpleList = [	'Simple/simple','Obj/obj','Req/Req1/req1','Req/Req2/req2','Req/Req3/req3',
		'Trans/Swap/swap','Trans/SwapAdv/swap','Trans/Pack/pack','Opt/Opt/opt',
		'SymList/Basic/sym','Extra/Punc/punc','Extra/Stages/stages',
		'Extra/CellFail/cell','Extra/TransSim/sim','Opt/AdvOpt/opt' 	]

advList = [  	'Real/River/V1/river1', 'Real/River/V2/river2', 'Real/Frog/frog',
		'Real/Mach/mach1', 'Real/Map/map', 'Real/Queen/Eight/8queen', 'Real/Queen/Four/4queen',
		'Real/Slide/sliding', 'Real/Sudo/sudo', 'Real/Tower/tower',
		'Real/Add/add', 'Real/Mult/mult', 'Real/Mine/mine', 'Real/Pack/BlockPack/pack',
		'Real/Conc/P1/philo1', 'Real/Conc/P2/philo2', 'Real/Conc/P3/philo3',
		'Real/Add/add', 'Real/Ein/ein', 'Real/Rube/Easy/1-solve', 'Real/Troyis/troyis'	]

hardList1 = [	'Hard/Pack/Z-Puzzle/pack'	]
hardList2 = [	'Hard/Rube/Medium/Six/6-solve'	]
hardList3 = [ 	'Hard/Rube/Medium/Ten/10-solve'	]

def hardProbs(testFunc):
	testFunc(hardList1,2)
	testFunc(hardList2,6)
	testFunc(hardList3,10)

coms = """usage: python test.py <command>

commands:
debug			Compiler post-process syntax checking
simple			Simple tests for compiler functionality
adv 			Advanced tests for compiler functionality
hard			Difficult tests for compiler functionality
all 			All tests for compiler functionality
write-all		Like all, but also saves debug and output files
clear-debug		Clear all debug info
help			Help screen
"""

if len(sys.argv) == 2:
	
	if sys.argv[1] == 'debug':
		debug(debugList)

	elif sys.argv[1] == 'simple':
		proc(simpleList,20)
	elif sys.argv[1] == 'adv':
	 	proc(advList,20)
	elif sys.argv[1] == 'hard':
		hardProbs(proc)
	elif sys.argv[1] == 'all':
		debug(debugList)
		proc(simpleList,20)
		proc(advList,20)
		hardProbs(proc)
		
	elif sys.argv[1] == 'write-all':
		procWrite(simpleList,20)
		procWrite(advList,20)
		hardProbs(procWrite)

	# debug files take up a lot of space, clearing them frees this
	elif sys.argv[1] == 'clear-debug':
		clear(simpleList)
		clear(advList)
		hardProbs(clear)
	else:
		print "Improper Command"
		exit()
		
	print "Passed All Tests"
	
else:
	print coms

