#ifndef GRAPH_H_
#define GRAPH_H_

#include "Vertex.h"

using namespace std;

class Graph {
  private:
    vector<Vertex> vertices;
    void output_graph(ofstream &outFS, Vertex v);
    void dfs_visit(Vertex &);
  public:
    Graph(ifstream&);
    void output_graph(const string & filename);
    void bfs();
    int findIndex(string);
    void dfs();
};

#endif /* GRAPH_H_ */