# based on https://gist.github.com/3904180

import os, numpy
 
def select(list):
    return ' '.join('(select a {0})'.format(l) for l in list)
 
def cvc4main(blockSize,model):
	
	nums = '123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMO'
	
	lineSize = blockSize * blockSize
	boardSize = lineSize * lineSize
	
	lines = []
	lines.append('(set-logic AUFLIRA)')
	lines.append('(set-option :produce-models true)')
	lines.append('(declare-fun a () (Array Int Int))')
	
	index = numpy.arange(boardSize).reshape(lineSize,lineSize)
	for i in xrange(lineSize):
		lines.append('(assert (distinct {}))'.format(select(index[:,i])))
		lines.append('(assert (distinct {}))'.format(select(index[i,:])))
	
		r0 = (i % blockSize) * blockSize
		c0 = (i // blockSize) * blockSize
		lines.append('(assert (distinct {}))'.format(
			select(index[r0:r0+blockSize,c0:c0+blockSize].ravel())
		))
	
	for i in xrange(boardSize):
		lines.append('(assert (< 0 (select a {0})))'.format(i))
		lines.append('(assert (> ' + str(lineSize+1) + ' (select a {0})))'.format(i))
	
	for i, n in zip(xrange(boardSize), model):
		if n != '.':
			outN = str(nums.index(n)+1)
			lines.append('(assert (= {0} (select a {1})))'.format(outN, i))
	
	lines.append('(check-sat)')
	lines.append('(get-value ({}))'.format(select(xrange(boardSize))))
	
	return lines
 
def solve(blockSize,line):

	model = line
	out = open('puzzle.smt', 'w')
	out.write('\n'.join(cvc4main(blockSize,model)))
	out.write('\n')
	out.close()
	
	# cvc4 must be added to project path
	# downloadable from http://cvc4.cs.nyu.edu/web/#Downloads
	os.system('cvc4 --lang smt puzzle.smt > cvc4-result.txt')
    
# model = '53..7....6..195....98....6.8...6...34..8.3..17...2...6.6....28....419..5....8..79'
# solve(3,model)
