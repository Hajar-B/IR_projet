# Execution:
#   python visualisation.py

from matplotlib import pyplot
from numpy import loadtxt

# draw the monuments
monuments = loadtxt("resuMonument.dat", dtype=float, delimiter=" ")
pyplot.scatter(monuments[:,0], monuments[:,1], alpha=0.5);

# draw the graph
graph = loadtxt("resuGraph.dat", dtype=int)
print(graph.shape[0])
for x in range(graph.shape[0]):
  edge = [graph[x,0], graph[x,1]]
  pyplot.plot(monuments[edge,0], monuments[edge,1], 'b')

pyplot.xlabel('Longitude')
pyplot.ylabel('Latitude')

# save in a PNG file
pyplot.savefig('result.png')

# show the result
pyplot.show()
