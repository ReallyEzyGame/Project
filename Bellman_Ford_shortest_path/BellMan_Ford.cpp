#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;
#include <bits/stdc++.h>
using namespace std;

struct Edge
{
    char from, to;
    double weight;

    Edge(char _from, char _to, double _weight) : from(_from), to(_to), weight(_weight) {};
};

// Relax edges from 'cur'
bool Relaxation(unordered_map<char, pair<char, double>> &graph, const vector<Edge> &edges, char cur)
{
    bool flag = false;
    for (const Edge &edge : edges)
    {
        if (edge.from != cur)
            continue;

        double cost = graph[cur].second + edge.weight;
        if (graph.find(edge.to) == graph.end() || cost < graph[edge.to].second)
        {
            graph[edge.to] = {cur, cost};
            flag = true;
        }
    }
    return flag;
}

vector<Edge> BellmanFord_Algor(vector<Edge> edges, vector<char> vertices, char from)
{
    unordered_map<char, pair<char, double>> graph;
    graph[from] = {from, 0};

    // Relax all edges |V|-1 times
    for (int i = 1; i < vertices.size(); ++i)
    {
        for (char v : vertices)
        {
            if (graph.find(v) == graph.end())
                continue;
            Relaxation(graph, edges, v);
        }
    }

    // Check for negative cycle
    char x = 0;
    for (const Edge &edge : edges)
    {
        if (graph.find(edge.from) == graph.end())
            continue;

        double cost = graph[edge.from].second + edge.weight;
        if (graph.find(edge.to) == graph.end() || cost < graph[edge.to].second)
        {
            // Found negative cycle
            graph[edge.to] = {edge.from, cost};
            x = edge.to;
            break;
        }
    }

    if (x != 0)
    {
        // Truy vết để tìm đỉnh nằm trong chu trình
        for (int i = 0; i < vertices.size(); ++i)
            x = graph[x].first;

        // Lưu chu trình
        vector<char> cycle;
        char cur = x;
        do
        {
            cycle.push_back(cur);
            cur = graph[cur].first;
        } while (cur != x);
        cycle.push_back(x);

        reverse(cycle.begin(), cycle.end());

        cout << "Found a Negative Cycle: ";
        for (char c : cycle)
            cout << c << " --> ";
        cout << "(back to " << cycle[0] << ")" << endl;

        return {};
    }

    // Ghi lại đường đi
    vector<Edge> min_cost;
    for (char vertex : vertices)
    {
        auto it = graph.find(vertex);
        if (it == graph.end() || vertex == from)
            continue;

        min_cost.push_back({it->second.first, it->first, it->second.second});
    }
    return min_cost;
}


int main()
{
    Edge e1('A', 'B', 10);
    Edge e2('B', 'C', 10);
    Edge e3('A', 'C', 15);
    Edge e4('C', 'A', -50);
    vector<Edge> list = {e1, e2, e3, e4};
    vector<Edge> path = BellmanFord_Algor(list, {'A', 'B', 'C'}, 'A');

    for (Edge e : path)
        cout << e.from << "  -->  " << e.to << "  -- cost: " << e.weight << endl;
}