# Edge-density of $C_{4}$-free 1-planar graphs

Code for work on the problem of bounding the maximum edge density of $C_4$-free 1-planar graphs.

Uses CGAL's lp-solver library to encode constraints that this class of graphs are subject to, setting the optimization objective to be the edge-density
(non-linear objective achieved by normalizing number of vertices to one, and setting the objective to maximize number of edges).

## Directory structure
```
.
├── src/
│   ├── mainMin.cpp
│   ├── main.cpp
│   ├── main_no8.cpp
│   └── c4_finder.cpp
├── compile.sh
└── CMakeLists.txt
```

 - `mainMin.cpp` contains the code for the simplified case in which we assume there are no cells larger than size 7.
 - `main.cpp` contains the code for the general problem.
 - `main_n08.cpp` contains the code for the problem where we combine cells of size 8 and 9 into one.
 - `c4_finder.cpp` is just some helper code to find 4-cycles in graphs.

 - `compile.sh` simply compiles the code using a simple bash script. The code can be compiled like any other CGAL-based cpp program otherwise.
 - `CMakeLists.txt` is required for CGAL. It controls which cpp file is compiled.
