// Copyright (C) 2016 Nguyen Ba Ngoc

#include "terms.h"
#include "util.h"

#include <stdio.h>
#include <string.h>

int cmp_int(Jval v1, Jval v2) {
  if (jval_i(v1) < jval_i(v2))
    return -1;
  if (jval_i(v1) > jval_i(v2))
    return 1;
  return 0;
}

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
    add_edge_gen(g, new_jval_i(u), new_jval_i(v), &cmp_int);
    add_edge_gen(g, new_jval_i(v), new_jval_i(u), &cmp_int);
  }
  fclose(f);
  *out = g;
  return 1;
}

void cmd_bfs_print(Graph g, int start) {  // duyet bfs bat dau tu start
  Queue q = new_queue();
  en_queue_i(q, start);
  JRB visited = make_jrb();
  Jval any_value;
  jrb_insert_int(visited, start, any_value);
  while (!queue_empty(q)) {
    int u = de_queue_i(q);
    printf("%d ", u);  // tham dinh u    
    JRB out, ptr;
    get_adjacent_gen(g, new_jval_i(u), &cmp_int, &out);
    jrb_traverse(ptr, out) {
      int v = jval_i(ptr->key);
      if (jrb_find_int(visited, v) == NULL) {
        en_queue_i(q, v);
        jrb_insert_int(visited, v, any_value);
      }
    }
  }
  free_queue(q);
}

void cmd_dfs_print(Graph g, int start) {  // duyet dfs bat dau tu start
  Stack s = new_stack();
  push_i(s, start);
  JRB visited = make_jrb();
  Jval any_value;
  jrb_insert_int(visited, start, any_value);
  while (!stack_empty(s)) {
    int u = pop_i(s);
    printf("%d ", u);  // tham dinh u    
    JRB out, ptr;
    get_adjacent_gen(g, new_jval_i(u), &cmp_int, &out);
    jrb_traverse(ptr, out) {
      int v = jval_i(ptr->key);
      if (jrb_find_int(visited, v) == NULL) {
        push_i(s, v);
        jrb_insert_int(visited, v, any_value);
      }
    }
  }
  free_stack(s);
}

void cmd_adjacent(Graph g, int u) {
  JRB out = NULL;
  int n = get_adjacent_gen(g, new_jval_i(u), &cmp_int, &out);
  printf("n = %d\n", n);
  if (n > 0) {
    JRB ptr;
    jrb_traverse(ptr, out) {
      printf("%d ", jval_i(ptr->key));
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
