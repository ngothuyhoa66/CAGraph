// Copyright (C) 2016 Nguyen Ba Ngoc

#include "terms.h"

#include <stdio.h>

#include "libfdr/jval.h"
#include "util.h"

// ---------- JRB APIs ----------
void jrb_mark_key(JRB tree, Jval key, CompareFunction cmp) {
  jrb_record_key(tree, key, cmp);
}

int jrb_contain_key(JRB tree, Jval key, CompareFunction cmp) {
  return jrb_counter_key(tree, key, cmp) > 0;
}

void jrb_record_key(JRB tree, Jval key, CompareFunction cmp) {
  JRB node = jrb_find_gen(tree, key, cmp);
  if (node) {
    node->val = new_jval_i(jval_i(node->val) + 1);
  } else {
    jrb_insert_gen(tree, key, new_jval_i(1), cmp);
  }
}

void jrb_unrecord_key(JRB tree, Jval key, CompareFunction cmp) {
  JRB node = jrb_find_gen(tree, key, cmp);
  if (node) {
    int cc = jval_i(node->val);
    if (cc > 0)
      node->val = new_jval_i(cc -1);
  } else {
    // Co the bao loi
  }
}

int jrb_counter_key(JRB tree, Jval key, CompareFunction cmp) {
  JRB node = jrb_find_gen(tree, key, cmp);
  return node? jval_i(node->val): 0;
}

int jrb_nodes_count(JRB tree) {
  if (tree == NULL)
    return 0;
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
Graph new_graph(CompareFunction jval_cmp) {
  Graph g;
  g.data = make_jrb();
  g.cmp = jval_cmp;
  return g;
}

void graph_add_vertex(Graph g, Jval v) {
  JRB node = jrb_find_gen(g.data, v, g.cmp);
  if (node) {
    // đã tồn tại
  } else {
    JRB lst = make_jrb();
    jrb_insert_gen(g.data, v, new_jval_v(lst), g.cmp);
  }
}

void graph_add_edge(Graph g, Jval v1, Jval v2, float w) {
  graph_add_vertex(g, v2);
  JRB s = jrb_find_gen(g.data, v1, g.cmp);
  JRB lst;
  if (s == NULL) {
    lst = make_jrb();
    jrb_insert_gen(g.data, v1, new_jval_v((void*)lst), g.cmp);
  } else {
    lst = (JRB) (jval_v(s->val));
  }

  if (jrb_find_gen(lst, v2, g.cmp) == NULL) {  // chua co dinh nay
    jrb_insert_gen(lst, v2, new_jval_f(w), g.cmp);
  }
}

int graph_export_svertex(Graph g, Jval v, SVertex* out) {
  JRB node = jrb_find_gen(g.data, v, g.cmp);
  if (node && out) {
    out->key = node->key;
    out->tbl = (JRB) jval_v(node->val);
    return 1;
  } else {
    return 0;
  }
}

JRB graph_export_indegree(Graph g) {
  JRB in_degree = make_jrb();
  JRB ptr;
  graph_traverse(ptr, g) {
    JRB tbl = (JRB) jval_v(ptr->val);
    JRB vv;
    jrb_traverse(vv, tbl) {
      jrb_record_key(in_degree, vv->key, g.cmp);
    }
  }
  return in_degree;
}

JRB adjacent_tree(Graph g, Jval v) {
  JRB tmp = jrb_find_gen(g.data, v, g.cmp);
  return tmp? (JRB) jval_v(tmp->val): NULL;
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

void stack_push(Stack s, Jval v) {
  if (s == NULL)
    return;
  dll_prepend(s, v);
}

Jval stack_pop(Stack s) {  // khong kiem tra stack rong
  Jval val = dll_val(dll_first(s));
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

void en_queue(Queue q, Jval v) {
  if (q == NULL)
    return;
  dll_append(q, v);
}

Jval de_queue(Queue q) {  // khong kiem tra q rong
  Jval val = dll_val(dll_first(q));
  dll_delete_node(dll_first(q));
  return val;
}

void free_queue(Queue q) {
  free_dllist(q);
}
