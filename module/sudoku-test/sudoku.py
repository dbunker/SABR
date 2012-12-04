# top95.txt from http://norvig.com/sudoku.html

import sys
sys.path.append("..")

import sabr

# sym
['1', '2', '3', '4', '5', '6', '7', '8', '9']

# req
letterArr = 'abcdefghi'

boardArr = [['.']*9 for x in xrange(9)]
for y in range(0,9):
	for x in range(0,9):
		boardArr[y][x] = letterArr[y] + str(x)

# desobj



# for each new line in file create new board
fi = open('top95.txt')
for line in fi:
	arr = list(line)
	print arr

# board
for y in range(0,9):
	for x in range(0,9):
		""

print 'hi'
# process