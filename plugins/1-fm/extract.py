#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

import json
import re
import base64
import urllib.parse

FILENAME = '1-fm.json' # from 'https://www.1.fm/mainstations'
STYLESHEET = 'flags.css' # from https://www.1.fm/less/flags.css
MASK = re.compile(u'\.bg([^{,]*)\{background(?:-image)?:url\(data:image\/svg\+xml;base64,([^}]+)\)\}')
OUTPUT = 'backgrounds.css'
TEMPLATE = '''\
.bg-%s { background-image: url(data:image/svg+xml,%s); }
'''

def main(args):
	stations = None
	with open(FILENAME) as f:
		stations = json.load(f)
	stationIds = [s['id'] for s in stations]
	print('|'.join(stationIds))

	content = ''
	with open(STYLESHEET) as f:
		content = f.read()
	matches = MASK.findall(content)
	with open(OUTPUT, 'w') as out:
		for k,v in matches:
			print(k)
			i = base64.standard_b64decode(v)
			out.write(TEMPLATE % (k, urllib.parse.quote(i)))
	return 0

if __name__ == '__main__':
	import sys
	sys.exit(main(sys.argv))
