/**
 * @brief Implementa las funciones para crear un nuevo jugador y las funciones para asignar y obtener la información
 * de sus diferentes campos, aparte de una función que imprimira la información de estos campos.
 *
 * @file player.c
 * @author Gonzalo Martinez
 * @version 1.0
 * @date 5-01-2018
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "player.h"
#include "space.h"
#include "game.h"

/*Habrá que incluir las funcionalidades para el object posteriormente (inv/link tambien)*/

struct _Player {
  char name[NAME_SIZE];
  Id id;
  Space * location;
}

Player * player_create (Id id){
  Player *newpl;

  if(id==NO_ID) return NULL;
  /*^^^Control de errores id^^^*/

  /*Reserva de memoria para player*/
  newpl=(Player*)malloc(sizeof(Player));
  if(!newpl) return NULL;

  /*Asignaciones campos player*/
  newpl->id=id; /*El id que se recibe se le asigna al nuevo jugador*/
  newpl->location=NULL;

  return newpl;

}

STATUS player_destroy (Player * pl){
  if(!pl) return ERROR;
  /*^^^Control de errores player^^^*/

  /*Liberación player*/
  free(pl);
  pl=NULL;

  return OK;
}

STATUS player_set_name (Player * pl, char * name){
  if(!pl) return ERROR;
  /*^^^Control de errores player^^^*/
  if(!name) return ERROR;
  /*^^^Control de errores name^^^*/

  /*Asignación del nombre recibido en el nombre de player*/
  strcpy(pl->name,name);

  return OK;
}

STATUS player_set_id (Player * pl, Id id){
  if(!pl) return ERROR;
  /*^^^Control de errores player^^^*/
  if(id==NO_ID) return ERROR;
  /*^^^Control de errores id^^^*/

  /*Asignación del id recibido en el id de player*/
  pl->id=id;

  return OK;
}

STATUS player_set_location (Player * pl, Space * location){
  if(!pl) return ERROR;
  /*^^^Control de errores player^^^*/
  if(!location) return ERROR;
  /*^^^Control de errores location^^^*/

  /*Asignación de la localización recibida en la localización de player*/
  pl->location=location;
}

char * player_get_name (Player * pl){
  if(!pl) return NULL;
  /*^^^Control de errores player^^^*/
  return pl->name;
}

Id player_get_id (Player * pl){
  if(!pl) return NO_ID;
  /*^^^Control de errores player^^^*/
  return pl->id;
}

Space * player_get_location (Player * pl){
  if(!pl) return NULL;
  /*^^^Control de errores player^^^*/
  return pl->location;
}

STATUS player_print(Player * pl){
	if (!pl) return ERROR;
  /*^^^Control de errores player^^^*/

  /*Se imprimen los campos del jugador y se devuelve OK si se ha ejecutado correctamente*/
  fprintf(stdout, "--> Player (Id: %ld; Name: %s\n", pl->id, pl->name);

	return OK;
}
