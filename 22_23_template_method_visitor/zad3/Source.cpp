#include<iostream>
#include<vector>
#include<queue>

class Graph {
	/*Jedan "programerski" primer. 
	Graph can be implemented using matrix or ajdency list. Regardless how the graph is implementet, 
	searching algorightms (such as bfs and dfs) can be implemented, under the assumption that function
	that returns adjacent nodes is implemented.
	Searching alhorithms will be implemented in base class, and derived classes will implement 'step' of
	getting adjacent nodes
	*/
protected:
	int n;
	void DFS(int currNode, bool* visitedNodes) { 
		visitedNodes[currNode] = true;
		std::cout << currNode << std::endl;
		std::vector<int> adjacents = adjacentsOf(currNode);
		for (int u : adjacents) {
			if (!visitedNodes[u])
				DFS(u, visitedNodes);
		}
	}
public:
	Graph(int n) : n(n) {}
	virtual void addEdge(int _from, int _to, bool directed = true) = 0;
	virtual std::vector<int> adjacentsOf(int v) = 0; // derived classes will override this metod
	void BFS(int s) {
		bool* visitedNodes = new bool[n];
		for (int i = 0; i < n; i++) {
			visitedNodes[i] = false;
		}
		std::queue<int> queue;
		queue.push(s);
		visitedNodes[s] = true;

		while (!queue.empty()) {
			int v = queue.front();
			queue.pop();
			std::cout << v << std::endl;
			std::vector<int> _adjacents = adjacentsOf(v); // calling implementation of derived class
			for (int u : _adjacents) {
				if (!visitedNodes[u]) {
					visitedNodes[u] = true;
					queue.push(u);
				}
			}
		}
		delete[]visitedNodes;
	}
	void DFS(int s) {
		bool* visitedNodes = new bool[n];
		for (int i = 0; i < n; i++) {
			visitedNodes[i] = false;
		}
		DFS(s, visitedNodes);
		delete[]visitedNodes;
	}
	virtual ~Graph() {}
};

class MatrixGraph : public Graph {
private:
	std::vector<std::vector<int>> matrix;
public:
	MatrixGraph(int n) : Graph(n) {
		matrix = std::vector<std::vector<int>>(n);
		for (int i = 0; i < n; i++)
			matrix[i] = std::vector<int>(n);
	}
	void addEdge(int _from, int _to, bool directed = true) override {
		matrix[_from][_to] = 1;
		if (!directed) {
			matrix[_to][_from] = 1;
		}
	}
	std::vector<int> adjacentsOf(int v) override {
		std::vector<int> _adjacents;
		for (int u = 0; u < n; u++) {
			if (matrix[v][u]) _adjacents.push_back(u);
		}
		return _adjacents;
	}
};

class AdjacentsGraph : public Graph {
private:
	std::vector<std::vector<int>> adjacentsList;
public:
	AdjacentsGraph(int n) : Graph(n) {
		adjacentsList = std::vector<std::vector<int>>(n);
	}
	void addEdge(int _from, int _to, bool directed = true) override {
		adjacentsList[_from].push_back(_to);
		if (!directed) {
			adjacentsList[_to].push_back(_from);
		}
	}
	std::vector<int> adjacentsOf(int v) override {
		return adjacentsList[v];
	}
};

void testGraph(Graph* g) {
	g->addEdge(0, 1, false);
	g->addEdge(0, 4, false);
	g->addEdge(1, 2, false);
	g->addEdge(1, 3, false);
	g->addEdge(1, 5, false);
	g->addEdge(5, 6, false);
	g->addEdge(6, 7, false);
	g->addEdge(3, 4, false);
	g->addEdge(3, 5, false);
	g->addEdge(5, 8, false);
	g->addEdge(8, 9, false);

	std::cout << "BFS:" << std::endl;
	g->BFS(0);
	std::cout << "\n\n\n";
	g->DFS(0);
}

int main() {
	Graph* g1 = new MatrixGraph(10);
	Graph* g2 = new MatrixGraph(10);
	testGraph(g2);

	delete g1;
	delete g2;
	return 0;
}