/**
 * @brief It implements the game interface and all the associated callbacks
 * for each command
 *
 * @file object.h
 * @author Javier Martin
 * @version 1.0
 * @date 4-02-2018
 * @copyright GNU Public License
 */


#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"

typedef struct _Object Object;

/*Funciones primitivas de object.c*/
Object* object_create(Id id);
STATUS object_destroy(Object* object);
STATUS object_set_name(Object* object, char* name);
const char * object_get_name(Object* object);
Id object_get_id(Object* object);
STATUS object_print(Object* object);
STATUS object_set_id(Object* object, Id id);
