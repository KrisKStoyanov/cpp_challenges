//References:
//Source: http://www.cplusplus.com/doc/tutorial/files/
//Author: cplusplus.com
//Source: 210CT - Week 6 Advanced Task code
//Author: Kristiyan Stoyanov

#include "stdafx.h"
#include <string>
#include <iostream>
#include <deque>
#include <fstream>

using namespace std;

//Write data to specified file location
void SaveBFSData(int data) {
	ofstream myfile;
	myfile.open("C:\Users\kriss\Desktop\BFS.txt");
	if (myfile.is_open()) {
		//cout << " Success ";
		myfile << data << " ";
	}
	else {
		cout << "Unable to open file \n";
	}
	myfile.close();
}

void SaveDFSData(int data) {
	ofstream myfile;
	myfile.open("C:\Users\kriss\Desktop\DFS.txt");
	if (myfile.is_open()) {
		//cout << " Success ";
		myfile << data << " ";
	}
	else {
		cout << "Unable to open file \n";
	}
	myfile.close();
}

//Adjacency List
class Vertex {
public:
	int value;

	deque<Vertex*> connections;

	Vertex(int v) {
		this->value = v;
	}

	void display_connections() {
		if (!connections.empty()) {
			for (int i = 0; i < connections.size(); i++) {
				cout << connections[i] << " ";
			}
			cout << "\n";
		}
		else {
			cout << "Vertex has no edges incident to it. \n";
		}
	}
};

class Edge {
public:
	Vertex* start;
	Vertex* end;

	Edge(Vertex* start, Vertex* end) {
		this->start = start;
		this->end = end;
		start->connections.push_back(end);
		end->connections.push_back(start);
	}
};

class GraphList {
public:
	deque<Vertex*> vertices;
	deque<Edge*> edges;

	GraphList(Vertex* v, Vertex* r = NULL) {
		this->vertices.push_back(v);
		if (r != NULL) {
			this->vertices.push_back(r);
		}
	}

	void insert_vertex(Vertex* v) {
		vertices.push_back(v);
	}

	void insert_edge(Vertex* start, Vertex* end) {
		start->connections.push_back(end);
		end->connections.push_back(start);
		edges.push_back(new Edge(start, end));
	}
	
	void display() {
		for (int i = 0; i < vertices.size(); i++) {
			cout << "Vertex: " << vertices[i]->value << " Edges: ";
			for (int j = 0; j < vertices[i]->connections.size(); j++) {
				if (vertices[i]->connections[j] != vertices[i]->connections.back()) {
					cout << vertices[i]->connections[j]->value << ", ";
				}
				else {
					cout << vertices[i]->connections[j]->value << "\n";
				}
			}
		}
	}
};

deque<Vertex*> dfs(GraphList* g, Vertex* v) {
	deque<Vertex*> stack;
	deque<Vertex*> visited;
	stack.push_back(v);
	while (!stack.empty())
	{
		Vertex* u = stack.back();
		stack.pop_back();
		if (!visited.empty()) {
			bool distinct = false;
			for (int i = 0; i < visited.size(); i++) {
				if (u != visited[i]) {
					distinct = true;
				}
				else {
					distinct = false;
					break;
				}
			}
			if (distinct) {
				visited.push_back(u);
				for (int i = 0; i < u->connections.size(); i++) {
					stack.push_back(u->connections[i]);
				}
			}
		}
		else {
			visited.push_back(u);
			for (int i = 0; i < u->connections.size(); i++) {
				stack.push_back(u->connections[i]);
			}
		}
	}
	cout << "Depth-First Search: \n";
	for (int i = 0; i < visited.size(); i++) {
		SaveDFSData(visited[i]->value);
		cout << visited[i]->value << " ";
	}
	cout << "\n";
	return visited;
}

deque<Vertex*> bfs(GraphList* g, Vertex* v) {
	deque<Vertex*> queue;
	deque<Vertex*> visited;
	queue.push_front(v);
	while (!queue.empty()) {
		Vertex* u = queue.front();
		queue.pop_front();
		if (!visited.empty()) {
			bool distinct = false;
			for (int i = 0; i < visited.size(); i++) {
				if (u != visited[i]) {
					distinct = true;
				}
				else {
					distinct = false;
					break;
				}
			}
			if (distinct) {
				visited.push_back(u);
				for (int i = 0; i < u->connections.size(); i++) {
					queue.push_back(u->connections[i]);
				}
			}
		}
		else {
			visited.push_back(u);
			for (int i = 0; i < u->connections.size(); i++) {
				queue.push_back(u->connections[i]);
			}
		}
	}
	cout << "Breadth-First Search: \n";
	for (int i = 0; i < visited.size(); i++) {
		SaveBFSData(visited[i]->value);
		cout << visited[i]->value << " ";
	}
	cout << "\n";
	return visited;
}

bool isPath(GraphList* g, Vertex* v, Vertex* w) {
	bool pathFound;
	deque<Vertex*> queue;
	for (int i = 0; i < v->connections.size(); i++) {
		queue.push_front(v->connections[i]);
	}
	while (!queue.empty())
	{
		Vertex* u = queue.front();
		queue.pop_front();
		if (u == w) {
			pathFound = true;
			cout << "Path is found \n";
			return pathFound;
		}
		else {
			pathFound = false;
		}
	}
	cout << "Path is not found \n";
	return pathFound;
}

bool isConnected(GraphList* g) {
	bool strConnected = false;
	deque<Vertex*> queue;
	//Individual queue for each vertex representing origin point of a bfs
	deque<Vertex*> indQueue;
	deque<Vertex*> visited;
	for (int i = 0; i < g->vertices.size(); i++) {
		queue.push_back(g->vertices[i]);
	}
	while (!queue.empty()) {
		indQueue.push_front(queue.front());
		queue.pop_front();
		while (!indQueue.empty())
		{
			Vertex* u = indQueue.front();
			indQueue.pop_front();
			if (!visited.empty()) {
				bool distinct = false;
				for (int i = 0; i < visited.size(); i++) {
					if (u != visited[i]) {
						distinct = true;
					}
					else {
						distinct = false;
						break;
					}
				}
				if (distinct) {
					visited.push_back(u);
					if (!u->connections.empty())
					{
						strConnected = true;
					}
					else {
						strConnected = false;
						//Implying the graph is not strongly connected due to current vertex lacking any connections in an undirected graph
						cout << "No \n";
						return strConnected;
					}
					for (int i = 0; i < u->connections.size(); i++) {
						indQueue.push_back(u->connections[i]);
					}
				}
			}
			else {
				visited.push_back(u);
				for (int i = 0; i < u->connections.size(); i++) {
					indQueue.push_back(u->connections[i]);
				}
			}
		}
	}

	//Implying the graph is strongly connected due to every vertex in the graph 
	//having at least one connection to another vertex in the graph
	cout << "Yes \n";
	return strConnected;
}

int main()
{
	//Adjacency List:
	Vertex* a = new Vertex(9);
	Vertex* b = new Vertex(3);
	Vertex* c = new Vertex(6);

	//Comment/uncomment to test isConnected method
	//Vertex* k = new Vertex(7);

	Edge* d = new Edge(a, b);
	Edge* e = new Edge(b, c);
	Edge* f = new Edge(c, a);

	GraphList* graph = new GraphList(a);
	graph->insert_vertex(b);
	graph->insert_vertex(c);
	//graph->insert_vertex(k);

	//graph->display();
	//dfs(graph, a);
	//bfs(graph, a);

	//isPath(graph, a, c);
	isConnected(graph);
	//display_edges_incident_to(a);

	system("pause");
    return 0;
}

