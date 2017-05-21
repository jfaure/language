%{
  #include "lang.h"
  #include "y.tab.h"

  void	api_t_all_destroy(t_all *this);
  static int	lex_t_all_new();
%}

%option		yylineno

DIGIT		[0-9]
ID		[a-z][a-z0-9]*
NOT_ALNUM	[^a-zA-Z0-9]
OPS_MATHS	"+"|"-"|"*"|"/"
FUNCTION_DEF	("def"|"func")
IF		"if"
ELIF		"elif"|"elsif"|"else if"
END		"end"

%%

" "|"\t"|"#".*"\n" /* Skip these */
"["|"]"|{OPS_MATHS}	return (*yytext);
{END}		return (END);
{FUNCTION_DEF}	puts("function def");
{IF}	        
{ID}		yylval.ID  = strdup(yytext); return (ID);
{DIGIT}+	return (lex_t_all_new());
<<EOF>>		|
'\0'		{ static char first = 0; ++first; return (first ? '\n' : EOF); }
\n		return ('\n');
.		return (*yytext);

%%

static inline int	lex_t_all_new()
{
  if (yyleng < 10)
    yylval.T_ALL = api_t_all_new(0, T_FIXNUM, (t_value) atoi(yytext));
  else
    yylval.T_ALL = api_t_all_new(0, T_BIGNUM, (t_value) strdup(yytext));
  return (T_ALL);
}

int	api_eval_string(char const *prog)
{
  YY_BUFFER_STATE	state;

  state = yy_scan_string(prog);
  yyparse();
  yy_delete_buffer(state);
}

int	yywrap()
{
  return (1);
}
