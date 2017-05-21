/*
** vm.h for  in /home/jamie/myp
** 
** Made by James Faure
** Login   <james.faure@epitech.eu>
** 
** Started on  Thu May 18 23:30:32 2017 James Faure
** Last update Sat May 20 15:51:40 2017 James Faure
*/

#ifndef VM_H_
# define VM_H_

typedef enum
  {
    NOP,
    // Variable
    GET_LOCAL,
    SET_LOCAL,
    // Put
    PUT_ALL,
    PRINT_ALL,
    // Stack
    POP,
    PUSH,
    // Setting
    DEF,
    ALIAS,
    CLASS,
    // Method
    // Exception
    THROW,
    // Jump
    JUMP,
    JUMP_IF,
    JUMP_UNLESS,
    // Opts
    OPT_PLUS,
    OPT_MINUS,
    OPT_MULT,
    OPT_DIV,
    OPT_MOD,
    // Test
    OPT_EQ,
    OPT_LT,
    OPT_LE,
    OPT_LEN,
    // Misc
    END_OF_INPUT,
  }		t_vm_instructions;

#endif
