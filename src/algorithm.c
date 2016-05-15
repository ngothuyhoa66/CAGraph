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

const float kInvalidDijikstraDistance = -1;

float dijikstra(Graph g, Jval start, Jval end, Dllist path) {
  JRB dist = make_jrb();
  JRB back = make_jrb();
  JRB solved = make_jrb();
  JRB vertex;
  // khoi tao
  graph_traverse(vertex, g) {
    Jval key = vertex->key;
    jrb_insert_gen(dist, key, new_jval_f(g.cmp(vertex->key, start) == 0?
                        0: kInvalidDijikstraDistance), g.cmp);
    jrb_insert_gen(back, key, start, g.cmp);
  }

  // tim duong di
  for (;;) {
    Jval minv;
    float mindist = kInvalidDijikstraDistance;
    JRB ptr;
    jrb_traverse(ptr, dist) {
      // tim min
      if (!jrb_contain_key(solved, ptr->key, g.cmp)) {
        float d = jval_f(ptr->val);
        if (float_equal(mindist, kInvalidDijikstraDistance) ||
            mindist > d) {
          mindist = d;
          minv = ptr->key;
        }
      }

      // dk dung
      if (float_equal(mindist, kInvalidDijikstraDistance)) {
        return kInvalidDijikstraDistance;  // ko co duong di den end
      } else if (g.cmp(minv, end) == 0) {
        dll_prepend(path, end);
        Jval bk = end;
        while (g.cmp(bk, start) != 0) {
          JRB node = jrb_find_gen(back, bk, g.cmp);
          if (node) {
            bk = node->val;
            dll_prepend(path, bk);
          } else {
            printf("Loi xac dinh duong di.\n");
            return mindist;
          }
        }
        return mindist;
      }

      // sua duong di
      EVertex e;
      SVertex svt;
      graph_export_svertex(g, minv, &svt);
      evertices_traverse(e, svt) {
        if (jval_f(jrb_find_gen(dist, e.key, g.cmp)->val) > 
                mindist + e.weight) {
          jrb_insert_gen(dist, e.key, new_jval_f(mindist + e.weight), g.cmp);
          jrb_insert_gen(back, e.key, minv, g.cmp);
        }
      }
    }
  }
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