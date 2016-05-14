// Copyright (C) 2016 Nguyen Ba Ngoc

#include "terms.h"

#include <stdio.h>

#include "libfdr/jval.h"
#include "util.h"

// ---------- JRB APIs ----------
void jrb_mark_int(JRB tree, int key) {
  jrb_record_int(tree, key);
}

int jrb_contain_int(JRB tree, int key) {
  return jrb_counter_int(tree, key) > 0;
}

void jrb_record_int(JRB tree, int key) {
  JRB node = jrb_find_int(tree, key);
  if (node) {
    node->val = new_jval_i(jval_i(node->val) + 1);
  } else {
    jrb_insert_int(tree, key, new_jval_i(1));
  }
}

void jrb_unrecord_int(JRB tree, int key) {
  JRB node = jrb_find_int(tree, key);
  if (node) {
    int cc = jval_i(node->val);
    if (cc > 0)
      node->val = new_jval_i(cc -1);
  } else {
    // Co the bao loi
  }
}

int jrb_counter_int(JRB tree, int key) {
  JRB node = jrb_find_int(tree, key);
  return node? jval_i(node->val): 0;
}

int jrb_nodes_count(JRB tree) {
  JRB ptr;
  int cc = 0;
  jrb_traverse(ptr, tree)
    ++cc;
  return cc;
}

int dll_length(Dllist lst) {
  if (lst == NULL)
    return 0;
  Dllist ptr;
  int cc = 0;
  dll_traverse(ptr, lst)
    ++cc;
  return cc;
}

// ---------- Graph APIs ---------
const int kInvalidVertexId = -1;

Graph new_graph_gen(CompareFunction jval_cmp) {
  Graph g;
  g.data = make_jrb();
  g.vertex_to_id = make_jrb();
  g.id_to_vertex = make_jrb();
  g.next_vertex_id = 0;
  g.cmp = jval_cmp;
  return g;
}

Graph new_graph() {
  return new_graph_gen(&cmp_int);
}

int graph_vertex_to_id(Graph g, Jval v) {
  JRB node = jrb_find_gen(g.vertex_to_id, v, g.cmp);
  if (node)
    return jval_i(node->val);
  else
    return kInvalidVertexId;
}

Jval* graph_id_to_pvertex(Graph g, int id) {
  JRB node = jrb_find_int(g.id_to_vertex, id);
  if (node)
    return &(node->val);
  else
    return NULL;
}

int svertex_id(SVertex s) {
  return jval_i(s->key);
}

EVertices svertex_lst(SVertex s) {
  return (EVertices) jval_v(s->val);
}

int evertex_id(EVertex e) {
  return jval_i(e->key);
}

float evertex_w(EVertex e) {
  return jval_f(e->val);
}

int graph_add_vertex_gen(Graph g, Jval v) {
  JRB node = jrb_find_gen(g.vertex_to_id, v, g.cmp);
  if (node) {
    return jval_i(node->val);
  } else {
    int id = g.next_vertex_id++;
    jrb_insert_gen(g.vertex_to_id, v, new_jval_i(id), g.cmp);
    jrb_insert_int(g.id_to_vertex, id, v);
    return id;
  }
}

void graph_add_edge_gen(Graph g, Jval v1, Jval v2, float w) {
  int id1 = graph_add_vertex_gen(g, v1),
      id2 = graph_add_vertex_gen(g, v2);
  
  // add (u, v, w) to data
  SVertex s = jrb_find_int(g.data, id1);
  EVertices lst;
  if (s == NULL) {
    lst = make_jrb();
    jrb_insert_int(g.data, id1, new_jval_v((void*)lst));
  } else {
    lst = svertex_lst(s);
  }

  if (jrb_find_int(lst, id2) == NULL) {  // chua co dinh nay
    jrb_insert_int(lst, id2, new_jval_f(w));
  }
}

Dllist graph_adjacent_list_gen(Graph g, Jval v) {
  SVertex s = jrb_find_int(g.data, 
                           graph_vertex_to_id(g, v));
  if (s) {
    EVertices lst = svertex_lst(s);
    EVertex e;
    Dllist out = new_dllist();
    evertices_traverse(e, lst) {
      Jval* p = graph_id_to_pvertex(g, evertex_id(e));
      if (p)
        dll_append(out, *p);
    }
    return out;
  } else {
    return NULL;
  }
}

int is_dag(Graph g) {
  SVertex ptr;
  JRB seen = make_jrb();
  graph_traverse(ptr, g) {
    int start = svertex_id(ptr);
    if (!jrb_contain_int(seen, start)) {
      // BFS
      Queue q = new_queue();
      en_queue_i(q, start);
      jrb_mark_int(seen, start);
      while (!queue_empty(q)) {
        int u = de_queue_i(q);
        Dlllist out = graph_adjacent_list(g, new_jval_i(u));
        if (out) > 0) {
          // luon phai kiem tra so dinh tra ve, vi neu so dinh bang 0, out co the khong hop le
          evertices_traverse(ptr, out) {
            int v = evertex_id(ptr);
            if (!jrb_contain_int(seen, v)) {
              en_queue_i(q, v);
              jrb_mark_int(seen, v);
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

// ---------- Stack APIs ---------
Stack new_stack() {
  return new_dllist();
}

int stack_empty(Stack s) {
  return dll_empty(s);
}

void free_stack(Stack s) {
  free_dllist(s);
}

int push_i(Stack s, int v) {
  if (s == NULL)
    return 0;
  dll_prepend(s, new_jval_i(v));
  return 1;
}

int pop_i(Stack s) {  // khong kiem tra stack rong
  int val = jval_i(dll_val(dll_first(s)));
  dll_delete_node(dll_first(s));
  return val;
}

// ---------- Queue APIs ---------
Queue new_queue() {
  return new_dllist();
}

int queue_empty(Queue q) {
  return dll_empty(q);
}

int en_queue_i(Queue q, int v) {
  if (q == NULL)
    return 0;
  dll_append(q, new_jval_i(v));
  return 1;
}

int de_queue_i(Queue q) {  // khong kiem tra q rong
  int val = jval_i(dll_val(dll_first(q)));
  dll_delete_node(dll_first(q));
  return val;
}

void free_queue(Queue q) {
  free_dllist(q);
}
