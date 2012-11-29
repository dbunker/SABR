# see license at project root

import os
import sys

# just test, don't write
def proc(newList,size):

	for elem in newList:

		# example: ./sabr 20 -all < test/Simple/simple.tb
		cmdExec = './sabr ' + str(size) + ' -all < test/' + elem + '.tb'
		os.system(cmdExec)

		# check debug
		cmdDif = 'diff -B -w debug.out test/' + elem + '-debug.txt'
		ans = os.system(cmdDif)
	
		if ans != 0:
			print 'Error Debug ' + cmdExec
			exit()

		# check expected results
		cmdDif = 'diff -B -w result.out test/' + elem + '-expected.txt'
		ans = os.system(cmdDif)

		if ans != 0:
			print 'Error Res ' + cmdExec
			exit()

		print 'Passed ' + elem

	print 'Passed All'

# run tests, and write out results
# use with caution
def full(newList,size):

	for elem in newList:

		cmdExec = './sabr ' + str(size) + ' -all < test/' + elem + '.tb > full.out'
		os.system(cmdExec)

		# output
		cmdPrint = 'cat full.out'
		os.system(cmdPrint)

		# this can be used when it is known the debug results are correct
		cmd = 'cp debug.out test/' + elem + '-debug.txt'
		ans = os.system(cmd)

		# this can be used when it is known the full results are correct
		# cmd = 'cp result.out test/' + elem + '-expected.txt'
		# ans = os.system(cmd)

		# this can be used when it is known the full out results are correct
		cmd = 'cp full.out test/' + elem + '-full.txt'
		ans = os.system(cmd)
		
		print 'Wrote ' + elem

# test post process debugger
def debug(newList):

	for elem in newList:

		cmdExec = './sabr 1 -all < test/Debug/' + elem + '/debug.tb > full.out'
		ans = os.system(cmdExec)

		if ans != 0:
			print 'Error Debug ' + cmdExec
			exit()

		# this can be used when it is known the debug results are correct
		# cmd = 'cp full.out test/Debug/' + elem + '/full.txt'
		# ans = os.system(cmd)

		cmdDif = 'diff -B -w full.out test/Debug/' + elem + '/full.txt'
		ans = os.system(cmdDif)
	
		if ans != 0:
			print 'Error Diff ' + cmdExec
			exit()

		print 'Passed ' + elem

def clear(newList):
	for elem in newList:
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

def hardProbs():
	proc(hardList1,2)
	proc(hardList2,6)
	proc(hardList3,10)

if len(sys.argv) == 2:
	
	if sys.argv[1] == 'debug':
		debug(debugList)

	elif sys.argv[1] == 'simple':
		proc(simpleList,20)
	elif sys.argv[1] == 'adv':
	 	proc(advList,20)
	elif sys.argv[1] == 'hard':
		hardProbs()
	elif sys.argv[1] == 'all':
		proc(simpleList,20)
		proc(advList,20)
		hardProbs()

	elif sys.argv[1] == 'simple-full':
		full(simpleList,20)
	elif sys.argv[1] == 'adv-full':
	 	full(advList,20)
	elif sys.argv[1] == 'hard-full':
		hardProbs()
	elif sys.argv[1] == 'all-full':
		full(simpleList,20)
		full(advList,20)
		hardProbs()

	# debug files take up a lot of space, clearing them frees this
	elif sys.argv[1] == 'clear-debug':
		clear(simpleList)
		clear(advList)
		clear(hardList1)
		clear(hardList2)
		clear(hardList3)
	else:
		print "Improper Commands."
else:
	print "Improper Commands."

