// Copyright (C) 2016 Nguyen Ba Ngoc

#include "terms.h"

#include <stdio.h>

#include "libfdr/jval.h"

// ---------- JRB APIs ----------
void jrb_mark_int(JRB tree, int val) {
  if (!jrb_contain_int(tree, val))
    jrb_insert_int(tree, val, new_jval_i(1));
}

int jrb_contain_int(JRB tree, int val) {
  return jrb_find_int(tree, val)? 1: 0;
}

void jrb_record_int(JRB tree, int val) {
  JRB node = jrb_find_int(tree, val);
  if (node) {
    node->val = new_jval_i(jval_i(node->val) + 1);
  } else {
    jrb_insert_int(tree, val, new_jval_i(1));
  }
}

void jrb_unrecord_int(JRB tree, int val) {
  JRB node = jrb_find_int(tree, val);
  if (node) {
    int cc = jval_i(node->val);
    if (cc > 0)
      node->val = new_jval_i(cc -1);
  } else {
    // Co the bao loi
  }
}

int jrb_count_int(JRB tree, int val) {
  JRB node = jrb_find_int(tree, val);
  return node? jval_i(node->val): 0;
}

// ---------- Graph APIs ---------
Graph new_graph() {
  return make_jrb();
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

void evertexes_free(EVertices lst) {
  jrb_free_tree(lst);
}

void graph_add_edge(Graph g, int v1, int v2, float w) {
  SVertex s = jrb_find_int(g, v1);
  EVertices lst;
  if (s == NULL) {
    lst = make_jrb();
    jrb_insert_int(g, v1, new_jval_v((void*)lst));
  } else {
    lst = svertex_lst(s);
  }

  if (jrb_find_int(lst, v2) == NULL) {  // chua co dinh nay
    jrb_insert_int(lst, v2, new_jval_f(w));
  }
}

int graph_adjacent_list(Graph g, int v, EVertices* out) {
  int n = 0;
  SVertex s = jrb_find_int(g, v);
  if (s == NULL)
    return 0;
  EVertex ptr;
  EVertices lst = svertex_lst(s);
  evertices_traverse(ptr, lst)
    n++;
  *out = lst;
  return n;
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
        EVertex ptr;
        EVertices out;
        if (graph_adjacent_list(g, u, &out) > 0) {
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
