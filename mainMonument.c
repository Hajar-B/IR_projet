#include "monumentReader.h"
#include "analyzer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main()
{
  analyzer_t * time_analysis1 = analyzer_create();
  analyzer_t * time_analysis2 = analyzer_create();
  analyzer_t * time_analysis3 = analyzer_create();

  struct timespec before1, after1;
  clockid_t clk_id1 = CLOCK_REALTIME;

  struct timespec before2, after2;
  clockid_t clk_id2 = CLOCK_REALTIME;

  struct timespec before3, after3;
  clockid_t clk_id3 = CLOCK_REALTIME;

  ListOfMonuments* monuments;
  monuments = MonumentsReader();
  graphe* g = creer_graphe((monuments->nbMonument*(monuments->nbMonument-1))/2);
  graphe* g2 = creer_graphe((monuments->nbMonument*(monuments->nbMonument-1))/2);
  graphe* g3 = creer_graphe((monuments->nbMonument*(monuments->nbMonument-1))/2);
  printf("nbarrete = %d\n", (monuments->nbMonument*(monuments->nbMonument-1))/2);
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

  clock_gettime(clk_id1, &before1);
	KruskalMST(graph, g);
  clock_gettime(clk_id1, &after1);
  analyzer_append(time_analysis1, after1.tv_nsec-before1.tv_nsec);
  fprintf(stderr,"Total cost: %Lf\n\n", get_total_cost(time_analysis1));

  clock_gettime(clk_id2, &before2);
  boruvkaMST(graph, g2);
  clock_gettime(clk_id2, &after2);
  analyzer_append(time_analysis2, after2.tv_nsec-before2.tv_nsec);
  fprintf(stderr,"Total cost: %Lf\n\n", get_total_cost(time_analysis2));

  clock_gettime(clk_id3, &before3);
  hbMST(graph, g3);
  clock_gettime(clk_id3, &after3);
  analyzer_append(time_analysis3, after3.tv_nsec-before3.tv_nsec);
  fprintf(stderr,"Total cost: %Lf\n", get_total_cost(time_analysis3));

  saveGraph(g3);
  saveListOfMonuments(monuments);

	return 0;
}
