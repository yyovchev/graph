#include <iostream>
#include "graph.h"

#include <vector>
#include <algorithm>

//test
#include <limits>

using namespace std;



int main()
{
    graph g;

    g.add_edge(1,4,1);
    g.add_edge(1,2,3);
    g.add_edge(4,3,3);
    g.add_edge(2,3,4);
    g.add_edge(3,5,5);
    g.add_edge(4,5,2);


    cout<<g.print_v();
    cout<<"------------------------------------------\ngraph : \n";
    cout<<g.print_g();
    cout<<"------------------------------------------\nweight between nodes : \n";
    cout<<g.print_l();

    cout<<"------------------------------------------\nDFS : \n";
    vector<int> l = g.DFS();

    for_each(l.begin(), l.end(), [](int arg){
        cout<<arg<<"  ";
    });
    cout<<"\n";

      cout<<"------------------------------------------\nDFS : \n";
    vector<int> l2 = g.BFS();

    for_each(l2.begin(), l2.end(), [](int arg){
        cout<<arg<<"  ";
    });
    cout<<"\n";

    cout<<"------------------------------------------\nshorthest path from 1 to 4 : \n";
    cout<<g.Dijkstras_algo(1,4);



    return 0;
}
