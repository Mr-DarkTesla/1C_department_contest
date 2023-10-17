#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#define VERBOSE true

typedef std::pair<size_t, size_t> Edge;

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
    Vector1dSizeT bridges{};
    Vector1dSizeT connections{};

    explicit Graph(size_t input_num_of_vertices) {
        num_of_vertices = input_num_of_vertices + 1;
        vertices = Vector1dVertex(num_of_vertices);
        num_of_comps = num_of_vertices - 1;
        for (size_t index = 0; index < num_of_vertices; ++index) {
            vertices[index].index = index;
        }
        size = Vector1dSizeT(num_of_vertices, 1);
    }

    void Connect(const Vector1dEdge& given_edges) {
        edges = Vector2dEdge(num_of_vertices, Vector1dEdge(0));
        for (auto edge : given_edges) {
            edges[edge.first].emplace_back(edge.first, edge.second);
            edges[edge.second].emplace_back(edge.second, edge.first);
            if (!SameRoot(edge.first, edge.second)) {
                Merge(edge.first, edge.second);
                num_of_comps--;
            }
        }
    }

    // Asymptotic: O(N + M), where N - vertices, M - edges.
    Edge GetNumOfBridgesAndConnections() {
        t_in_.resize(num_of_vertices);
        t_up_.resize(num_of_vertices);
        used_.resize(num_of_vertices, false);

        size_t time = 0;
        for (size_t i = 1; i < num_of_vertices; ++i) {
            if (!used_[i]) {
                Dfs(i, 0, time);
            }
        }
        return Edge(bridges.size() / 2, connections.size() / 2);
    }

private:
    Vector1dVertex vertices{};
    Vector1dSizeT size{};
    Vector2dEdge edges{};

    size_t num_of_vertices{}; // Asymptotic: O(\alpha (N)), where \alpha - Ackerman func <= 4 (almost every time).

    Vector1dSizeT t_in_{};
    Vector1dSizeT t_up_{};
    Vector1dBool used_{};

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

    void Dfs(size_t cur, size_t prev, size_t time) {
        used_[cur] = true;
        t_in_[cur] = t_up_[cur] = time++;
        for (Edge next_pair : edges[cur]) {
            size_t next = next_pair.second;
            size_t edge_idx = next_pair.first;
            if (next == prev) {
                continue;
            }
            if (used_[next]) {
                t_up_[cur] = std::min(t_up_[cur], t_in_[next]);
            } else {
                Dfs(next, cur, time);
                t_up_[cur] = std::min(t_up_[cur], t_up_[next]);
                if (t_up_[next] > t_in_[cur]) {
                    Bridge(cur, next, edge_idx);
                }
                if (t_up_[next] > t_in_[cur]) {
                    Bridge(cur, next, edge_idx);
                }
                if (t_up_[next] >= t_in_[cur]) {
                    auto it = std::upper_bound(connections.cbegin(), connections.cend(), cur);
                    connections.insert(it, cur);
                }
            }
        }
    }

    void Bridge(size_t from, size_t to, size_t edge_idx) {
        for (Edge next_pair : edges[from]) {
            size_t neighbor = next_pair.second;
            size_t index = next_pair.first;
            if (neighbor == to && index != edge_idx) {
                return;
            }
        }
        auto it = std::upper_bound(bridges.cbegin(), bridges.cend(), edge_idx);
        bridges.insert(it, edge_idx);
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
        Edge bridge_and_connections = graph.GetNumOfBridgesAndConnections();
        if (VERBOSE) {
            std::cout << "Amount of connected components: " << graph.num_of_comps << std::endl;
            std::cout << "Amount of bridges: " << bridge_and_connections.first << std::endl;
            std::cout << "Amount of cut-points: " << bridge_and_connections.second << std::endl;
            std::cout << "Lower bound of starting infections " << 1 + graph.num_of_comps +
            bridge_and_connections.first + bridge_and_connections.second << std::endl;
        } else {
            std::cout << "" << 1 + graph.num_of_comps +
            bridge_and_connections.first + bridge_and_connections.second << std::endl;
        }
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
