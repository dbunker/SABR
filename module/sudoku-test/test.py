import re, subprocess
from sudoku import *

# create and run as a shell script
def runWithTime(cmd,timeout):

	print cmd
	
	fi = open('test.sh','w')
	fi.write(cmd + ';exit 0')
	fi.close()
	
	cmd = '( time timeout ' + str(timeout) + ' sh test.sh ) 2> time.txt'
	ret = subprocess.Popen(cmd, shell=True).wait()
	
	if ret == 0:
		return 'Success'
	else:
		return 'Failed'

# generateTest takes an integer argument for test number as well as 
# blockSize which is block width
def runTests(blockSize,generateTest,solver,shower,numTests=100,
				outFile='tests.txt',timeout=1000,numFails=1000,threshold=-1.0):
	
	# run all if it passes the first numFails
	curFails = 0
	runAll = False
	
	file = open(outFile,'w')
	for i in range(numTests):
		
		line = generateTest(blockSize,i)
		
		if line == None:
			return
		line = line.strip()
		
		cmd = solver(blockSize,line)
		
		start = time.time()
		
		run = True
		while run:
		
			status = runWithTime(cmd,timeout)
			
			fi = open('time.txt','r')
			show = fi.read().replace('\n',' ')
			print '\n' + show + '\n'
			fi.close()
			
			getRe = '[0-9]*\.[0-9]*'
			userTime = float(re.findall(getRe+'user',show)[0][:-4])
			systemTime = float(re.findall(getRe+'system',show)[0][:-6])
			
			print userTime, systemTime
			print ''
			
			# if it failed, but insufficient time was given to run, run it again
			run = False
			if status == 'Failed' and userTime+systemTime < 120:
				
				timeout += 120
				print 'Run Again For: ' + str(timeout)
				run = True
		
		tm = time.time()-start
		
		if status == 'Failed':
			curFails += 1
			line = 'Failed ' + line
		else:
			runAll = True
			curFails = 0
			
		# failed too many consecutive times
		if curFails >= numFails and not runAll:
			file.write('Failed Tests')
			return
		
		res = ''
		outLine = shower(line,res,tm)
		print i
		
		file.write(outLine.strip() + ' ' + show + '\n')
		
		if tm > threshold:
			print outLine

# random
def randomTest(size,i):
	res = sudokurand.random_puzzle(size)
	return res

def regLineShower(line,res,tm):
	
	return str(tm) + '\t' + line + '\n'

# show sabr stats and regular
def statsLineShower(line,res,tm):
	
	statsFile = open('stats.txt','r')
	stats = statsFile.read()
	arr1 = stats.split('CPU time              : ')[1]
	numStr = arr1.split('s',)[0].strip();
	
	ret = str(tm) + '\t' + str(numStr) + '\t' + line + '\n'
	return ret

# closure
def fileTestGen(name):
	file = open(name,'r')
	lines = file.read().strip().split('\n')
	
	def fileTest(size,i):
		if i >= len(lines):
			return None
		return lines[i]
		
	return fileTest

# test battery
def testBat():

	# file95Test = fileTestGen('top95.txt')
	# testOptions = [ randomTest, file95Test ]
	# tester = testOptions[0]
	
	solverNames = [ 'sabr', 'minizinc', 'swi-prolog', 'cvc4', 'python' ]
	solverOptions = [ sabrSolver, minizincSolver, prologSolver, cvc4Solver, pythonSolver ]
	
	timeShowOptions = [ regLineShower, statsLineShower ]
	shower = timeShowOptions[0]
	numTests = 500

	for boardSize in range(2,7):
	
		# create test file of random tests
		testFileName = str(boardSize) + '-test.txt'
		testFile = open(testFileName,'w')
		for i in range(numTests):
			res = sudokurand.random_puzzle(boardSize) + '\n'
			testFile.write(res)
			
		testFile.close()
		
		tester = fileTestGen(testFileName)
		
		for solverNum in range(len(solverOptions)):
			
			name = solverNames[solverNum]
			solver = solverOptions[solverNum]
			print 'RUN: ' + name
			
			timeout = 5*60
			numFails = 5
			outTestName = str(boardSize) + '-' + name + '-' + 'out.txt'
			runTests(boardSize,tester,solver,shower,numTests,outTestName,timeout,numFails)
			
			# run these tests
			# if it fails to solve within 5 minutes for 5 initial tests, give up

testBat()
