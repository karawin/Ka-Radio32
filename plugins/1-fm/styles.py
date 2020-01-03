#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import urllib.request
import urllib.parse
import re
import base64

URL = 'https://www.1.fm/less/style.css'
OUTPUT = 'symbols.svg'

MASK = re.compile(r'\.svg-([^{]*?)\s*\{.*?background(?:-image)\s*:url\(data:image\/svg\+xml(;base64)?,([^}]*)\)', re.DOTALL)
# .onefmlogo
MASK2 = re.compile(r'<svg.*viewBox=\"([^\"]*)[^>]*>(.*)<\/svg>', re.DOTALL)
SYMBOL_START_PATTERN = '<symbol id="icon-%s" viewBox="%s">\n'
SYMBOL_END_PATTERN = '</symbol>\n'
PREAMBLE = '''\
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE svg PUBLIC "-//W3C//DTD SVG 1.1//EN" "http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd">
<svg xmlns="http://www.w3.org/2000/svg">
'''

def main(args):
	try:
		with urllib.request.urlopen(URL) as req:
			symbols = MASK.findall(str(req.read(), 'utf-8'))

			with open(OUTPUT, 'w') as f:
				f.write(PREAMBLE)
				print('%d items' % len(symbols))
				i = 0
				for k, w, v in symbols:
					warning = '\033[36mBase64\033[0m' if w else ''
					print('%2d:%s %s' % (i, k, warning))
					content = None
					if w:
						decodedBytes = base64.urlsafe_b64decode(v)
						content = str(decodedBytes, "utf-8")
					else:
						content = urllib.parse.unquote(v)
					matches = MASK2.search(content)
					if matches:
						f.write(SYMBOL_START_PATTERN % (k, matches.group(1).strip()))
						f.write(matches.group(2).strip())
						f.write('\n')
						f.write(SYMBOL_END_PATTERN)
					else:
						print(content)
						print('\033[31mFailed\033[0m')
					i += 1
				f.write('</svg>\n')
			return 0
	except  urllib.error.HTTPError as e:
		print(e.code)
		print(e.read())

if __name__ == '__main__':
	import sys
	sys.exit(main(sys.argv))
