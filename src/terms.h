// Copyright (C) 2016 Nguyen Ba Ngoc

#ifndef TERMS_H_
#define TERMS_H_

#include "libfdr/dllist.h"
#include "libfdr/jrb.h"
typedef int (*CompareFunction)(Jval, Jval);
typedef void (*FreeComplexVertex)(Jval);


/*
 * TODO(bangoc): Vấn đề giải phóng bộ nhớ dữ liệu đồ thị.
 * Cân nhắc việc tìm kiếm giải pháp khái quát cho vấn đề giải phóng
 * dữ liệu đồ thị, có tính đến các giải pháp lưu trữ dữ liệu đỉnh 
 * khác nhau.
 *
 * Hiện tại, mọi người cần tự định nghĩa hàm giải phóng đồ thị cho
 * phù hợp với cách cấp phát bộ nhớ cho đỉnh của mình.
 */

typedef struct {
  JRB data;
  CompareFunction cmp;  // sử dụng để so sánh đỉnh
} Graph;
typedef struct {
  Jval key;
  float weight;
} EVertex; // đỉnh kết thúc của một cạnh có hướng, chứa trọng số cạnh
typedef struct {
  Jval key;
  JRB tbl;
  JRB ptr;
} SVertex;  // đỉnh bắt đâu của một danh sách cạnh có hướng

typedef Dllist Stack;
typedef Dllist Queue;
typedef Dllist Path;

// ---------- JRB APIs ----------
extern void jrb_mark_key(JRB tree, Jval key, CompareFunction cmp);
extern int jrb_contain_key(JRB tree, Jval key, CompareFunction cmp);
extern void jrb_record_key(JRB tree, Jval key, CompareFunction cmp);  // nếu key đã có trong tree, tăng biến đếm lên 1
extern void jrb_unrecord_key(JRB tree, Jval key, CompareFunction cmp);  // trừ 1 vào biến đếm
extern int jrb_counter_key(JRB tree, Jval key, CompareFunction cmp);  // đếm số lần key được record
extern int jrb_nodes_count(JRB tree); // số đỉnh trong cây

extern int dll_length(Dllist lst);  // Độ dài danh sach

// ---------- Graph APIs ---------
extern Graph new_graph(CompareFunction jval_cmp);

extern void graph_add_vertex(Graph g, Jval v);
extern void graph_add_edge(Graph g, Jval v1, Jval v2, float w);
extern int graph_export_svertex(Graph g, Jval v, SVertex* out);
extern JRB graph_export_indegree(Graph g);
extern JRB adjacent_tree(Graph g, Jval v);
extern void free_graph(Graph g);

// ---------- Stack APIs ---------
extern Stack new_stack();
extern int stack_empty(Stack s);
extern void stack_push(Stack s, Jval v);
extern Jval stack_pop(Stack s);
extern void free_stack(Stack s);

// ---------- Queue APIs ---------
extern Queue new_queue();
extern int queue_empty(Queue q);
extern void en_queue(Queue q, Jval v);
extern Jval de_queue(Queue q);
extern void free_queue(Queue q);

// ----------Helper macros --------
#define str_equal(s1, s2) strcmp(s1, s2) == 0
#define adjacent_traverse(g, v, ptr, tree) \
    tree = adjacent_tree(g, v);            \
    if (tree)                              \
      jrb_traverse(ptr, tree)
#define vkey(ptr) ptr->key
#define vweight(ptr) jval_f(ptr->val)
#define graph_traverse(ptr, g) jrb_traverse(ptr, g.data)

#define float_abs(f) (f < 0? -f: f)
#define float_equal(f1, f2) (float_abs(f1 - f2) < 1e-5)

#endif  // TERMS_H_
