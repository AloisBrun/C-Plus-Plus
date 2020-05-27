
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
//#include<list>

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


class Event{
public:
    bool is_site_event;
    Pos *pos;

    Event(Pos *pos, bool is_site_event = true) : pos(pos), is_site_event(is_site_event) {}
};

class Parabola{
public:
    Parabola *parent,
             /// left branch : son is below this parabola, right it's above
             *left_son, *right_son;
    Pos *site;
    Event *event;
    //bool isBranch;  /// is the parabola used in the BST only as a branch to the leaves?

    Parabola(Parabola *parent, Pos *site, Event *event) : //, bool isBranch = false) :
                                parent(parent), site(site), event(event),// isBranch(isBranch),
                                left_son(nullptr), right_son(nullptr)  {}

    /// used for insertions in BST
    void add(Pos *new_site, Event *new_event);

    /// create 5 new parabolas ; two copy of the original to the left and right of the son parabola,
    ///                          the son and two parabolas as branches
    ///  0         ->          b                              b
    ///                       / \                            / \
    ///                      0   b                          b   0
    ///                         / \                        / \
    ///                        R   0  <- copy             0   L
    ///                      (RIGHT)                       (LEFT)
    void createLeft(Pos *new_site, Event *new_event);
    void createRight(Pos *new_site, Event *new_event);
};




void Parabola::add(Pos *new_site, Event *new_event){
    if(new_site->second < site->second){
        if(left_son == nullptr){
            createLeft(new_site, new_event);
        }
        else{
            left_son->add(new_site, new_event);
        }
    }
    else{
        if(right_son == nullptr){
            createRight(new_site, new_event);
        }
        else{
            right_son->add(new_site, new_event);
        }
    }
}

void Parabola::createLeft(Pos *new_site, Event *new_event){
    Parabola *duplicate = new Parabola(this, site, event),
             *left_branch = new Parabola(this, site, nullptr),
             *left_right_son = new Parabola(left_branch, new_site, new_event);

    left_son = left_branch;
    left_son->left_son = duplicate;
    left_son->right_son = left_right_son;
    right_son = duplicate;
}

void Parabola::createRight(Pos *new_site, Event *new_event){
    Parabola *duplicate = new Parabola(this, site, event),
             *right_branch = new Parabola(this, site, nullptr),
             *right_left_son = new Parabola(right_branch, new_site, new_event);

    right_son = right_branch;
    right_son->right_son = duplicate;
    right_son->left_son = right_left_son;
    left_son = duplicate;
}



void VoronoiGraph::FortuneLineSweep(const std::vector<Pos> &collection){
    /// parabolas are stored in a BST
    Parabola* root;
    std::priority_queue<std::pair<double, Event*>> event_queue;
    Event* curr_event = nullptr;
    double sweep_line_x = 0;

    /// line sweeps left to right
    for(Pos site : collection){
        event_queue.push(std::make_pair(site.first, new Event(&site)));
    }


    ///
    while(event_queue.size() != 0){
        curr_event = event_queue.top().second;
        sweep_line_x = curr_event->pos->first;

        if(curr_event->is_site_event){
            root->add(curr_event->pos, curr_event);
        }
        else{
            event_queue.pop();
        }
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
