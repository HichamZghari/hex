#include <string.h>
#include "player.h"
#define MAX_STRING 20

struct player{
  
  char* name;
  struct graph_t *graph;
  enum color_t color;
  struct move_t (*player_propose_opening)();
  int (*player_accept_opening)(const struct move_t opening);
  void (*player_initialize_color)(enum color_t id);
  void (*player_initialize_graph)(struct graph_t* graph);
  struct move_t (*player_play)(struct move_t previous_move);
  void (*finalize)();
  
};

struct player player = {.name ="-random-"};


void initialize_player_functions(struct player* player){
  
  player->player_propose_opening = propose_opening;
  player->player_accept_opening = accept_opening;
  player->player_initialize_graph = initialize_graph;
  player->player_initialize_color = initialize_color;
  player->player_play = play;
  
}




struct player get_player(){
  
  initialize_player_functions(&player);
  player.name = "player";
  
  return player;
  
}

char const* get_player_name(){
  
  return player.name;
  
}


struct move_t propose_opening(){
  
    size_t vertices = size__graph_t(player.graph);
    size_t width = width__graph_t(player.graph);
    struct move_t open = {.m = (vertices + width)/2}
    
    return opening;
    
}


int accept_opening(const struct move_t opening){
  
    return 0;
    
}

void initialize_graph(struct graph_t* graph){
  
    //Copy is made by the server for this player
    player.graph = graph;
    
}

void initialize_color(enum color_t id){
  
    player.color = id;
}

struct move_t play(struct move_t previous_move)
{
  struct move_t next;
  int id = player.color;
  gsl_spmatrix *o = player.graph->o;
  size_t vertices = size__graph_t(player.graph);
  size_t width = width__graph_t(player.graph);
  size_t move = previous_move.m;
  size_t side = (id == 1);
  size_t ran[vertices];
  int a = 0;

  next.c = id;
  size_t i = width * (1 - side) + side;
  while(i < (width * side + (1 - side)){

    if(gsl_spmatrix_get(o, id, i))

      break;

    i = i + width * side + (1 - side);

  }

  if(i >= vertices){

    for(size_t j = width * (1 - side) + side;
	j < vertices;
	j = j + width * side + (1 - side)){

      if((!gsl_spmatrix_get(o, id, j)) &&
	 (!gsl_spmatrix_get(o, 1 - id, j))){

	next.m = j;
	return next;

      }
    }

    int b = 1;
    
    while(b){

      if(move + side + width * (1 - side) < vertices &&
	 (! gsl_spmatrix_get(o, 0, move + side + width * (1 - side))) &&
	 (! gsl_spmatrix_get(o, 1, move + side + width * (1 - side))))

	move = move + side + width * (1 - side);

      else if(move + side * width + (1 - side) < vertices &&
	 (! gsl_spmatrix_get(o, 0, move + side * width + (1 - side))) &&
	 (! gsl_spmatrix_get(o, 1, move + side * width + (1 - side))))

	move = move + side * width + (1 - side);
      
      else if(move - side * width + (1 - side) < vertices &&
	 (! gsl_spmatrix_get(o, 0, move - side * width + (1 - side))) &&
	 (! gsl_spmatrix_get(o, 1, move - side * width + (1 - side))))

	move = move - side * width - (1 - side);

      else
	b = 0;
    
	 
  
  










  
  
}

void finalize(){
  
  free__graph_t(player.graph);
  
}
