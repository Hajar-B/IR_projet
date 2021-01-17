#ifndef MONUMENT_READER
#define MONUMENT_READER

typedef struct ListOfMonuments ListOfMonuments;

struct ListOfMonuments
{
  int nbMonument;
  char** name;
  float* lon;
  float* lat;
};

typedef struct Edge Edge;

struct Edge {
	int src, dest;
  float weight;
};

typedef struct Graph Graph;

struct Graph {
	int V, E;
	Edge* edge;
};

typedef struct subset subset;

struct subset {
	int parent;
	int rank;
};

typedef struct graphe graphe;

struct graphe{
  int nb_sommet;
  int* tab_sommet;
};

ListOfMonuments* createMonuments(int number);
ListOfMonuments* MonumentsReader();
void freeListOfMonument(ListOfMonuments * monuments);
void saveGraph(graphe * g);
void saveListOfMonuments(ListOfMonuments* monuments);

graphe* creer_graphe(int n);
float distance(float lon1, float lat1, float lon2, float lat2);

Graph* createGraph(int V, int E);
int find(subset subsets[], int i);
void Union(subset subsets[], int x, int y);
int myComp(const void* a, const void* b);
void KruskalMST(Graph* graph, graphe* g);
void boruvkaMST(Graph* graph, graphe* g);

#endif
