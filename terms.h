// Copyright (C) 2016 Nguyen Ba Ngoc

#ifndef TERMS_H_
#define TERMS_H_

#include "libfdr/dllist.h"
#include "libfdr/jrb.h"

typedef JRB Graph;
typedef Dllist Stack;
typedef Dllist Queue;
typedef int (*CompareFuncGen)(Jval, Jval);

// ---------- JRB APIs ----------
extern void jrb_mark_int(JRB tree, int val);
extern int jrb_contain_int(JRB tree, int key);

// ---------- Graph APIs ---------
extern Graph new_graph();
extern void add_edge_gen(Graph g, Jval v1, Jval v2, CompareFuncGen func);
extern int get_adjacent_gen(Graph g, Jval v, CompareFuncGen func, JRB* out);

// ---------- Stack APIs ---------
extern Stack new_stack();
extern int stack_empty(Stack s);
extern int push_i(Stack s, int v);
extern int pop_i(Stack s);
extern void free_stack(Stack s);

// ---------- Queue APIs ---------
extern Queue new_queue();
extern int queue_empty(Queue q);
extern int en_queue_i(Queue q, int v);
extern int de_queue_i(Queue q);
extern void free_queue(Queue q);

// ----------Helper macros --------
#define str_equal(s1, s2) strcmp(s1, s2) == 0

#endif  // TERMS_H_

