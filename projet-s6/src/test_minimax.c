#include <assert.h>
#include <stdio.h>
#define PASSED "\033[32;1mPASSED\033[0m"


void test___of__possible_moves(){

  printf("Test___of__possible_moves...");
  struct graph_t *G = new__graph_t(3, 'h');
  struct dynamic_array *p = get__possible_moves(G);
  assert(p->size == 6);
  
  struct move_t m = {.m = 5, .c = 0};
  coloriate__graph_t(G, 1, m);
  
  struct dynamic_array *p2 = get__possible_moves(G);
  assert(p2->size == 4);
  
  free__dynamic_array(p);
  free__dynamic_array(p2);
  free__graph_t(G);

  printf("%s\n",PASSED); 

}


int main(){

  test___of__possible_moves();

  return 0;

}
