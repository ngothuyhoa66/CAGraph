// Copyright (C) 2016 Nguyen Ba Ngoc

#ifndef TERMS_H_
#define TERMS_H_

#include "libfdr/dllist.h"
#include "libfdr/jrb.h"
typedef int (*CompareFunction)(Jval, Jval);

typedef struct {
  JRB data;
  JRB vertex_to_id;
  JRB id_to_vertex;
  int vertices_count;
  CompareFunction cmp;  // sử dụng để so sánh đỉnh
} Graph;
typedef JRB SVertex;  // đỉnh bắt đâu của một danh sách cạnh có hướng
typedef JRB SVertices;  // danh sách đỉnh bắt đầu
typedef JRB EVertex;  // đỉnh kết thúc của một cạnh có hướng, chứa trọng số cạnh
typedef JRB EVertices;  // danh sách đỉnh kết thúc (danh sách kề của một đỉnh)
typedef Dllist Stack;
typedef Dllist Queue;
typedef Dllist Path;

// ---------- JRB APIs ----------
extern void jrb_mark_int(JRB tree, int val);
extern int jrb_contain_int(JRB tree, int val);
extern void jrb_record_int(JRB tree, int val);  // nếu val đã có trong tree, tăng biến đếm lên 1
extern void jrb_unrecord_int(JRB tree, int val);  // trừ 1 vào biến đếm
extern int jrb_count_int(JRB tree, int val);  // đếm số lần gọi record với val

// ---------- Graph APIs ---------
extern Graph new_graph_gen(CompareFunction jval_cmp);
extern Graph new_graph();  // mặc định sử dụng id kiểu int
extern void graph_add_edge(Graph g, int v1, int v2, float w);
extern int graph_adjacent_list(Graph g, int v, EVertices* out);
extern int svertex_id(SVertex s);
extern EVertices svertex_lst(SVertex s);
extern int evertex_id(EVertex e);
extern float evertex_w(EVertex e);
extern void evertexes_free(EVertices lst);
extern int is_dag(Graph g);

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
#define evertices_traverse(ptr, lst) jrb_traverse(ptr, lst)
#define graph_traverse(ptr, g) jrb_traverse(ptr, g.data)

#endif  // TERMS_H_
