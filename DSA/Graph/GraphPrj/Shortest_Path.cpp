#include<iostream>
#include<vector>
#include<string>
#include<queue>
#include<iomanip>

using namespace std;
using VVI = vector<vector<int>>;
using VI = vector<int>;
using PII = pair<int, int>;
constexpr int MAX_VERTEX = 100;

enum ShortestPathAlgoType {
	MODIFIED_BFS,
	DIJKSTRA,
	BELLMAN_FORD
};

class MyGraph {
public:
	MyGraph(int _v = 0, bool dummy = false):isInit(false), v(_v){
		if (dummy == true) {
			CreateDummyGraph();
		}
		else if (v > 0) {
			Init(v);
		}
	}

	void Init(int v);
	void AddEdge(int x, int y, int w);
	void CreateDummyGraph();

	int GetV() {
		return v;
	}
	VVI& GetAdj() {
		return adj;
	}

private:
	bool isInit;
	int v;
	VVI adj;
};


void MyGraph::Init(int v)
{
	if (isInit == false) {
		isInit = true;
		adj = VVI(v, VI(v));
	}
}

void MyGraph::AddEdge(int x, int y, int w)
{
	if (x >= 0 && y >= 0
		&& x <= v && y <= v) {
		adj[x][y] = w;
		adj[y][x] = w;
	}
}

void MyGraph::CreateDummyGraph()
{
	v = 9;
	Init(v);
	//Add edge
	AddEdge(0, 1, 4);
	AddEdge(0, 7, 8);
	AddEdge(1, 2, 8);
	AddEdge(1, 7, 11);
	AddEdge(2, 3, 7);
	AddEdge(2, 8, 2);
	AddEdge(2, 5, 4);
	AddEdge(3, 4, 9);
	AddEdge(3, 5, 14);
	AddEdge(4, 5, 10);
	AddEdge(5, 6, 2);
	AddEdge(6, 7, 1);
	AddEdge(6, 8, 6);
	AddEdge(7, 8, 7);

	/* Dijkstra output minimum distance from source 0
	Vertex   Distance from Source
	0          0
	1          4
	2          12
	3          19
	4          21
	5          11
	6          9
	7          8
	8          14
	*/
}

class ShortestPathAlgo {
private:
	MyGraph *m_pGraph;

public:
	ShortestPathAlgo(){
		m_pGraph = new MyGraph();
	}

	//Helper function
	void PrintMatrix(VVI vv);
	void PrintVector(VI vi);

	int ReadLowerHalfAdjMatrix(VVI& matrix);

	//Algo
	void Dijktra(MyGraph *pG, VI& dist, int src);

	void TestFun(ShortestPathAlgoType type);
};

void ShortestPathAlgo::PrintVector(VI vi)
{
	for (size_t j = 0; j < vi.size(); j++) {
		cout << j <<" : "<< vi[j] << endl;
	}
}

void ShortestPathAlgo::PrintMatrix(VVI vv)
{
	for (size_t i = 0; i < vv.size(); i++) {
		for (size_t j = 0; j < vv[i].size(); j++) {
			cout << setw(4) << vv[i][j] << " ";
		}
		cout << endl;
	}
}

/*
5
6
9 33
x 12 34
8 55 x 67
*/

int ShortestPathAlgo::ReadLowerHalfAdjMatrix(VVI& matrix)
{
	cout << "Enter no of vertex:";
	int v = 0;
	cin >> v;
	string str;
	matrix = VVI(v);
	for (auto i = 0; i < v; i++) {
		matrix[i] = vector<int>(v);
		matrix[i][i] = 0;
		for (auto j = 0; j < i; j++) {
			cin >> str;
			if (str == "x" || str == "X") {
				matrix[j][i] = matrix[i][j] = 0;
			}
			else {
				matrix[j][i] = matrix[i][j] = stoi(str);
			}
		}
	}
	return v;
}

void ShortestPathAlgo::Dijktra(MyGraph* pG, VI& dist, int src)
{
	VVI& adj = pG->GetAdj();
	VI visited(pG->GetV(), false);
	priority_queue<PII, vector<PII>, greater<PII>> pq;
	pq.push(make_pair(0, src));
	
	//for (size_t i = 0; i < dist.size(); i++) {
	//	dist[i] = INT_MAX;
	//}
	
	dist[src] = 0;

	while (!pq.empty()) {
		auto u = pq.top().second;
		pq.pop();
		visited[u] = true;

		for (size_t v = 0; v < adj.size(); v++) {
			if ((adj[u][v] != 0) && visited[v] == false) {
			//if ((adj[u][v] != 0)) {
				int new_d = dist[u] + adj[u][v];
				if (new_d < dist[v]) {
					dist[v] = new_d;
					pq.push(make_pair(new_d, v));
				}
			}
		}
	}


	for (size_t i = 0; i < dist.size(); i++) {
		cout << i << " -> " << dist[i] << endl;;
	}

}

void ShortestPathAlgo::TestFun(ShortestPathAlgoType type)
{

	switch (type) {
		case MODIFIED_BFS:
		{
			
		}
			break;
		case DIJKSTRA: 
		{
			m_pGraph->CreateDummyGraph();
			VI dist(m_pGraph->GetV(), INT_MAX);

			PrintMatrix(m_pGraph->GetAdj());
			Dijktra(m_pGraph, dist, 0);
			PrintVector(dist);
		}
			break;
		case BELLMAN_FORD:
			break;
	}
}

void ShortestPathAlogTest()
{
	ShortestPathAlgo algo;
	ShortestPathAlgoType type = DIJKSTRA;
	algo.TestFun(type);
}