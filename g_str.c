// Copyright (C) 2016 Nguyen Ba Ngoc

#include "src/algorithm.h"
#include "src/terms.h"
#include "src/util.h"

#include <stdio.h>
#include <string.h>

void cmd_bfs_print(Graph g, char* start) {  // duyet bfs bat dau tu start
  Dllist out = bfs(g, new_jval_s(start));
  Dllist ptr;
  printf("n = %d\n", dll_length(out));
  dll_traverse(ptr, out) {
    printf("%s ", jval_s(ptr->val));
  }
  printf("\n");
  free_dllist(out);
}

void cmd_dfs_print(Graph g, char* start) {  // duyet bfs bat dau tu start
  Dllist out = dfs(g, new_jval_s(start));
  Dllist ptr;
  printf("n = %d\n", dll_length(out));
  dll_traverse(ptr, out) {
    printf("%s ", jval_s(ptr->val));
  }
  printf("\n");
  free_dllist(out);
}

void cmd_usage() {
  printf("./g --help: hien thi huong dan su dung nay.\n"
         "./g adjacent g.txt 1: in ra so luong dinh ke voi dinh 1 va danh sach cac dinh nay\n"
         "./g bfs_print g.txt 1: duyet theo chieu rong va in ra cac dinh, bat dau tu dinh 1\n"
         "./g dfs_print g.txt 1: duyet theo chieu sau va in ra cac dinh, bat dau tu dinh 1\n");
}

void cmd_adjacent(Graph g, char* u) {
  JRB ptr, tree;
  int n = 0;
  adjacent_traverse(g, new_jval_s(u), ptr, tree) {
    printf("%s ", jval_s(vkey(ptr)));
    ++n;
  }
  if (tree) {
    printf("n = %d\n", n);
  } else {
    printf("Dinh ko ton tai.\n");
  }
}

int main(int argc, char *argv[]) {
  if (argc == 1 || strcmp(argv[1], "--help") == 0) {
    cmd_usage();
  } else if (str_equal(argv[1], "bfs_print")) {
    Graph g;
    if (parse_graph_ustr(argv[2], &g))
      cmd_bfs_print(g, argv[3]);
    else
      printf("Loi doc tham so.\n");
  } else if (str_equal(argv[1], "dfs_print")) {
    Graph g;
    if (parse_graph_ustr(argv[2], &g)) {
      cmd_dfs_print(g, argv[3]);
    } else{
      printf("Loi doc tham so.\n");
    }
  } else if (str_equal(argv[1], "adjacent")) {
    Graph g;
    if (parse_graph_ustr(argv[2], &g)) {
      cmd_adjacent(g, argv[3]);
    } else {
      printf("Loi doc tham so.\n");
    }
  } else {
    printf("Cau lenh khong duoc ho tro.\n");
  }
  return 0;
}
