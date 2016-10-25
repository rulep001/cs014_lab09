#include <vector>
#include <string>
#include <list>
#include <queue>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <climits>

#include "Graph.h"

using namespace std;

Graph::Graph(ifstream& ifs) {
    unsigned numNodes;
    unsigned numEdges;
    unsigned fIndex;
    unsigned lIndex;
    
    ifs >> numNodes;
    ifs >> numEdges;
    
    for (unsigned i = 0; i < numNodes; ++i) {
        string title;
        ifs >> title;
        Vertex newVert(title);
        vertices.push_back(newVert);
    }
    
    for (unsigned i = 0; i < numEdges; ++i) {
        string fTitle, lTitle;
        int c;
        ifs >> fTitle >> lTitle >> c;
        
        // Find index of both titles
        fIndex = findIndex(fTitle);
        lIndex = findIndex(lTitle);
        
        // push back into list the pair
        vertices.at(fIndex).neighbors.push_back(make_pair(lIndex,c));
    }
}

void Graph::output_graph(const string & filename) {
    ofstream outFS(filename.c_str());
    if(!outFS.is_open()){
        cout<<"Error opening "<< filename<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    output_graph(outFS,vertices.at(0));
    outFS<<"}";
    outFS.close();
    string jpgFilename = filename.substr(0,filename.size()-4)+".jpg";
    string command = "dot -Tjpg " + filename + " -o " + jpgFilename;
    system(command.c_str());
}

void Graph::output_graph(ofstream &outFS, Vertex v) {
    Vertex* u = NULL;
    for(unsigned i = 0; i < vertices.size(); ++i){
        u = &vertices.at(i);
        outFS << u->label << "_" << u->distance << "[ label = \"" << u->label << "_" << u->distance << "\"];" << endl;
        
        list< pair<int, int> >::iterator iter;
        for (iter = u->neighbors.begin(); iter != u->neighbors.end(); ++iter){
            outFS << u->label << "_" << u->distance << "->" << vertices.at((*iter).first).label << "_" << vertices.at((*iter).first).distance << ";" << endl;
        }
    }
}

void Graph::bfs() {
    vertices.at(0).color = "GRAY";
    vertices.at(0).distance = 0;
    queue<Vertex *> Q;
    
    Q.push(&vertices.at(0));
    
    while (!Q.empty()) {
        Vertex * u = Q.front();
        Q.pop();
        
        list< pair<int, int> >::iterator iter;

        for (iter = u->neighbors.begin(); iter != u->neighbors.end(); ++iter){
            if (vertices.at((*iter).first).color == "WHITE") {
                vertices.at((*iter).first).color = "GRAY";
                vertices.at((*iter).first).distance = u->distance + 1;
                vertices.at((*iter).first).prev = u;
                Q.push(&vertices.at((*iter).first));
            }
            vertices.at((*iter).first).color = "BLACK";
        }
    }
}

int Graph::findIndex(string str) {
    for (unsigned i = 0; i < vertices.size(); ++i) {
        if (vertices.at(i).label == str) {
            return i;
        }
    }
    return -1;
}

void Graph::dfs(){
    list< pair<int, int> >::iterator iter;
    
    for (unsigned i = 0; i < vertices.size(); i++) {
        if ( vertices.at(i).color == "WHITE" ) {
            dfs_visit( vertices.at(i) );
        }
    }
    
    cout << endl;
}

void Graph::dfs_visit(Vertex &u) {
    u.color = "GRAY";
    cout << u.label << ", ";
    
    list< pair<int, int> >::iterator iter;

    for (iter = u.neighbors.begin(); iter != u.neighbors.end(); ++iter){
        if (vertices.at((*iter).first).color == "WHITE") {
            vertices.at((*iter).first).prev = &u;
            dfs_visit(vertices.at((*iter).first));
        }
    }
    
    u.color = "BLACK";
}




/*

void Graph::dfs(){
    for(int i = 0; i < vertices.size(); i++)
        if( vertices.at(i).color == "WHITE" )
            dfs_visit( vertices.at(i) );
}

void Graph::dfs_visit(Vertex &u) {
    u.color = "GRAY";
    cout << u.label << ", ";
    list< pair<int, int> >::iterator iter;
    
    for (iter = u->neighbors.begin(); iter != u->neighbors.end(); ++iter){
    if (vertices.at((*iter).first).color == "WHITE") {
        vertices.at((*iter).first).prev = u;
        dfs_visit(iter);
    }
    u.color = "BLACK";
}
*/




