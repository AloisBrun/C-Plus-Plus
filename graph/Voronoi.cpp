
/****************************************************************************************************************
    Complexity : O(n*log(n))
    Spatial complexity : O(n)


    This is an implementation of Fortune's algorithm to generate a Voronoï graph from a sorted collection of 2D
    positions.
    This algorithm can be extended to lower or higher dimensions, with adequates changes.

    Each new node is a corner of a polygon, each polygon containing exactly one node of the provided collection and
    each point (x,y) inside the polygon being closer to said node than any other one from the provided collection.

    In other terms, the generated graph can be seen as adjacent areas, each built around one node of the collection
    in such a way that it contains all of the positions closest to said node.

    The complementary to a Voronoï graph is a Delaunay graph, where every node of the provided graph are linked
    together if and only if their "areas" are neighboring each other.


    !!!WARNING!!!
    . The collection must be sorted on the x-axis, from lesser to higher
    . Providing a collection with duplicated positions will provide undefined results.
      Likewise, small distances between positions (<0.000001) might induce precision errors.
    !!!WARNING!!!
*****************************************************************************************************************/




#include<iostream>
#include<vector>
#include<queue>
#include<list>

/// delimitations for extern nodes
const int maxCornerX = 1000000,
          maxCornerY = 1000000,
          minCornerX = -maxCornerX,
          minCornerY = -maxCornerY;

/// handy type for position
typedef std::pair<double, double> Pos;


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
    /// only the areas of the graph are shown, note the nodes
    void Show();
};


class Parabole{
private:
    Parabole *parent;
    Node *site;

public:
    Parabole(Parabole *parent, Node *site){
        this->parent = parent;
        this->site = site;
    }
};

class Event{
private:

public:

};



void VoronoiGraph::FortuneLineSweep(const std::vector<Pos> &collection){
    /// line sweeps left to right
    double sweepLineY = 0;
    std::list<Parabole*> parabole_list;
    std::priority_queue<std::pair<double, Event*>> event_order;
    auto next_pos = collection.begin();


    next_pos++;

    while(event_order.size() != 0){

    }
}

void VoronoiGraph::Show(){

}


int main(){
    /// collection have to be sorted on the x-axis

    return 0;
}


/******
ISSUES :
    -
******/
