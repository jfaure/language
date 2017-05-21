/*
** list.c for  in /home/jamie/myp
** 
** Made by James Faure
** Login   <james.faure@epitech.eu>
** 
** Started on  Mon May 15 15:50:53 2017 James Faure
** Last update Sun May 21 15:42:40 2017 James Faure
*/

#include <stdarg.h>
#include <malloc.h>
#include "lang.h"
#include <string.h>

t_list		*api_list_new(int len, ...)
{
  va_list	ap;
  int		i;
  t_list	*first;

  first = malloc(sizeof(*first));
  first->len = len;
  va_start(ap, len);
  i = -1;
  while (++i < len)
    first->list[i] = va_arg(ap, t_all *);
  va_end(ap);
  return (first);
}

inline t_list	*api_list_push(t_list *list, t_all *var)
{
  list->list[list->len++] = var;
  return (list);
}

inline t_list	*api_list_pop(t_list *list)
{
  list->list[--list->len];
  return (list);
}

inline t_all	*api_list_get(t_list *list, char const *name, t_all *index)
{
  int		i;

  if (name && list->len)
    {
      i = 0;
      while (strcmp(list->list[i]->name, name))
	if (++i == list->len)
	  return (0);
      return (list->list[i]);
    }
  if (!index)
    return (0);
  return (list->list[index->value.fixnum]);
}

inline t_list	*api_list_slice(t_list *list, t_all *a, t_all *b)
{
  t_list	*ne;
  int		slice[2];

  slice[0] = api_to_int(a);
  slice[1] = api_to_int(b);
  ne = api_list_new(0);
  ne->len = slice[1] - slice[0];
  memcpy(ne->list, list->list + slice[0], (ne->len) * sizeof(ne->list[0]));
  return (ne);
}

inline void	api_list_puts(t_list *list)
{
  int		i;

  i = -1;
  fputs("[", stdout);
  if (++i < list->len)
    api_print(list->list[i]);
  while (++i < list->len)
    {
      fputs(", ", stdout);
      api_print(list->list[i]);
    }
  puts("]");
}
