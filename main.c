/*
** main.c for  in /home/jamie/myp
** 
** Made by James Faure
** Login   <james.faure@epitech.eu>
** 
** Started on  Fri May 12 16:26:08 2017 James Faure
** Last update Sun May 21 14:04:35 2017 James Faure
*/

#include "lang.h"
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

t_list	*sym_table;

void	yyparse();
char	*print_number(char *);

t_types	api_to_bool(t_all *this)
{
  if (!this || this->type == T_FALSE)
    return (T_FALSE);
  else if (this->type == T_FIXNUM)
    return (this->value.fixnum ? T_TRUE : T_FALSE);
  return (T_TRUE);
}

int	api_to_int(t_all *this)
{
  if (this->type == T_FIXNUM)
    return (this->value.fixnum);
  else if (this->type == T_BIGNUM)
    return (atoi(this->value.bignum));
  return (0);
}

t_all	*api_t_all_new(char *name, t_types type, t_value value)
{
  t_all	*this;

  this = malloc(sizeof(*this));
  this->name = name;
  this->type = type;
  this->value = value;
  return (this);
}


void	api_t_all_destroy(t_all *this)
{
  free(this->name);
  free(this);
}

void	putsym(char *name, t_all *value)
{
  value->name = name;
  api_list_push(sym_table, value);
}

t_all	*getsym(char const *name)
{
  return (api_list_get(sym_table, name, 0));
}

void	api_puts(t_all *this)
{
  if (this->type == T_FIXNUM)
    printf("%d\n", this->value.fixnum);
  else if (this->type == T_BIGNUM)
    print_number(this->value.bignum);
  else if (this->type == T_LIST)
    api_list_puts(this->value.list);
}

void	api_print(t_all *this)
{
  if (this->type == T_FIXNUM)
    {
      printf("%d", this->value.fixnum);
      fflush(stdout);
    }
}

#include <readline/readline.h>
#include <readline/history.h>

int	main(int ac, char **av)
{
  char	*line;

  sym_table = api_list_new(0);
  while (line = readline("<< "))
    {
      api_eval_string(line);
      add_history(line);
    }
}
