##
## Makefile for  in /home/jamie/myp
## 
## Made by James Faure
## Login   <james.faure@epitech.eu>
## 
## Started on  Tue May  9 01:03:07 2017 James Faure
## Last update Tue May 16 14:39:02 2017 James Faure
##

NAME	=	l

CFLAGS	=	-Iinclude -ggdb3 -fgnu89-inline
LFLAGS	=	-lreadline

SRC	=	main.c floats.c list.c

PARSER	=	prs.c
LEXER	=	lexer.c

all:	$(PARSER) $(LEXER)
	gcc $(CFLAGS) -o $(NAME) $(SRC) prs.c lexer.c $(LFLAGS)

$(PARSER): parse.y
	bison -o prs.c --defines=include/y.tab.h parse.y
$(LEXER): flex.c
	flex -o lexer.c flex.c
