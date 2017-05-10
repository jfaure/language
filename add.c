/*
** add.c for  in /home/jamie/myp
** 
** Made by James Faure
** Login   <james.faure@epitech.eu>
** 
** Started on  Tue May  9 00:34:44 2017 James Faure
** Last update Wed May 10 16:30:35 2017 James Faure
*/

#include <malloc.h>
#include <string.h>

char	*format_number(char *a)
{
  char	*r;

  r = a;
  if (*a == '-' && ++a)
    putchar('-');
  while (*a == '0' && a[1])
    ++a;
  puts(a);
  return (r);
}

char	*negate(char *a)
{
  char	*r;

  r = a;
  while (*r == '0')
    ++r;
  if (*r == '-')
    {
      *r = '0';
      return (a);
    }
  else if (--r != a)
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
** '.' is 46 in ascii
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
      swp = *a;
      *a = *b;
      *b = swp;
      s = len[0];
      len[0] = len[1];
      len[1] = s;
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

  normalize_args(&a, &b, len, 0);
  r = malloc((len[0] > len[1] ? len[0] : len[1]) + 2);
  *r = '0';
  i = len[2];
  while (i > 0)
    r[i] = a[--i];
  a += (i = len[2]);
  while (*a && *b)
    r[++i] = *a == '.' && ++a && ++b ? '.' : *a++ + *b++ - 48;
  while (*b)
    r[++i] = *b++;
  while (*a)
    r[++i] = *a++;
  r[++i] = 0;
  while (--i >= 0)
    if (r[i] > '9')
      {
	r[i - 1] != '.' && ++r[i - 1] || ++r[i - 2];
	r[i] -= 10;
      }
  return (r);
}

char	*sub(char const *a, char const *b)
{
  char	*r;
  int	len[2];
  int	i;
  char	neg;

  neg = normalize_args(&a, &b, len, 1);
  r = malloc((len[0] > len[1] ? len[0] : len[1]) + 2);
  *r = '0';
  i = len[0] - len[1];
  while (i > 0)
    r[i] = a[--i];
  a += (i = len[0] - len[1]);
  while (*a)
    r[++i] = *a++ - *b++ + 48;
  r[++i] = 0;
  while (--i >= 0)
    if (r[i] < '0')
      {
	--r[i - 1];
	r[i] += 10;
      }
  return (neg ? negate(r) : r);
}

char	*mul(char const *a, char const *b)
{
  char	*r;
  int	len[3];
  int	i;
  int	j;

  normalize_args(&a, &b, len, 0);
  len[2] = len[0]-- + len[1]-- + 1;
  r = malloc(len[2] + 2);
  memset(r, 0, len[2] + 2);
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

int	scale = 10;

char	*div(char const *a, char const *b)
{
  extern int scale;
  int	len;
  char	*buf;
  char	*r;
  int	i;
  int	n;

  r = malloc(len = strlen(a) + scale + 2);
  memset(r, '0', len);
  buf = malloc(len);
  strncpy(buf, a, 1)[n = 1] = 0;
  *r = '0';
  i = 1;
  while (num_strcmp(buf, "0") && *a)
    {
      while (num_strcmp(buf, b) < 0 && a[n])
	{
	  buf[n] = a[n];
	  buf[++n] = 0;
	  r[i++] = '0';
	}
      while (num_strcmp(buf, b) >= 0)
	{
	  strcpy(buf, sub(buf, b));
	  ++r[i];
	}
      ++i, a += n, n = 1;
    }
  i || (r[i++] = '0');
  r[i] = 0;
  return (r);
}
