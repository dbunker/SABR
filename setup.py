# see license at project root

import os
import sys

def depend():

	os.system('dot doc/depend/depend.dot -Tpng -o doc/depend/depend.png')

def minisat():
	
	os.system('make -C cnf/minisat')
	os.system('rm cnfsat')
	os.system('cp cnf/minisat/build/release/bin/minisat cnfsat')

def parser():

	res = os.system('flex parser/tbl.l')
	if res != 0:
		print 'Flex Error.'
		exit()
	os.system('mv lex.yy.c parser')

	res = os.system('bison -y -d parser/tbl.y')
	if res != 0:
		print 'Bison Error.'
		exit()
	os.system('mv y.tab.c parser')
	os.system('mv y.tab.h parser')

def sabr():

	cmd  = 'gcc -g -Wall -o sabr '
	cmd += 'utils/linkedlist.c utils/skiplist.c utils/botlist.c utils/gendebug.c '
	cmd += 'parser/y.tab.c parser/lex.yy.c '
	cmd += 'core/arch.c core/structs.c core/debug.c core/tbl.c core/req.c core/var.c'
	os.system(cmd)

def clean():
	
	os.system('rm debug.out dimin.in dimout.out full.out result.out cnfsat sabr')

def cleanall():

	clean()
	os.system('make clean -C cnf/minisat')

coms = """usage: python setup.py <command>

commands:
build		Compile minisat and sabr
depend		Create a dependency diagram using the dot file in doc
minisat		Compile minisat, the default cnf solver used by SABR
parser		Use flex and bison to create c files from parser directory
sabr		build SABR from core utils and parser
clean		Clear all unnesary files in the SABR directory
cleanall	Clear minisat installation
help		Help screen
"""

if len(sys.argv) == 2:
	if sys.argv[1] == 'depend':
		depend()
	elif sys.argv[1] == 'minisat':
		minisat()
	elif sys.argv[1] == 'parser':
		parser()
	elif sys.argv[1] == 'sabr':
		sabr()
	elif sys.argv[1] == 'build':
		minisat()
		parser()
		sabr()
	elif sys.argv[1] == 'clean':
		clean()
	elif sys.argv[1] == 'cleanall':
		cleanall()
	elif sys.argv[1] == 'help':
		print coms
	else:
		print "Improper Command"
else:
	print coms
