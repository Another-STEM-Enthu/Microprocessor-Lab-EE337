from matplotlib import pyplot as plt
import numpy as np

values = np.loadtxt("D:\\337 Projects\\Lab10\\capture2.txt", dtype=int)
#values = np.genfromtxt("D:\\337 Projects\\Lab10\\capture1.txt", dtype=str,encoding=None, delimiter=" ")
index = []

for i in range(0,len(values)):
    index.append(i)

plt.plot(index,values)
plt.show()