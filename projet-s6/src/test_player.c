#include <string.h>
#include "player2.c"
#define MAX_STRING 20

int main(){
  
  struct graph_t *graph = new__graph_t(11,'h');


  print_graph(graph, 'h');
  player2.color = 1;
 
  struct move_t mv = {.m = 40, .c = 0};
  coloriate__graph_t(graph, 0, mv);  
  mv = play(mv);
  coloriate__graph_t(graph, 0, mv);
  print_graph(graph, 'h');

  return 0;

}
