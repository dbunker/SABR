## Solve Every Sudoku Puzzle

## See http://norvig.com/sudoku.html

## Throughout this program we have:
##   r is a row,    e.g. 'A'
##   c is a column, e.g. '3'
##   s is a square, e.g. 'A3'
##   d is a digit,  e.g. '9'
##   u is a unit,   e.g. ['A1','B1','C1','D1','E1','F1','G1','H1','I1']
##   grid is a grid,e.g. 81 non-blank chars, e.g. starting with '.18...7...
##   values is a dict of possible values, e.g. {'A1':'12349', 'A2':'8', ...}

import math, time, random, sys
sys.setrecursionlimit(10000)

def cross(A, B):
    "Cross product of elements in A and elements in B."
    return [a+b for a in A for b in B]

################ Parse a Grid ################

def parse_grid(data,grid):
    """Convert grid to a dict of possible values, {square: digits}, or
    return False if a contradiction is detected."""
    ## To start, every square can be any digit; then assign values from the grid.
    values = dict((s, data.digits) for s in data.squares)
    for s,d in grid_values(data,grid).items():
        if d in data.digits and not assign(data,values, s, d):
            return False ## (Fail if we can't assign d to square s.)
    return values

def grid_values(data,grid):
    "Convert grid into a dict of {square: char} with '0' or '.' for empties."
    chars = [c for c in grid if c in data.digits or c in '0.']
    
    assert len(chars) == data.size * data.size
    return dict(zip(data.squares, chars))

################ Constraint Propagation ################

def assign(data,values, s, d):
    """Eliminate all the other values (except d) from values[s] and propagate.
    Return values, except return False if a contradiction is detected."""
    other_values = values[s].replace(d, '')
    if all(eliminate(data,values, s, d2) for d2 in other_values):
        return values
    else:
        return False

def eliminate(data,values, s, d):
    """Eliminate d from values[s]; propagate when values or places <= 2.
    Return values, except return False if a contradiction is detected."""
    if d not in values[s]:
        return values ## Already eliminated
    values[s] = values[s].replace(d,'')
    ## (1) If a square s is reduced to one value d2, then eliminate d2 from the peers.
    if len(values[s]) == 0:
        return False ## Contradiction: removed last value
    elif len(values[s]) == 1:
        d2 = values[s]
        if not all(eliminate(data,values, s2, d2) for s2 in data.peers[s]):
            return False
    ## (2) If a unit u is reduced to only one place for a value d, then put it there.
    for u in data.units[s]:
        dplaces = [s for s in u if d in values[s]]
        if len(dplaces) == 0:
            return False ## Contradiction: no place for this value
        elif len(dplaces) == 1:
            # d can only be in one place in unit; assign it there
            if not assign(data, values, dplaces[0], d):
                return False
    return values

################ Display as 2-D grid ################

def display(values):
    print values

################ Search ################

def setData(blockSize):

	class data:
		""
	
	data.size = blockSize*blockSize
	digits = '123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMO'
	rows   = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ123456789abcdefghijklmo'
	
	data.digits = digits[:data.size]
	data.rows   = rows[:data.size]
	
	data.cols = data.digits
	data.squares  = cross(data.rows, data.cols)
	
	blen = int(math.sqrt(data.size)+0.5)
	rb = [data.rows[i:i+blen] for i in range(0,data.size,blen)]
	cb = [data.cols[i:i+blen] for i in range(0,data.size,blen)]
		
	unitlist = ([cross(data.rows, c) for c in data.cols] +
				[cross(r, data.cols) for r in data.rows] +
				[cross(rs, cs) for rs in rb for cs in cb])
				
	data.units = dict((s, [u for u in unitlist if s in u])
				 for s in data.squares)
				 
	data.peers = dict((s, set(sum(data.units[s],[]))-set([s]))
				 for s in data.squares)

	return data

def solve(grid,blockSize): 

	data = setData(blockSize)
	return search(data,parse_grid(data,grid))

def search(data,values):
    "Using depth-first search and propagation, try all possible values."
    if values is False:
        return False ## Failed earlier
    if all(len(values[s]) == 1 for s in data.squares):
        return values ## Solved!
    ## Chose the unfilled square s with the fewest possibilities
    n,s = min((len(values[s]), s) for s in data.squares if len(values[s]) > 1)
    return some(search(data, assign(data, values.copy(), s, d))
                for d in values[s])

################ Utilities ################

def some(seq):
    "Return some element of seq that is true."
    for e in seq:
        if e: return e
    return False

def from_file(filename, sep='\n'):
    "Parse a file into a list of strings, separated by sep."
    return file(filename).read().strip().split(sep)

def shuffled(seq):
    "Return a randomly shuffled copy of the input sequence."
    seq = list(seq)
    random.shuffle(seq)
    return seq

################ System test ################

def random_puzzle(blockSize,N=17):
	"""Make a random puzzle with N or more assignments. Restart on contradictions.
	Note the resulting puzzle is not guaranteed to be solvable, but empirically
	about 99.8% of them are solvable. Some have multiple solutions."""
	
	data = setData(blockSize)
	values = dict((s, data.digits) for s in data.squares)
	for s in shuffled(data.squares):
		if not assign(data,values, s, random.choice(values[s])):
			break
		ds = [values[s] for s in data.squares if len(values[s]) == 1]
		if len(ds) >= N and len(set(ds)) >= 8:
			return ''.join(values[s] if len(values[s])==1 else '.' for s in data.squares)
	return random_puzzle(blockSize,N) ## Give up and make a new puzzle

## References used:
## http://www.scanraid.com/BasicStrategies.htm
## http://www.sudokudragon.com/sudokustrategy.htm
## http://www.krazydad.com/blog/2005/09/29/an-index-of-sudoku-strategies/
## http://www2.warwick.ac.uk/fac/sci/moac/currentstudents/peter_cock/python/sudoku/