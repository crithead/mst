# SUB-README

This sub-project is for visualizing the minimum spanning trees generated by
'mst'.  It is a simple program to generate a PNG image of a graph.  The input
data to 'mstplot' is the output data from 'mst --csv'.  A graph is a set of
edges.  An edge is a pair of vertices and a weight.


## File format

Each line describes an edge of two points (x1, y1), (x2, y2) and
a weight (float).  One edge per line.


```
x1\ty1\tx2\ty2\twt\n
```

## Prerequisites

This project uses PNGwriter to generate the output graphics.  It needs zlib,
libpng and FreeType fonts.

```
$ sudo apt-get install libpng-dev
$ sudo apt-get install libfreetype6-dev         # optional
```

## PNGwriter

http://pngwriter.sourceforge.net

https://github.com/pngwriter/pngwriter.git

1.  PNGWriter added as a submodule.
    1.    Install 'libfreetype6-dev' and 'libpng12-dev'
    2.    Disable building with FreeType fonts by uncommenting
          <code>P_FREETYPE = 1</code>
          in 'makefile.include.linux'
    3.    Fix compiler warnings (optional)

## Not a submodule

PNGWriter should be include as a submodule, but the code here is just a
snapshot (with some minor fixes) so the modifications to get it to compile
cleanly aren't needed every time the repository is cloned.

## To Do
*   Add some padding to the graph so the vertices near the edge of the
    graphic are easier to see.
*   Improve option "parsing" (to at least not seg fault with no args).
