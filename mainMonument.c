#include "monumentReader.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char ** argv) {

  ListOfMonuments* monuments;
  monuments = MonumentsReader();
  float distance;
  graphe* g = creer_graphe((monuments->nbMonument*(monuments->nbMonument-1))/2);
  /*
  for(int i=0; i<monuments->nbMonument; i++){
    printf("%s %f %f\n", monuments->name[i], monuments->lon[i], monuments->lat[i]);
  }
  */
  distance = kruskal_algo(monuments, g);
  printf("distance = %f\n", distance);
  saveGraph(g);
  saveListOfMonuments(monuments);
  free(g->tab_sommet);
  free(g);
  freeListOfMonument(monuments);
  return 0;
}
