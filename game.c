/**
 * @brief It implements the game interface and all the associated callbacks
 * for each command
 *
 * @file game.c
 * @author Profesores PPROG
 * @version 1.0
 * @date 13-01-2015
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"

#define N_CALLBACK 4

/**
   Define the function type for the callbacks
*/
typedef void (*callback_fn)(Game* game);

/**
   List of callbacks for each command in the game
*/
void game_callback_unknown(Game* game);
void game_callback_exit(Game* game);
void game_callback_following(Game* game);
void game_callback_previous(Game* game);

static callback_fn game_callback_fn_list[N_CALLBACK]={
  game_callback_unknown,
  game_callback_exit,
  game_callback_following,
  game_callback_previous};

/**
   Private functions
*/

STATUS game_load_spaces(Game* game, char* filename);
STATUS game_add_space(Game* game, Space* space);
Id     game_get_space_id_at(Game* game, int position);
STATUS game_set_player_location(Game* game, Id id);
STATUS game_set_object_location(Game* game, Id id);

/**
   Game interface implementation
*/
/*-----------------------------------------------------------------------------------------------------------------------*/
/*Función de creación del juego*/

STATUS game_create(Game* game) {
  int i;
  /*Bucle que inicializa un puntero (a NULL) por cada espacio de juego (MAX_SPACES=100)*/
  for (i = 0; i < MAX_SPACES; i++) {
    game->spaces[i] = NULL;
  }
  /*Inicialización de la localización del jugador y del objeto a -1 (NO_ID), es decir, que no están en ningún espacio*/
	/*Inicialización del último comando a ninguno ya que no ha habido un comando anterior*/
  game->player_location = NO_ID;
  game->object_location = NO_ID;
  game->last_cmd = NO_CMD;

	/*Se devuelve OK si el juego se ha creado correctamente (falta control de errores)*/
  return OK;
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*Función de creación del juego en el archivo que se va a mostrar por pantalla*/

STATUS game_create_from_file(Game* game, char* filename) {

  if (game_create(game) == ERROR)
    return ERROR;

  if (game_load_spaces(game, filename) == ERROR)
    return ERROR;
	/*^^^Controles de errores para las funciones game_create y game_load_spaces^^^*/
	
	/*Se ponen las localizaciones del jugador y del objeto en el inicio*/
  game_set_player_location(game, game_get_space_id_at(game, 0));
  game_set_object_location(game, game_get_space_id_at(game, 0));

	/*Se devuelve OK si se ha creado el juego en el archivo correctamente (falta control de errores)*/
  return OK;
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*Función para destruir el juego cuando se vaya a salir de él o se produzca algún error*/

STATUS game_destroy(Game* game) {
  int i = 0;

	/*Se destruirán los espacios de todo el juego uno a uno (hasta MAX_SPACES) siempre que estos todavía no hayan sido destruidos o sean NULL*/
  for (i = 0; (i < MAX_SPACES) && (game->spaces[i] != NULL); i++) {
    space_destroy(game->spaces[i]);
  }

	/*Se devuelve OK si se ha destruido el juego correctamente (falta control de errores)*/
  return OK;
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*Función para añadir un espacio adicional*/

STATUS game_add_space(Game* game, Space* space) {
  int i = 0;

	/*Control de errores space*/
  if (space == NULL) {
    return ERROR;
  }

	/*Ir al último espacio, para ello buscamos el primero menor que MAX_SPACES que sea igual a NULL, es decir, que este vacío*/
  while ( (i < MAX_SPACES) && (game->spaces[i] != NULL)){
    i++;
  }

	/*Se devuelve error si ha habido un problema y el número del último espacio supera a la macro MAX_SPACES*/
  if (i >= MAX_SPACES) {
    return ERROR;
  }

	/*Se sitúa en el último espacio añadido*/
  game->spaces[i] = space;

	/*Se devuelve OK si se ha añadido el espacio correctamente*/
  return OK;
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*Función para obtener el id de la posición en la que se encuentra*/

Id game_get_space_id_at(Game* game, int position) {
  if (position < 0 || position >= MAX_SPACES) {
    return NO_ID;
  }
	/*^^^Se devuelve un NO_ID, es decir, ninguno, si se introduce una posición no válida^^^*/
	/*Se devuelve el id del espacio en el que se encuentra a partir de la función de space.c*/
  return space_get_id(game->spaces[position]);
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*Función para obtener la posición en la que se encuentra a partir de un id*/

Space* game_get_space(Game* game, Id id){
  int i = 0;

  if (id == NO_ID) {
    return NULL;
  }
	/*^^^Si no se obtiene un id se devuelve NULL^^^*/

	/*Bucle for: desde 0 hasta el final y siempre que los espacios estén cubiertos, si el id dado es igual al del espacio, se devuelve ese espacio*/
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    if (id == space_get_id(game->spaces[i])){
      return game->spaces[i];
    }
  }
	
	/*Si no se devuelve el espacio entonces se devolverá NULL*/
  return NULL;
}

/*COMENTADO HASTA AQUÍ*/
/*-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-*/

STATUS game_set_player_location(Game* game, Id id) {

  if (id == NO_ID) {
    return ERROR;
  }

  game->player_location = id;

  return OK;
}

STATUS game_set_object_location(Game* game, Id id) {

  /*int i = 0;*/

  if (id == NO_ID) {
    return ERROR;
  }

  game->object_location = id;

  return OK;
}

Id game_get_player_location(Game* game) {
  return game->player_location;
}

Id game_get_object_location(Game* game) {
  return game->object_location;
}

STATUS game_update(Game* game, T_Command cmd) {
  game->last_cmd = cmd;
  (*game_callback_fn_list[cmd])(game);
  return OK;
}

T_Command game_get_last_command(Game* game){
  return game->last_cmd;
}

void game_print_data(Game* game) {
  int i = 0;

  printf("\n\n-------------\n\n");

  printf("=> Spaces: \n");
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    space_print(game->spaces[i]);
  }

  printf("=> Object location: %d\n", (int) game->object_location);
  printf("=> Player location: %d\n", (int) game->player_location);
  printf("prompt:> ");
}

BOOL game_is_over(Game* game) {
  return FALSE;
}

/**
   Callbacks implementation for each action
*/

void game_callback_unknown(Game* game) {
}

void game_callback_exit(Game* game) {
}

void game_callback_following(Game* game) {
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id) {
      current_id = space_get_south(game->spaces[i]);
      if (current_id != NO_ID) {
	game_set_player_location(game, current_id);
      }
      return;
    }
  }
}

void game_callback_previous(Game* game) {
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);

  if (NO_ID == space_id) {
    return;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    current_id = space_get_id(game->spaces[i]);
    if (current_id == space_id) {
      current_id = space_get_north(game->spaces[i]);
      if (current_id != NO_ID) {
	game_set_player_location(game, current_id);
      }
      return;
    }
  }
}

/*STATUS game_load_spaces(Game* game, char* filename) {
  FILE* file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char* toks = NULL;
  Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;
  Space* space = NULL;
  STATUS status = OK;

  if (!filename) {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#s:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      north = atol(toks);
      toks = strtok(NULL, "|");
      east = atol(toks);
      toks = strtok(NULL, "|");
      south = atol(toks);
      toks = strtok(NULL, "|");
      west = atol(toks);
#ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%ld|%ld|%ld\n", id, name, north, east, south, west);
#endif
      space = space_create(id);
      if (space != NULL) {
	space_set_name(space, name);
	space_set_north(space, north);
	space_set_east(space, east);
	space_set_south(space, south);
	space_set_west(space, west);
	game_add_space(game, space);
      }
    }
  }

  if (ferror(file)) {
    status = ERROR;
  }

  fclose(file);

  return status;
}*/
