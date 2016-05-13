// Copyright (C) 2016 Nguyen Ba Ngoc

#include "terms.h"
#include "util.h"

#include <stdio.h>
#include <string.h>

// tra ve 0 neu co loi,
//        1 neu thanh cong.
int parse_graph(char* fname, Graph* out) {
  FILE* f = fopen(fname, "r");
  if (!f)
    return 0;
  Graph g = new_graph();
  int n;  // so luong canh
  fscanf(f, "%d", &n);
  for (int i = 0; i < n; i++) {
    int u, v;
    fscanf(f, "%d%d", &u, &v);
    graph_add_edge(g, u, v, 1.0);
    graph_add_edge(g, v, u, 1.0);
  }
  fclose(f);
  *out = g;
  return 1;
}

void cmd_bfs_print(Graph g, int start) {  // duyet bfs bat dau tu start
  Queue q = new_queue();
  en_queue_i(q, start);
  JRB seen = make_jrb();
  jrb_mark_int(seen, start);
  while (!queue_empty(q)) {
    int u = de_queue_i(q);
    printf("%d ", u);  // tham dinh u
    EVertex ptr;
    EVertices out;
    if (graph_adjacent_list(g, u, &out) > 0) {
      // luon phai kiem tra so dinh tra ve, vi neu so dinh bang 0, out co the khong hop le
      evertices_traverse(ptr, out) {
        int v = evertex_id(ptr);
        if (!jrb_contain_int(seen, v)) {
          en_queue_i(q, v);
          jrb_mark_int(seen, v);
        }
      }
    }
  }
  free_queue(q);
  jrb_free_tree(seen);
}

void cmd_dfs_print(Graph g, int start) {  // duyet dfs bat dau tu start
  Stack s = new_stack();
  push_i(s, start);
  JRB seen = make_jrb();
  jrb_mark_int(seen, start);
  while (!stack_empty(s)) {
    int u = pop_i(s);
    printf("%d ", u);  // tham dinh u
    EVertex ptr;
    EVertices out;
    if (graph_adjacent_list(g, u, &out) > 0) {
      // luon phai kiem tra so dinh tra ve, vi neu so dinh bang 0, out co the khong hop le
      evertices_traverse(ptr, out) {
        int v = evertex_id(ptr);
        if (!jrb_contain_int(seen, v)) {
          push_i(s, v);
          jrb_mark_int(seen, v);
        }
      }
    }
  }
  free_stack(s);
  jrb_free_tree(seen);
}

void cmd_adjacent(Graph g, int u) {
  EVertices out = NULL;
  int n = graph_adjacent_list(g, u, &out);
  printf("n = %d\n", n);
  if (n > 0) {
    EVertex ptr;
    evertices_traverse(ptr, out) {
      printf("%d ", evertex_id(ptr));
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc == 1 || strcmp(argv[1], "--help") == 0) {
    printf("./g --help: hien thi huong dan su dung nay.\n"
           "./g adjacent g.txt 1: in ra so luong dinh ke voi dinh 1 va danh sach cac dinh nay\n"
           "./g bfs_print g.txt 1: duyet theo chieu rong va in ra cac dinh, bat dau tu dinh 1\n"
           "./g dfs_print g.txt 1: duyet theo chieu sau va in ra cac dinh, bat dau tu dinh 1\n");
  } else if (str_equal(argv[1], "bfs_print")) {
    Graph g;
    int start;
    if (parse_graph(argv[2], &g) && parse_int(argv[3], &start))
      cmd_bfs_print(g, start);
    else
      printf("Loi doc tham so.\n");
  } else if (str_equal(argv[1], "dfs_print")) {
    Graph g;
    int start;
    if (parse_graph(argv[2], &g) && parse_int(argv[3], &start))
      cmd_dfs_print(g, start);
    else
      printf("Loi doc tham so.\n");
  } else if (str_equal(argv[1], "adjacent")) {
    Graph g;
    int start;
    if (parse_graph(argv[2], &g) && parse_int(argv[3], &start)) {
      cmd_adjacent(g, start);
    } else {
      printf("Loi doc tham so.\n");
    }
  } else {
    printf("Cau lenh khong duoc ho tro.\n");
  }
  return 0;
}
