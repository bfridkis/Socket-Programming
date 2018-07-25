/**********************************************************************************
** Program name: get_in_addr.c
** Class name: CS372
** Author: Ben Fridkis
** Date: 7/16/2018
** Description: Simple client-side chat program to demonstrate socket programming.
***********************************************************************************/

#include "get_in_addr.h"

//get sockaddr, IPv4 or IPv6:
//Returns a void pointer so either 
//--IPv4 or IPv6 socket input address
//--can be accomodated.
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}
