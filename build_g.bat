gcc -o g -w g.c src/terms.c src/util.c src/algorithm.c src/libfdr/jval.c src/libfdr/jrb.c src/libfdr/dllist.c --std=c99 &
g --help &
g adjacent data\g.txt 1 &
g bfs_print data\g.txt 1 &
g dfs_print data\g.txt 1 &
g is_dag data\g.txt &
g topo_print data\g.txt &
g dijikstra data\djk.txt 1 5

