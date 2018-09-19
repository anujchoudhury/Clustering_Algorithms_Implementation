# generate random points in a circle

import numpy as np 
import pylab as plt 
import random,math

num_samples = 20
theta = np.linspace(0, 2*np.pi, num_samples)
a, b = 1 * np.cos(theta), 1 * np.sin(theta)







# generate the points
theta_centre = np.linspace(0, 2*np.pi, 5)[:-1]
cos_centre,sin_centre=300*np.cos(theta_centre),np.sin(theta_centre)*300

num_samples = 5000
r=20
rho = np.sqrt(np.random.uniform(0, 1, num_samples))
phi = np.random.uniform(0, 2*np.pi, num_samples)

x1 = np.empty(0)
y1 = np.empty(0)
for i in range(len(cos_centre)):
	x=cos_centre[i]+r*rho * np.cos(phi)
	y=sin_centre[i]+r*rho * np.sin(phi)
	x1=np.concatenate((x1,x),axis=None)
	y1=np.concatenate((y1,y),axis=None)
	print(i)







# generate the points
theta_centre = (np.linspace(0, 2*np.pi, 5)+(np.pi/4))[:-1]
cos_centre,sin_centre=700*np.cos(theta_centre),np.sin(theta_centre)*700

num_samples = 5000
r=20
rho = np.sqrt(np.random.uniform(0, 1, num_samples))
phi = np.random.normal(0, 2*np.pi, num_samples)

x2 = np.empty(0)
y2 = np.empty(0)
for i in range(len(cos_centre)):
	x=cos_centre[i]+r*rho * np.cos(phi)
	y=sin_centre[i]+r*rho * np.sin(phi)
	x2=np.concatenate((x2,x),axis=None)
	y2=np.concatenate((y2,y),axis=None)
	print(i)




# make a simple unit circle 

num_samples = 4000
r=250
rho = np.sqrt(np.random.uniform(0, 1, num_samples))
phi = np.random.normal(0, 2*np.pi, num_samples)

num_samples = 6001
theta = (np.linspace(0, 2*np.pi, num_samples)+(np.pi/8))[:-1]
x3, y3 = 12000+100 * np.cos(theta), 100 * np.sin(theta)+10000
x4, y4 = 12000+200 * np.cos(theta), 200 * np.sin(theta)+10000
x=12000+r*rho * np.cos(phi)
y=10000+r*rho * np.sin(phi)
x3=np.concatenate((x3,x),axis=None)
y3=np.concatenate((y3,y),axis=None)
x10=12000+r*rho * np.cos(phi)
y10=10000+r*rho * np.sin(phi)




num_samples = 4000
r=1200
rho = np.sqrt(np.random.uniform(0, 1, num_samples))
phi = np.random.normal(0, 2*np.pi, num_samples)
x5, y5 = 6000+1000 * np.cos(theta), 1000 * np.sin(theta)+6000
x6, y6 = 6000+500 * np.cos(theta), 500 * np.sin(theta)+6000
# x=6000+r*rho * np.cos(phi)
# y=6000+r*rho * np.sin(phi)
# x5=np.concatenate((x5,x),axis=None)
# y5=np.concatenate((y5,y),axis=None)
x9=6000+r*rho * np.cos(phi)
y9=6000+r*rho * np.sin(phi)











num_samples=100
r=800
rho = np.sqrt(np.random.uniform(0, 1, num_samples))
phi = np.random.uniform(0, 2*np.pi, num_samples)

x7 = r*rho * np.cos(phi)
y7 = r*rho * np.sin(phi)



# generate the points
theta_centre = np.linspace(0, 2*np.pi, 8)[:-1]
cos_centre,sin_centre=500*np.cos(theta_centre),np.sin(theta_centre)*500

num_samples = 4000
r=75
rho = np.sqrt(np.random.uniform(0, 1, num_samples))
phi = np.random.uniform(0, 2*np.pi, num_samples)

x8 = np.empty(0)
y8 = np.empty(0)
for i in range(len(cos_centre)):
	x=cos_centre[i]+r*rho * np.cos(phi)+10000
	y=sin_centre[i]+r*rho * np.sin(phi)
	x8=np.concatenate((x8,x),axis=None)
	y8=np.concatenate((y8,y),axis=None)
	print(i)



















a=list(zip(x1,y1))+list(zip(x2,y2))+list(zip(x3,y3))+list(zip(x4,y4))+list(zip(x5,y5))+list(zip(x6,y6))+list(zip(x7,y7))+list(zip(x8,y8))+list(zip(x9,y9))+list(zip(x10,y10))
p=list(map(list, zip(*a)))
# plt.plot(x, y, marker='.', markersize=2, linestyle='None', label='Samples')

plt.plot(x1, y1, marker='.', markersize=3, linestyle='None', label='Samples')
plt.plot(x2, y2, marker='.', markersize=3, linestyle='None', label='Samples')
plt.plot(x9, y9, marker='.', markersize=3, linestyle='None', label='Samples')
plt.plot(x10, y10, marker='.', markersize=3, linestyle='None', label='Samples')
plt.plot(x3, y3, marker='.', markersize=3, linestyle='None', label='Samples')
plt.plot(x4, y4, marker='.', markersize=3, linestyle='None', label='Samples')
plt.plot(x5, y5, marker='.', markersize=3, linestyle='None', label='Samples')
plt.plot(x6, y6, marker='.', markersize=3, linestyle='None', label='Samples')
plt.plot(x7, y7, marker='.', markersize=3, linestyle='None', label='Samples')
plt.plot(x8, y8, marker='.', markersize=3, linestyle='None', label='Samples')

file_handle = open("centres_kmeans.txt", 'r')
lines_list = (file_handle.readlines())
my_data = [[float(val) for val in line.split()] for line in lines_list]
np_data=np.array(my_data,dtype="float")
plt.plot(np_data[:,0], np_data[:,1], color='fuchsia',marker='o', markersize=6, linestyle='None', label='Samples')



plt.grid()


with open('your_file_1.txt', 'w') as f:
    for item in a:
        f.write(str(item[0])+" "+str(item[1])+"\n")

plt.show(block=True)
f.close()