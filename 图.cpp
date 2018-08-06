#include<iostream>
#include "vector.h"
using namespace std;
typedef enum {UNDISCOVERED,DISCOVERED,VISITED} VStatus;//�����״̬
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } Estatus; //�ߵ�״̬
//ͼ������
template<typename Tv>
struct Vertex {
	Tv data;  //�ڵ������
	int inDegree; //���
	int outDegree; // ����
	VStatus status; //���� ��״̬  ����
	int dTime, fTime; // ʱ���ǩ ��
	int Parent; //�������и��ڵ�ĸ��� ��
	int priority; //���ȼ��� ��
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
//ͼ����
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
//���ڽӾ������ʽ����ͼ
template<typename Tv,typename Te>
class Graph  {
public:
	Vector<Vertex<Tv>> V; // ���㼯  ������ʽ
	int n; // ������
	Vector<Vector<Edge<Te>*>> E;// �߼� ��ά����������ʽ
	int e; //����
	Graph(int num_v = 0, int num_e = 0) {  //���캯��
		n = num_v;
		e = num_e;
	}
	~Graph() {          //��������  ɾ�������ı�
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				delete E[i][j];
	}
	//����Ļ�������
	//����Ķ�̬����
	int insert_vertex(Tv const & value);  //����ֵΪvalue�Ķ��� ��������
	Tv remove_vertex(int i); //ɾ����i������ �Լ������ı�
};

//����Ĳ���
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

//������
int main() {
	Graph<int,int> test_graph;
	cout << test_graph.n << endl;
	test_graph.insert_vertex(1);
	cout << test_graph.n << endl;
	//cout << test_graph.E[0][0]->data << endl;
	return 0;
}