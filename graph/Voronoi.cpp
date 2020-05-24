
/****************************************************************************************************************
    Complexity : O(n*log(n))
    Spatial complexity : O(n)


    This is an implementation of Fortune's algorithm to generate a Voronoï graph from a collection of 2D position.
    This algorithm can be extended to lower or higher dimensions, with adequates changes.

    Each new node is a corner of a polygon, each polygon containing exactly one node of the provided collection and
    each point (x,y) inside the polygon being closer to said node than any other one from the provided collection.

    In other terms, the generated graph can be seen as adjacent areas, each built around one node a collection
    in such a way that it contains all of the positions closest to said node.

    The opposite of a Voronoï graph is a Delaunay graph, where every node of the provided graph are linked together
    if and only their "areas" are neighboring each other.


    !!!WARNING!!!
    . Providing a graph containing nodes with duplicated positions will provide undefined results.
      Likewise, small distances between nodes (<0.000001) might induce precision errors.
    !!!WARNING!!!
*****************************************************************************************************************/




#include<iostream>
#include<vector>

/// handy type for position
typedef double pos_precision;
typedef std::pair<pos_precision, pos_precision> Pos;

/// represent a node of the graph : contains a position (x,y) and a pointer towards each node it is linked with
class Node{
private:
    Pos pos;
    std::vector<Node*> neighbors;

public:
    Node(Pos pos){
        this->pos = pos;
    }

    void addNeighbor(Node* neighbor){
        neighbors.push_back(neighbor);
    }

    Pos getPos(){ return pos; }
};

///
class VoronoiGraph{
private:
    std::vector<Node*> nodes;

public:
    Graph(const std::vector<Pos> &collection){
        FortuneLineSweep(collection);
    }

    /// generate the Voronoï graph from a collection of positions
    void FortuneLineSweep(const std::vector<Pos> &collection);

    /// print the graph in the console
    void Show();
};



void VoronoiGraph::FortuneLineSweep(const std::vector<Pos> &collection){

}

void VoronoiGraph::Show(){

}


int main(){
    return 0;
}
