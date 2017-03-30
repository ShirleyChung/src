import xml.etree.ElementTree as ET
import os.path as OSPATH

fn = raw_input("input xml file:")

while (len(fn) <1 or not OSPATH.isfile(fn)):
	print "please specify a file to read."
	fn = raw_input(":")

tree = ET.parse(fn)
for item in tree.iter():
	print item