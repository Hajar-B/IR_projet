#include "monumentReader.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <limits.h>

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
// *****************************************************************************
float distance(float lon1, float lat1, float lon2, float lat2){
  float distance, val;
  val = 3.14159265/180;
  distance = 6371 * acos(sin(lat1*val) * sin(lat2*val) + cos(lon1*val - lon2*val) * cos(lat1*val) * cos(lat2*val));
  return distance;
}

// *****************************************************************************
arete* creer_arete(int monument_d, int monument_a, float lon1, float lat1, float lon2, float lat2){
  arete* a = malloc(sizeof(arete*));
  a->Monument_D = monument_d;
  a->Monument_A = monument_a;
  a->distance = distance(lon1, lat1, lon2, lat2);
  return a;
}

// *****************************************************************************
tas* creer_tas(int capacite_max){
  tas* t = malloc(sizeof(tas));
  t->nb_element = 0;
  t->capacite_max = capacite_max;
  t->tab = malloc(capacite_max*sizeof(arete));
  return t;
}

// *****************************************************************************
graphe* creer_graphe(int n){
  graphe* g = malloc(sizeof(graphe));
  g->nb_sommet=0;
  g->tab_sommet = malloc(n*sizeof(int));
  return g;
}

// *****************************************************************************
void entasser(tas* t, int pos){
  while(t->tab[parent(pos)].distance > t->tab[pos].distance){
    echanger(t, parent(pos), pos);
    pos = parent(pos);
  }
}

// *****************************************************************************
int parent(int pos){
  return (pos-1)/2;
}

// *****************************************************************************
void echanger(tas* t, int pos1, int pos2){
  arete tmp;

  tmp = (t->tab[pos1]);
  t->tab[pos1] = t->tab[pos2];
  t->tab[pos2] = tmp;
}

// *****************************************************************************
void inserer_tas(tas* t, arete* a){
  if(t->nb_element == t->capacite_max){
    printf("tableau plein\n");
    return;
  }
  t->tab[t->nb_element] = *a;
  entasser(t, t->nb_element);
  t->nb_element++;
}

// *****************************************************************************
int filsDroit(int pos){
  return 2*pos+2;
}

// *****************************************************************************
int filsGauche(int pos){
  return 2*pos+1;
}

// *****************************************************************************
int plusPetitEnfant(tas* t, int pos){
  if(t->tab[filsGauche(pos)].distance < t->tab[filsDroit(pos)].distance)
    return filsGauche(pos);
  return filsDroit(pos);
}

// *****************************************************************************
arete supprimer_tas(tas* t){
  int pos=0;
  int tmp=0;
  int continu=0;
  arete a = t->tab[0];
  echanger(t, 0, t->nb_element-1);

  while((pos < t->nb_element/2) && continu==0){
    if((t->tab[pos].distance > t->tab[plusPetitEnfant(t,pos)].distance) && (plusPetitEnfant(t,pos) < t->nb_element-1)){
      tmp = plusPetitEnfant(t,pos);
      echanger(t, pos, plusPetitEnfant(t,pos));
      pos = tmp;
    }
    else
      continu = 1;
  }
  t->nb_element--;
  return a;
}

// *****************************************************************************
int find(compressionC* p, int sommet){
  if(p[sommet].parent != sommet)
    p[sommet].parent = find(p, p[sommet].parent);
  return p[sommet].parent;
}

// *****************************************************************************
int union_find(arete a, compressionC* parent){
  int x = find(parent, a.Monument_D);
  int y = find(parent, a.Monument_A);
  if (x==y)
    return 0;
  if(parent[x].rank < parent[y].rank)
    parent[x].parent = y;
  else if (parent[x].rank > parent[y].rank)
    parent[y].parent = x;
  else{
    parent[y].parent = x;
    parent[x].rank++;
  }
  return 1;
}

// *****************************************************************************
float kruskal_algo(ListOfMonuments * monuments, graphe* g){
  tas* t = creer_tas((monuments->nbMonument*(monuments->nbMonument-1))/2);
  arete* a;
  arete tmp;
  float distance_total = 0;
  int ext;
  compressionC* tab = (compressionC*)malloc(monuments->nbMonument*sizeof(compressionC));

  for(int i=0; i<monuments->nbMonument; i++){
    tab[i].parent = i;
    tab[i].rank = 0;
    for(int j=i+1; j<monuments->nbMonument; j++){
      a = creer_arete(i,j,monuments->lon[i],monuments->lat[i], monuments->lon[j],monuments->lat[j]);
      inserer_tas(t,a);
    }
  }
  while(t->nb_element != 0){
    tmp = supprimer_tas(t);
    //printf("%f -- ", tmp.distance);
    ext = union_find(tmp, tab);
    if(ext == 1){
      distance_total = distance_total + tmp.distance;
      g->tab_sommet[g->nb_sommet] = tmp.Monument_D;
      g->nb_sommet++;
      g->tab_sommet[g->nb_sommet] = tmp.Monument_A;
      g->nb_sommet++;
    }
  }
  free(t->tab);
  free(t);

  return distance_total;
}


