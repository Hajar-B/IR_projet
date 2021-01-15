#include "monumentReader.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

void freeListOfMonument(ListOfMonuments * monuments){
  free(monuments->name);
  free(monuments->lon);
  free(monuments->lat);
  free(monuments);
}

void saveGraph(ListOfMonuments * monuments){
  FILE* fileOut = NULL;
  fileOut = fopen("resuGraph.dat", "w");
  for(int i=0; i<monuments->nbMonument; i++){
    for(int j=i; j<monuments->nbMonument; j++){
      fprintf(fileOut, "%i %i\n", i, j);
    }
  }
  fclose(fileOut);
}

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
