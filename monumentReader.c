#include "monumentReader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// *****************************************************************************
ListOfMonuments* createMonuments(int nbMonument){
    int i;
    ListOfMonuments* monument = malloc(sizeof(ListOfMonuments));
    monument->nbMonument = nbMonument;
    monument->name = malloc(monument->nbMonument*sizeof(char*));
    for(i = 0; i < monument->nbMonument; i++)
      monument->name[i] = (char*) malloc(100*sizeof(char));
    monument->lon  = malloc(monument->nbMonument*sizeof(float));
    monument->lat  = malloc(monument->nbMonument*sizeof(float));

    return monument;
}

// *****************************************************************************
int countMonuments(FILE* inputFile){
  int number = 0, myMon , i;
  char line[512];
  const char s[2] = ",";
  char *token;

  while(fgets(line, 512, inputFile) != NULL){
    number++;
  }
  fseek(inputFile, 0, SEEK_SET);
  printf("number of monument = %d\n", number);

  return number;
}

// *****************************************************************************
void loadListOfMonuments(FILE* inputFile, ListOfMonuments* monuments){
  // Reading/Saving data
  int index=0;
  int i;
  char line[512];
  const char s[2] = ",";
  char *token;
  char monName[100];

  while(fgets(line, 512, inputFile) != NULL){
    token = strtok(line, s);
    for(i=0; i<2;  i++) token = strtok(NULL, s);
    strncpy(monName, token, 100);
    strncpy(monuments->name[index], monName, 100);

    for(i=0; i<1;  i++) token = strtok(NULL, s);
    monuments->lon[index] = atof(token);

    for(i=0; i<1;  i++) token = strtok(NULL, s);
    monuments->lat[index] = atof(token);

    index++;
  }

}

// *****************************************************************************
ListOfMonuments* MonumentsReader(){
  /* READING cities with population greater than or equal to 'popMin' */
  printf("== Reading nationaux monuments from 'liste-coordonnees-gps-des-monuments.csv' ==\n");

  FILE* inputFile = NULL;
  if( (inputFile = fopen("liste-coordonnees-gps-des-monuments.csv", "r")) == NULL){
    perror("Could not open file citiesList.csv");
    exit(-1);
  }
  ListOfMonuments* monuments = createMonuments(countMonuments(inputFile));
  loadListOfMonuments(inputFile, monuments);

  fclose(inputFile);
  return monuments;
}

// *****************************************************************************
void freeListOfMonument(ListOfMonuments * monuments){
  free(monuments->name);
  free(monuments->lon);
  free(monuments->lat);
  free(monuments);
}

// *****************************************************************************
void saveGraph(graphe * g){
  FILE* fileOut = NULL;
  fileOut = fopen("resuGraph.dat", "w");
  for(int i=0; i<g->nb_sommet-1; i=i+2){
    fprintf(fileOut, "%i %i\n", g->tab_sommet[i], g->tab_sommet[i+1]);
  }
  fclose(fileOut);
}

// *****************************************************************************
void saveListOfMonuments(ListOfMonuments* monuments){
  FILE* outputFile = NULL;
  if( (outputFile = fopen("resuMonument.dat", "w")) == NULL){
    perror("Could not open file resuCities.dat");
    exit(-1);
  }

  for(int i=0; i<monuments->nbMonument; i++)
    fprintf(outputFile, "%f %f\n", monuments->lon[i], monuments->lat[i]);
  fclose(outputFile);
}

// *****************************************************************************
graphe* creer_graphe(int n){
  graphe* g = malloc(sizeof(graphe));
  g->nb_sommet=0;
  g->tab_sommet = malloc(n*sizeof(int));
  return g;
}

// *****************************************************************************
float distance(float lon1, float lat1, float lon2, float lat2){
  float distance, val;
  val = 3.14159265/180;
  distance = 6371 * acos(sin(lat1*val) * sin(lat2*val) + cos(lon1*val - lon2*val) * cos(lat1*val) * cos(lat2*val));
  return distance;
}

