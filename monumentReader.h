#ifndef CITIES_READER
#define CITIES_READER

typedef struct ListOfMonuments ListOfMonuments;

struct ListOfMonuments
{
  int nbMonument;
  char** name;
  float* lon;
  float* lat;
};

typedef struct arete arete;

struct arete{
  int Monument_D;   //monument de depart
  int Monument_A;   //monument d'arrivé
  float distance;   //distance entre les deux villes
};

typedef struct tas tas;

struct tas{
  int nb_element;   //nombre d'élément dans le tas
  int capacite_max; //nombre maximum d'élément dans le tas
  arete* tab;       //tableau
};

typedef struct graphe graphe;

struct graphe{
  int nb_sommet;
  int* tab_sommet;
};

typedef struct compressionC compressionC;

struct compressionC{
  int parent;
  int rank;
};

ListOfMonuments* createMonuments(int number);
ListOfMonuments* MonumentsReader();
void freeListOfMonument(ListOfMonuments * monuments);
void saveGraph(graphe * g);
void saveListOfMonuments(ListOfMonuments* monuments);

float distance(float lon1, float lat1, float lon2, float lat2);
arete* creer_arete(int monument_d, int monument_a, float lon1, float lat1, float lon2, float lat2);
tas* creer_tas(int capacite_max);
graphe* creer_graphe(int n);

void entasser(tas* t, int pos);
int parent(int pos);
void echanger(tas* t, int pos1, int pos2);
void inserer_tas(tas* t, arete* a);

int filsDroit(int pos);
int filsGauche(int pos);
int plusPetitEnfant(tas* t, int pos);
arete supprimer_tas(tas* t);

int find(compressionC* p, int sommet);
int union_find(arete a, compressionC* parent);

float kruskal_algo(ListOfMonuments * monuments, graphe* g);

#endif
