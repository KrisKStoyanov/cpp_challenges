//References:
//Address: 210CT - Week 6 Advanced Task N#1 Code
//Author: Kristiyan Stoyanov

#include "stdafx.h"
#include <string>
#include <iostream>
#include <deque>
#include <fstream>

using namespace std;

//Directed Acyclic Graph

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

	//Vertices which can be reached from current one
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
	int cost;

	Edge(Vertex* start, Vertex* end, int cost) {
		this->start = start;
		this->end = end;
		this->cost = cost;
		start->connections.push_back(end);
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

	void insert_edge(Vertex* start, Vertex* end, int weight) {
		edges.push_back(new Edge(start, end, weight));
	}

	void display() {
		for (int i = 0; i < vertices.size(); i++) {
			cout << "Vertex: " << vertices[i]->value << " Edges: ";
			for (int j = 0; j < vertices[i]->connections.size(); j++) {
				if (vertices[i]->connections[j] != vertices[i]->connections.back()) {
					cout << vertices[i]->connections[j]->value <<", ";
				}
				else if (vertices[i]->connections[j] == vertices[i]->connections.back()) {
					cout << vertices[i]->connections[j]->value << "\n";
				}
			}
			cout << "\n";
		}
		cout << "\n";

		for (int i = 0; i < edges.size(); i++) {
			cout << "Edge: (Start: " << edges[i]->start->value << "), " << "(End: " << edges[i]->end->value << ") Cost: " << edges[i]->cost << "\n";
		}
	}
};

deque<Vertex*> dfs(GraphList* g, Vertex* v = NULL) {
	//Take first vertex found in graph if no specified starting vertex is given
	if (v == NULL) {
		if (!g->vertices.empty()) {
			v = g->vertices[0];
		}
		else {
			return g->vertices;
		}
	}

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

deque<Vertex*> bfs(GraphList* g, Vertex* v = NULL) {
	//Take first vertex found in graph if no specified starting vertex is given
	if (v == NULL) {
		if (!g->vertices.empty()) {
			v = g->vertices[0];
		}
		else {
			return g->vertices;
		}
	}

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

	if (strConnected) {
		cout << "Yes \n";
	}
	else {
		cout << "No \n";
	}
	return strConnected;
}

int findLongestCostSimplePath(GraphList* g, Vertex* v = NULL) {
	//Take first vertex found in graph if no specified starting vertex is given
	if (v == NULL) {
		if (!g->vertices.empty()) {
			v = g->vertices[0];
		}
		else {
			return g->vertices.size();
		}
	}

	//Longest cost simple path variable storage for edge cost (weight) sum and number of verts
	int lcsp = 0;
	int lcspVerts = 1;
	
	//Visited vertices:
	deque<Vertex*> visited;

	//Alternative edges starting from current edge end point:
	deque<Edge*> altPaths;
	Edge* curEdge = NULL;
	int curEdgeCost = 0;

	//Find all alternative edges to follow from starting vertex
	for (int i = 0; i < g->edges.size(); i++) {
		if (g->edges[i]->start == v) {
			altPaths.push_back(g->edges[i]);
		}
	}

	//Locate most efficient edge to start from
	for (int i = 0; i < altPaths.size(); i++) {
		if (altPaths[i]->cost > curEdgeCost) {
			curEdgeCost = altPaths[i]->cost;
			curEdge = altPaths[i];
		}
	}

	visited.push_back(curEdge->start);
	lcsp += curEdge->cost;
	lcspVerts += 1;


	//Move the current edge until it has no further connections
	while (curEdge->end->connections.size() > 0) {

		//Clear alternative paths from last edge
		while (!altPaths.empty()) {
			altPaths.pop_back();
		}

		//Obtain alternative paths from this edge
		for (int i = 0; i < g->edges.size(); i++) {
			if (g->edges[i]->start == curEdge->end) {
				bool distinct = false;
				for (int j = 0; j < visited.size(); j++) {
					if (g->edges[i]->start != visited[j]) {
						distinct = true;
					}
					else {
						distinct == false;
						break;
					}
				}
				if (distinct) {
					altPaths.push_back(g->edges[i]);
				}
			}
		}

		//Locate most efficient edge to travel on
		curEdgeCost = 0;
		for (int i = 0; i < altPaths.size(); i++) {
			if (altPaths[i]->cost > curEdgeCost) {
				curEdgeCost = altPaths[i]->cost;
				curEdge = altPaths[i];
			}
		}

		visited.push_back(curEdge->start);
		lcsp += curEdge->cost;
		lcspVerts += 1;
	}
	
	cout << "Longest cost simple path is: " << lcsp << " (verts: " << lcspVerts << ") \n";
	return lcsp;
}


int main()
{
	//Adjacency List:
	GraphList* graph = new GraphList(new Vertex(6)); // [0]
	graph->insert_vertex(new Vertex(3)); // [1]
	graph->insert_vertex(new Vertex(9)); // [2]
	graph->insert_vertex(new Vertex(7)); // [3]
	graph->insert_vertex(new Vertex(5)); // [4]

	graph->insert_edge(graph->vertices[0], graph->vertices[1], 2);
	graph->insert_edge(graph->vertices[0], graph->vertices[3], 7);
	graph->insert_edge(graph->vertices[1], graph->vertices[2], 4);
	graph->insert_edge(graph->vertices[2], graph->vertices[3], 1);
	graph->insert_edge(graph->vertices[2], graph->vertices[4], 5);
	graph->insert_edge(graph->vertices[3], graph->vertices[4], 6);
	//graph->insert_vertex(b);
	//graph->insert_vertex(c);

	graph->display();
	//dfs(graph, a);
	//bfs(graph, a);

	//isPath(graph, a, c);
	cout << "\n";
	findLongestCostSimplePath(graph);
	//isConnected(graph);
	//display_edges_incident_to(a);

	system("pause");
	return 0;
}

