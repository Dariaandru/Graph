#include <iostream>
#include <vector>
#include <unordered_map>

struct Vertex {
    int data;
    struct Edge* next;
    std::vector<Vertex*> adjacencyList;  // Adjacency list to store neighboring vertices
};

struct Edge {
    Vertex* connectedVertex;
    Edge* nextEdge;
};

struct Graph {
    std::vector<Vertex*> vertices;

    Vertex* findVertex(int data) {
        for (Vertex* vertex : vertices) {
            if (vertex->data == data) {
                return vertex;
            }
        }
        return nullptr;
    }

    void addVertex(int data) {
        Vertex* newVertex = new Vertex;
        newVertex->data = data;
        newVertex->next = nullptr;
        vertices.push_back(newVertex);
    }

    void addEdge(int data1, int data2) {
        Vertex* vertex1 = findVertex(data1);
        Vertex* vertex2 = findVertex(data2);

        if (vertex1 == nullptr || vertex2 == nullptr) {
            std::cout << "One or both vertices not found in the graph" << std::endl;
            return;
        }

        Edge* newEdge = new Edge;
        newEdge->connectedVertex = vertex2;
        newEdge->nextEdge = vertex1->next;
        vertex1->next = newEdge;
    }

    void removeEdge(int data1, int data2) {
        Vertex* vertex1 = findVertex(data1);

        if (vertex1 == nullptr) {
            std::cout << "Vertex " << data1 << " not found in the graph" << std::endl;
            return;
        }

        Edge* currentEdge = vertex1->next;
        Edge* prevEdge = nullptr;

        while (currentEdge != nullptr) {
            if (currentEdge->connectedVertex->data == data2) {
                if (prevEdge == nullptr) {
                    vertex1->next = currentEdge->nextEdge;
                } else {
                    prevEdge->nextEdge = currentEdge->nextEdge;
                }
                delete currentEdge;
                return;
            }

            prevEdge = currentEdge;
            currentEdge = currentEdge->nextEdge;
        }

        std::cout << "Edge between vertices " << data1 << " and " << data2 << " not found" << std::endl;
    }

};
// ... (struct definitions and Graph class)

void printAllPaths(Vertex* start, Vertex* end, std::vector<Vertex*>& path, std::vector<bool>& visited) {
    
    path.push_back(start);
    visited[start->data - 1] = true; // Assuming vertex data is 1-indexed

    if (start == end) {
        for (Vertex* vertex : path) {
            std::cout << vertex->data << "-";
        }
        std::cout << std::endl;
    } else {
        for (Vertex* neighbor : start->adjacencyList) {
            if (!visited[neighbor->data - 1]) {
                printAllPaths(neighbor, end, path, visited);
            }
        }
    }

    path.pop_back();
    visited[start->data - 1] = false;
}






int main() {
    Graph graph;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addVertex(3);
    graph.addVertex(4);
    
    graph.addEdge(1, 2);
    // graph.addEdge(2, 1);

    graph.addEdge(1, 3);
    // graph.addEdge(3, 1);

    graph.addEdge(2, 3);
    // graph.addEdge(3, 2);

    graph.addEdge(2, 4);
    // graph.addEdge(4, 2);
    
    graph.addEdge(3, 4);
    // graph.addEdge(4, 3);
    
    // Find and print all paths from vertex 1 to vertex 4
    std::vector<bool> visited(4, false); // Assuming vertex data is in the range 1-4
    std::vector<Vertex*> path;
    Vertex* start = graph.findVertex(1);
    Vertex* end = graph.findVertex(4);
    printAllPaths(start, end, path, visited);

    return 0;
}