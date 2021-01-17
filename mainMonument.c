#include "monumentReader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  ListOfMonuments* monuments;
  monuments = MonumentsReader();
  graphe* g = creer_graphe((monuments->nbMonument*(monuments->nbMonument-1))/2);
  graphe* g2 = creer_graphe((monuments->nbMonument*(monuments->nbMonument-1))/2);
  /*
  for(int i=0; i<monuments->nbMonument; i++){
    printf("%s %f %f\n", monuments->name[i], monuments->lon[i], monuments->lat[i]);
  }
  */

	int V = monuments->nbMonument;
	int E = (monuments->nbMonument*(monuments->nbMonument-1))/2;
	Graph* graph = createGraph(V, E);
  int cpt=0;
  for(int i=0; i<V; i++){
    for(int j=i+1; j<V; j++){
      float dist = distance(monuments->lon[i], monuments->lat[i], monuments->lon[j], monuments->lat[j]);
      graph->edge[cpt].src = i;
      graph->edge[cpt].dest = j;
      graph->edge[cpt].weight = dist;
      cpt++;
    }
  }
	KruskalMST(graph, g);
  boruvkaMST(graph, g2);
  saveGraph(g2);
  saveListOfMonuments(monuments);

	return 0;
}
