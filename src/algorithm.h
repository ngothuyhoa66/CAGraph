#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include "terms.h"

extern const float kInvalidDijikstraDistance;

extern Dllist bfs(Graph g, Jval s);
extern Dllist dfs(Graph g, Jval s);
extern float dijikstra(Graph g, Jval start, Jval end, Dllist path);
extern int is_dag(Graph g);
extern Dllist topo_print(Graph g);

#endif  // ALGORITHM_H_