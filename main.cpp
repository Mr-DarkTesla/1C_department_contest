#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

typedef std::pair<size_t, size_t> Edge;
//typedef std::pair<char, Pair> Edge;

typedef std::vector<bool> Vector1dBool;
typedef std::vector<size_t> Vector1dSizeT;

typedef std::vector<Edge> Vector1dEdge;
typedef std::vector<Vector1dEdge> Vector2dEdge;

struct vertex {
    size_t index{};
    vertex* root = this;
};

typedef std::vector<vertex> Vector1dVertex;

class Graph {
public:
    size_t num_of_comps{};

    explicit Graph(size_t input_num_of_vertices) {
        num_of_vertices = input_num_of_vertices;
        vertices = Vector1dVertex(num_of_vertices);
        num_of_comps = num_of_vertices;
        for (size_t index = 0; index < num_of_vertices; ++index) {
            vertices[index].index = index;
        }
        size = Vector1dSizeT(num_of_vertices, 1);
    }

    void Connect(const Vector1dEdge& given_edges) {
        edges = Vector2dEdge(num_of_vertices, Vector1dEdge(0));
        for (auto edge : given_edges) {
            edges[edge.first].push_back(edge);
            edges[edge.second].push_back(edge);
            if (!SameRoot(edge.first, edge.second)) {
                Merge(edge.first, edge.second);
                num_of_comps--;
            }
        }
    }

private:
    Vector1dVertex vertices{};
    Vector1dSizeT size{};
    Vector2dEdge edges{};
    Vector1dSizeT bridges{};
    size_t num_of_vertices{}; // Asymptotic: O(\alpha (N)), where \alpha - Ackerman func <= 4 (almost every time).

    vertex* Root(size_t i) {
        vertex& cur_vertex = vertices[i];
        if (cur_vertex.root != &cur_vertex) {
            cur_vertex.root = Root(cur_vertex.root->index);
        }
        return cur_vertex.root;
    }

    bool SameRoot(size_t i, size_t j) {
        return Root(i) == Root(j);
    }

    void Merge(size_t i, size_t j) {
        if (size[i] < size[j]) {
            Root(i)->root = Root(j);
        } else {
            Root(j)->root = Root(i);
        }
    }


};

class Solver {
public:
    void Input() {
        std::cin >> num_of_vert >> num_of_edges_;
        for (size_t i = 0; i < num_of_edges_; ++i) {
            Edge edge;
            std::cin >> edge.first >> edge.second;
            input_edges.push_back(edge);
        }
    }
    void Process() {
        Graph graph(num_of_vert);
        graph.Connect(input_edges);
        std::cout << "Amount of connected components: " << graph.num_of_comps;
    }

    size_t num_of_edges_{};
    size_t num_of_vert{};
    Vector1dEdge input_edges{};
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    Solver solver = Solver();
    solver.Input();
    solver.Process();
    return 0;
}
