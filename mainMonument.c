#include "monumentReader.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char ** argv) {

  ListOfMonuments* monuments;
  monuments = MonumentsReader();
  float distance;
  float distance2;
  float distance3;
  graphe* g = creer_graphe((monuments->nbMonument*(monuments->nbMonument-1))/2);
  graphe* g1 = creer_graphe((monuments->nbMonument*(monuments->nbMonument-1))/2);
  /*
  for(int i=0; i<monuments->nbMonument; i++){
    printf("%s %f %f\n", monuments->name[i], monuments->lon[i], monuments->lat[i]);
  }
  */
  distance = kruskal_algo(monuments, g);
  distance2 = prim_algo(monuments, g1);
  distance3 = boruvka_algo(monuments, g1);
  printf("distance = %f\n", distance);
  printf("distance = %f\n", distance2);
  printf("distance = %f\n", distance3);
  saveGraph(g1);
  saveListOfMonuments(monuments);
  free(g->tab_sommet);
  free(g);
  freeListOfMonument(monuments);
  return 0;
}
