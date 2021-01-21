#include"analyzer.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

analyzer_t * analyzer_create(){
  analyzer_t * res = (analyzer_t *) malloc( sizeof(analyzer_t) );
  res->capacity = 4;
  res->cost = (double *) malloc( sizeof(double) * res->capacity );
  res->cumulative_cost = (long double *) malloc( sizeof(long double) * res->capacity );
  res->cumulative_square = 0.;
  res->size = 0;
  return res;
}

void analyzer_destroy(analyzer_t * a){
  if( a != NULL ){
    free( a->cost );
    free( a->cumulative_cost );
    free( a );
  }
}

void analyzer_append(analyzer_t * a, double x){
  if( a!=NULL ){
    if( a->size >= (a->capacity * 3)/4 ){
      a->capacity *= 2;
      a->cost = (double *) realloc(a->cost, sizeof(double) * a->capacity*2);
      a->cumulative_cost = (long double *) realloc(a->cumulative_cost, sizeof(long double) * a->capacity*2);
    }
    a->cost[a->size] = x;
    a->cumulative_cost[a->size] = (a->size) ? a->cumulative_cost[a->size-1]+x : x;
    a->cumulative_square += x*x;
    a->size++;
  }
}

long double get_total_cost(analyzer_t * a){
  return (a->size) ? a->cumulative_cost[a->size-1] : -1;
}
