#include "algorithm.h"

Dllist bfs(Graph g, Jval start) {
  Dllist out = new_dllist();
  Queue q = new_queue();
  en_queue(q, start);
  JRB seen = make_jrb();
  jrb_mark_key(seen, start, g.cmp);
  while (!queue_empty(q)) {
    Jval u = de_queue(q);
    dll_append(out, u);
    SVertex nd; 
    if (graph_export_svertex(g, u, &nd) && !jrb_empty(nd.tbl)) {
      EVertex e;
      evertices_traverse(e, nd) {
        Jval v = e.key;
        if (!jrb_contain_key(seen, v, g.cmp)) {
          en_queue(q, v);
          jrb_mark_key(seen, v, g.cmp);
        }
      }
    }
  }
  free_queue(q);
  jrb_free_tree(seen);
  return out;
}

Dllist dfs(Graph g, Jval start) {
  Dllist out = new_dllist();
  Stack stk = new_stack();
  stack_push(stk, start);
  JRB seen = make_jrb();
  jrb_mark_key(seen, start, g.cmp);
  while (!stack_empty(stk)) {
    Jval u = stack_pop(stk);
    dll_append(out, u);
    SVertex nd; 
    if (graph_export_svertex(g, u, &nd) && !jrb_empty(nd.tbl)) {
      EVertex e;
      evertices_traverse(e, nd) {
        Jval v = e.key;
        if (!jrb_contain_key(seen, v, g.cmp)) {
          stack_push(stk, v);
          jrb_mark_key(seen, v, g.cmp);
        }
      }
    }
  }
  free_stack(stk);
  jrb_free_tree(seen);
  return out;
}

int is_dag(Graph g) {
  JRB ptr;
  JRB seen = make_jrb();
  graph_traverse(ptr, g) {
    Jval start = ptr->key;
    if (!jrb_contain_key(seen, start, g.cmp)) {
      // BFS
      Queue q = new_queue();
      en_queue(q, start);
      jrb_mark_key(seen, start, g.cmp);
      while (!queue_empty(q)) {
        Jval u = de_queue(q);
        SVertex svt;
        if (graph_export_svertex(g, u, &svt) ) {
          // luon phai kiem tra so dinh tra ve, vi neu so dinh bang 0, out co the khong hop le
          EVertex e;
          evertices_traverse(e, svt) {
            Jval v = e.key;
            if (!jrb_contain_key(seen, v, g.cmp)) {
              en_queue(q, v);
              jrb_mark_key(seen, v, g.cmp);
            } else {
              // co chu trinh
              free_queue(q);
              jrb_free_tree(seen);
              return 0;
            }
          }
        }
      }
      free_queue(q);
    }
  }
  jrb_free_tree(seen);
  return 1;  
}

// int topo_print(Graph g) {
//   // in degree
//   SVertex s;
//   JRB in_degree = make_jrb();
//   graph_traverse(s, g) {
//     EVertices adj = svertex_lst(s);
//     EVertex v;
//     evertices_traverse(v, adj) {
//       jrb_record_int(in_degree, evertex_id(v));
//     }
//   }

//   // print
//   JRB seen = make_jrb();
//   for (;;) {
//     int n = 0;
//     graph_traverse(s, g) {
//       int u = svertex_id(s);
//       if (jrb_contain_int(seen, u))
//         continue;

//       if (jrb_counter_int(in_degree, u) == 0) {
//         printf("%d ", u);
//         jrb_mark_int(seen, u);
//         ++n;
//         EVertices adj = svertex_lst(s);
//         EVertex v;
//         evertices_traverse(v, adj) {
//           jrb_unrecord_int(in_degree, evertex_id(v));
//         }
//         jrb_unrecord_int(in_degree, u);
//       }
//     }
//     if (n == 0)
//       break;
//   }
//   jrb_free_tree(in_degree);
//   jrb_free_tree(seen);
// }