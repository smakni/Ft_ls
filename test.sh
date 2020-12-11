#!/bin/bash

NOCOLOR='\033[0m'
RED='\033[0;31m'
LIGHTGREEN='\033[1;32m'

PATH_1=./../Ft_ls/ft_ls
PATH_2=ls

echo "${LIGHTGREEN}***********************************************************"
echo ">>>>>>>>>>>>>>>>>>>>TESTER<<<<<<<<<<<<<<<<<<<<<<<<<<"
echo "***********************************************************${NOCOLOR}"

read -p "Write here the options for ls : " OPT_1
read -p "Write here the path to list : " args

echo "${LIGHTGREEN}Store first to exec_1.debug...${NOCOLOR}"
$PATH_1 $OPT_1 $args > exec_1.debug

echo "${LIGHTGREEN}Store second to exec_2.debug...${NOCOLOR}"
$PATH_2 $OPT_1 $args > exec_2.debug

read -p "Store the output ? | less ? (y/n/less) " answer2
echo "${LIGHTGREEN}===========================================${NOCOLOR}"

if [ "$answer2" = "y" ] || [ "$answer2" = "Y" ] || [ "$answer2" = "yes" ]
then
	echo "${LIGHTGREEN}Store diff to diff.debug${NOCOLOR}"
	diff -y exec_1.debug exec_2.debug > diff.debug
elif [ "$answer2" = "less" ]
then
	diff -y exec_1.debug exec_2.debug | less
else
	diff -y exec_1.debug exec_2.debug 
	if [ $? != 0 ]
	then
		echo "${RED}==========================================="
		echo "[diff error]${NOCOLOR}"
	else
		echo "${LIGHTGREEN}==========================================="
		echo "[diff ok]${NOCOLOR}"
	fi
fi