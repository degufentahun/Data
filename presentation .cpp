#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <limits>
using namespace std;
// Graph class representing the patient management system
class Patients {
private:
    // Adjacency list representation of the graph
    unordered_map<int, vector<pair<int, int>>> adjList; // Node -> {Neighbor, Weight}
public:
    // Add a patient node to the graph
    void addPatient(int patientID) {
        if (adjList.find(patientID) == adjList.end()) {
            adjList[patientID] = {};
            cout << "Patient " << patientID << " added successfully.\n";
        } else {
            cout << "Patient " << patientID << " already exists.\n";
        }
    }

    // Delete a patient node from the graph
    void deletePatient(int patientID) {
        if (adjList.find(patientID) != adjList.end()) {
            // Remove the patient node from the adjacency list
            adjList.erase(patientID);

            // Remove all edges pointing to this patient node
            for (auto it = adjList.begin(); it != adjList.end(); ++it) {
                vector<pair<int, int>> &neighbors = it->second;
                for (int i = 0; i < neighbors.size(); ++i) {
                    if (neighbors[i].first == patientID) {
                        neighbors.erase(neighbors.begin() + i);
                        --i; // Adjust index after erasing
                    }
                }
            }
            cout << "Patient " << patientID << " deleted successfully.\n";
        } else {
            cout << "Patient " << patientID << " does not exist.\n";
        }
    }

    // Add a weighted edge between two patients
    void addConnection(int src, int dest, int weight) {
        if (adjList.find(src) != adjList.end() && adjList.find(dest) != adjList.end()) {
            adjList[src].emplace_back(dest, weight);
            cout << "Connection added: " << src << " -> " << dest << " with weight " << weight << "\n";
        } else {
            cout << "One or both patients do not exist.\n";
        }
    }

    // Breadth-First Search (BFS)
    void BFS(int startNode) {
        if (adjList.find(startNode) == adjList.end()) {
            cout << "Start node " << startNode << " does not exist.\n";
            return;
        }

        unordered_map<int, bool> visited;
        queue<int> q;

        q.push(startNode);
        visited[startNode] = true;

        cout << "BFS Traversal: ";
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            cout << current << " ";

            vector<pair<int, int>> &neighbors = adjList[current];
            for (int i = 0; i < neighbors.size(); ++i) {
                int nextNode = neighbors[i].first;
                if (!visited[nextNode]) {
                    visited[nextNode] = true;
                    q.push(nextNode);
                }
            }
        }
        cout << endl;
    }

    // Depth-First Search (DFS)
    void DFS(int startNode) {
        if (adjList.find(startNode) == adjList.end()) {
            cout << "Start node " << startNode << " does not exist.\n";
            return;
        }

        unordered_map<int, bool> visited;
        stack<int> s;

        s.push(startNode);
        visited[startNode] = true;

        cout << "DFS Traversal: ";
        while (!s.empty()) {
            int current = s.top();
            s.pop();
            cout << current << " ";

            vector<pair<int, int>> &neighbors = adjList[current];
            for (int i = 0; i < neighbors.size(); ++i) {
                int nextNode = neighbors[i].first;
                if (!visited[nextNode]) {
                    visited[nextNode] = true;
                    s.push(nextNode);
                }
            }
        }
        cout << endl;
    }

    // Display the graph
    void displayGraph() {
        cout << "Graph Representation:\n";
        for (auto it = adjList.begin(); it != adjList.end(); ++it) {
            int node = it->first;
            vector<pair<int, int>> &neighbors = it->second;

            cout << "Patient " << node << " -> ";
            for (int i = 0; i < neighbors.size(); ++i) {
                cout << "(" << neighbors[i].first << ", " << neighbors[i].second << ") ";
            }
            cout << endl;
        }
    }
};

int main() {
    Patients pms;
    int choice, patientID, src, dest, weight;

    while (true) {
        cout << "\nPatient Management System in application of graph\n";
        cout << "1. Add Patient to the node\n";
        cout << "2. Delete Patient from the node\n";
        cout << "3. Add edge\n";
        cout << "4. Perform BFS\n";
        cout << "5. Perform DFS\n";
        cout << "6. Display Graph\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter patient ID to add: ";
                cin >> patientID;
                pms.addPatient(patientID);
                break;

            case 2:
                cout << "Enter patient ID to delete: ";
                cin >> patientID;
                pms.deletePatient(patientID);
                break;

            case 3:
                cout << "Enter source patient ID: ";
                cin >> src;
                cout << "Enter destination patient ID: ";
                cin >> dest;
                cout << "Enter connection weight: ";
                cin >> weight;
                pms.addConnection(src, dest, weight);
                break;

            case 4:
                cout << "Enter starting patient ID for BFS: ";
                cin >> patientID;
                pms.BFS(patientID);
                break;

            case 5:
                cout << "Enter starting patient ID for DFS: ";
                cin >> patientID;
                pms.DFS(patientID);
                break;

            case 6:
                pms.displayGraph();
                break;

            case 7:
                cout << "Exiting the program...\n";
                return 0;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}