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

ax = plt.axes(projection='3d')

smallerTime = []
for i in range(len(x)):
    smallerTime.append(min(x[i], y[i]))

# ax2 = plt.axes()
# ax2.scatter(smallerTime,z)
# ax2.set_xlabel('Time taken to calculate the smaller number')
# ax2.set_ylabel('Time saved by using parallel calculation')


ax.scatter(x,y,z, cmap='viridis')
ax.set_xlabel('Time to calculate first number')
ax.set_ylabel('Time to calculate second number')
ax.set_title('Time saved by using parallel over series for calculation times x and y')
plt.show()