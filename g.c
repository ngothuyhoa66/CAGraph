// Copyright (C) 2016 Nguyen Ba Ngoc

#include "src/terms.h"
#include "src/util.h"

#include <stdio.h>
#include <string.h>

// tra ve 0 neu co loi,
//        1 neu thanh cong.
int parse_graph(char* fname, Graph* out) {
  FILE* f = fopen(fname, "r");
  if (!f)
    return 0;
  Graph g = new_graph(&cmp_int);
  int n;  // so luong canh
  fscanf(f, "%d", &n);
  for (int i = 0; i < n; i++) {
    int u, v;
    fscanf(f, "%d%d", &u, &v);
    graph_add_edge(g, new_jval_i(u), new_jval_i(v), 1.0);
    graph_add_edge(g, new_jval_i(v), new_jval_i(u), 1.0);
  }
  fclose(f);
  *out = g;
  return 1;
}

// tra ve 0 neu co loi,
//        1 neu thanh cong.
int parse_graph_directed(char* fname, Graph* out) {
  FILE* f = fopen(fname, "r");
  if (!f)
    return 0;
  Graph g = new_graph(&cmp_int);
  int n;  // so luong canh
  fscanf(f, "%d", &n);
  for (int i = 0; i < n; i++) {
    int u, v;
    fscanf(f, "%d%d", &u, &v);
    graph_add_edge(g, new_jval_i(u), new_jval_i(v), 1.0);
  }
  fclose(f);
  *out = g;
  return 1;
}

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
         "./g topo_print g.txt: in ra danh sach dinh theo trinh tu topo\n");
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

void cmd_adjacent(Graph g, int u) {
  SVertex svt;
  if (graph_export_svertex(g, new_jval_i(u), &svt)) {
    EVertex e;
    printf("n = %d\n", jrb_nodes_count(svt.tbl));
    evertices_traverse(e, svt) {
      printf("%d ", jval_i(e.key));
    }
    printf("\n");
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
    if (parse_graph(argv[2], &g) && parse_int(argv[3], &start))
      cmd_bfs_print(g, start);
    else
      printf("Loi doc tham so.\n");
  } else if (str_equal(argv[1], "dfs_print")) {
    Graph g;
    int start;
    if (parse_graph(argv[2], &g) && parse_int(argv[3], &start)) {
      cmd_dfs_print(g, start);
    } else{
      printf("Loi doc tham so.\n");
    }
  } else if (str_equal(argv[1], "adjacent")) {
    Graph g;
    int start;
    if (parse_graph(argv[2], &g) && parse_int(argv[3], &start)) {
      cmd_adjacent(g, start);
    } else {
      printf("Loi doc tham so.\n");
    }
  } else if (str_equal(argv[1], "is_dag")) {
    Graph g;
    if (parse_graph_directed(argv[2], &g)) {
      printf("%s\n", is_dag(g)? "Khong co chu trinh.\n":
                                "Co chu trinh.\n");
    } else {
      printf("Loi doc tham so.\n");
    }
  } else if(str_equal(argv[1], "topo_print")) {
    Graph g;
    if (parse_graph_directed(argv[2], &g)) {
      cmd_topo(g);
    } else {
      printf("Loi doc tham so.\n");
    }
  } else {
    printf("Cau lenh khong duoc ho tro.\n");
  }
  return 0;
}
