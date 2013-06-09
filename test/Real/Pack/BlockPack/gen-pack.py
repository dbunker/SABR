# this will write out the the TBL of the z bin packing problem
# which is to fit long-z shaped pieces into a 5x5x5 cube

# shape
# O O
#   O O O

# 25 peices

print 'Start'

start = """
Sym { 0 1 }

Board{
	000 001 002 003 004; 
	010 011 012 013 014; 
	020 021 022 023 024; 
	030 031 032 033 034; 
	040 041 042 043 044;

	100 101 102 103 104; 
	110 111 112 113 114; 
	120 121 122 123 124; 
	130 131 132 133 134; 
	140 141 142 143 144;

	200 201 202 203 204; 
	210 211 212 213 214; 
	220 221 222 223 224; 
	230 231 232 233 234; 
	240 241 242 243 244;

	300 301 302 303 304; 
	310 311 312 313 314; 
	320 321 322 323 324; 
	330 331 332 333 334; 
	340 341 342 343 344;

	400 401 402 403 404; 
	410 411 412 413 414; 
	420 421 422 423 424; 
	430 431 432 433 434; 
	440 441 442 443 444;
}

Start{
	0 0 0 0 0;
	0 0 0 0 0;
	0 0 0 0 0;
	0 0 0 0 0;
	0 0 0 0 0;

	0 0 0 0 0;
	0 0 0 0 0;
	0 0 0 0 0;
	0 0 0 0 0;
	0 0 0 0 0;

	0 0 0 0 0;
	0 0 0 0 0;
	0 0 0 0 0;
	0 0 0 0 0;
	0 0 0 0 0;

	0 0 0 0 0;
	0 0 0 0 0;
	0 0 0 0 0;
	0 0 0 0 0;
	0 0 0 0 0;
	
	0 0 0 0 0;
	0 0 0 0 0;
	0 0 0 0 0;
	0 0 0 0 0;
	0 0 0 0 0;
}

End{
	1 1 1 1 1;
	1 1 1 1 1;
	1 1 1 1 1;
	1 1 1 1 1;
	1 1 1 1 1;
	
	1 1 1 1 1;
	1 1 1 1 1;
	1 1 1 1 1;
	1 1 1 1 1;
	1 1 1 1 1;

	1 1 1 1 1;
	1 1 1 1 1;
	1 1 1 1 1;
	1 1 1 1 1;
	1 1 1 1 1;
	
	1 1 1 1 1;
	1 1 1 1 1;
	1 1 1 1 1;
	1 1 1 1 1;
	1 1 1 1 1;
	
	1 1 1 1 1;
	1 1 1 1 1;
	1 1 1 1 1;
	1 1 1 1 1;
	1 1 1 1 1;
}

TransSim Fill:Block  { 0 0 0 0 0 => 1 1 1 1 1 }

"""

fi = open('pack.tb','w')
fi.write(start);

# horiz peices
# ---------
# ---------
for z in range(0,5):
	for y in range(0,5):
		lengthStr = ""		
		for x in range(0,5):
			lengthStr = lengthStr + str(z) + str(y) + str(x) + " "

		desobj = "DesObj Horiz-Z" + str(z) + "-Y" + str(y) + ":Block { " + lengthStr + "}\n"
		fi.write(desobj)
	fi.write('\n')
fi.write('\n')

# vert peices
# | | | |
# | | | |
for z in range(0,5):
	for x in range(0,5):
		lengthStr = ""		
		for y in range(0,5):
			lengthStr = lengthStr + str(z) + str(y) + str(x) + " "

		desobj = "DesObj Vert-Z" + str(z) + "-X" + str(x) + ":Block { " + lengthStr + "}\n"
		fi.write(desobj)
	fi.write('\n')
fi.write('\n')

# back peices
# o o o o
# o o o o
for x in range(0,5):
	for y in range(0,5):
		lengthStr = ""		
		for z in range(0,5):
			lengthStr = lengthStr + str(z) + str(y) + str(x) + " "

		desobj = "DesObj Back-X" + str(x) + "-Y" + str(y) + ":Block { " + lengthStr + "}\n"
		fi.write(desobj)
	fi.write('\n')
fi.write('\n')

