# Working with graphs

At step 1, we are describing what our graph must look like and on what types it must be based. The boost::adjacency_list is a class that represents graphs as two-dimensional structures, where the first dimension contains vertexes and the second dimension contains edges for that vertex. The boost::adjacency_list must be the default choice for representing a graph because it suits most cases.

The first template parameter, boost::adjacency_list, describes the structure used to represent the edge list for each of the vertexes.
The second one describes a structure to store vertexes.
The third template parameter is used to make an indirect, directed, or bidirectional graph. Use the boost::undirectedS, boost::directedS, and boost::bidirectionalS selectors respectively.
The fifth template parameter describes the datatype that is used as a vertex. In our example we choose std::string. We may also support a datatype for edges and provide it as a template parameter.

Steps 2 and 3 are simple, but in step 4 you may see some undocumented way to speed up graph construction. In our example, we use std::vector as a container for storing vertexes, so we may force it to reserve memory for the required number of vertexes. This leads to less memory allocations/deallocations and copy operations during insertion of vertexes into the graph. This step is not very portable and may break in one of the future versions of Boost, because the step is highly dependent on the current implementation of boost::adjacency_list and on the chosen container type for storing vertexes.

At step 4, we see how vertexes can be added to the graph. Note how boost::graph_traits<graph_type> has been used. The boost::graph_traits class is used to get types that are specific for a graph type. We'll see its usage and the description of some graph-specific types later in this chapter. Step 5 shows what we need to connect vertexes with edges.

If we had provided some datatype for the edges, adding an edge would look as follows: boost::add_edge(ansic, guru, edge_t(initialization_parameters), graph)
In step 6, the graph type is a template parameter. This is recommended to achieve better code re-usability and make this function work with other graph types.

At step 7, we see how to iterate over all the vertexes of the graph. The type of vertex iterator is received from boost::graph_traits. The function boost::tie is a part of Boost.Tuple and is used for getting values from tuples to the variables. So, calling boost::tie(it, end) = boost::vertices(g) puts the begin iterator into the it variable and the end iterator into the end variable.

It may come as a surprise to you, but dereferencing a vertex iterator does not return vertex data. Instead, it returns the vertex descriptor desc, which can be used in boost::get(boost::vertex_bundle, g)[desc] to get vertex data, just as we have done in step 8. The vertex descriptor type is used in many of the Boost.Graph functions. We already saw its use in the edge construction function in step 5.

As already mentioned, the Boost.Graph library contains implementations of many algorithms. You may find many search policies implemented, but we won't discuss them in this book. We limit this recipe just to the basics of the graph library.

If we are using vertexes that are heavy to copy, we may gain speed using the following trick:
```
vertex_descriptor desc = boost::add_vertex(graph);
boost::get(boost::vertex_bundle, g_)[desc] = std::move(vertex_data);
```
It avoids copy constructions inside boost::add_vertex(vertex_data, graph) and uses the default construction with move assignment instead.

The efficiency of Boost.Graph depends on multiple factors, such as the underlying containers types, graph representation, edge, and vertex datatypes.

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

Boost
C++ guru

```