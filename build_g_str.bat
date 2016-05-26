gcc -o g -w g_str.c src/terms.c src/util.c src/algorithm.c src/libfdr/jval.c src/libfdr/jrb.c src/libfdr/dllist.c --std=c99 &
g --help &
g adjacent data\g_str.txt V0 &
g bfs_print data\g_str.txt V1 &
g dfs_print data\g_str.txt V1 &

