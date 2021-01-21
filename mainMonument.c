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
  analyzer_t * time_analysis4 = analyzer_create();
  analyzer_t * time_analysis5 = analyzer_create();
  analyzer_t * time_analysis6 = analyzer_create();

  struct timespec before1, after1;
  clockid_t clk_id1 = CLOCK_REALTIME;

  struct timespec before2, after2;
  clockid_t clk_id2 = CLOCK_REALTIME;

  struct timespec before3, after3;
  clockid_t clk_id3 = CLOCK_REALTIME;

  struct timespec before4, after4;
  clockid_t clk_id4 = CLOCK_REALTIME;

  struct timespec before5, after5;
  clockid_t clk_id5 = CLOCK_REALTIME;

  struct timespec before6, after6;
  clockid_t clk_id6 = CLOCK_REALTIME;

  ListOfMonuments* monuments;
  monuments = MonumentsReader();
  graphe* g = creer_graphe((monuments->nbMonument*(monuments->nbMonument-1))/2);
  graphe* g2 = creer_graphe((monuments->nbMonument*(monuments->nbMonument-1))/2);
  graphe* g3 = creer_graphe((monuments->nbMonument*(monuments->nbMonument-1))/2);
  graphe* g4 = creer_graphe((monuments->nbMonument*(monuments->nbMonument-1))/2);
  graphe* g5 = creer_graphe((monuments->nbMonument*(monuments->nbMonument-1))/2);
  graphe* g6 = creer_graphe((monuments->nbMonument*(monuments->nbMonument-1))/2);
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
  /*
  printf("\t Kruskal Algo\n");
  clock_gettime(clk_id1, &before1);
	KruskalMST(graph, g);
  clock_gettime(clk_id1, &after1);
  analyzer_append(time_analysis1, after1.tv_nsec-before1.tv_nsec);
  fprintf(stderr,"Total cost: %Lf ns\n\n", get_total_cost(time_analysis1));

  printf("\t Boruvka Algo\n");
  clock_gettime(clk_id2, &before2);
  boruvkaMST(graph, g2);
  clock_gettime(clk_id2, &after2);
  analyzer_append(time_analysis2, after2.tv_nsec-before2.tv_nsec);
  fprintf(stderr,"Total cost: %Lf ns\n\n", get_total_cost(time_analysis2));

  printf("\t Prim Algo\n");
  clock_gettime(clk_id3, &before3);
  primMST(graph, g3);
  clock_gettime(clk_id3, &after3);
  analyzer_append(time_analysis3, after3.tv_nsec-before3.tv_nsec);
  fprintf(stderr,"Total cost: %Lf ns\n\n", get_total_cost(time_analysis3));
  */
  printf("\t Mon Algo\n");
  clock_gettime(clk_id4, &before4);
  hbMST(graph, g4);
  clock_gettime(clk_id4, &after4);
  analyzer_append(time_analysis4, after4.tv_nsec-before4.tv_nsec);
  fprintf(stderr,"Total cost: %Lf ns\n\n", get_total_cost(time_analysis4));
  /*
  printf("\t Mon3 Algo\n");
  clock_gettime(clk_id6, &before6);
  hb3MST(graph, g6);
  clock_gettime(clk_id6, &after6);
  analyzer_append(time_analysis6, after6.tv_nsec-before6.tv_nsec);
  fprintf(stderr,"Total cost: %Lf ns\n\n", get_total_cost(time_analysis6));
  */
  saveGraph(g4);
  saveListOfMonuments(monuments);
  analyzer_destroy(time_analysis1);
  analyzer_destroy(time_analysis2);
  analyzer_destroy(time_analysis3);
  analyzer_destroy(time_analysis4);
  analyzer_destroy(time_analysis5);
  analyzer_destroy(time_analysis6);
  free(g->tab_sommet);
  free(g2->tab_sommet);
  free(g3->tab_sommet);
  free(g4->tab_sommet);
  free(g5->tab_sommet);
  free(g6->tab_sommet);
  free(g);
  free(g2);
  free(g3);
  free(g4);
  free(g5);
  free(g6);
  free(graph->edge);
  free(graph);
	return 0;
}
