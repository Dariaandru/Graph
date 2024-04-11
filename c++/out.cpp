#include <iostream>
#include <vector>

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


void printPath(const std::vector<Vertex*>& path) {
    for (Vertex* vertex : path) {
        std::cout << vertex->data << "-";
    }
    std::cout << std::endl;
}


void dfs(Vertex* current, Vertex* destination, std::vector<Vertex*>& path, std::vector<bool>& visited) {
    if (current == nullptr) {
        return;
    }

    path.push_back(current);
    visited[current->data - 1] = true; // Assuming vertex data is 1-indexed

    if (current == destination) {
        printPath(path);
    } else {
        for (Vertex* neighbor : current->adjacencyList) {
            if (!visited[neighbor->data - 1]) {
                dfs(neighbor, destination, path, visited);
            }
        }
    }

    path.pop_back();
    visited[current->data - 1] = false;
};

void printAllPaths(Vertex* start, Vertex* destination) {
    if (start == nullptr || destination == nullptr) {
        std::cout << "Invalid start or destination vertex" << std::endl;
        return;
    }

    std::vector<Vertex*> path;
    std::vector<bool> visited; // Инициализируйте в соответствии с вашим графом

    dfs(start, destination, path, visited);
};




int main() {
    // Create the graph
    Vertex* vertices = new Vertex[4];
    vertices[0].data = 1;
    vertices[1].data = 2;
    vertices[2].data = 3;
    vertices[3].data = 4;

    vertices[0].adjacencyList.push_back(&vertices[1]);
    vertices[0].adjacencyList.push_back(&vertices[2]);
    vertices[1].adjacencyList.push_back(&vertices[0]);
    vertices[1].adjacencyList.push_back(&vertices[2]);
    vertices[1].adjacencyList.push_back(&vertices[3]);
    vertices[2].adjacencyList.push_back(&vertices[0]);
    vertices[2].adjacencyList.push_back(&vertices[1]);
    vertices[3].adjacencyList.push_back(&vertices[1]);
    vertices[2].adjacencyList.push_back(&vertices[3]);
    vertices[3].adjacencyList.push_back(&vertices[2]);
    

    // Perform DFS traversal
    std::vector<Vertex*> path;
    std::vector<bool> visited(4, false); // Assuming there are 4 vertices in the graph
    Vertex* start = &vertices[0];
    Vertex* destination = &vertices[3];
    dfs(start, destination, path, visited);

    // Clean up
    delete[] vertices;

    return 0;
}