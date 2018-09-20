import matplotlib.pyplot as plt
import numpy as np

file_handle = open("optics.txt", 'r')
lines_list = (file_handle.readlines())
my_data = [[float(val) for val in line.split()] for line in lines_list]
np_data=np.array(my_data,dtype="float")
y=np_data[:,0]
ans=y
width=2/3
N=len(y)
x = range(len(y))
fig, ax = plt.subplots()
ax.plot(x, y, width, color="blue")
x45 = np.arange(0.0, N, 1)
y45 = 0*x45
ax.fill_between(x45, y45, ans, where=ans>y45, facecolor='green')

# plt.plot(x, y)
plt.xlabel("Cluster-order of the objects")
plt.ylabel("Reachability distance")
plt.title("Reachability Distance Plot")
plt.show()