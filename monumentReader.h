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

ListOfMonuments* createMonuments(int number);
ListOfMonuments* MonumentsReader();
void freeListOfMonument(ListOfMonuments * monuments);

#endif
