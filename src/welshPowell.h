#ifndef WELSHPOWELL_H
#define WELSHPOWELL_H

#include "graphes.h"

int compareDegree(const void* a, const void* b);
int areNeighbors(Node* node1, Node* node2);
int findAvailableColor_wp(Node* node, int numColors) ;
int welshPowell(Graph *graph);


#endif 