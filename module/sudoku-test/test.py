from sudoku import *
import subprocess, threading

class Command(object):
    def __init__(self, cmd):
        self.cmd = cmd
        self.process = None

    def run(self, timeout):
    
    	result = 'Success'
    
        def target():
            print 'Thread started'
            self.process = subprocess.Popen(self.cmd, shell=True)
            self.process.communicate()
            print 'Thread finished'

        thread = threading.Thread(target=target)
        thread.start()

        thread.join(timeout)
        if thread.is_alive():
            print 'Terminating process'
            self.process.terminate()
            thread.join()
            result = 'Failed'
        
        code = self.process.returncode
        
        return result
        
def runWithTime(cmd,timeout):

	command = Command(cmd)
	return command.run(timeout)

# generateTest takes an integer argument for test number as well as 
# blockSize which is block width
def runTests(blockSize,generateTest,solver,shower,numTests=100,
				outFile='tests.txt',timeout=1000,numFails=1000,threshold=-1.0):
	
	curFails = 0
	
	file = open(outFile,'w')
	for i in range(numTests):
	
		line = generateTest(blockSize,i)
		
		if line == None:
			return
		line = line.strip()
		
		cmd = solver(blockSize,line)
		
		start = time.time()
		status = runWithTime(cmd,timeout)
		tm = time.time()-start
		
		if status == 'Failed':
			curFails += 1
		else:
			curFails = 0
			
		# failed too many consecutive times
		if curFails > numFails :
			return
		
		res = ''
		outLine = shower(line,res,tm)
		print i
		
		file.write(outLine)
		
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
	numTests = 10

	for boardSize in range(2,3):
	
		# create test file of 1000 random tests
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
			
			timeout = 10
			numFails = 5
			outTestName = str(boardSize) + '-' + name + '-' + 'out.txt'
			runTests(boardSize,tester,solver,shower,numTests,outTestName,timeout,numFails)
			
			# run these tests
			# if it fails to solve within 5 minutes for 5 initial tests, give up

"""
command = Command("echo 'Process started'; sleep 2; echo 'Process finished'")
print command.run(timeout=3)
print command.run(timeout=1)
"""

testBat()
