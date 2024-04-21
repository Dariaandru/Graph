#include <iostream>
#include <vector>

struct Vertex; // Объявляем структуру Vertex, чтобы использовать её в структуре Edge

struct Edge {
    Vertex* connectedVertex;
    int length;
};

struct Vertex {
    int data;
    std::vector<Edge> adjacencyList;
};

class Graph {
public:
    void addEdge(Vertex* vertex1, Vertex* vertex2, int length) {
        Edge newEdge;
        newEdge.connectedVertex = vertex2;
        newEdge.length = length;
        vertex1->adjacencyList.push_back(newEdge);
    }

    void dfs(Vertex* currentVertex, Vertex* destination, std::vector<Vertex*>& path, std::vector<bool>& visited) {
        visited[currentVertex->data - 1] = true;
        path.push_back(currentVertex);

        if (currentVertex == destination) {
            int totalLength = 0;
            for (int i = 0; i < path.size() - 1; i++) {
                totalLength += path[i]->adjacencyList[i].length;
            }
            std::cout << "Path: ";
            for (Vertex* vertex : path) {
                std::cout << vertex->data << " - ";
            }
            std::cout << "(length: " << totalLength << ")" << std::endl;
        } else {
            for (Edge& edge : currentVertex->adjacencyList) {
                if (!visited[edge.connectedVertex->data - 1]) {
                    dfs(edge.connectedVertex, destination, path, visited);
                }
            }
        }

        path.pop_back();
        visited[currentVertex->data - 1] = false;
    }

private:
    std::vector<Vertex> vertices;
};

int main() {
    Graph graph;

    Vertex vertex1 = {1, {}};
    Vertex vertex2 = {2, {}};
    Vertex vertex3 = {3, {}};
    Vertex vertex4 = {4, {}};

    graph.addEdge(&vertex1, &vertex2, 2);
    // graph.addEdge(&vertex2, &vertex1, 1);

    // graph.addEdge(&vertex1, &vertex3, 1);
    // graph.addEdge(&vertex3, &vertex1, 1);s

    graph.addEdge(&vertex2, &vertex3, 3);
    // graph.addEdge(&vertex3, &vertex2, 1);

    // graph.addEdge(&vertex4, &vertex2, 1);
    graph.addEdge(&vertex2, &vertex4, 4);

    graph.addEdge(&vertex3, &vertex4, 4);
    // graph.addEdge(&vertex4, &vertex3, 1);



    std::vector<Vertex*> path;
    std::vector<bool> visited(4, false);
    Vertex* start = &vertex1;
    Vertex* destination = &vertex4;

    graph.dfs(start, destination, path, visited);

    return 0;
}