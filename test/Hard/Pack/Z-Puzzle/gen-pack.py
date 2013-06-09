# this will write out the the TBL of the z bin packing problem
# which is to fit long-z shaped pieces into a 5x5x5 cube

# shape
# O O
#   O O O

# 25 peices

out = '\nSym { 0 1 }\n\n'

out += 'Board{\n'
for z in range(0,5):
	for y in range(0,5):
		out += '\t'
		for x in range(0,5):
			out += str(z) + str(y) + str(x) + ' '
		out = out[0:-1] + ';\n'
	out += '\n'
out = out[0:-1] + '}\n\n'

def startEnd(init,fill):
	out = init + '{\n'
	for z in range(0,5):
		for y in range(0,5):
			out += '\t' + fill + ';\n'
		out += '\n'
	out = out[0:-1] + '}\n\n'
	return out

out += startEnd('Start','0 0 0 0 0')
out += startEnd('End'  ,'1 1 1 1 1')

out += 'TransSim Fill:Block { 0 0 0 0 0 => 1 1 1 1 1 }\n\n'

orientArr = [(-1,0),(1,0),(0,-1),(0,1)]
directArr = ['Vert','Horiz','Back']
# horiz: switch z and y
# back: switch x and y

# this tiles the 3d space with z structures, they can be anywhere
for directInd in range(0,3):
	for z in range(0,5):
		for orientInd in range(0,4):
			orient = orientArr[orientInd]

			for yFlip in range(0,2):
				for yShift in range(0,2):
					for x in range(0,5):
					
						orientZ = orient[0]
						orientX = orient[1]
					
						if z+orientZ < 5 and z+orientZ >= 0 and x+orientX < 5 and x+orientX >= 0:
	
							lengthStr = ''
							for y in range(0,2+yFlip):
								if directInd == 0:
									lengthStr += str(z) + str(y+yShift) + str(x) + ' '
								if directInd == 1:
									lengthStr += str(y+yShift) + str(z) + str(x) + ' '
								if directInd == 2:
									lengthStr += str(z) + str(x) + str(y+yShift) + ' '
	
							for y in range(1+yFlip,4):
								if directInd == 0:
									lengthStr += str(z+orientZ) + str(y+yShift) + str(x+orientX) + ' '
								if directInd == 1:
									lengthStr += str(y+yShift) + str(z+orientZ) + str(x+orientX) + ' '
								if directInd == 2:
									lengthStr += str(z+orientZ) + str(x+orientX) + str(y+yShift) + ' '
	
							out += 'DesObj ' + directArr[directInd]
							if directInd == 0:
								out += '-Z' + str(z)
								out += '-YS' + str(yShift) + '-YF' + str(yFlip)
								out += '-X' + str(x)
							if directInd == 1:
								out += '-ZS' + str(yShift) + '-ZF' + str(yFlip)
								out += '-Y' + str(z)
								out += '-X' + str(x)
							if directInd == 2:
								out += '-Z' + str(z)
								out += '-Y' + str(x)
								out += '-XS' + str(yShift) + '-XF' + str(yFlip)

							out += '-OR' + str(orientInd)
							out += ':Block { ' + lengthStr + '}\n'
	
					out += '\n'

fi = open('pack.tb','w')
fi.write(out);
