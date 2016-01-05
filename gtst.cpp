#include <iostream>
#include "Graph.h"
using namespace std;

enum V {a, b, c, d, e, z};

int main()
{
	Graph grph(6);
	grph.AddEdge(a, b, 2);
	grph.AddEdge(a, d, 1);
	grph.AddEdge(b, c, 3);
	grph.AddEdge(b, e, 1);
	grph.AddEdge(d, e, 1);
	grph.AddEdge(c, z, 2);
	grph.AddEdge(e, z, 2);
	cout << grph.Dijkstra(a, z) << endl;
	return 0;
}
