/********************************************************************************************************
** Program name: getch.c
** Class name: CS372
** Author: Ben Fridkis
** Date: 7/20/2018
** Description: This code was copied directly from: 
** 				https://stackoverflow.com/questions/7469139/what-is-equivalent-to-getch-getche-in-linux.
** 				It provides getch and getche, which provide a way to receive input from the input buffer
**				without a user-entered '\n'. (Note only getch() is used in chatclientEC)
**********************************************************************************************************/

#include "getch.h"

static struct termios old, new;

/* Initialize new terminal i/o settings */
void initTermios(int echo) 
{
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  new = old; /* make new settings same as old settings */
  new.c_lflag &= ~ICANON; /* disable buffered i/o */
  if (echo) {
      new.c_lflag |= ECHO; /* set echo mode */
  } else {
      new.c_lflag &= ~ECHO; /* set no echo mode */
  }
  tcsetattr(0, TCSANOW, &new); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo) 
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

/* Read 1 character without echo */
char getch() 
{
  return getch_(0);
}

/* Read 1 character with echo */
char getche() 
{
  return getch_(1);
}