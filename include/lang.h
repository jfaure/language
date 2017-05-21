/*
** lang.h for  in /home/jamie/myp
** 
** Made by James Faure
** Login   <james.faure@epitech.eu>
** 
** Started on  Fri May 12 16:21:35 2017 James Faure
** Last update Tue May 16 18:23:25 2017 James Faure
*/

#ifndef LANG_H_
# define LANG_H_

typedef	struct s_list	t_list;

// Symbol type specifications
typedef enum
  {
    T_NONE,
    T_UNDEF,
    T_LIST,
    T_BIGNUM,
    T_FIXNUM,
    T_FILE,
    T_NIL,
    T_TRUE,
    T_FALSE,
  }		t_types;

// Semantic types
typedef union
{
  char		*bignum;
  int		fixnum;
  t_list	*list;
}		t_value;

// language object (top level)
typedef struct
{
  char		*name;
  t_types	type;
  t_value	value;
}		t_all;

////////////////////////////// list
#include <stdarg.h>
#define LIST_SIZE 50

struct s_list
{
  int		len;
  t_all		*list[LIST_SIZE];
  struct s_list	*next;
};

t_list		*api_list_new(int len, ...);
extern inline t_list	*api_list_push(t_list *list, t_all *var);
extern inline t_list	*api_list_pop(t_list *list);
extern inline t_all	*api_list_get(t_list *list, char const *name, t_all *index);
extern inline t_list	*api_list_slice(t_list *, t_all *, t_all *);
extern inline void	api_list_puts(t_list *list);

t_all	*api_t_all_new(char *name, t_types type, t_value value);
void	api_puts(t_all *this);
t_all	*getsym(char const *);
void	putsym(char *name, t_all *);
int	api_to_int(t_all *this);
int	api_eval_string(char const *);

#endif
