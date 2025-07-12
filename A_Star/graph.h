#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Graph;

class Vertex
{
private:
    friend Graph;
    char name;
    double x, y;

public:
    Vertex(char,double,double);

    char vertexName();      
    pair<double, double> cordinate();
};

class Graph
{
private:
    unordered_map<char, Vertex> set;
    unordered_map<char, vector<Vertex>> graph;

public:
    Graph();
    Graph(const vector<pair<Vertex, Vertex>>);

    
    
    bool isAdjcent(const char, const char);
    Vertex isAdjcent(const Vertex, const Vertex);\
    Vertex find(const char);
    vector<Vertex> neighboorOf(const char);
    
    void connect(const Vertex, const Vertex);
    void disconnect(const Vertex, const Vertex);
};