// Copyright (C) 2016 Nguyen Ba Ngoc

#include "terms.h"
#include "util.h"

#include <stdio.h>
#include <string.h>

// tra ve 0 neu co loi,
//        1 neu thanh cong.
int load_graph(char* fname, Graph out) {
  FILE* f = fopen(fname, "r");
  if (!f)
    return 0;
  int n;  // so luong canh
  fcanf(f, "%d", &n);
  for (int i = 0; i < n; i++) {
    int u, v;
    fcanf(f, "%d%d", &u, &v);
    add_edge_gen(out, new_jval_i(u), new_jval_i(v), &cmp_int);
    add_edge_gen(out, new_jval_i(v), new_jval_i(u), &cmp_int);
  }
  fclose(f);
  return 1;
}

void bfs_print(char* fname, char* arg) {
  Graph g;
  int u;
  if (load_graph(fname, &g) == 0 || parse_int(arg, &u)) {
    printf("Loi doc du lieu.\n");
    return;
  }

  // duyet bfs
  Queue q = new_queue();
  en_queue_i(q, u);
  JRB visited = make_jrb();
  Jval any_value;
  while (!queue_empty(q)) {
    u = de_queue_i(q);
    printf("%d ", u);  // tham dinh u
    jrb_insert_int(visited, u, any_value);
    Queue out = get_adjacent(g, u);
    while (!empty_queue(out)) {
      int v = de_queue_i(out);
      if (jrb_find_int(visited, v) == NULL)
        en_queue_i(q, v);
    }
  }
  free_queue(q);
}

int main(int argc, char *argv[]) {
  if (argc == 1 || strcmp(argv[1], "--help") == 0) {
    printf("./g --help: hien thi huong dan su dung nay.\n"
           "./g adjacent g.txt 1: in ra so luong dinh ke voi dinh 1 va danh sach cac dinh nay\n"
           "./g bfs_print g.txt 1: duyet theo chieu rong va in ra cac dinh, bat dau tu dinh 1\n"
           "./g dfs_print g.txt 1: duyet theo chieu sau va in ra cac dinh, bat dau tu dinh 1\n");
  } else if (str_equal(argv[1], "bfs_print")) {
    bfs_print(argv[2], argv[3]);
  } else if (str_equal(argv[1], "dfs_print")) {
    dfs_print(argv[2], argv[3]);
  } else if (str_equal(argv[1], "adjacent")) {
    adjacent(argv[2], argv[3]);
  } else {
    printf("Cau lenh khong duoc ho tro.\n");
  }
  return 0;
}
