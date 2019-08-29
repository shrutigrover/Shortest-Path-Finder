## Find shortest path between point A and point B of two same or different streets

Here, I have used Breadth-First-Search Algorithm to find the shortest. Other famous algorithms for the same are Bellman-Ford and Floyd-Warshall.

#### Task:  
Mention the following as command line arguments (k is an integer):

*-s k : The number of streets, default k = 10 and k >= 2

*-n k : The number of line segments in each street, default k = 5 and k >= 1

*-l k : Wait time in seconds before generating next random street, default k = 5 and k >= 5

*-c k : Coordinates generated in the range of [-k,k], default k = 15

A random generator (rgen) generates streets based on above specifications. 

I used pipes to connect following processes (Inter-Process communication):
1. A process between Rgen that generated streets(Vertices and Edges) and graphgen that validates the commands from rgen and outputs a graph.
2. A process that reads output of graphgen and reads user input to find shortest distance between two vertices.

#### Run code:
Use below commands in shell:

$ mkdir build

$ cd build

$ make install

$ cd ./run/bin

$ ./a3-ece650 -s 5 -n 4 -l 5

V 8

E {<0,2>,<0,3>,<0,4>,<1,3>,<4,7>,<5,2>,<5,6>}

s 2 4 ----> user input

2-0-4 ----> shortest path
