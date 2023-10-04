
f = open('res.txt')
a = []
for line in f:
    if line[-1] == '\n':
        line = line[0:-1]
    if line[-1] == ' ':
        line = line[0:-1]
    line = line.split(' ')
    print(line)
    a.append([float(x) for x in line])

import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle

fig, ax = plt.subplots(1,1)
ax.set_xlim([0,100])
ax.set_ylim([0,100])
for i in range(0, len(a), 3):
    ax.plot([a[i][0], a[i][2]], [a[i][1], a[i][3]])
    for j in range(len(a[i+1])):
        ax.add_patch(Rectangle((a[i+1][j], a[i+2][j]), 1, 1, fc="yellow", fill=True))

ax.vlines([x for x in range(100)], 0, 100)
ax.hlines([x for x in range(100)], 0, 100)
F = plt.gcf()
F.set_size_inches(50, 50, forward=True)
plt.savefig('res.pdf')
plt.show()