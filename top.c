/*
** top.c for  in /home/jamie/myp
** 
** Made by James Faure
** Login   <james.faure@epitech.eu>
** 
** Started on  Mon May 15 19:53:17 2017 James Faure
** Last update Mon May 15 22:26:56 2017 James Faure
*/

t_all	*top_sum(t_all *a, t_all *b)
{
  if (a->type == T_FIXNUM)
    a->value.fixnum = (a->value.fixnum + b->value.fixnum);
  else if (a->type == T_BIGNUM)
    a->value.bignum = sum(a->value.bignum, b->value.bignum);
  return (a);
}

t_all	*top_sub(t_all *a, t_all *b)
{
    if (a->type == T_FIXNUM)
    a->value.fixnum = (a->value.fixnum - b->value.fixnum);
  else if (a->type == T_BIGNUM)
  a->value.bignum = sub(a->value.bignum, b->value.bignum);
  return (a);
}

t_all	*top_mul(t_all *a, t_all *b)
{
  if (a->type == T_FIXNUM)
    a->value.fixnum = (a->value.fixnum * b->value.fixnum);
  else if (a->type == T_BIGNUM)
    a->value.bignum = mul(a->value.bignum, b->value.bignum);
  return (a);
}

t_all	*top_div(t_all *a, t_all *b)
{
  if (a->type == T_FIXNUM)
    a->value.fixnum = (a->value.fixnum / b->value.fixnum);
  else if (a->type == T_BIGNUM)
    a->value.bignum = div(a->value.bignum, b->value.bignum);
  return (a);
}
