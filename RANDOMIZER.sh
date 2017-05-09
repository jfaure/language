#!/bin/sh
## RANDOMIZER.sh for debug in /home/guitta_l/projets/bistro
##
## Made by Louis GUITTARD
## Login   <guitta_l@epitech.net>
##
## Started on  Mon Oct 26 22:41:54 2015 Louis GUITTARD
## Last update Sun Feb  5 06:38:33 2017 Jamie Faure
##

GREEN="\\033[32;7m"
GREEN_RES="\\033[32m"
RED="\\033[31;5m"
RED_RES="\\033[31m"
BLUE="\\033[34m"
MAGENTA="\\033[35m"
YELLOW="\\033[33m"
NORMAL="\\033[m"

PROB=0
Here="AUTO_GEN_FILES/"
digits="0123456789"
operators="$1"
time=0
time2=0
size=0
size2=0

if [ -z "$4" ]
then
    echo -e "\nUsage : ./RANDOMIZER "operands" "nb_tests" "nb_length1" "nb_length2"\n"
    exit
fi

rm -rf ${Here}
mkdir ${Here}

echo ------------------
for (( c = 1; c <= $2; c++ ))
do
    for (( t = 0; t < $3; t++ ))
    do
        rand="$rand$RANDOM"
    done
    for (( t = 0; t < $4; t++ ))
    do
	rand2="$rand2$RANDOM"
    done
    SIZE=${#rand}
    SIZE2=${#rand2}
    size=$(echo "$size+$SIZE" | bc)
    size2=$(echo "$size2+$SIZE2" | bc)
    tot=$(echo -e "$rand${operators:$(($RANDOM%${#operators})):1}$rand2")
    START=$(date +%s.%N)
    echo $(echo $tot | ./calc "0123456789" "()+-*/%" `echo -n $tot | wc -c` 2> ${Here}debug) 1> ${Here}debug1
    SPEED=$(echo "$(date +%s.%N) - $START" | bc -l 2> ${Here}debug2)
    time=$(echo "$time+$SPEED" | bc -l)
    START2=$(date +%s.%N)
    echo $(echo $tot | bc 2> ${Here}debug2) | sed 's/[\\ ]//g' 1> ${Here}debug3
    SPEED2=$(echo "$(date +%s.%N) - $START2" | bc -l 2> ${Here}debug2)
    time2=$(echo "$time2+$SPEED2" | bc -l)
    diff -s ${Here}debug1 ${Here}debug3 > /dev/null ; echo $? > ${Here}store
    echo -n "Test ${c} : "
    if [ $(cat ${Here}store) != 0 ]
    then
        echo -e "[${RED}ERROR${NORMAL}]   ==>[ ${tot} ]<=="
	echo -e "${RED_RES} $(diff -s ${Here}debug1 ${Here}debug2 | cat)${NORMAL}"
	(( PROB++ ))
    else
	if [ "$(cat ${Here}debug)" == "syntax error" ]
        then
	    echo -n -e "[${GREEN}OK${NORMAL}] ${tot} = "
            echo -e "${GREEN_RES} $(cat ${Here}debug)${NORMAL}"
        else
	    echo -n -e "[${GREEN}OK${NORMAL}] ${tot} = ${RED_RES}"
            echo -e "${GREEN_RES}$(echo $(echo "${tot}" | bc) | sed 's/[\\ ]//g')${NORMAL}"
        fi
    fi
    rand=0
    rand2=0
done
echo -e "\n ${BLUE}Bug(s) restant(s) : ${PROB}${NORMAL}\n"
time=$(echo "$time/$c" | bc -l)
time2=$(echo "$time2/$c" | bc -l)
size=$(echo "$size/($c-1)" | bc)
size2=$(echo "$size2/($c-1)" | bc)
echo -e " ${MAGENTA}vitesse moyenne de la bistro pour un calcul : $time seconds"
echo -e " vitesse moyenne de BC pour un calcul : $time2 seconds${NORMAL}\n"
echo -e " ${YELLOW}Taille moyenne du premier nombre : ${size} caractere(s)"
echo -e " Taille moyenne du deuxieme nombre : ${size2} caractere(s)${NORMAL}\n"

echo ------------------

rm -rf ${Here}debug
rm -rf ${Here}debug1
rm -rf ${Here}debug2
rm -rf ${Here}debug3
rm -rf ${Here}store
rm -rf ${Here}
