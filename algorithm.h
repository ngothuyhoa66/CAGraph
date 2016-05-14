#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include "terms.h"

extern Dllist bfs(Graph g, Jval s);
extern Dllist dfs(Graph g, Jval s);
extern float dijikstra(Graph g, int start, int end, Dllist path);
extern int is_dag(Graph g);
extern Dllist topo_print(Graph g);

#endif  // ALGORITHM_H_