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

Vertex new_vertex_i(int id) {
  return new_jval_i(id);
}

void add_edge_gen(Graph g, Vertex v1, Vertex v2, float w, CompareFuncGen func) {
  JRB node = jrb_find_gen(g, v1, func);
  JRB vertex;
  if (node == NULL) {
    vertex = make_jrb();
    jrb_insert_gen(g, v1, new_jval_v((void*)vertex), func);
  } else {
    vertex = (JRB) jval_v(node->val);
  }

  if (jrb_find_gen(vertex, v2, func) == NULL) {  // chua co dinh nay
    jrb_insert_gen(vertex, v2, new_jval_f(w), func);
  }
}

int get_adjacent_gen(Graph g, Vertex v, CompareFuncGen func, EdgeTree* out) {
  int n = 0;
  JRB node = jrb_find_gen(g, v, func);
  if (node == NULL)
    return 0;
  Edge ptr;
  EdgeTree edges = (JRB) jval_v(node->val);
  jrb_traverse(ptr, edges)
    n++;
  *out = edges;
  return n;
}

int edge_end_i(Edge e) {
  return jval_i(e->key);
}

int edge_weight_f(Edge e) {
  return jval_f(e->val);
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
