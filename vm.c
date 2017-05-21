/*
** vm.c for  in /home/jamie/myp
** 
** Made by James Faure
** Login   <james.faure@epitech.eu>
** 
** Started on  Thu May 18 23:30:16 2017 James Faure
** Last update Sat May 20 00:43:09 2017 James Faure
*/

#include "vm.h"

int	rip;
int	rbp;
int	rsp;

char	run_bytecode(char *byte_code)
{
  t_all	*stack[5000];

  rip = 0;
  rsp = -1;
  while (byte_code[rip] != END_OF_INPUT)
    switch (byte_code[rip])
      {
      case (NOP): ++rip; break;
      case (SET_LOCAL): stack[++rsp] = (t_all *) byte_code[++rip]; break;
      case (JUMP): rip = (int) byte_code[rip + 1];
      case (JUMP_IF) rip = stack[rsp] ? (int) byte_code[rip + 1] : rip + 5;
      case (JUMP_UNLESS) rip = stack[rsp] ? rip + 5 : (int) byte_code[rip + 1];
      default: perror("unrecognized instruction.\n"); exit(84);
      }
}
