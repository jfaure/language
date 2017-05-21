/*
** parse.y for  in /home/jamie/myp
** 
** Made by James Faure
** Login   <james.faure@epitech.eu>
** 
** Started on  Tue May  9 03:37:36 2017 James Faure
** Last update Sat May 20 16:18:36 2017 James Faure
*/

%{
  #include "ops.h"
  #include "lang.h"
  #include <stdio.h>
  #include <string.h>

  int	yylex(void);
  void	yyerror(char const *);
  
#include "top.c" //!!!!!!!
%}

%define api.value.type union
/*
** The lexer handles miscellaneous initialization work for raw <t_all *>,
** the semantic type of all language objects, since it is the earliest place
** where these may be recognized.
*/
%token <t_all *> T_ALL
%token <char *> ID
%token DEF F_RETURN IF ELIF ELSE END
%type <t_all *> obj id
%type <t_list *> list comma_list// comma_list_opt_paren

%left '-' '+'
%left '*' '/'
%left '[' ']'

%%

input: %empty | input line ;

line:
'\n'
| obj '\n'	{ api_puts($1);	}
| error '\n'	{ yyerrok;	}

obj:
T_ALL		{ $$ = $1;		}
| list		{ $$ = api_t_all_new(0, T_LIST, (t_value) $1);		}
| id		{ $$ = $1;		}
| '+' obj	{ $$ = $2;		}
| '-' obj	{ $$ = $2; negate($2->value.bignum);	}
| obj '+' obj	{ $$ = top_sum($1, $3);	}
| obj '-' obj	{ $$ = top_sub($1, $3); }
| obj '*' obj	{ $$ = top_mul($1, $3); }
| obj '/' obj { $$ = top_div($1, $3); }
| '(' obj ')'	{ $$ = $2;		}
| list '[' obj ']'	{ $$ = api_list_get($1, 0, $3);		}
;

id:
ID			{ if (!($$ = getsym($1))) YYERROR;	}
| ID '=' obj	{ putsym($1, $3); $$ = $3;		}
;


list:
'[' comma_list ']'			{ $$ = $2;	}
| list '[' obj ':' obj ']'	{ $$ = api_list_slice($1, $3, $5); }
;

comma_list:
%empty				{ $$ = api_list_new(0); }
| T_ALL				{ $$ = api_list_new(1, $1);	}
| comma_list ',' obj	{ $$ = $1; api_list_push($$, $3);	}
;

%%

void	yyerror(char const *s)
{
  extern int	yylineno;

  fprintf(stderr, "(line %d) %s\n", yylineno, s);
}
