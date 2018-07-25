/***************************************
** Program name: getch.h
** Class name: CS372
** Author: Ben Fridkis
** Date: 7/20/2018
** Description: Header file for getch.c
****************************************/

#ifndef getch_h
#define getch_h

#include <termios.h>
#include <stdio.h>

void initTermios(int echo);
void resetTermios(void);
char getch_(int echo);
char getch(); 
char getche();

#endif /* get_in_addr_h */