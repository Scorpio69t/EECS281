/*  Identifier = 15C1680EE94C640EC35E1694295A3625C3254CBA

    EECS 281 Lab 4: Connected Components

    For this lab, you will write a program that calculates the
    number of connected components in an undirected graph.

    Your program will receive an input file in the following format:
    1) The first line of input contains the number of vertices V and number
       of edges E in the graph.
    2) The next E lines list out the connections between vertices in the
       graph in the format of "u v", which indicates the existence of an edge
       between u and v.

    For example, the following input file would be read as follows:
    4 2  (the graph has 4 vertices numbered from 0-3, and two edges exist in
          the graph)
    0 1  (the first of these edges connects vertex 0 with vertex 1)
    0 2  (the second of these edges connects vertex 0 with vertex 2)

    In this case, vertices {0, 1, 2} form a connected component, and vertex
    {3} forms a connected component (since 3 is not connected to anything).
    Thus, your program should print out 2.

    You will be using union-find to complete this lab. The following starter
    code has been provided. Feel free to modify this code in your
    implementation. Good luck!
*/

#include <iostream>
#include <numeric>
using std::cin;
using std::cout;
using std::endl;
#include <vector>
using std::vector;


class Graph {
    uint32_t V;
    uint32_t E;
    // TODO: add any additional member variables, as needed

    vector<uint32_t> reps;


public:
    // Graph constructor that initializes the graph and its member variables
    Graph(uint32_t v, uint32_t e) : V{v}, E{e} {
        // TODO: initialize member variables that you added above

        reps.reserve(v);
        for(uint32_t i = 0; i < V; i++){
            reps.push_back(i);
        }

    }  // Graph()


    uint32_t find_set(uint32_t v) {
        // TODO: implement the find_set function

        uint32_t start = v;

        while(reps[v] != v){
            v = reps[v];
        } 

        //rep is ultimate rep

        while(reps[start] != v){
            uint32_t tmp = reps[start];
            reps[start] = v;
            start = tmp;
        }  
        return v;
    }  // find_set()


    void union_set(uint32_t a, uint32_t b) {
        // TODO: implement the union_set function
        reps[find_set(b)] = find_set(a);
    }  // union_set()


    uint32_t count_components() {
        // TODO: implement the count_components function
        uint32_t a, b;
        uint32_t counter = 0;
        for(uint32_t i = 0; i < E; i++){
            cin >> a >> b;
            union_set(a,b);
        }

        for(uint32_t i = 0; i < reps.size(); i++){
            if(reps[i] == i){
                counter++;
            }
        }
        return counter;
    }  // count_components()
};  // Graph{}


int main() {
    // You do not need to modify main.
    std::ios_base::sync_with_stdio(false);
    uint32_t vertex_count, edge_count = 0;

    cin >> vertex_count;
    cin >> edge_count;

    Graph g(vertex_count, edge_count);

    cout << g.count_components() << endl;
    return 0;
}  // main()
