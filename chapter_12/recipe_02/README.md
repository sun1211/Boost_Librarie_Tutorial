# Visualizing graphs

The Boost.Graph library contains function to output graphs in Graphviz (DOT) format. If we write boost::write_graphviz(out, g) with two parameters in step 1, the function outputs a graph picture with vertexes numbered from 0. That's not very useful, so we provide an instance of the hand-written vertex_writer class that outputs vertex names.

As we can see in step 2, the Graphviz tool understands DOT format. If you wish to output more info for your graph, then you may need to read the Graphviz documentation for more info about the DOT format.

If you wish to add some data to the edges during visualization, we need to provide an instance of the edge visualizer as a fourth parameter to boost::write_graphviz.

## How to build
```
mkdir build
cd build
cmake ..
cmake --build .
```

## How to run
```
./bin/main

digraph G {
0 [label="C++"];
1 [label="STL"];
2 [label="Boost"];
3 [label="C++ guru"];
4 [label="C"];
0->1 ;
1->2 ;
2->3 ;
4->3 ;
}

```