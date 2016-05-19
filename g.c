// Copyright (C) 2016 Nguyen Ba Ngoc

#include "src/algorithm.h"
#include "src/terms.h"
#include "src/util.h"

#include <stdio.h>
#include <string.h>

void cmd_bfs_print(Graph g, int start) {  // duyet bfs bat dau tu start
  Dllist out = bfs(g, new_jval_i(start));
  Dllist ptr;
  printf("n = %d\n", dll_length(out));
  dll_traverse(ptr, out) {
    printf("%d ", jval_i(ptr->val));
  }
  printf("\n");
  free_dllist(out);
}

void cmd_dfs_print(Graph g, int start) {  // duyet bfs bat dau tu start
  Dllist out = dfs(g, new_jval_i(start));
  Dllist ptr;
  printf("n = %d\n", dll_length(out));
  dll_traverse(ptr, out) {
    printf("%d ", jval_i(ptr->val));
  }
  printf("\n");
  free_dllist(out);
}

void cmd_usage() {
  printf("./g --help: hien thi huong dan su dung nay.\n"
         "./g adjacent g.txt 1: in ra so luong dinh ke voi dinh 1 va danh sach cac dinh nay\n"
         "./g bfs_print g.txt 1: duyet theo chieu rong va in ra cac dinh, bat dau tu dinh 1\n"
         "./g dfs_print g.txt 1: duyet theo chieu sau va in ra cac dinh, bat dau tu dinh 1\n"
         "./g isdag g.txt: kiem tra xem g.txt co phai la DAG hay khong\n"
         "./g topo_print g.txt: in ra danh sach dinh theo trinh tu topo\n"
         "./g dijikstra g.txt 1 5: tim duong di ngan nhat tu 1 toi 5\n");
}

void cmd_topo(Graph g) {
  Dllist out = topo_print(g);
  if (out) {
    Dllist ptr;
    printf("n = %d\n", dll_length(out));
    dll_traverse(ptr, out) {
      printf("%d ", jval_i(ptr->val));
    }
    printf("\n");
  } else {
    printf("Do thi ko thoa man dieu kien DAG.\n");
  }
}

void cmd_dijikstra(Graph g, int start, int end) {
  Dllist path = new_dllist();
  float w;
  w = dijikstra(g, new_jval_i(start), new_jval_i(end), path);
  int n = dll_length(path);
  if (n > 0) {
    printf("w = %.2f n = %d\n", w, n);
    Dllist ptr;
    dll_traverse(ptr, path) {
      printf("%d ", jval_i(ptr->val));
    }
  } else {
    printf("Khong ton tai duong di tu %d den %d\n", start, end);
  }
}

void cmd_adjacent(Graph g, int u) {
  JRB ptr, tree;
  int n = 0;
  adjacent_traverse(g, new_jval_i(u), ptr, tree) {
    printf("%d ", jval_i(vkey(ptr)));
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
    int start;
    if (parse_graph_ud(argv[2], &g) && parse_int(argv[3], &start))
      cmd_bfs_print(g, start);
    else
      printf("Loi doc tham so.\n");
  } else if (str_equal(argv[1], "dfs_print")) {
    Graph g;
    int start;
    if (parse_graph_ud(argv[2], &g) && parse_int(argv[3], &start)) {
      cmd_dfs_print(g, start);
    } else{
      printf("Loi doc tham so.\n");
    }
  } else if (str_equal(argv[1], "adjacent")) {
    Graph g;
    int start;
    if (parse_graph_ud(argv[2], &g) && parse_int(argv[3], &start)) {
      cmd_adjacent(g, start);
    } else {
      printf("Loi doc tham so.\n");
    }
  } else if (str_equal(argv[1], "is_dag")) {
    Graph g;
    if (parse_graph_d(argv[2], &g)) {
      printf("%s\n", is_dag(g)? "Khong co chu trinh.\n":
                                "Co chu trinh.\n");
    } else {
      printf("Loi doc tham so.\n");
    }
  } else if(str_equal(argv[1], "topo_print")) {
    Graph g;
    if (parse_graph_d(argv[2], &g)) {
      cmd_topo(g);
    } else {
      printf("Loi doc tham so.\n");
    }
  } else if (str_equal(argv[1], "dijikstra")) {
    Graph g;
    int start, end;
    if (parse_graph_udw(argv[2], &g) &&
        parse_int(argv[3], &start) && parse_int(argv[4], &end)) {
      cmd_dijikstra(g, start, end);
    } else {
      printf("Loi doc tham so.\n");
    }
  } else {
    printf("Cau lenh khong duoc ho tro.\n");
  }
  return 0;
}
