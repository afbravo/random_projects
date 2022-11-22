import random
import time
import cursor
import os

print(os.get_terminal_size())

cursor.hide()

title = "Downloading Python 3.6.1"
scale = 1
progress = "#"
missing = "."

for i in range(0, 101):
    a = int(i/scale)
    b = int(100/scale) - a
    toPrint = "{} [{}{}] {}%".format(title, progress*a, missing*b, i)
    print(toPrint, end="\r")
    time.sleep(0.1)
print(toPrint)
print(len(toPrint))

cursor.show()

