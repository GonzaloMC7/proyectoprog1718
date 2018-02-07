#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "space.h"

/*COMENTADO*/

struct _Space {
  Id id;
  char name[WORD_SIZE + 1];
  Id north;
  Id south;
  Id east;
  Id west;
  BOOL object;
};

/*-----------------------------------------------------------------------------------------------------------------------*/
/*Función de creación del espacio de juego con sus diferentes posiciones*/

Space* space_create(Id id) {

  Space *newSpace = NULL;

  /*Control de errores del id recibido*/
  if (id == NO_ID)
    return NULL;

  /*Creación del espacio y su correspondiente control de errores*/
  newSpace = (Space *) malloc(sizeof (Space));

  if (newSpace == NULL) {
    return NULL;
  }
  
  /*Asignaciones de los valores de newSpace*/
 
  newSpace->id = id;

  newSpace->name[0] = '\0';

  newSpace->north = NO_ID;
  newSpace->south = NO_ID;
  newSpace->east = NO_ID;
  newSpace->west = NO_ID;

  newSpace->object = FALSE;

  return newSpace;
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*Función de destrucción del espacio de juego y sus diferentes posiciones*/

STATUS space_destroy(Space* space) {
  if (!space) {
    return ERROR;
  }
  
  /*^^^Control de errores space^^^*/

  free(space);
  space = NULL;

  /*Se libera el espacio y se devuelve OK si no ha habido ningún error en la función entera*/
  
  return OK;
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*Función de asignación de nombres para cada uno de los espacios*/

STATUS space_set_name(Space* space, char* name) {
  if (!space || !name) {
    return ERROR;
  }

  /*^^^Control de errores space y name^^^*/
  
  if (!strcpy(space->name, name)) {
    return ERROR;
  }
  /*Se hace la asignación y después se devuelve OK si no ha habido ningún problema*/

  return OK;
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*Función de asignación de la posición norte*/

STATUS space_set_north(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }  
  /*^^^Control de errores arriba y asignación debajo^^^*/  
  space->north = id;
  return OK;
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*Función de asignación de la posición sur*/

STATUS space_set_south(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  /*^^^Control de errores arriba y asignación debajo^^^*/  
  space->south = id;
  return OK;
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*Función de asignación de la posición este*/

STATUS space_set_east(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  /*^^^Control de errores arriba y asignación debajo^^^*/  
  space->east = id;
  return OK;
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*Función de asignación de la posición oeste*/

STATUS space_set_west(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  /*^^^Control de errores arriba y asignación debajo^^^*/  
  space->west = id;
  return OK;
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*Función de asignación del objeto en una posición*/

STATUS space_set_object(Space* space, BOOL value) {
  if (!space) {
    return ERROR;
  }
  /*^^^Control de errores arriba y asignación debajo^^^*/
  space->object = value;
  return OK;
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*Función de obtención del nombre de un espacio*/

const char * space_get_name(Space* space) {
  if (!space) {
    return NULL;
  }
  /*^^^Control de errores arriba y se devuelve el nombre del espacio (debajo)^^^*/
  return space->name;
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*Función de obtención del id de un espacio*/

Id space_get_id(Space* space) {
  if (!space) {
    return NO_ID;
  }
  /*^^^Control de errores arriba y se devuelve el id del espacio (debajo)^^^*/
  return space->id;
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*Función de obtención de la posición norte de un espacio*/

Id space_get_north(Space* space) {
  if (!space) {
    return NO_ID;
  }
  /*^^^Control de errores arriba y se devuelve el espacio norte (debajo)^^^*/
  return space->north;
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*Función de obtención de la posición sur de un espacio*/

Id space_get_south(Space* space) {
  if (!space) {
    return NO_ID;
  }
  /*^^^Control de errores arriba y se devuelve el espacio sur (debajo)^^^*/
  return space->south;
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*Función de obtención de la posición este de un espacio*/

Id space_get_east(Space* space) {
  if (!space) {
    return NO_ID;
  }
  /*^^^Control de errores arriba y se devuelve el espacio este (debajo)^^^*/
  return space->east;
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*Función de obtención de la posición oeste de un espacio*/

Id space_get_west(Space* space) {
  if (!space) {
    return NO_ID;
  }
  /*^^^Control de errores arriba y se devuelve el espacio oeste (debajo)^^^*/
  return space->west;
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*Función de obtención del objeto en un espacio*/

BOOL space_get_object(Space* space) {
  if (!space) {
    return FALSE;
  }
  /*^^^Control de errores arriba y se devuelve el objeto (debajo)^^^*/
  return space->object;
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*Función que imprime el estado de un espacio*/

STATUS space_print(Space* space) {
  Id idaux = NO_ID;

  if (!space) {
    return ERROR;
  }
  /*^^^Control de errores space^^^*/
  
  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

  /*Se busca un link en el norte y si existe se muestra por pantalla*/
  
  idaux = space_get_north(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> North link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No north link.\n");
  }

  /*Se busca un link en el sur y si existe se muestra por pantalla*/
  
  idaux = space_get_south(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> South link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No south link.\n");
  }
  
  /*Se busca un link en el este y si existe se muestra por pantalla*/

  idaux = space_get_east(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> East link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No east link.\n");
  }
  
  /*Se busca un link en el oeste y si existe se muestra por pantalla*/

  idaux = space_get_west(space);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> West link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No west link.\n");
  }

  /*Se busca un objeto en la posición actual y si existe se muestra por pantalla*/
  
  if (space_get_object(space)) {
    fprintf(stdout, "---> Object in the space.\n");
  } else {
    fprintf(stdout, "---> No object in the space.\n");
  }

  return OK;
}

