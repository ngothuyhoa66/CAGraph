// Copyright (C) 2016 Nguyen Ba Ngoc

#include "util.h"

#include <stdio.h>
#include <string.h>

int parse_int(char* arg, int* out) {
  return sscanf(arg, "%d", out);
}

int parse_graph_ud(char* fname, Graph* out) {
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

int parse_graph_d(char* fname, Graph* out) {
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

int parse_graph_udw(char* fname, Graph* out) {
  FILE* f = fopen(fname, "r");
  if (!f)
    return 0;
  Graph g = new_graph(&cmp_int);
  int n;  // so luong canh
  fscanf(f, "%d", &n);
  for (int i = 0; i < n; i++) {
    int u, v;
    float w;
    fscanf(f, "%d%d%f", &u, &v, &w);
    graph_add_edge(g, new_jval_i(u), new_jval_i(v), w);
    graph_add_edge(g, new_jval_i(v), new_jval_i(u), w);
  }
  fclose(f);
  *out = g;
  return 1;
}

int parse_graph_ustr(char* fname, Graph* out) {
  FILE* f = fopen(fname, "r");
  if (!f)
    return 0;
  Graph g = new_graph(&cmp_str);
  int n;  // so luong canh
  fscanf(f, "%d", &n);
  for (int i = 0; i < n; i++) {
    char u[100], v[100];
    fscanf(f, "%s%s", u, v);
    char *p1 = (char*) malloc(strlen(u) + 1),
         *p2 = (char*) malloc(strlen(v) + 1);
    strcpy(p1, u);
    strcpy(p2, v);
    graph_add_edge(g, new_jval_i(p1), new_jval_i(p2), 1.0);
    graph_add_edge(g, new_jval_i(p2), new_jval_i(p1), 1.0);
  }
  fclose(f);
  *out = g;
  return 1;
}

int cmp_int(Jval v1, Jval v2) {
  if (jval_i(v1) < jval_i(v2))
    return -1;
  if (jval_i(v1) > jval_i(v2))
    return 1;
  return 0;
}

int cmp_str(Jval v1, Jval v2) {
  char *s1 = (char*) jval_v(v1),
       *s2 = (char*) jval_v(v2);
  return strcmp(s1, s2);
}