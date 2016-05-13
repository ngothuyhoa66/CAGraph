// Copyright (C) 2016 Nguyen Ba Ngoc

#include "terms.h"

#include <stdio.h>

#include "libfdr/jval.h"

// ---------- JRB APIs ----------
void jrb_mark_int(JRB tree, int val) {
  jrb_insert_int(tree, val, new_jval_i(1));
}

int jrb_contain_int(JRB tree, int key) {
  return jrb_find_int(tree, key)? 1: 0;
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
