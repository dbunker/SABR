print 'Start'
# use >> (bit shift) and % (mod) bit manipulation

def combo(fi,name,totSize):

	fullSize = pow(2,totSize)
	bit = {}

	for i in range(0,fullSize):
		
		tot = 0
		for n in range(0,totSize):
			bit[n] = (i >> n) % 2
			tot = tot + bit[n]
		
		line = 'Opt ' + name + ' { ' + str(tot)
		for n in range(0,totSize):
			if bit[n] == 0:
				line = line + ' !m'
			else:
				line = line + '  m'
		
		line = line + ' }\n'
		fi.write(line)

	last = 'Opt ' + name + ' { m'
	for i in range(0,totSize):
		last = last + '  ?'
	fi.write(last + ' }\n\n')

fi = open('source.tb','w')

fi.write("""# this will solve a 4x4 minesweeper problem

Sym { m 0 1 2 3 4 5 6 7 8 }

Board {
	a0 a1 a2 a3;
	b0 b1 b2 b3;
	c0 c1 c2 c3;
	d0 d1 d2 d3;
}

Req Board {
	m 2 2 2;
	1 ? m m;
	1 ? 3 2;
	1 ? ? 0;
}\n
""")

combo(fi,'BlockA',8)
combo(fi,'BlockB',5)
combo(fi,'BlockC',3)

fi.write("""# surround each cell
# a0 a1 a2 a3
# b0 b1 b2 b3
# c0 c1 c2 c3
# d0 d1 d2 d3

DesObj BlockA { b1 	a0 a1 a2 b0 b2 c0 c1 c2; }
DesObj BlockA { b2 	a1 a2 a3 b1 b3 c1 c2 c3; }
DesObj BlockA { c1 	b0 b1 b2 c0 c2 d0 d1 d2; }
DesObj BlockA { c2 	b1 b2 b3 c1 c3 d1 d2 d3; }

DesObj BlockB { b0 	a0 a1 b1 c0 c1; }
DesObj BlockB { c0 	b0 b1 c1 d0 d1; }
DesObj BlockB { d1 	c0 c1 c2 d0 d2; }
DesObj BlockB { d2	c1 c2 c3 d1 d3; }
DesObj BlockB { b3	a2 a3 b2 c2 c3; }
DesObj BlockB { c3	b2 b3 c2 d2 d3; }
DesObj BlockB { a1	a0 a2 b0 b1 b2; }
DesObj BlockB { a2	a1 a3 b1 b2 b3; }

DesObj BlockC { a0	a1 b0 b1; }
DesObj BlockC { a3	a2 b2 b3; }
DesObj BlockC { d0	c0 c1 d1; }
DesObj BlockC { d3	c2 c3 d2; }
""")

