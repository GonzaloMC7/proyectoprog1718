/** 
 * @brief It implements the command interpreter
 * 
 * @file command.h
 * @author Profesores PPROG
 * @version 1.0 
 * @date 19-12-2014 
 * @copyright GNU Public License
 */

/*COMENTADO*/

#ifndef COMMAND_H
#define COMMAND_H

typedef enum enum_Command {
  NO_CMD = -1, 
  UNKNOWN, 
  EXIT, 
  FOLLOWING, 
  PREVIOUS} T_Command;
/*Esta enumeración define los comandos que se pueden reconocer, asi como el unknown para los casos en los que no se reconozca*/

T_Command get_user_input(); /*Función para obtener el comando introducido por el usuario*/

#endif
