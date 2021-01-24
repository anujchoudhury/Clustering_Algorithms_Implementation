import time
start_time = time.time()
import numpy as np,sys
import heapq
from operator import itemgetter
from queue import PriorityQueue
from heapdict import heapdict
import sys
from sklearn.neighbors import NearestNeighbors

file_handle = open(sys.argv[3], 'r')
lines_list = (file_handle.readlines())
my_data = [[float(val) for val in line.split()] for line in lines_list]
np_data=np.array(my_data,dtype="float")

# files and numbers read, now what ?
epsilon= float(sys.argv[1])#150000#sys.argv[1]
min_points=int(sys.argv[2])#10#sys.argv[2]

# all data received

neigh = NearestNeighbors(n_neighbors=min_points, radius=epsilon,algorithm='kd_tree',metric='euclidean',p=2)
neigh.fit(np_data)


def neighbours(index):
    np_data_index=np_data[index]
    np_data_index=np_data_index.reshape(1,-1)
    points_dist,neighbours_list=neigh.radius_neighbors(np_data_index,float(epsilon),return_distance=True)
    core_dist=-1
    points_dist=points_dist[0]
    neighbours_list=neighbours_list[0]
    if(len(neighbours_list)<min_points):
        core_dist=-1
        return (neighbours_list,core_dist)
    else:
        sorted_points=sorted(points_dist)
        a1=sorted_points[min_points-1]
        return (neighbours_list,a1)
    


def Update(neighbour_array_tuple,index,Seeds):
    core_dist=neighbour_array_tuple[1]
    for point_index in neighbour_array_tuple[0]:
        if(is_processed[point_index]==0):
            new_reach_dist=max(core_dist,np.linalg.norm(np_data[index]-np_data[point_index]))
            if(new_reach_dist>epsilon):
                continue            
            if(reachability_dist[point_index]<0):
                reachability_dist[point_index]=new_reach_dist
                Seeds[point_index]=new_reach_dist
            elif(new_reach_dist<reachability_dist[point_index]):
                reachability_dist[point_index]=new_reach_dist
                Seeds[point_index]=new_reach_dist

clusters=0
labels=[0]*len(np_data)
is_processed=[0]*len(np_data)
reachability_dist=[-1]*len(np_data)
core_dist_array=[-1]*len(np_data)
ordered_list_ans=[]


for i in range(len(np_data)):
    # print(i,end=' ')
    # print("--- %s seconds ---" % (time.time() - start_time))
    # sys.stdout.flush()

    if(is_processed[i]==1):
        continue
    else:
        is_processed[i]=1
        reachability_dist[i]=-1
        ordered_list_ans.append(i)
        neighbour_array_tuple=neighbours(i)
        neighbour_array=neighbour_array_tuple[0]
        core_dist_p=neighbour_array_tuple[1]
        if(not core_dist_p==-1):
            Seeds=heapdict()
            Update(neighbour_array_tuple,i,Seeds)
            while(not len(Seeds)==0):
                a1tuple=Seeds.popitem()
                q=a1tuple[0]
                if(is_processed[q]==1):
                    print("errors")
                    continue
                is_processed[q]=1
                print(q,end=' ')
                sys.stdout.flush()
                ordered_list_ans.append(q)
                N_dash=neighbours(q)
                neighbours_dash=N_dash[0]
                core_dash=N_dash[1]
                if(core_dash!=-1):
                    Update(N_dash,q,Seeds)
# print("done")
N = len(reachability_dist)
x = range(N)
import matplotlib.pyplot as plt
width = 1/1.5
ans=[]
maxim=max(reachability_dist)*2
for p in ordered_list_ans:
    if(reachability_dist[p]==-1):
        ans.append(maxim)
    else:
        ans.append(reachability_dist[p])


fig, ax = plt.subplots()

# plt.bar(x, ans, width, color="blue")
ax.plot(x, ans, width, color="blue")
x45 = np.arange(0.0, N, 1)
y45 = 0*x45
ax.fill_between(x45, y45, ans, where=ans>y45, facecolor='green')
plt.show()
# print("--- %s seconds ---" % (time.time() - start_time))