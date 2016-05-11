// Copyright (C) 2016 Nguyen Ba Ngoc

#include "terms.h"

#include "libfdr/jval.h"

Graph new_graph() {
  return make_jrb();
}

void add_edge_gen(Graph g, Jval v1, Jval v2, int (*func)(Jval, Jval)) {
  JRB vertex = jrb_find_gen(g, v1, func);
  if (vertex == NULL) {
    vertex = make_jrb();
    jrb_insert_gen(v1, new_jval_v((void*)vertex));
  }

  if (jrb_find_gen(vertex, v2, func) == NULL) {  // chua co dinh nay
    jrb_insert_gen(vertex, v2, func);
  }
}

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
