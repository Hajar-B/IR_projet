#include "monumentReader.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char ** argv) {

  ListOfMonuments* monuments;
  monuments = MonumentsReader();

  for(int i=0; i<monuments->nbMonument; i++){
    printf("%s %f %f\n", monuments->name[i], monuments->lon[i], monuments->lat[i]);
  }

  saveGraph(monuments);
  saveListOfMonuments(monuments);
  freeListOfMonument(monuments);
  return 0;
}
