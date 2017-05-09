##
## Makefile for  in /home/jamie/myp
## 
## Made by James Faure
## Login   <james.faure@epitech.eu>
## 
## Started on  Tue May  9 01:03:07 2017 James Faure
## Last update Tue May  9 04:42:22 2017 James Faure
##

NAME	=	calc

CFLAGS	=	-ggdb3

all:
	bison parse.y -o prs.c
	gcc $(CFLAGS) -o $(NAME) add.c prs.c
