#include "Graph.h"

int main()
{
	setlocale(LC_ALL, "rus");
	int n, m, f;
	std::cout << "Введите количество городов и дорог: ";
	//std::cin >> n >> m;
	GraphOnArray table(6);
	table.addEdge(0, 1);
	table.addEdge(1, 2);
	table.addEdge(2, 3);
	table.addEdge(3, 1);
	table.addEdge(3 ,4);
	table.addEdge(2, 5);

	std::cout << "Введите номера городов, которые соеденены дорогой: \n";
	/*for (int i = 0; i < m; i++)
	{
		int a, b;
		std::cin >> a >> b;
		table.addEdge(--a, --b);
	}*/
	std::cout << table << '\n';

	DFS(table, 2, 3);

	/*
	std::cout << "Введите номер города, в который надо попасть волшебнику: ";
	std::cin >> f;
	std::cout << "Введите положение волшебника: ";
	int a;
	std::cin >> a;
	*/
}
