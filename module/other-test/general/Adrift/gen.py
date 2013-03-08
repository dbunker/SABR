# adrift game

import sys, time
relFold = "../../../../"
sys.path.append(relFold+'module')
import sabr

sabrObj = sabr.SabrObj()

colors = [ 'R', 'G', 'Y', 'B', 'O' ]

sabrObj.setSym(colors)
sabrObj.setBoard(sides)

