#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "screen.h"

#pragma GCC diagnostic ignored "-Wpedantic"

#define ROWS 23
#define COLUMNS 80
#define TOTAL_DATA (ROWS * COLUMNS) + 1

#define BG_CHAR '~'
#define FG_CHAR ' '
#define PROMPT " prompt:> "

#define ACCESS(d, x, y) (d + ((y) * COLUMNS) + (x))

/*COMENTADO (faltan dos funciones) */

struct _Area{
  int x, y, width, height;
  char *cursor;
};

char *__data;

/****************************/
/*     Private functions    */
/****************************/
int  screen_area_cursor_is_out_of_bounds(Area* area);
void screen_area_scroll_up(Area* area);
void screen_utils_replaces_special_chars(char* str);

/****************************/
/* Functions implementation */
/****************************/

/*-----------------------------------------------------------------------------------------------------------------------*/
/*Función de creación de pantalla*/

void screen_init(){
  screen_destroy(); /* Dispose if previously initialized */
  __data = (char *) malloc(sizeof(char) * TOTAL_DATA);

  if (__data){
    memset(__data, (int) BG_CHAR, TOTAL_DATA); /*Fill the background*/
    *(__data + TOTAL_DATA - 1) = '\0';         /*NULL-terminated string*/
  }
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*Función de destrucción de pantalla*/

void screen_destroy(){
  if (__data)
    free(__data);
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*Función para "pintar" la pantalla en la terminal*/

void screen_paint(){
  char *src = NULL;
  char dest[COLUMNS + 1];
  int i=0;

  memset(dest, 0, COLUMNS + 1);
  
  if (__data){
    /* puts(__data); */ /*Vuelca la información directamente en la terminal*/
    /*Funcionará correctamente si el tamaño de la ventana de la terminal es el adecuado*/
    
    puts("\033[2J"); /*Despejar la terminal*/
    for (src=__data; src < (__data + TOTAL_DATA - 1); src+=COLUMNS){
      memcpy(dest, src, COLUMNS);
      /* printf("%s\n", dest); */
      for (i=0; i<COLUMNS; i++){
	if (dest[i] == BG_CHAR){
	  printf("\033[0;34;44m%c\033[0m", dest[i]); /* foreground:blue(34); background:blue(44) */
		/*Este printf sirve para imprimir los colores, al igual que el de abajo que está en el siguiente else*/
	}else{
	  printf("\033[0;30;47m%c\033[0m", dest[i]); /* foreground:black(30); background:white(47) */
	}
      }
      printf("\n");
    }
  }
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*Función que coge el comando y coge la información que va a aparecer por pantalla*/

void screen_gets(char *str){
  fprintf(stdout, PROMPT);
  if (fgets(str, COLUMNS, stdin))
    *(str + strlen(str) - 1) = 0; /* Replaces newline character with '\0' */
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*Función que reserva memoria para el área en el que se imprimirá la pantalla*/

Area* screen_area_init(int x, int y, int width, int height){
  int i = 0;
  Area* area = NULL;

  if ( (area  = (Area*) malloc (sizeof(struct _Area))) ){
    *area = (struct _Area) {x, y, width, height, ACCESS(__data, x, y)};
		/*^^^Inicialización del espacio para la pantalla^^^*/

    for (i=0; i < area->height; i++)
      memset(ACCESS(area->cursor, 0, i), (int) FG_CHAR, (size_t) area->width);
  }
	
	/*Se devuelve el área creado en esta función*/
  return area;
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*Función que destruye el área de pantalla y libera toda su memoria*/

void screen_area_destroy(Area* area){
  if(area)
    free(area);
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*Función que hace un clear de la pantalla para pasar a la siguiente pantalla cuando un comando se ha introducido*/

void screen_area_clear(Area* area){
  int i = 0;

  if (area){
    screen_area_reset_cursor(area);
    
    for (i=0; i < area->height; i++)
      memset(ACCESS(area->cursor, 0, i), (int) FG_CHAR, (size_t) area->width);
  }
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*Función que reinicia la posición del cursor*/

void screen_area_reset_cursor(Area* area){
  if (area)
    area->cursor = ACCESS(__data, area->x, area->y);
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*FALTA ENTENDER ESTA FUNCIÓN*/

void screen_area_puts(Area* area, char *str){
  int len = 0;
  char *ptr = NULL;

  if (screen_area_cursor_is_out_of_bounds(area))
    screen_area_scroll_up(area);
  
  screen_utils_replaces_special_chars(str);

  for (ptr = str; ptr < (str + strlen(str)); ptr+=area->width){
    memset(area->cursor, FG_CHAR, area->width);
    len = (strlen(ptr) < area->width)? strlen(ptr) : area->width;
    memcpy(area->cursor, ptr, len);
    area->cursor += COLUMNS;
  }
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*Función que comprueba si el cursor está fuera de los límites del área establecidos*/

int screen_area_cursor_is_out_of_bounds(Area* area){
  return area->cursor > ACCESS(__data,
			       area->x + area->width,
			       area->y + area->height - 1);
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*Función que permite subir en el área definida*/

void screen_area_scroll_up(Area* area){
  for(area->cursor = ACCESS(__data, area->x, area->y);
      area->cursor < ACCESS(__data, area->x + area->width, area->y + area->height - 2);
      area->cursor += COLUMNS){
    memcpy(area->cursor, area->cursor+COLUMNS, area->width);
  }
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*FALTA ENTENDER ESTA FUNCIÓN*/

void screen_utils_replaces_special_chars(char* str){
  char *pch = NULL;

  /* Replaces acutes and tilde with '??' */
  while ((pch = strpbrk (str, "ÁÉÍÓÚÑáéíóúñ")))
    memcpy(pch, "??", 2);
}
