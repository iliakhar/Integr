# -*- coding: cp1251 -*-
from math import fabs
import numpy

import matplotlib.pyplot as plt
from matplotlib.ticker import (MultipleLocator, FormatStrFormatter,
                               AutoMinorLocator)
import numpy as np
import csv

mas = []
mas1 = []
mas2 = []
x = []
y = []
size = 0
coordCount = 0
ind = -1
with open('../example.csv', 'r') as f:
    content = csv.reader(f, delimiter= ';')
    counter = 0
    for row in content:
      
      if(counter == coordCount):
          if(counter!=0):
            mas.append(mas1.copy())
            mas1.clear()
          counter = 0
          ind+=1
          coordCount = float(row[0])
      else:
          mas2.append(float(row[0]))
          mas2.append(float(row[1]))
          mas1.append(mas2.copy())
          mas2.clear()
          counter+=1

mas.append(mas1.copy())
mas1.clear()

fig, ax = plt.subplots(figsize=(8, 6))

intervStart = []
intervEnd = []    

with open('../integ.csv', 'r') as f:
    content = csv.reader(f, delimiter= ';')
    for row in content:
        intervStart.append(float(row[0]))
        intervEnd.append(float(row[1]))

ax.set_xlabel("x")
ax.set_ylabel("y")
ax.grid(which="major", linewidth=1.2)
ax.grid(which="minor", linestyle="--", color="gray", linewidth=0.5)

maxX = 0
maxY = 0
minX = 0
minY = 0

colorList = ["b-","r-","k-", "y-", "m-"]
colorFill = ["blue", "red","black", "yellow",]
for i in range(len(mas)):
    x=[]
    y=[]
    for j in range(len(mas[i])):
        x.append(mas[i][j][0])
        y.append(mas[i][j][1])
    if(i == 0):
        maxX = max(x)
        maxY = max(y)
        minX = min(x)
        minY = min(y)
    #if(i == 0):
        #ax.plot(x, y, "h-b", linestyle="--")
    #else:
    ax.plot(x, y, colorList[i%len(colorList)])
    for i in range(len(intervStart)):
        plt.fill_between(x, y, where = (numpy.asarray(x)>=intervStart[i]) & (numpy.asarray(x)<=intervEnd[i]), color = colorFill[i%len(colorFill)], alpha = .6)




#for i in range(len(intervX)-1):
    #plt.fill_between(intervX[i], intervY[i])



ax.set_ylim([minY - fabs(minY/10), maxY + maxY/10])
ax.set_xlim([minX - fabs(minX/10), maxX + maxX/10])
#ax.legend()


ax.xaxis.set_minor_locator(AutoMinorLocator())
ax.yaxis.set_minor_locator(AutoMinorLocator())
ax.tick_params(which='major', length=10, width=2)
ax.tick_params(which='minor', length=5, width=1)

plt.show()
