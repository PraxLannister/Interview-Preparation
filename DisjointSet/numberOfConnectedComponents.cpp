#include<iostream>
#include <set>
using namespace std;
// class Graph
// {
// 	int V;
// 	list<int> *adj;
// public:
// 	Graph(int V)
// 	{
// 		this->V = V;
// 		adj = new list<int>[V];
// 	}
// 	void addEdge(int u,int v,bool bidir=true)
// 	{
// 		adj[u].push_back(v);
// 		if(bidir)
// 			adj[v].push_back(u);

// 	}
// }

int findRep(int x, int parent[])
{
	if (parent[x] == x)
		return x;
	return parent[x] = findRep(parent[x], parent);
}


/* This function does union of 2 nodes a and b */
// a : node 1
// b : node 2
// arr : array (n+1) size with elements from 1 to N equal to its index.
// rank1 : array (n+1) size with all elements equal to 1.
// n : Number of nodes
void unionNodes( int a, int b, int parent[], int rank1[], int n) {
	int a_rep = findRep(a, parent);
	int b_rep = findRep(b, parent);

	if (a_rep == b_rep)
		return;
	if (rank1[a_rep] > rank1[b_rep])
		parent[b_rep] = a_rep;
	else if (rank1[a_rep] < rank1[b_rep])
		parent[a_rep] = b_rep;
	else
	{
		parent[b_rep] = a_rep;
		rank1[a_rep]++;
	}
}

/* This function returns number of connected components */
// arr : array (n+1) size with elements from 1 to N equal to its index.
// rank1 : array (n+1) size with all elements equal to 1.
// n : Number of nodes
int findNumberOfConnectedNodes( int n, int parent[], int rank1[]) {
	set<int> s;
	for (int i = 1; i <= n; i++)
	{
		int x_rep = findRep(i, parent);
		s.insert(x_rep);
	}
	return s.size();
}
int main()
{
#ifndef ONLINE_JUDGE

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	freopen("error.txt", "w", stderr);

#endif
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);



	int test;
	cin >> test;
	while (test--)
	{
		int n, m;
		cin >> n >> m;
		int parent[n + 1];
		int rank1[n + 1];
		for (int i = 1; i <= n; i++) {
			parent[i] = i;
			rank1[i] = 1;
		}
		for (int i = 0; i < m; i++)
		{
			int u, v;
			cin >> u >> v;
			unionNodes(u, v, parent, rank1, n);
		}
		cout << findNumberOfConnectedNodes(n, parent, rank1) << endl;


	}


	return 0;
}