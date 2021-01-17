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


import csv
import numpy as np
from numpy import loadtxt
lon = []
lat = []
with open('liste-coordonnees.csv', 'r') as data:
    coord = csv.reader(data, delimiter= ',')
    for row in coord :
        lon = np.append(lon, float(row[0]))
        lat = np.append(lat, float(row[1]))
data.close()

import folium
c = (lon[0], lat[1])

fmap = folium.Map(location=c, title = 'carte', zoom_start = 6)
for i in range(len(lon)):
    c = (lon[i], lat[i])
    folium.CircleMarker(c, color='green', radius = 5, fill = True).add_to(fmap)

graph = loadtxt("resuGraph.dat", dtype=int)
for x in range(graph.shape[0]):
    c1 = (lon[graph[x,0]], lat[graph[x,0]])
    c2 = (lon[graph[x,1]], lat[graph[x,1]])
    c = [c1,c2]
    folium.PolyLine(c, color="blue", weight=2.5, opacity=0.8).add_to(fmap)

fmap.save('via.html')
