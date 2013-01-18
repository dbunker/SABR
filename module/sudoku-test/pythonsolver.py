import sys, sudokurand

if len(sys.argv) != 3:
	exit()

blockSize = int(sys.argv[1])
line = sys.argv[2]
sudokurand.solve(blockSize,line)
