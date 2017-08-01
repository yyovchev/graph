#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <algorithm>

#include <iostream>
#include <string>

#include <limits>


using namespace std;

struct node
{
    int index;
    int name;
    vector<int> neighbours;
};

struct lengths{
    int node_1;
    int node_2;
    int length;
};

class graph : public vector<node>
{
    private:
        bool directions;
        int nodes;
        vector<lengths> len;

    public:
        graph();
        void set_directions(bool d);

    public:
        bool add_node(int node_name);
        bool add_edge(int node_name_1, int node_name_2, int len = 1);
        void add_len(int node_1, int node_2, int len);
        int get_index(int name);
        int get_name(int index);
        string print_v();
        string print_g();
        string print_l();
        vector<int> DFS();
        vector<int> DFS(int strtIndex);
        vector<int> BFS();
        int Dijkstras_algo(int start_node, int end_node);

    private:
        void dfs_indx(int index, vector<int> &list_of_visited, bool *visited);
        bool all_visited(bool *visited);
        int find_next(bool *visted, int *table_info);
        int get_weight(int index_1, int index_2);
};

#endif // GRAPH_H
