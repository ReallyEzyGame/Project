#include "graph.h"
#include <cmath>
#include <queue>
#include <stack>

vector<Vertex> reconstruct_path(vector<Vertex> previous, int des);

static Graph G;

double heuricstic_Evaluate(const char from, const char to)
{
    Vertex start = G.find(from);
    Vertex des = G.find(to);

    pair<double, double> start_loc = start.cordinate();
    pair<double, double> des_loc = des.cordinate();

    return sqrt(pow(des_loc.first - start_loc.first, 2) + pow(des_loc.second - start_loc.second, 2));
}

vector<char> reconstruct_path(unordered_map<char, char> previous, char start, char des)
{
    stack<char> path;
    path.push(des);

    for (auto edge = previous.find(des); edge != previous.end(); edge = previous.find(des))
    {
        path.push(edge->first);
        if (edge->first == start)
            break;
        des = edge->second;
    }
    vector<char> list;
    while (path.size() > 1)
    {
        list.push_back(path.top());
        path.pop();
    }
    return list;
}

vector<char> A_star(const char from, const char to)
{
    priority_queue<pair<double, char>, vector<pair<double, char>>, greater<>> openSet; // Set that are visiting
    unordered_map<char, char> cameFrom;                                                // Record  the  Previous Vertex  with  the Smallest cost
    cameFrom[from] = from;

    unordered_map<char, double> GScore; // Actual Cost
    GScore[from] = 0;

    unordered_map<char, double> FScore; // Evaluate the theory distance from current vertex to destination
    FScore[from] = heuricstic_Evaluate(from, to);

    openSet.push({FScore[from], from});
    while (!openSet.empty())
    {
        pair<double, char> cur_ver = openSet.top();
        openSet.pop();

        char name = cur_ver.second;
        double cost = cur_ver.first;
        if (name == to)
            return reconstruct_path(cameFrom, from, to);

        // Exapnd || Adjust the path
        vector<Vertex> neighboors = G.neighboorOf(name);
        for (Vertex neighboor : neighboors)
        {
            char neig_name = neighboor.vertexName();
            double tentative_GScore = GScore.find(name)->second + heuricstic_Evaluate(name, neig_name);

            if (GScore.find(neig_name) == GScore.end() || tentative_GScore < GScore.find(neig_name)->second)
            {
                cameFrom[neig_name] = name;
                GScore[neig_name] = tentative_GScore;
                FScore[neig_name] = tentative_GScore + heuricstic_Evaluate(neig_name, to);

                openSet.push({FScore[neighboor.vertexName()], neighboor.vertexName()});
            }
        }
    }
    return {}; // No Path was Found
}
int main()
{
    // Danh sách các đỉnh ngẫu nhiên
    Vertex v1 = {'Q', 23.4, 45.6};
    Vertex v2 = {'w', -15.2, 30.1};
    Vertex v3 = {'e', 40.8, -22.5};
    Vertex v4 = {'R', -5.0, 18.9};
    Vertex v5 = {'t', 31.7, -48.2};
    Vertex v6 = {'y', 10.5, 25.0};
    Vertex v7 = {'u', -38.4, -12.3};
    Vertex v8 = {'i', 4.1, 40.0};
    Vertex v9 = {'O', -27.6, -35.8};
    Vertex v10 = {'p', 12.0, 5.0};
    Vertex v11 = {'a', -2.5, -4.5};
    Vertex v12 = {'S', 28.9, 14.7};
    Vertex v13 = {'d', -19.3, -32.6};
    Vertex v14 = {'F', 46.2, 8.1};
    Vertex v15 = {'g', -3.8, -21.4};
    Vertex v16 = {'h', 35.5, -17.0};
    Vertex v17 = {'J', -42.1, 29.3};
    Vertex v18 = {'k', 2.9, 44.5};
    Vertex v19 = {'L', -17.8, -9.6};
    Vertex v20 = {'z', 39.0, 3.2};
    Vertex v21 = {'x', -10.1, -26.7};
    Vertex v22 = {'C', 21.5, 33.8};
    Vertex v23 = {'V', -29.9, -1.2};
    Vertex v24 = {'b', 18.3, -40.5};
    Vertex v25 = {'N', -45.6, 11.1};
    Vertex v26 = {'m', 6.7, -19.8};
    Vertex v27 = {'M', 32.4, 38.6};
    Vertex v28 = {'n', -24.8, -49.0};
    Vertex v29 = {'B', 48.0, 7.3};
    Vertex v30 = {'v', -8.2, 16.5};
    Vertex v31 = {'c', 15.6, 2.7};
    Vertex v32 = {'X', -36.7, -42.1};
    Vertex v33 = {'Z', 9.4, 3.6};
    Vertex v34 = {'A', 25.1, -11.9};
    Vertex v35 = {'s', -49.5, 22.8};
    Vertex v36 = {'D', 1.0, -30.0};
    Vertex v37 = {'G', 41.5, 10.3};
    Vertex v38 = {'H', -13.0, 24.6};
    Vertex v39 = {'K', 30.2, -1.8};
    Vertex v40 = {'l', -4.5, -34.7};
    // Giả sử bạn đã định nghĩa và khởi tạo 40 đỉnh ở trên

    vector<pair<Vertex, Vertex>> graph = {
        {v1, v2}, {v1, v12}, {v2, v3}, {v3, v4}, {v4, v5}, {v5, v6}, {v6, v7}, {v7, v8}, {v8, v9}, {v9, v10}, {v10, v11}, {v11, v12}, {v12, v13}, {v13, v14}, {v14, v15}, {v15, v16}, {v16, v17}, {v17, v18}, {v18, v19}, {v19, v20}, {v20, v21}, {v21, v22}, {v22, v23}, {v23, v24}, {v24, v25}, {v25, v26}, {v26, v27}, {v27, v28}, {v28, v29}, {v29, v30}, {v30, v31}, {v31, v32}, {v32, v33}, {v33, v34}, {v34, v35}, {v35, v36}, {v36, v37}, {v37, v38}, {v38, v39}, {v39, v40},

        // Thêm các cạnh ngẫu nhiên khác để tăng độ phức tạp
        {v1, v20},
        {v2, v19},
        {v3, v18},
        {v4, v17},
        {v5, v16},
        {v6, v15},
        {v7, v14},
        {v8, v13},
        {v9, v12},
        {v10, v11},
        {v1, v40},
        {v2, v39},
        {v3, v38},
        {v4, v37},
        {v5, v36},
        {v6, v35},
        {v7, v34},
        {v8, v33},
        {v9, v32},
        {v10, v31},
        {v11, v30},
        {v12, v29},
        {v13, v28},
        {v14, v27},
        {v15, v26},
        {v16, v25},
        {v17, v24},
        {v18, v23},
        {v19, v22},
        {v20, v21}};
    G = Graph(graph);
    vector<char> path = A_star(v1.vertexName(), v39.vertexName());

    for (char ch : path)
        cout << ch << "  -->  ";
    cout << endl;
}