// *****************************************************************************
Graph* createGraph(int V, int E)
{
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	graph->V = V;
	graph->E = E;
	graph->edge = (Edge*)malloc(E*sizeof(Edge));
	return graph;
}

int find(subset subsets[], int i){
	if (subsets[i].parent != i)
		subsets[i].parent	= find(subsets, subsets[i].parent);
	return subsets[i].parent;
}

void Union(subset subsets[], int x, int y){
	int xroot = find(subsets, x);
	int yroot = find(subsets, y);

	if (subsets[xroot].rank < subsets[yroot].rank)
		subsets[xroot].parent = yroot;
	else if (subsets[xroot].rank > subsets[yroot].rank)
		subsets[yroot].parent = xroot;
	else{
		subsets[yroot].parent = xroot;
		subsets[xroot].rank++;
	}
}

int myComp(const void* a, const void* b){
	Edge* a1 = (Edge*)a;
	Edge* b1 = (Edge*)b;
	return a1->weight > b1->weight;
}

void KruskalMST(Graph* graph, graphe* g)
{
	int V = graph->V;
	Edge result[V];
	int e = 0;
	int i = 0;

	qsort(graph->edge, graph->E, sizeof(graph->edge[0]), myComp);

	subset* subsets	= (subset*)malloc(V * sizeof(subset));

	for (int v = 0; v < V; ++v) {
		subsets[v].parent = v;
		subsets[v].rank = 0;
	}

	while (e < V - 1 && i < graph->E) {
		Edge next_edge = graph->edge[i++];

		int x = find(subsets, next_edge.src);
		int y = find(subsets, next_edge.dest);

		if (x != y) {
			result[e++] = next_edge;
			Union(subsets, x, y);
		}
	}
	//printf("Following are the edges in the constructed MST\n");
	float minimumCost = 0;
	for (i = 0; i < e; ++i)
	{
		//printf("%d -- %d == %f\n", result[i].src, result[i].dest, result[i].weight);
		minimumCost += result[i].weight;
		g->tab_sommet[g->nb_sommet] = result[i].src;
		g->nb_sommet++;
		g->tab_sommet[g->nb_sommet] = result[i].dest;
		g->nb_sommet++;
	}
	printf("Minimum Cost Spanning tree : %f\n",minimumCost);
	return;
}

void boruvkaMST(Graph* graph, graphe* g)
{
	int V = graph->V, E = graph->E;
	Edge *edge = graph->edge;

	subset subsets[V];
	int cheapest[V];

	for (int v = 0; v < V; ++v)
	{
		subsets[v].parent = v;
		subsets[v].rank = 0;
		cheapest[v] = -1;
	}

	int numTrees = V;
	float MSTweight = 0;
	while (numTrees > 1)
	{
		for (int v = 0; v < V; ++v){
			cheapest[v] = -1;
		}

		for (int i=0; i<E; i++)
		{
			int set1 = find(subsets, edge[i].src);
			int set2 = find(subsets, edge[i].dest);
			if (set1 == set2){
				continue;
			}
			else{
				if (cheapest[set1] == -1 || edge[cheapest[set1]].weight > edge[i].weight){
					cheapest[set1] = i;
				}
				if (cheapest[set2] == -1 || edge[cheapest[set2]].weight > edge[i].weight){
					cheapest[set2] = i;
				}
			}
		}
		for (int i=0; i<V; i++){
			if (cheapest[i] != -1){
				int set1 = find(subsets, edge[cheapest[i]].src);
				int set2 = find(subsets, edge[cheapest[i]].dest);
				if (set1 == set2)
					continue;
				MSTweight += edge[cheapest[i]].weight;
				//printf("Edge %d-%d included in MST\n", edge[cheapest[i]].src, edge[cheapest[i]].dest);
				g->tab_sommet[g->nb_sommet] = edge[cheapest[i]].src;
				g->nb_sommet++;
				g->tab_sommet[g->nb_sommet] = edge[cheapest[i]].dest;
				g->nb_sommet++;
				Union(subsets, set1, set2);
				numTrees--;
			}
		}
	}

	printf("Weight of MST is %f\n", MSTweight);
	return;
}
