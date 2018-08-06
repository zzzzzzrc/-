#include<iostream>
#include "vector.h"
using namespace std;
typedef enum {UNDISCOVERED,DISCOVERED,VISITED} VStatus;//顶点的状态
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } Estatus; //边的状态
//图顶点类
template<typename Tv>
struct Vertex {
	Tv data;  //节点的数据
	int inDegree; //入度
	int outDegree; // 出度
	VStatus status; //顶点 的状态  三种
	int dTime, fTime; // 时间标签 ？
	int Parent; //遍历树中父节点的个数 ？
	int priority; //优先级数 ？
	Vertex(Tv const & value = (Tv) 0, int indegree=0, int outdegree=0, VStatus sta=UNDISCOVERED, int dtime = -1, int ftime = -1, int parent = -1, int prior = INT_MAX) {
		data = value;
		inDegree = indegree;
		outDegree = outdegree;
		status = sta;
		dTime = dtime;
		fTime = ftime;
		Parent = parent;
		priority = prior;
	}
};
//图边类
template<typename Te>
struct Edge {
	Te data;
	int weight;
	Estatus status;
	Edge(Te value, int w=0, Estatus stat=UNDETERMINED) {
		data = value;
		weight = w;
		status = stat;
	}
};
//以邻接矩阵的形式构建图
template<typename Tv,typename Te>
class Graph  {
public:
	Vector<Vertex<Tv>> V; // 顶点集  向量形式
	int n; // 顶点数
	Vector<Vector<Edge<Te>*>> E;// 边集 二维向量矩阵形式
	int e; //边数
	Graph(int num_v = 0, int num_e = 0) {  //构造函数
		n = num_v;
		e = num_e;
	}
	~Graph() {          //析构函数  删除创建的边
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				delete E[i][j];
	}
	//顶点的基本操作
	//顶点的动态操作
	int insert_vertex(Tv const & value);  //插入值为value的顶点 返回其编号
	Tv remove_vertex(int i); //删除第i个顶点 以及关联的边
};

//顶点的插入
template<typename Tv,typename Te>
int Graph<Tv, Te>::insert_vertex(Tv const & value) {
	for (int i = 0; i < n; i++) {
		E[i].insert(NULL);
	}
	n++;
	E.insert(Vector<Edge<Te>*>(n, n, (Edge<Te>*)NULL));
	return V.insert(Vertex<Tv>(value));
}
template<typename Tv,typename Te>
Tv Graph<Tv, Te>::remove_vertex(int i) {
	for (int j = 0; j < n; j++) {
		if (E[i][j]) {             //i to other exist
			delete E[i][j];
			V[j].inDegree--;
		}
	}
	E.remove(i, i + 1);
	n--;
	for (int j = 0; j < n; j++) {
		if (E[j][i]) {           //others to i exist
			delete E[j][i];
			V[j].outDegree--;
		}
	}
	V.remove(i, i + 1);
}

//主函数
int main() {
	Graph<int,int> test_graph;
	cout << test_graph.n << endl;
	test_graph.insert_vertex(1);
	cout << test_graph.n << endl;
	//cout << test_graph.E[0][0]->data << endl;
	return 0;
}