float boruvka_algo(ListOfMonuments * monuments, graphe* g){

  arete* a;
  int ext;
  compressionC* tab = (compressionC*)malloc(monuments->nbMonument*sizeof(compressionC));
  int cheapest[monuments->nbMonument];

  for(int i=0; i<monuments->nbMonument; i++){
    tab[i].parent = i;
    tab[i].rank = 0;
    cheapest[i] = -1;
  }

  int numTrees = monuments->nbMonument;
  float distance_total = 0;

  while (numTrees > 1){
    for(int i=0; i<monuments->nbMonument; i++){
      cheapest[i] = -1;
    }

    for(int i=0; i<monuments->nbMonument; i++){
      for(int j=i+1; j<monuments->nbMonument; j++){
        int x = find(tab, i);
        int y = find(tab, j);
        if(x == y){
          continue;
        }

        else{
          float dist1 = distance(monuments->lon[i], monuments->lat[i], monuments->lon[j], monuments->lat[j]);
          float dist2 = distance(monuments->lon[cheapest[x]], monuments->lat[cheapest[x]], monuments->lon[j], monuments->lat[j]);
          if(cheapest[x] == -1 || dist2 > dist1){
            cheapest[x] = i;
          }
          float dist3 = distance(monuments->lon[i], monuments->lat[i], monuments->lon[cheapest[y]], monuments->lat[cheapest[y]]);
          if(cheapest[y] == -1 || dist3 > dist1){
            cheapest[y] = i;
          }
        }
      }
    }

    for(int i=0; i<monuments->nbMonument; i++){
      for(int j=i+1; j<monuments->nbMonument; j++){
        if(cheapest[j] != -1){
          int x = find(tab, i);
          int y = find(tab, j);
          if(x == y)
            continue;

          float dist1 = distance(monuments->lon[i], monuments->lat[i], monuments->lon[j], monuments->lat[j]);
          a = creer_arete(i,j,monuments->lon[i],monuments->lat[i], monuments->lon[j],monuments->lat[j]);
          ext = union_find(*a, tab);
          if(ext == 1){
            distance_total = distance_total + dist1;
            g->tab_sommet[g->nb_sommet] = i;
            g->nb_sommet++;
            g->tab_sommet[g->nb_sommet] = j;
            g->nb_sommet++;
          }
          numTrees--;
        }
      }
    }
  }
  return distance_total;
}







int minKey(float* poids, int* visite, int taille){
  int min = INT_MAX;
  int min_index;
  for(int i = 0; i < taille; i++){
    if (visite[i]==0 && poids[i] < min)
      min = poids[i];
      min_index = i;
  }
  return min_index;
}
float prim_algo(ListOfMonuments * monuments, graphe * g){
  int * parent = (int*)malloc(monuments->nbMonument*sizeof(int));
  int * visite = (int*)malloc(monuments->nbMonument*sizeof(int));
  float * poids = (float*)malloc(monuments->nbMonument*sizeof(float));
  float distance_total = 0;

  for(int i=0; i<monuments->nbMonument; i++){
    poids[i] = INT_MAX;
    visite[i] = 0;
  }
  poids[0] = 0;
  parent[0] = -1;
  for(int j=0; j<monuments->nbMonument-1; j++){
    int v = minKey(poids, visite, monuments->nbMonument);
    visite[v] = 1;
    for(int k=j+1; k<monuments->nbMonument; k++){
      float dis = distance(monuments->lon[j], monuments->lat[j], monuments->lon[k], monuments->lat[k]);
      if(visite[k] == 0 && dis < poids[k]){
        parent[k] = v;
        poids[k] = poids[j+k];
        distance_total = distance_total + dis;
        g->tab_sommet[g->nb_sommet] = j;
        g->nb_sommet++;
        g->tab_sommet[g->nb_sommet] = k;
        g->nb_sommet++;
      }
    }
  }
  return distance_total;
}
