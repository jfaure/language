/*
** add.c for  in /home/jamie/myp
** 
** Made by James Faure
** Login   <james.faure@epitech.eu>
** 
** Started on  Tue May  9 00:34:44 2017 James Faure
** Last update Thu May 11 05:15:03 2017 James Faure
*/

#include <malloc.h>
#include <string.h>
#include "ops.h"

char	*print_number(char *a)
{
  char	*r;
  char	neg;

  r = a;
  neg = *a == '-' && ++a;
  while (*a == '0' && a[1])
    ++a;
  neg && *a != '0' && putchar('-');
  puts(a);
  return (r);
}

/*
** Functions are expected to always prefix positive numbers with '0'
*/
char	*negate(char *a)
{
  char	*r;

  r = a;
  if (*r == '-')
    {
      *r = '0';
      return (a);
    }
  else if (--r >= a)
    *r = '-';
  else
    {
      r = malloc(strlen(a) + 2);
      strcpy(r + 1, a);
      *r = '-';
      free(a);
      return (r);
    }
  return (a);
}

/*
** '.' is 46 in ascii so ('.' < '0')
*/
int	num_strcmp(char const *a, char const *b)
{
  int	len[2];

  if ((*a == '-' || *b == '-') && (*a != *b))
    return (*a == '-' ? -1 : 1);
  if (*a == '-')
    {
      ++a;
      ++b;
    }
  while (*a == '0')
    ++a;
  while (*b == '0')
    ++b;
  len[0] = strlen(a);
  len[1] = strlen(b);
  if (len[0] != len[1])
    return (len[0] - len[1]);
  return (strcmp(a, b));
}

void	swap(void **a, void **b)
{
  void	*c;

  c = *a;
  *a = *b;
  *b = c;
}

char	normalize_args(char const **a, char const **b, int len[3], char sub)
{
  char	const *swp;
  int	s;

  while (**a == '0')
    ++*a;
  while (**b == '0')
    ++*b;
  len[0] = (len[1] = 0);
  while (a[0][len[0]] && a[0][len[0]] != '.')
    ++len[0];
  while (b[0][len[1]] && b[0][len[1]] != '.')
    ++len[1];
  len[2] = len[0] - len[1];
  len[0] += strlen(*a + len[0]);
  len[1] += strlen(*b + len[1]);
  if (len[2] < 0 || sub && num_strcmp(*a, *b) < 0)
    {
      swap((void **) a, (void **) b);
      len[0] ^= len[1] ^= len[0] ^= len[1];
      len[2] = -len[2];
      return (1);
    }
  return (0);
}

char	*sum(char const *a, char const *b)
{
  char	*r;
  int	len[3];
  int	i;

  if ((*a == '-' || *b == '-'))
    return (*a == *b ? negate(sum(a + 1, b + 1)) :
	    sub(*b == '-' ? a : b, *b == '-' ? b + 1 : a + 1));
  normalize_args(&a, &b, len, 0);
  r = malloc((len[0] > len[1] ? len[0] : len[1]) + 3);
  *r = (*r++ = '0');
  i = len[2];
  while (i > 0)
    r[i] = a[--i];
  a += (i = len[2]);
  while (*a && *b)
    r[++i] = *a++ + *b++ - 48;
  r[++i] = 0;
  while (--i >= 0)
    if (r[i] > '9')
      {
	r[i - 1] != '.' && ++r[i - 1] || ++r[i - 2];
	r[i] -= 10;
      }
  return (r - 1);
}

char	*sub(char const *a, char const *b)
{
  char	*r;
  int	len[3];
  int	i;

  if (*a == '-' || *b == '-')
    return (*a == *b ? sub(b + 1, a + 1) : *b == '-' ? sum(a, b + 1) :
	    negate(sum(a + 1, b)));
  i = normalize_args(&a, &b, len, 1);
  r = malloc((len[0] > len[1] ? len[0] : len[1]) + 2);
  *r = i ? '-' : '0';
  i = len[0] - len[1];
  while (i > 0)
    r[i] = a[--i];
  a += (i = len[0] - len[1]);
  while (*a)
    r[++i] = *a++ - *b++ + 48;
  r[++i] = 0;
  while (--i > 0)
    if (r[i] < '0')
      {
	--r[i - 1];
	r[i] += 10;
      }
  return (r);
}

char	*mul(char const *a, char const *b)
{
  char	*r;
  int	len[3];
  int	i;
  int	j;

  if (*a == '-' || *b == '-')
    return (*a == *b ? mul(a + 1, b + 1) :
	    negate(mul(a + (*a == '-'), (b + (*b == '-')))));
  normalize_args(&a, &b, len, 0);
  len[2] = len[0]-- + len[1]-- + 1;
  memset(r = malloc(len[2] + 2), 0, len[2] + 2);
  i = -1;
  while (a[++i] && (j = -1))
    while (b[++j])
      {
	r[len[2] - (i + j)] += (a[len[0] - i] - 48) * (b[len[1] - j] - 48);
	while (r[len[2] - (i + j)] > 9)
	  {
	    ++r[len[2] - (i + j + 1)];
	    r[len[2] - (i + j)] -= 10;
	  }
      }
  while (len[2] >= 0)
    r[len[2]--] += 48;
  return (r);
}

char	*div(char const *a, char const *b)
{
  char	*buf;
  char	*r;
  char	*t;
  int	i;
  int	n;

  if (*a == '-' || *b == '-')
    return (*a == *b ? div(a + 1, b + 1) :
	    negate(div(a + (*a == '-'), (b + (*b == '-')))));
  r = malloc(n = strlen(a) + 2);
  memset(r, '0', n);
  buf = malloc(n);
  *buf = i = n = 0;
  while (*a == '0')
    ++a;
  while (*a)
    {
      buf[n] = *a++;
      buf[++n] = 0;
      r[i] = '0';
      while (num_strcmp(buf, b) >= 0)
	{
	  strcpy(buf, t = sub(buf, b));
	  free(t);
	  ++r[i];
	}
      n = strlen(buf);
      ++i;
    }
  i || (r[i++] = '0');
  r[i] = 0;
  free(buf);
  return (r);
}
