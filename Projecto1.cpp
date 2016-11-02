// Diogo Freitas 81586
// Francisco Mira 80888
// Projecto 1 - Analise e Sintese de Algoritmos

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <list>

#define NIL -1

std::vector< std::list<int> > graph;
std::vector<bool> visited;
std::vector<int> discovery;
std::vector<int> low;
std::vector<int> parent;
std::vector<bool> ap;
int countAP = 0, Min = -1, Max = -1;

int min(int a, int b){
	return !(b < a) ? a:b;
}

void tarjanAlgorithm(int u){
	static int time = 0;
	int childCount = 0;
	visited[u] = true;
	discovery[u] = low[u] = ++time;
	std::list<int>::iterator i;
	for (i = graph[u].begin(); i != graph[u].end(); i++){
		int v = *i;
		if (visited[v] == false){
			childCount++;
			parent[v] = u;
			tarjanAlgorithm(v);
			low[u] = min(low[u], low[v]);
			if ((parent[u] == NIL && childCount > 1) || (parent[u] != NIL && low[v] >= discovery[u])){
				if (ap[u] != true){
					ap[u] = true;
					countAP++;
					if (Min == -1 || Min > u)
						Min = u;
					if (Max == -1 || Max < u)
						Max = u;
				}
			}
		}
		else if (v != parent[u])
			low[u] = min(low[u], discovery[v]);
	}
}

int main() {
	int nVer, nCon, v1, v2;
	scanf("%d %d", &nVer, &nCon);
	graph = std::vector< std::list<int> >(nVer + 1);
	visited = std::vector<bool>(nVer + 1, false);
	discovery = std::vector<int>(nVer + 1, NIL);
	low = std::vector<int>(nVer + 1, NIL);
	parent = std::vector<int>(nVer + 1, NIL);
	ap = std::vector<bool>(nVer + 1, false);
	for (int c = 0; c < nCon; c++){
		scanf("%d %d", &v1, &v2);
		graph[v1].push_back(v2);
		graph[v2].push_back(v1);
	}
	tarjanAlgorithm(1);
	printf("%d\n%d %d\n", countAP, Min, Max);
	return 0;
}