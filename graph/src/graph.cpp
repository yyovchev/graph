/*
template <class T>
graph<T>::graph(){
    directions = false;     //flag for dir graph, default false
    nodes = 0;              //number of nodes in the graph

}

//set directioned or not
template <class T>
void graph<T>::set_directions(bool d){
    directions = d;
}

//add node
//if there is node with the same name return false
//if the node is created successfully return true
template <class T>
bool graph<T>::add_node(T node_name){
    if (count_if(this->begin(), this->end(), [node_name, this](node<T> arg){ return (arg.name == node_name)? true : false; }) > 0)
    {
        //the node is already created (there is a node with the same name)
        return false;
    }
    else
    {
        node<T> new_node;
        new_node.name = node_name;      //set the name of the node
        new_node.index = this->nodes;   //the index of the node is a value of this->nodes
        this->nodes++;                  //1 is added to nodes every time node is created
        this->push_back(new_node);      //the new node is add to the vector with all nodes
        return true;
    }
}

//get the index of a node with "name":name
template <class T>
int graph<T>::get_index(T name){
    int index ;

    //find the node with .name=name and get its index
    for_each(this->begin(), this->end(), [&index, name](node<T> arg){
        if (arg.name == name) index = arg.index;
    });

    return index;
}

//get the name of the node with "index":index
template <class T>
T graph<T>::get_name(int index){
    T name ;

    //find the node with .index=index and get its name
    for_each(this->begin(), this->end(), [index, &name](node<T> arg){
        if (arg.index == index) name = arg.name;
    });

    return name;
}

//add edge between two nodes
//default weight is 1
//first check if node exist and create it if it doesnt
//return true if edge is created successfully and false if it doesnt
template <class T>
bool graph<T>::add_edge(T node_name_1, T node_name_2, int len){

    add_node(node_name_1);      //check if the first node exists
    add_node(node_name_2);      //check if the second node exists
                                //if one of the nodes dont exist it is created

    int node_1 = get_index(node_name_1);        //get the index of the fr node
    int node_2 = get_index(node_name_2);        //get the index of the sc node

    bool return_value = false;                  //return value by default is false
    bool directions = this->directions;

    //create a edge between nodeA and nodeB with weight=len
    //if directions is true create edge ONLY FROM nodeA TO nodeB
    //if directions is false create edge in both way with equal weights
    for_each(this->begin(), this->end() , [node_1, node_2, directions, &return_value](node<T> &arg){
        if (arg.index == node_1){
            if (count(arg.neighbours.begin(), arg.neighbours.end(), node_2) == 0){
                arg.neighbours.push_back(node_2);
                return_value = true;
            }
        }

        //check if the graph is directioned
        if (arg.index == node_2 && !directions){
            if (count(arg.neighbours.begin(), arg.neighbours.end(), node_1) == 0 ){
                arg.neighbours.push_back(node_1);
            }
        }
    });

    //if the edge is created successfully, weight in a list with all edges' weight
    if (return_value)
        add_len(node_1, node_2, len);
    return return_value;
}

//add edge's weight in a list with all edges' weight
//if the graph is directioned weight is added only from nodeA to nodeB
//if the graph is not directioned weights are added in both way
template <class T>
void graph<T>::add_len(T node_1, T node_2, int len){

    lengths l;

    //weight is added form nodeA to nodeB
    l.node_1 = node_1;
    l.node_2 = node_2;
    l.length = len;
    this->len.push_back(l);

    //check if the graph is directioned
    //if the graph is not directioned, weight is added form nodeB to nodeA
    if (!this->directions){
        l.node_1 = node_2;
        l.node_2 = node_1;
        l.length = len;
        this->len.push_back(l);
    }
}

//depth-first search algorithm
//start from the first node
template <class T>
vector<T> graph<T>::DFS(){
    vector<T> list_of_visited;        //the list with visited node in chronological order
    bool visited[nodes];                 //arr[i] is 1 if node.index == i is seen

    //set all values to 0
    for (int i=0 ; i<nodes ; i++)
        visited[i] = 0;

    int start_index = get_index(this->begin()->name);   //get the index of the first node
    dfs_indx(start_index, list_of_visited, visited);

    return list_of_visited;
}

//depth-first search algorithm
//start from the node with "name" = startIndex
template <class T>
vector<T> graph<T>::DFS(T startIndex){
    vector<T> list_of_visited;        //the list with visited node in chronological order
    bool visited[nodes];                 //arr[i] is 1 if node.index == i is seen

    //set all values to 0
    for (int i=0 ; i<nodes ; i++)
        visited[i] = 0;

    int start_index = get_index(startIndex);            //get the index of the given node
    dfs_indx(start_index , list_of_visited, visited);

    return list_of_visited;
}


template <class T>
void graph<T>::dfs_indx(int index, vector<T> &list_of_visited, bool *visited){
    list_of_visited.push_back(get_name(index));
    visited[index] = 1;
    for_each(this->begin(), this->end(), [&visited, index, this, &list_of_visited](node<T> arg){
        if (arg.index == index){
            for_each(arg.neighbours.begin(), arg.neighbours.end(), [&visited, this, &list_of_visited](int arg){
                if (visited[arg] == 0)
                    this->dfs_indx(arg, list_of_visited, visited);
            });
        }
    });
}

template <class T>
vector<T> graph<T>::BFS(){
    vector<T> list_of_visited;
    list<int> que;

    int visited[nodes];
    for (int i=0 ; i<nodes ; i++)
        visited[i] = 0;

    int fr = this->begin()->index;

    que.push_back(fr);
    list_of_visited.push_back(get_name(fr));
    visited[fr] = 1;
    while (!que.empty()){
        int value = que.front();
        que.pop_front();

        for_each(this->begin(), this->end(), [&que, &list_of_visited, this, &visited, value](node<T> arg){
            if (arg.index == value){
                for_each(arg.neighbours.begin(), arg.neighbours.end(), [&que, &list_of_visited, this, &visited](int arg){
            //  for_each(arg.neighbours.begin(), arg.neighbours.end(), [&visited, this, &list_of_visited](int arg){

                    if (visited[arg] == 0){
                        list_of_visited.push_back(this->get_name(arg));
                        visited[arg] = 1;
                        que.push_back(arg);
                    }
                });
            }
        });
    }
    return list_of_visited;
}

// TODO: Dijkstras
template <class T>
int graph<T>::Dijkstras_algo(T start_node, T end_node){
    bool visited[nodes];
    int table_info[nodes];
    for (int i=0 ; i<nodes ; i++){
        visited[i] = false;
        table_info[i] = numeric_limits<int>::max();
    }

    int index = get_index(start_node);
    table_info[index] = 0;

    while (!all_visited(visited)){
        index = find_next(visited, table_info);
        for_each(this->begin(), this->end(), [this, &table_info, index](node<T> arg){
            if (arg.index == index){
                for_each(arg.neighbours.begin(), arg.neighbours.end(), [this, &table_info, index](int arg){

                    int info = table_info[index] + this->get_weight(index, arg);
                    if (info<table_info[arg])
                        table_info[arg] = info;

                });
            }
        });
        visited[index] = true;
    }
    int end_node_index = get_index(end_node);
    return table_info[end_node_index];
}

template <class T>
bool graph<T>::all_visited(bool *visited){
    bool return_value = true;

    for(int i=0 ; i<this->nodes ; i++)
        return_value &= visited[i];

    return return_value;
}

template <class T>
int graph<T>::find_next(bool *visted, int *table_info){
    int next = numeric_limits<int>::max();

    for (int i=0 ; i<this->nodes ; i++){
        if (table_info[i] < next && !visted[i]){
            next = i;
        }
    }

    return next;
}

template <class T>
int graph<T>::get_weight(int index_1, int index_2){
    int w;

    for_each(this->len.begin(), this->len.end(), [&w, index_1, index_2](lengths arg){
        if (arg.node_1 == index_1 && arg.node_2 == index_2){
            w = arg.length;
        }
    });

    return w;
}

//return a string with all nodes' name and index
//RETURN STRING
template <class T>
string graph<T>::print_v(){
    string return_string = "";
    for_each(this->begin(),this->end(),[&return_string](node<T> arg)
    {
        return_string +="name ";
        return_string += to_string(arg.name);
        return_string +=" index ";
        return_string += to_string(arg.index);
        return_string += "\n";
    });
    return return_string;
}

template <class T>
string graph<T>::print_g(){
    string return_str = "";
    for_each(this->begin(), this->end(), [&return_str, this](node<T> arg){
        return_str += to_string(arg.name);
        for_each(arg.neighbours.begin(), arg.neighbours.end(),[&return_str,this](int arg){
                return_str += " --> ";
                return_str += to_string(this->get_name(arg));
        });
        return_str += "\n";
    });
    return return_str;
}

template <class T>
string graph<T>::print_l(){
    string return_str;
    for_each(this->len.begin(), this->len.end(),[&return_str, this](lengths arg){
        return_str += to_string(this->get_name(arg.node_1));
        return_str += " : ";
        return_str += to_string(this->get_name(arg.node_2));
        return_str += " len ";
        return_str += to_string(arg.length);
        return_str += " \n";
    });

    return return_str;
}
*/



