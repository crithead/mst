# README

This project is an example implementations of Prim's algorithm for finding
a **minimum spanning** tree of a completely connected, undirected graph.  The
graph is a set of points where there is an edge from every vertex to every
other vertex.  The goal is to find a set of edges that connect all points
with minimum length of the resulting edges.  The weight of each edge is the
distance between vertices.

The 'data' directory contains files with sets of points.  Each line describes
a single point in the form of an x-value, a tab character, and a y-value.

```
make
./mst ../data/graph-100.dat
./mst --csv ../data/graph-100.dat > ../data/graph-100.csv
```

## PLOT

This sub-project generates a tool to graph the minimum spanning tree output
from "mst --csv".  See plot/README for more information.

```
make
./mstplot ../data/graph-100.csv
```

## PLOT-JAVA

This sub-project is a rewrite of PLOT in Java.
See plot/README.md for more information.

```
ant
./mstplot       # a script to run the JAR on all of the data
```

