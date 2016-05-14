#include "algorithm.h"

int topo_print(Graph g) {
  // in degree
  SVertex s;
  JRB in_degree = make_jrb();
  graph_traverse(s, g) {
    EVertices adj = svertex_lst(s);
    EVertex v;
    evertices_traverse(v, adj) {
      jrb_record_int(in_degree, evertex_id(v));
    }
  }

  // print
  JRB seen = make_jrb();
  for (;;) {
    int n = 0;
    graph_traverse(s, g) {
      int u = svertex_id(s);
      if (jrb_contain_int(seen, u))
        continue;

      if (jrb_count_int(in_degree, u) == 0) {
        printf("%d ", u);
        jrb_mark_int(seen, u);
        ++n;
        EVertices adj = svertex_lst(s);
        EVertex v;
        evertices_traverse(v, adj) {
          jrb_unrecord_int(in_degree, evertex_id(v));
        }
        jrb_unrecord_int(in_degree, u);
      }
    }
    if (n == 0)
      break;
  }
  jrb_free_tree(in_degree);
  jrb_free_tree(seen);
}