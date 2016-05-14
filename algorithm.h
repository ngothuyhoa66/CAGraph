#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include "terms.h"

extern float dijikstra(Graph g, int start, int end, Path path);

extern int topo_print(Graph g);

#endif  // ALGORITHM_H_