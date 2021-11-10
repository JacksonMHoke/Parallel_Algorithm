import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits import mplot3d
import pandas as pd

fig = plt.figure()

df = pd.read_csv('time.csv')

x = df['Num1_Time'].to_list()
y = df['Num2_Time'].to_list()
parTime = df['Parallel_Time']
serTime = df['Series_Time']
z = []

for i in range(len(serTime)):
    z.append(serTime[i]-parTime[i])

fig = plt.figure()
ax = plt.axes(projection='3d')

smallerTime = []
for i in range(len(x)):
    smallerTime.append(min(x[i], y[i]))

# ax.scatter(smallerTime,z)
ax.scatter(x,y,z)

plt.show()