#include "graph_minimax1.h"
#include "graph_aux.h"

struct dynamic_array *neighbours(struct graph_t *graph, int position)
{
  struct dynamic_array *neighbours = empty__dynamic_array();
  
  for (int k = 0; k < graph->num_vertices; k++)
    if (gsl_spmatrix_get(graph->t, position, graph->num_vertices - k - 1) == 1)
      add__to_dynamic_array(neighbours, graph->num_vertices - k - 1);
  
  return neighbours;
}


int max_a_b(int a, int b)
{
  return (a >= b)? a: b;
}


int min_a_b(int a, int b)
{
  return (a <= b)? a: b;
}


struct dynamic_array *path_intesection(struct dynamic_array *p1, struct dynamic_array *p2)
{
  
  struct dynamic_array *inter = empty__dynamic_array();

  for(size_t i = 0; i < p1->size; i++)
    for(size_t j = 0; j < p2->size; j++)
      if(p1->array[i] == p2->array[j])
	add__to_dynamic_array(inter, p1->array[i]);

  return inter;

}


int path_score(struct dynamic_array *path, struct graph_t *G)
{
  size_t score = 0, i = 0;
  
  for (i = 0; i < path->size; i++)
    if ((gsl_spmatrix_get(G->o, 0, path->array[i]) == 0) && ((gsl_spmatrix_get(G->o, 1, path->array[i]) == 0)))
      score++;
  
  return score;
}


struct dynamic_array *path_union(struct dynamic_array *p1, struct dynamic_array *p2)
{

  struct dynamic_array *unio = empty__dynamic_array();

  for(size_t i = 0; i < p1->size; i++)
    add__to_dynamic_array(unio, p1->array[i]);
  
  for (size_t i = 0; i < p2->size; i++)
    add__to_dynamic_array(unio, p2->array[i]);
  
  return unio;
}


int path_value(struct graph_t *G, int move, enum color_t color){

  struct move_t m1 = {.m = move, .c = color};
  struct move_t m2 = {.m = move, .c = 1 - color};
    
  if(over(G, m1))
    return -INFINIT;

  else if(over(G, m2))
    return INFINIT;

  struct dynamic_array *p1 = djikstra(G, move, color);
  struct dynamic_array *p2 = djikstra(G, move, 1 - color);

  int d = path_score(p1, G) - path_score(p2, G);
  free__dynamic_array(p1);
  free__dynamic_array(p2);

  return d;

}


int min_distance(int *distance, int *selected, int num_vertices)
{
  int min = INFINIT;
  int min_index = -1;
  
  for (int k = 0; k < num_vertices; k++)
    if (distance[k] <= min && selected[k] == 0)
      min = distance[k], min_index = k;
 
  return min_index;
}


struct dynamic_array *djikstra(struct graph_t *G, int src, enum color_t color)
{

  int vertices = G->num_vertices;
  int distance[vertices];
  int parent[vertices];
  int selected[vertices];
 
  for (size_t i = 0; i < vertices; i++)
    parent[i] = INFINIT, distance[i] = INFINIT, selected[i] = 0; 

  distance[src] = 0;
  parent[src] = -1;

  for (int count = 0; count < vertices - 1; count++){

    int u = min_distance(distance, selected, vertices);
    selected[u] = 1;

    for (size_t v = 0; v < G->num_vertices; v++){

      int d = (int)(gsl_spmatrix_get(G->t, u, v) - gsl_spmatrix_get(G->o, color, v) * gsl_spmatrix_get(G->o, color, u));
      
      if (!selected[v] &&
	  gsl_spmatrix_get(G->t, u, v) &&
	  distance[u] != INFINIT &&
	  !gsl_spmatrix_get(G->o, (color + 1) % 2, v) &&
	  distance[u] + d <= distance[v])
	
        distance[v] = distance[u] + d, parent[v] = u;

      if(color * first + (1 - color) * second % u == 0)
	break;
    }
  }

  struct dynamic_array *p = empty__dynamic_array();
  int i = u;
  while (i != -1)
  {
    add__to_dynamic_array(p, i);
    i = parent[i];
  }

  return p;
}


void change_value(int *a, int b){

  *a = b;

}


int minimax(struct graph_t *G, int move, int maxminplayer, int depth, int alpha, int beta, enum color_t color){

  struct move_t make_move = {.m = move, .c = color};
  
  if(depth == 0 || over(G, make_move))
    return path_value(G, move, color);

  if(maxminplayer){

    int maxValue = -INFINIT;
    struct dynamic_array *p = neighbours(G, move);
    
    for(int i = 0; i < p->size; i++){
      
      struct move_t new_move = {.c = color, .m = p->array[i]};
      struct graph_t *G1 = copy_new_graph(G, new_move);
      int value = minimax(G1, new_move.m, 1 - maxminplayer, depth - 1, alpha, beta, color);
      maxValue = max_a_b(maxValue, value);
      change_value(&alpha, max_a_b(alpha, value));
      free__graph_t(G1);
      if(beta <= alpha)
	break;
    }

    free__dynamic_array(p);
    return maxValue;
  }

  else{

    int minValue = INFINIT;
    struct dynamic_array *p2 = neighbours(G, move);
    
    for(int i = 0; i < p2->size; i++){
      
      struct move_t new_move2 = {.c = color, .m = p2->array[i]};
      struct graph_t *G2 = copy_new_graph(G, new_move2, color);
      int value2 = minimax(G2, new_move2.m, maxminplayer, depth - 1, alpha, beta, color);
      minValue = min_a_b(minValue, value2);
      change_value(&beta, min_a_b(beta, value2));
      free__graph_t(G2);
      if(beta <= alpha)
	break;
    }

    free__dynamic_array(p2);
    return minValue;
  }
}


 
