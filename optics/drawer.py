

import matplotlib.pyplot as plt
import pickle,numpy as np
width = 1/1.5
reachability_dist=pickle.load(open('Reachability_dist_unsorted','rb'))
ordered_list_ans=pickle.load(open('ordering','rb'))
N = len(reachability_dist)
x = range(N)
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