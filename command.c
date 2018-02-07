/**
 * @brief It implements the command interpreter
 *
 * @file command.c
 * @author Profesores PPROG
 * @version 1.0
 * @date 19-12-2014
 * @copyright GNU Public License
 */


/*COMENTADO*/

#include <stdio.h>
#include <strings.h>
#include "command.h"

#define CMD_LENGHT 30
#define N_CMD 5

char *cmd_to_str[N_CMD] = {"No command", "Unknown", "Exit", "Following", "Previous"};
char *short_cmd_to_str[N_CMD] =  {"","","e","f","p"};


T_Command get_user_input(){
  T_Command cmd = NO_CMD;
  char input[CMD_LENGHT] = "";
  int i=UNKNOWN- NO_CMD + 1;

  if (scanf("%s", input) > 0){
    cmd = UNKNOWN;
    while(cmd == UNKNOWN && i < N_CMD){
      if (!strcasecmp(input,short_cmd_to_str[i]) || !strcasecmp(input,cmd_to_str[i])){
        cmd = i + NO_CMD;
      } /*Este bucle while se repetirá hasta que el comando coincida con los definidos previamente, y si llega a N_CMD también se detendrá*/
      else {
        i++;
      }
    }
  }
  return cmd; /*Se retornará el comando que se ha introducido sea uno válido o sea uno desconocido (unknown)*/
}
