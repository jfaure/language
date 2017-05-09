/*
** get_next_line.c for  in /mnt/james.faure/SHELL
** 
** Made by James Faure
** Login   <james.faure@epitech.eu>
** 
** Started on  Mon Mar 27 02:02:32 2017 James Faure
** Last update Tue May  9 04:28:47 2017 James Faure
*/

#include "string.h"

int	my_strlen(const char *const str)
{
  int	i;

  if (!str)
    return (0);
  i = 0;
  while (str[i])
    ++i;
  return (i);
}

char	*my_strdup(const char *str)
{
  char	*r;
  char	*p;

  r = malloc(my_strlen(str) + 1);
  p = r;
  while (*str)
    *p++ = *str++;
  *p = 0;
  return (r);
}

char	*my_strndup(const char *str, int n)
{
  char	*r;
  char	*p;

  r = malloc(1 + n);
  p = r;
  while (*str && n--)
    *p++ = *str++;
  *p = 0;
  return (r);
}

char	*my_astrcat(const char *a, const char *b)
{
  char	*r;
  char	*p;

  r = malloc(my_strlen(a) + my_strlen(b) + 1);
  p = r;
  if (a)
    while (*a)
      *p++ = *a++;
  if (b)
    while (*b)
      *p++ = *b++;
  *p = 0;
  return (r);
}

char	*get_next_line(const int fd)
{
  char		buf[READ_SIZE + 1];
  static char	*save = 0;
  static int	i = 0;
  static int	done = 1;
  int	j;
  char	*plop;

  j = i;
  if (save && done)
    while (save[i])
      if (10 == save[i++])
	return (my_strndup(save + j, i - j - 1));
  if (!done || fd < 0 || !(done = read(fd, buf, READ_SIZE)))
    {
      plop = save && save[j] ? my_strndup(save + j, i - j) : 0;
      free(save + !!(save = 0));
      return (plop);
    }
  save = my_astrcat((plop = save) + j + (i = (buf[done] = 0)), buf);
  free(plop);
  return (get_next_line(fd));
}
