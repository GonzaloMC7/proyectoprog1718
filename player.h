/**
 * @brief Define las primitivas de las funciones que se van a desarrollar en player.c, así como la definición
 * de la estructura a utilizar en este módulo player.c
 *
 * @file player.h
 * @author Gonzalo Martinez
 * @version 1.0
 * @date 7-01-2018
 * @copyright GNU Public License
 */

 #ifndef PLAYER_H
 #define PLAYER_H

 #include "types.h"
 #include "space.h"

 typedef struct _Player Player;


/*-----------------------------------------------------------------------------------------------------*/


 Player * player_create (Id id);

 /*-----------------------------------------------------------------------------------------------------*/


 STATUS player_destroy (Player * pl);

 /*-----------------------------------------------------------------------------------------------------*/


 STATUS player_set_name (Player * pl, char * name);

 /*-----------------------------------------------------------------------------------------------------*/


 STATUS player_set_id (Player * pl, Id id);

 /*-----------------------------------------------------------------------------------------------------*/


 STATUS player_set_location (Player * pl, Space * location);

 /*-----------------------------------------------------------------------------------------------------*/


 char * player_get_name (Player * pl);

 /*-----------------------------------------------------------------------------------------------------*/


 Id player_get_id (Player * pl);

 /*-----------------------------------------------------------------------------------------------------*/


 Space * player_get_location (Player * pl);

 /*-----------------------------------------------------------------------------------------------------*/


 STATUS player_print(Player * pl);


 #endif
