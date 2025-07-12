#include "graph.h"

Vertex::Vertex(char _name, double _x, double _y) : name(_name), x(_x), y(_y) {};

bool Graph::isAdjcent(const char start, const char adjName)
{
    vector<Vertex> adjList = graph.find(start)->second;
    for (Vertex neighboor : adjList)
        if (neighboor.name == adjName)
            return true;
    return false;
}
// Find  if the  Vertex is  adjcent to another
// return itself if the vertex is not adjcent
Vertex Graph::isAdjcent(const Vertex start, const Vertex adj)
{
    vector<Vertex> adjList = graph.find(start.name)->second;
    for (Vertex neighboor : adjList)
        if (neighboor.name == adj.name)
            return neighboor;
    return start;
}
char Vertex::vertexName() { return name; }
pair<double, double> Vertex::cordinate() { return {x, y}; }

Graph::Graph(const vector<pair<Vertex, Vertex>> list)
{
    for (pair<Vertex, Vertex> edge : list)
    {
        auto find1 = set.find(edge.first.name);
        auto find2 = set.find(edge.second.name);

        if (find1 == set.end())
            set.insert({edge.first.name, edge.first});
        if (find2 == set.end())
            set.insert({edge.second.name, edge.second});
        graph[edge.first.name].push_back(edge.second);
    }   
}
Graph::Graph() {};
Vertex Graph::find(const char vertex)
{
    return set.find(vertex)->second;
}
void Graph::connect(const Vertex from, const Vertex to)
{
    // New Verticies that were not in the  Graph
    if (set.find(from.name) == set.end())
        set.insert({from.name, from});
    if (set.find(to.name) == set.end())
        set.insert({to.name, to});

    graph[from.name].push_back(to);
}

void Graph::disconnect(const Vertex from, const Vertex to)
{
    // the  Verticies aren't in the graph yet
    if (set.find(from.name) == set.end() || (set.find(to.name) == set.end()))
        return;
    int size = graph[from.name].size();
    vector<Vertex> list = graph[from.name];
    // Find the Vertex in the neighboor
    for (int i = 0; i < size; ++i)
    {
        if (list[i].name == to.name)
        {
            // Earse the Vertex
            for (int j = i + 1; j < size; ++j)
                list[j] = list[j - 1];
            break;
        }
    }
    list.pop_back();
    graph[from.name] = list;
}

vector<Vertex> Graph::neighboorOf(const char name)
{
    unordered_map<char, vector<Vertex>>::iterator list = graph.find(name);
    return list->second;
}