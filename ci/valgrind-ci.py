#!/usr/bin/python3

from ValgrindCI.parse import ValgrindData
from ValgrindCI.render import HTMLRenderer
from ValgrindCI.report import Report
import glob
import argparse

# Instantiate the parser
parser = argparse.ArgumentParser(description='Valgrind CI for hyperoute')

parser.add_argument('--sources-directory', type=str, dest="sources", help='Sources')
parser.add_argument('--valgrind-directory', type=str, dest="valgrind", help='Valgrind')

args = parser.parse_args()



data = ValgrindData()
data.set_source_dir(args.sources)

for file in glob.iglob(args.valgrind + '/valgrind_*.xml', recursive=True):
    print("file: " + file)
    data.parse(file)
    
print('---')

report = Report(data)
print(report.summary())

renderer = HTMLRenderer(data)
renderer.render('build/valgrind-html', lines_before=3, lines_after=3)

if data.get_num_errors() > 0:
    exit(1)

exit(0)