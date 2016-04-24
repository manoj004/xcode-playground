//
//  main.cpp
//  PlayGround
//
//  Created by Manoj Chakkaravarthy on 4/23/16.
//  Copyright © 2016 Manoj Chakkaravarthy. All rights reserved.
//

#include "Graph.h"

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    string inputfile = argv[1];
    
    cout << "Parsing Test Case: " << inputfile << endl;
    
    Graph* G = new Graph;
    G->parse(inputfile);
    
    cout << "Parsing Done : " << (G->getVertices()).size() << " Vertices , "
                              << (G->getEdges()).size() << " Edges" << endl;
    G->print();
    return 0;
}
