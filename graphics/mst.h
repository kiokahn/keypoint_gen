#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
namespace graphics {
	// a structure to represent a weighted edge in graph
	struct MSTEdge
	{
		int src, dest;
		float weight;
		MSTEdge(const MSTEdge& cp):src(cp.src), dest(cp.dest), weight(cp.weight) {}
		MSTEdge(): src(0),dest(0), weight(0) {}
		MSTEdge(int s, int d, float w): src(s), dest(d), weight(w) {}
	};

	// a structure to represent a connected, undirected
	// and weighted graph
	struct MSTGraph
	{
		// V-> Number of vertices, E-> Number of edges
		int V;

		// graph is represented as an array of edges. 
		// Since the graph is undirected, the edge
		// from src to dest is also edge from dest
		// to src. Both are counted as 1 edge here.
		std::vector<MSTEdge> edge;

		void addEdge(MSTEdge& cp) {
			edge.push_back(cp);
		}

		MSTGraph() : edge() {}
	};

	// Creates a graph with V vertices and E edges
	MSTGraph* createGraph(int V);

	std::vector<MSTEdge> KruskalMST(MSTGraph* graph);
}