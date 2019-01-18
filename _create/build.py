
# this creates the pages in _pages
# based on layouts main-gen and main-ex in _layout

from jinja2 import Template
import shutil, os

print('start')

# clear out directory
outDir = '_out'
if os.path.exists(outDir):
	shutil.rmtree(outDir)

if os.path.exists('_raw'):
	shutil.copytree('_raw','_out')

if not os.path.exists(outDir):
	os.makedirs(outDir)

# get layouts
curFolder = '_layouts'
allLayoutFiles = os.listdir(curFolder)
layoutFiles = [layout for layout in allLayoutFiles if layout.endswith('.html')]

temDict = {}
for layout in layoutFiles:

	name = curFolder + '/' + layout
	data = open(name,'r').read()
	
	temRaw = layout[:-len('.html')]
	newTem = Template(data)

	temDict[temRaw] = newTem

# get pages
curFolder = '_pages'
allPageFiles = os.listdir(curFolder)
pageFiles = [page for page in allPageFiles if page.endswith('.html')]

for page in pageFiles:
	
	name = curFolder + '/' + page
	input = open(name,'r')
	
	pageData = ''
	setDict = {}

	# start -> keys -> post
	state = 'start'
	
	for line in input:
		line = line.strip()
		
		if state == 'start':
			if line != '---':
				print(line)
				print(name + ' not templated')
				exit()
			else:
				state = 'keys'
		
		elif state == 'keys':
			if line == '---':
				state = 'post'	
			else:
				arr = line.split(':')
				key = arr[0].strip()
				val = arr[1].strip()
				setDict[key] = val
			
		elif state == 'post':
			pageData += line + '\n'
	
	input.close()
	
	temName = setDict['layout']
	template = temDict[temName]
	args = { 'content':pageData }
	
	outData = template.render(args)
	
	outDir = '_out'
	pageRaw = page[:-len('.html')]
	
	pageOutDir = outDir
	if pageRaw != 'index':
		pageOutDir = outDir + '/' + pageRaw
		os.makedirs(pageOutDir)
	
	pageOutName = pageOutDir + '/index.html'
	outFile = open(pageOutName,'w')
	outFile.write(outData)
	outFile.close()

# run: jekyll _out _site --server
# cp -r _out/* ..

