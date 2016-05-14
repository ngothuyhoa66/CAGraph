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
  graph_traverse(ptr, g) {
    Jval start = ptr->key;
    // BFS
    Queue q = new_queue();
    JRB seen = make_jrb();
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
          if (g.cmp(v, start) == 0) {
            // co chu trinh
            free_queue(q);
            jrb_free_tree(seen);
            return 0;
          }
          if (!jrb_contain_key(seen, v, g.cmp)) {
            en_queue(q, v);
            jrb_mark_key(seen, v, g.cmp);
          }          
        }
      }
    }
    free_queue(q);
    jrb_free_tree(seen);
  }
  return 1;  
}

Dllist topo_print(Graph g) {
  if (!is_dag(g))
    return 0;
  // in degree
  JRB in_degree = graph_export_indegree(g);

  // print
  JRB seen = make_jrb();
  Dllist out = new_dllist();
  for (;;) {
    int n = 0;
    JRB s;
    graph_traverse(s, g) {
      Jval u = s->key;
      if (jrb_contain_key(seen, u, g.cmp))
        continue;

      if (jrb_counter_key(in_degree, u, g.cmp) == 0) {
        dll_append(out, u);
        jrb_mark_key(seen, u, g.cmp);
        ++n;
        JRB tbl = (JRB) jval_v(s->val);
        JRB v;
        jrb_traverse(v, tbl) {
          jrb_unrecord_key(in_degree, v->key, g.cmp);
        }
      }
    }
    if (n == 0)
      break;
  }
  jrb_free_tree(in_degree);
  jrb_free_tree(seen);
  return out;
}