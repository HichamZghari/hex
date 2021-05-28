#include <string.h>
#include "player.h"
#define MAX_STRING 20

struct person{
  char* name;
  struct graph_t *graph;
  enum color_t color;
};

struct person player1;

char const* get_player_name()
{
  player1.name = "Player1";
  printf("%s\n", player1.name);
  return player1.name;
}

struct move_t propose_opening()
{
    size_t vertices = graph__size(player1.graph);
    size_t width =  graph__width(player1.graph);
    gsl_spmatrix *o = player1.graph->o;
    size_t mv = rand()%(vertices - 2*width) + width;
    while((gsl_spmatrix_get(o, 0, mv) == 1) || (gsl_spmatrix_get(o, 1, mv) == 1))
      {
	mv = rand()%(vertices - 2*width) + width;
      } 
    struct move_t opening = {mv};
    return opening;
}

int accept_opening(const struct move_t opening)
{
    (void)opening;
    return 1;
}

void initialize_graph(struct graph_t* graph)
{
    //A copy is made by a server, it's a copy for this player
    player1.graph = graph;
}

void initialize_color(enum color_t id)
{
    player1.color = id;
}

struct move_t play(struct move_t previous_move)
{
  struct move_t next;
  size_t pm = previous_move.v;
  int id = player1.color;
  gsl_spmatrix *o = player1.graph->o;
  size_t vertices = graph__size(player1.graph);
  size_t width =  graph__width(player1.graph);
  gsl_spmatrix_set(o,2%(id + 1),pm,1);
  size_t move = rand()%vertices;
  
  if((pm + width < vertices ) && (gsl_spmatrix_get(o, 0, pm + width) == 0) && (gsl_spmatrix_get(o, 1, pm + width) == 0) && (graph__edge(player1.graph, pm + width, pm)))
    {
      next.v = pm + width;
    }
  else if((pm + 1 + width < vertices) && (gsl_spmatrix_get(o, 0, pm + 1 + width) == 0) && (gsl_spmatrix_get(o, 1, pm + 1 + width) == 0) && (graph__edge(player1.graph, pm + 1 + width, pm)))
    {
      next.v = pm + 1 + width;
    }
  else if((pm - width > 0) && (gsl_spmatrix_get(o, 0, pm - width) == 0) && (gsl_spmatrix_get(o, 1, pm - width) == 0) && (graph__edge(player1.graph, pm - width, pm)))
    {
      next.v = pm - width;
    }
  else if((pm - 1 - width > 0) && (gsl_spmatrix_get(o, 0, pm - 1 - width) == 0) && (gsl_spmatrix_get(o, 1, pm - 1 - width) == 0) && (graph__edge(player1.graph, pm - 1 - width, pm)))
    {
      next.v = pm - 1 - width;
    }
  else if((pm - 1 > 0) && (gsl_spmatrix_get(o, 0, pm - 1) == 0) && (gsl_spmatrix_get(o, 1, pm - 1) == 0) && (graph__edge(player1.graph, pm - 1, pm)))
    {
      next.v = pm - 1;
    }
  else if((pm + 1 > 0) && (gsl_spmatrix_get(o, 0, pm + 1) == 0) && (gsl_spmatrix_get(o, 1, pm + 1) == 0) && (graph__edge(player1.graph, pm + 1, pm)))
    {
      next.v = pm + 1;
    }
  else
    {
      while((gsl_spmatrix_get(o,0,move) == 1) || (gsl_spmatrix_get(o,1,move) ==1))
	{
	  move = rand()%vertices;
	}
      next.v = move;
    }
  gsl_spmatrix_set(o,player1.color,move,1);
  return next;
}

void finalize()
{
  graph__free(player1.graph);
}
