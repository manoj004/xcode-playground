//
//  Graph.h
//  PlayGround
//
//  Created by Manoj Chakkaravarthy on 4/23/16.
//  Copyright © 2016 Manoj Chakkaravarthy. All rights reserved.
//

#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

//#ifndef Graph_h
//#define Graph_h

// Class forward declaration
class Vertex;
class Edge;

// Vertex Class
class Vertex {
private:
    int val;
    vector<Edge*> edges;
    
public:
    Vertex(int _val): val(_val) {};
    ~Vertex();
    
    int getValue()            { return val; }
    vector<Edge*> getEdges()  { return edges; }
    
    void setValue(int _val)   { val = _val; }
    void addEdge(Edge* _edge) { edges.push_back(_edge); }    
};

// Edge Class
class Edge {
private:
    Vertex* v1;
    Vertex* v2;
    int wt;
    
public:
    Edge(int _wt): wt(_wt) {};
    ~Edge();
    
    int getWt()                                { return wt; }
    vector<Vertex*> getVertices()              { vector<Vertex*> retval {v1, v2} ; return retval; }
    
    void setWt(int _wt)                        { wt = _wt; }
    void setVertices(Vertex* _v1, Vertex* _v2) { v1 = _v1; v2 = _v2; }
    
    void print() {
        cout << v1->getValue() << "---" << wt << "---" << v2->getValue() << endl;
    }
};

// Graph Class
class Graph {
private:
    vector<Vertex*> vertices;
    vector<Edge*> edges;
    map<int,Vertex*> vertex_lookup;
    
public:
    //Graph();
    //~Graph();
    
    void addVertex(Vertex* _v)  { vertices.push_back(_v); }
    Vertex* addVertex(int _val)    {
        Vertex* _v = new Vertex(_val);
        vertices.push_back(_v);
        vertex_lookup.insert(pair<int,Vertex*>(_val,_v));
        return _v;
    }
    Edge* addEdge(int _val1, int _val2, int wt) {
        Vertex* v1;
        Vertex* v2;
        
        map<int,Vertex*>::iterator vit;
        
        // Check for val1
        vit = vertex_lookup.find(_val1);
        if (vit == vertex_lookup.end()) { v1 = addVertex(_val1); }
        else { v1 = vit->second;}
        
        // Check for val2
        vit = vertex_lookup.find(_val2);
        if (vit == vertex_lookup.end()) { v2 = addVertex(_val2); }
        else { v2 = vit->second;}

        // Create new Edge. Todo: Check for pre-existing edge
        Edge* edge = new Edge(wt);
        edge->setVertices(v1,v2);
        v1->addEdge(edge);
        v2->addEdge(edge);
        edges.push_back(edge);
        
        return edge;
    }
    
    vector<Vertex*> getVertices() { return vertices; }
    vector<Edge*> getEdges() { return edges; }
    
    void print() {
        for (int i = 0; i < edges.size(); i++ ) {
            edges[i]->print();
        }
    }
    void parse(string file, char delimiter = ' ') {
        ifstream myfile(file);
        string str;
        
        if (myfile.is_open()) {
            while(getline(myfile,str)) {
                
                vector<int> elems;
                stringstream sstr(str);
                string token;
                
                while(getline(sstr, token, delimiter)) {
                    elems.push_back(stoi(token));
                }
                
                if (elems.size() == 3) {
                    addEdge(elems[0], elems[1], elems[2]);
                }
            }
            myfile.close();
        } else {
            cout << "Error: Could not open file: " << file << endl;
        }
    }
};

//#endif /* Graph_h */
