from sudoku import *
import os, signal, errno
from contextlib import contextmanager

def testWithTimeout(cmd,timeLeft):

	@contextmanager
	def timeout(seconds):
		def timeout_handler(signum, frame):
			pass
	
		original_handler = signal.signal(signal.SIGTERM, timeout_handler)
	
		try:
			signal.alarm(seconds)
			yield
		finally:
			signal.alarm(0)
			signal.signal(signal.SIGTERM, original_handler)
	
	with timeout(timeLeft):
		try:
			os.system(cmd)
		except IOError, e:
			if e.errno != errno.EINTR:
				raise e
			print "Timed Out"

def runTests():

	# file95Test = fileTestGen('top95.txt')
	# testOptions = [ randomTest, file95Test ]
	# tester = testOptions[0]
	
	solverNames = [ 'sabr', 'minizinc', 'swi-prolog', 'python', 'cvc4' ]
	solverOptions = [ sabrSolver, minizincSolver, prologSolver, sudokurand.solve, cvc4sudo.solve ]
	
	timeShowOptions = [ regLineShower, statsLineShower ]
	shower = timeShowOptions[0]
	numTests = 1000

	for boardSize in range(3,7):
	
		# create test file of 1000 random tests
		testFileName = str(boardSize) + 'test.txt'
		testFile = open(testFileName,'w')
		for i in range(numTests):
			res = sudokurand.random_puzzle(size)
			testFile.write()
			
		testFile.close()
		tester = fileTestGen(testFileName)
		
		for solverNum in range(len(solverOptions)):
			
			name = solverNames[solverNum]
			solver = solverOptions[solverNum]
			
			runTests(boardSize,tester,solver,shower,numTests)
			
			# run these 1000 tests
			# if it fails to solve within 5 minutes for 5 initial tests, give up

testWithTimeout('echo \'start\'; sleep 3; echo \'end\'',2)

