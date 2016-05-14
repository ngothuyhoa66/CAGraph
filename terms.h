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
  int next_vertex_id;
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
extern void jrb_mark_int(JRB tree, int key);
extern int jrb_contain_int(JRB tree, int key);
extern void jrb_record_int(JRB tree, int key);  // nếu key đã có trong tree, tăng biến đếm lên 1
extern void jrb_unrecord_int(JRB tree, int key);  // trừ 1 vào biến đếm
extern int jrb_counter_int(JRB tree, int key);  // đếm số lần key được record
extern int jrb_nodes_count(JRB tree); // số đỉnh trong cây

extern int dll_length(Dllist lst);  // Độ dài danh sach

// ---------- Graph APIs ---------
extern const int kInvalidVertexId;
extern Graph new_graph_gen(CompareFunction jval_cmp);
extern int graph_vertex_to_id(Graph g, Jval v);
extern Jval* graph_id_to_pvertex(Graph g, int id);

extern int svertex_id(SVertex s);
extern EVertices svertex_lst(SVertex s);
extern int evertex_id(EVertex e);
extern float evertex_w(EVertex e);

extern int graph_add_vertex_gen(Graph g, Jval v);
extern void graph_add_edge_gen(Graph g, Jval v1, Jval v2, float w);
extern Dllist graph_adjacent_list_gen(Graph g, Jval v);
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
