#pragma once
#include <iostream>
#include <vector>
#include <fstream>

class Graph
{
public:
	virtual void addEdge(int i, int j) = 0;
	virtual void addVertex(int i) = 0;
	virtual void removeVertex(int i) = 0;
	virtual void removeEdge(int i, int j) = 0;
	virtual bool isEdgeExist(int i, int j) = 0;
};

class GraphOnArray: public Graph
{
	std::vector<std::vector<int>> graph;
	int vertex_count;
public:
	GraphOnArray() :vertex_count(0) {};
	GraphOnArray(int n) :vertex_count(n) 
	{
		std::vector<int> temp(n, 0);
		graph = std::vector<std::vector<int>> (n, temp);
	};
	GraphOnArray(std::vector<std::vector<int>> matrix)
	{
		graph = matrix;
		vertex_count = matrix.size();
	}
	void addEdge(int i, int j);
	void addVertex(int i)
	{
		graph.push_back(std::vector<int>(vertex_count, 0));
		vertex_count++;
		for (int i = 0; i < vertex_count; i++)
		{
			graph[i].push_back(0);
		}
	}
	void removeEdge(int i, int j);
	void removeVertex(int i);
	bool isEdgeExist(int i, int j) { return graph[i][j] == 1; };
	std::vector<std::vector<int>> getGraphTable() { return graph; }
	int getVertexCount() { return vertex_count; }
	friend std::ostream& operator<<(std::ostream& out, GraphOnArray& obj)
	{
		for (int i = 0; i < obj.vertex_count; i++)
		{
			out << (i + 1) << "->";
			for (int j = 0; j < obj.vertex_count; j++)
			{
				if (obj.graph[i][j] == 1)
					out << (j + 1) << "->";
			}
			out << '\n';
		}
		return out;
	}
};

void GraphOnArray::addEdge(int x, int y) 
{
	if (x < vertex_count && y < vertex_count && x >= 0 && y >= 0)
	{
		graph[x][y] = 1;
		graph[y][x] = 1;
	}
}

inline void GraphOnArray::removeEdge(int i, int j)
{
	if (i < vertex_count && j < vertex_count && i >= 0 && j >= 0)
	{
		graph[i][j] = 0;
		graph[j][i] = 0;
	}
}

inline void GraphOnArray::removeVertex(int i)
{
	graph.erase(graph.begin() + i);
	vertex_count--;
	for (int j = 0; j < vertex_count; j++)
	{
		graph[j].erase(graph[j].begin() + i);
	}
}
void dfs1(std::vector<std::vector<int>> table, int i, int f, int &fin, int* mas)
{
	std::cout << i + 1 << "->";
	mas[i] = 1;
	for (int j = 0; j < table[i].size(); j++)
	{
		if (mas[j] != 1)
		{
			if (table[i][j] == 1)
			{
				if (j != f && fin != f)
				{
					dfs1(table, j, f, fin, mas);
				}
				else if (j == f && fin != f)
				{
					fin = f;
					std::cout << j + 1;
				}
			}
		}

	}
}

void dfs2(std::vector<std::vector<int>> table, int i, int f, int* mas, int &fin)
{
	int temp;
	std::cout << i + 1 << "->";
	if (mas[i] != 1)
	{
		mas[i] = 2;
	}
	else if (mas[i] == 1)
	{
		mas[i] = 3;
	}
	for (int j = table[i].size()-1; j >= 0; j--)
	{
		if (mas[j] == 1)
		{
			temp = j;
		}
		if (mas[j] != 2 && mas[j] != 3 && mas[j] != 1)
		{
			if (table[i][j] == 1)
			{
				if (j != f && fin != f)
				{
					dfs2(table, j, f, mas, fin);
				}
				else
				{
					std::cout << j + 1;
					fin = f;
				}
			}
		}
	}
	if (fin != f)
	{
		for (int j = temp; j >= 0; j--)
		{
			if (mas[j] != 2 && mas[j] != 3)
			{
				if (table[i][j] == 1)
				{
					if (j != f)
					{
						dfs2(table, j, f, mas, fin);
					}
				}
			}
		}
	}
}

void DFS(GraphOnArray graph , int mag1, int mag2)
{
	std::vector<std::vector<int>> table = graph.getGraphTable();
	int n = graph.getVertexCount();
	int* mas = new int[n];

	//0 - не окрашено, 1 - синий, 2 - жёлтый, 3 - зелёный, 4 - чёрный(хода нет)
	for (int i = 0; i < n; i++)
	{
		mas[i] = 0;
	}
	int fin = -1;
	int last = 0;
	dfs1(table, mag1, last, fin, mas);
	std::cout << '\n';
	for (int i = 0; i < n; i++)
	{
		std::cout << mas[i];
	}
	std::cout << '\n';

	fin = -1;
	std::cout << '\n';
	dfs2(table, mag2, last, mas, fin);
	

	int count = 0;
	std::cout << '\n';
	mas[last] = 3;
	for (int i = 0; i < n; i++)
	{
		std::cout << mas[i];
	}
	std::cout << '\n';


	for (int i = 0, j = 1; i < n - 1, j < n; i++, j++)
	{
		if (mas[i] == mas[j])
			if (mas[i] == 3)
				count++;
	}
	std::cout << '\n' << count;
	//for (int i = 0; i < n; i++)
	//{
	//	if (mas[i] == 0)
	//		dfs(table, i, mas);
	//}
}

//void bfs(int v, std::vector<std::vector<int>> table, int* mas)
//{
//	TQueue q;
//	q.enque(v);
//	mas[v] = 1;
//	while (!q.isEmpty())
//	{
//		int temp = q.peek();
//		for (int j = 0; j < table[temp].size(); j++)
//		{
//			if (table[temp][j] == 1)
//			{
//				q.enque(j);
//				mas[j] = 1;
//			}
//		}
//		q.deque();
//	}
//}

//void BFS(Graph graph)
//{
//	std::vector<std::vector<int>> table = graph.getGraphTable();
//	int n = graph.getVertexCount();
//	int* mas = new int[n];
//	for (int i = 0; i < n; i++)
//	{
//		mas[i] = 0;
//	}
//	for (int i = 0; i < n; i++)
//	{
//		if (mas[i] = 0)
//			bfs(i, table, mas);
//	}
//}