import sys
import time
import datetime

args = sys.argv
title = ""
if len(args) > 1:
    title = sys.argv[1]

'''
for i in range(100):
    print(title, i)
'''

ts = datetime.datetime.now()
print("begin at", ts)

time.sleep(5)

ts = datetime.datetime.now()
print("end at", ts)