#include <iostream>
#include <map>
#include <queue>
#include <vector>


#define INF 10000000

struct vert {
    int index;
    int distance;
    struct vert *parent;
}typedef Vertex;


class Graph {
public:
    int m_nVertex;
    std::map<int, std::vector<int>> m_adjacencyList;
    std::vector<std::vector<int>> m_weights;

    Graph(bool isDefault, int nVertex);

    friend std::vector<Vertex> InitialiseDijkstra(Graph &graph, int start_index);
    friend  bool Relax(Graph &graph, Vertex *u, Vertex *v);
    void Dijkstra(int start_index);

};


Graph::Graph(bool isDefault, int nVertex) {
    if (isDefault) {
        /*m_nVertex = 8;
        m_adjacencyList.emplace(0, std::vector<int> {2, 3});
        m_adjacencyList.emplace(1, std::vector<int> {2, 3});
        m_adjacencyList.emplace(2, std::vector<int> {0, 1, 4, 5});
        m_adjacencyList.emplace(3, std::vector<int> {0, 1, 4});
        m_adjacencyList.emplace(4, std::vector<int> {2, 3, 6, 7});
        m_adjacencyList.emplace(5, std::vector<int> {2, 6});
        m_adjacencyList.emplace(6, std::vector<int> {4, 5});
        m_adjacencyList.emplace(7, std::vector<int> {4});

        m_weights.emplace_back(std::vector<int> {0, INF, 3, 6, INF, INF, INF, INF});
        m_weights.emplace_back(std::vector<int> {INF, 0, 4, 2, INF, INF, INF, INF});
        m_weights.emplace_back(std::vector<int> {3, 4, 0, INF, 8, 2, INF, INF});
        m_weights.emplace_back(std::vector<int> {6, 2, INF, 0, 6, INF, INF, INF});
        m_weights.emplace_back(std::vector<int> {INF, INF, 8, 6, 0, INF, 2, 2});
        m_weights.emplace_back(std::vector<int> {INF, INF, 2, INF, INF, 0, 5, INF});
        m_weights.emplace_back(std::vector<int> {INF, INF, INF, INF, 2, 5, 0, INF});
        m_weights.emplace_back(std::vector<int> {INF, INF, INF, INF, 2, INF, INF, 0});*/

        m_nVertex = 6;
        m_adjacencyList.emplace(0, std::vector<int> {1, 2, 5});
        m_adjacencyList.emplace(1, std::vector<int> {0, 2, 3});
        m_adjacencyList.emplace(2, std::vector<int> {0, 1, 3, 5});
        m_adjacencyList.emplace(3, std::vector<int> {1, 2, 4});
        m_adjacencyList.emplace(4, std::vector<int> {3, 5});
        m_adjacencyList.emplace(5, std::vector<int> {0, 2, 4});

        m_weights.emplace_back(std::vector<int> {0, 7, 9, INF, INF, 14});
        m_weights.emplace_back(std::vector<int> {7, 0, 10, 15, INF, INF});
        m_weights.emplace_back(std::vector<int> {9, 10, 0, 11, INF, 2});
        m_weights.emplace_back(std::vector<int> {INF, 15, 11, 0, 6, INF});
        m_weights.emplace_back(std::vector<int> {INF, INF, INF, 6, 0, 9});
        m_weights.emplace_back(std::vector<int> {14, INF, 2, INF, 9, 0});

    }
    else {
        for (size_t i = 0; i < nVertex; ++i) {
            continue;
        }
    }
}


void Graph::Dijkstra(int start_index) {

    std::vector<Vertex> vertexList = InitialiseDijkstra(*this, start_index);

    auto cmp = [](Vertex* left, Vertex* right){ return left->distance > right->distance;};
    std::priority_queue<Vertex*, std::vector<Vertex*>, decltype(cmp)> Q(cmp);

    for (size_t i = 0; i < m_nVertex; ++i) {
        Q.push(&vertexList[i]);
    }

    while (!Q.empty()) {

        Vertex *u = Q.top();
        Q.pop();

        for (auto &item: m_adjacencyList[u->index]) {
            Vertex *v = &vertexList[item];
            Relax(*this, u, v);


        }
    }


    std::cout << "Distances from the start vertex: \n";
    for(auto &item : vertexList){
        std::cout <<"Vertex " << item.index << ": " << item.distance << std::endl;
    }

    std::cout << std::endl;

    std::cout << "Paths to the start vertex: \n";
    for(auto &item1 : vertexList) {
        Vertex temp = item1;
        std::cout << "Vertex " << temp.index << ": " << temp.index;
        while (temp.parent != nullptr) {
            std::cout << "->" <<temp.parent->index;
            temp = *temp.parent;
        }
        std::cout << std::endl;
    }
}


std::vector<Vertex> InitialiseDijkstra(Graph &graph, int start_index) {

    std::vector<Vertex> vertexList;

    for (size_t i = 0; i < graph.m_nVertex; ++i) {
        Vertex vertex;
        vertex.index = i;
        vertex.distance = INF;
        vertex.parent = nullptr;

        vertexList.push_back(vertex);
    }

    vertexList[start_index].distance = 0;

    return  vertexList;
}


bool Relax(Graph &graph, Vertex *u, Vertex *v) {
    if (v->distance > u->distance + graph.m_weights[u->index][v->index]) {
        v->distance = u->distance + graph.m_weights[u->index][v->index];

        v->parent = u;
        return true;
    }
    return false;
}


