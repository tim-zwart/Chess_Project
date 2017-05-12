#ifndef MOVEGEN_H_INCLUDED
#define MOVEGEN_H_INCLUDED

#include "libraries.h"
#include "bitboards.h"

struct node
{
    node* trunk;
    vector<node*> branches;
    Board container;
};

node* create(Board b);


#endif // MOVEGEN_H_INCLUDED
