#ifndef GRAPH_H
#define GRAPH_H
#include <limits>

typedef unsigned long long uint64;
typedef long double real;

class Graph
{
	uint64 numV;
	uint64 numE;
	real** am;	
public:

	void AddDEdge(uint64 v1, uint64 v2, real w)
	{
		am[v1][v2] = w;
		++numE;
	}

	void AddEdge(uint64 v1, uint64 v2, real w)
	{
		AddDEdge(v1, v2, w);
		AddDEdge(v2, v1, w);
	}

	real Dijkstra(uint64 v1, uint64 v2)
	{
		real* L = new real[numV];
		bool* done = new bool[numV];
		for(uint64 i = 0; i < numV; ++i)
		{
			L[i] = std::numeric_limits<real>::infinity();
			done[i] = false;
		}
		L[v1] = 0;
		while(true)
		{	//Find next shortest path
			uint64 min = 0;
			real minv = std::numeric_limits<real>::infinity();
			for(uint64 i = 0; i < numV; ++i)
			{
				if(!done[i] && minv > L[i])
				{
					minv = L[i];
					min = i;
				}
			}
			//Check if we found the desired vertex
			if(v2 == min)
				break;
			//Mark visited
			done[min] = true;
			//Update adjacent vertices
			for(uint64 i = 0; i < numV; ++i)
			{
				if(done[i])
					continue;
				if(EdgeExists(min, i))
					L[i] = (L[i] > L[min] + am[min][i] ? L[min] + am[min][i] : L[i]);
			}
		}
		real retv = L[v2];
		delete [] L;
		delete [] done;
		return retv;	
	}

	bool EdgeExists(uint64 v1, uint64 v2)
	{
		return am[v1][v2] != std::numeric_limits<real>::infinity();
	}

	Graph(uint64 numVertex)
	{
		numV = numVertex;
		am = new real*[numV];
		for(uint64 i = 0; i < numV; ++i)
			am[i] = new real[numV];
		Reset();
	}

	~Graph()
	{
		for(uint64 i = 0; i < numV; ++i)
			delete [] am[i];
		delete [] am;
	}

	void Reset()
	{
		for(uint64 i = 0; i < numV; ++i)
		{
			for(uint64 j = 0; j < numV; ++j)
				am[i][j] = std::numeric_limits<real>::infinity();
		}	
		numE = 0;
	}	
};
#endif
