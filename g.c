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
  Graph g = new_graph_gen(&cmp_int);
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
    Dllist out = graph_adjacent_list_gen(g, new_jval_i(u));
    if (out) {
      // luon phai kiem tra so dinh tra ve, vi neu so dinh bang 0, out co the khong hop le
      Dllist ptr;
      dll_traverse(ptr, out) {
        int v = jval_i(ptr->val);
        if (!jrb_contain_int(seen, v)) {
          en_queue_i(q, v);
          jrb_mark_int(seen, v);
        }
      }
      free_dllist(out);
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
    Dllist out = graph_adjacent_list_gen(g, new_jval_i(u));
    if (out) {
      // luon phai kiem tra so dinh tra ve, vi neu so dinh bang 0, out co the khong hop le
      Dllist ptr;
      dll_traverse(ptr, out) {
        int v = jval_i(ptr->val);
        if (!jrb_contain_int(seen, v)) {
          push_i(s, v);
          jrb_mark_int(seen, v);
        }
      }
      free_dllist(out);
    }
  }
  free_stack(s);
  jrb_free_tree(seen);
}

void cmd_adjacent(Graph g, int u) {
  Dllist out = NULL;
  out = graph_adjacent_list_(g, new_jval_i(u));
  printf("n = %d\n", dll_length(out));
  if (out) {
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
