/*
** parse.y for  in /home/jamie/myp
** 
** Made by James Faure
** Login   <james.faure@epitech.eu>
** 
** Started on  Tue May  9 03:37:36 2017 James Faure
** Last update Tue May  9 20:09:23 2017 James Faure
*/

%{
  #include "ops.h"
  #include <ctype.h>
  #include <stdio.h>
  #include <string.h>

  int	yylex(void);
  void	yyerror(char const *);
  char	*get_next_number(const int fd);
  char	*format_number(char *a);
%}

%define api.value.type union
%token <char *> NUM
%type <char *> exp

%left '-' '+'
%left '*' '/'

%%

input:
  %empty
| input line
;

line:
  '\n'
| exp '\n'	{ free(format_number($1));	}
| error '\n'	{ yyerrok;	}

exp:
NUM		{ $$ = $1;		}
| '+' exp	{ $$ = $2;		}
| '-' exp	{ $$ = negate($2);	}
| exp '+' exp	{ $$ = sum($1, $3); free($1); free($3);	} // Is this safe ?
| exp '-' exp	{ $$ = sub($1, $3); free($1); free($3);	}
| exp '*' exp	{ $$ = mul($1, $3); free($1); free($3);	}
| exp '/' exp	{
  if (!num_strcmp($3, "0"))
    YYABORT;
  $$ = div($1, $3); free($1); free($3);
  }
| '(' exp ')'	{ $$ = $2;		}
;

%%

void	yyerror(char const *s)
{
  fprintf(stderr, "%s\n", s);
}

#define MYPRINTF
//#define MYPRINTF printf
int	yylex()
{
  char	c;
  char	*buf;

  while ((c = getchar()) == ' ' || c == '\t');
  if (c == '.' || isdigit(c))
    {
      ungetc(c, stdin);
      scanf("%m[.0-9]", &buf);
      yylval.NUM = buf;
      MYPRINTF("got: %s\n", (char *) (yylval.NUM));
      return (NUM);
    }
  if (c == EOF)
    return (0);
  MYPRINTF("returning: %c\n", c);
  return (c);
}

int	main()
{
  yyparse();
}
