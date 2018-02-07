/** 
 * @brief It defines the game interface
 * for each command
 * 
 * @file game_reader.h
 * @author Profesores PPROG
 * @version 1.0 
 * @date 13-01-2015 
 * @copyright GNU Public License
 */

#include "space.h"
#include "game.h"

#ifndef _GAME_READER_H
#define _GAME_READER_H

STATUS game_add_space(Game* game, Space* space);
STATUS game_load_spaces(Game* game, char* filename);
Id     game_get_space_id_at(Game* game, int position);
STATUS game_set_player_location(Game* game, Id id);
STATUS game_set_object_location(Game* game, Id id);


#endif
