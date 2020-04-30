#include <iostream>
#include <vector>
#include<algorithm>

using namespace std;





/*  Function to check if there is cycle in graph
*   adj[]: array of vectors to represent graph
*   n and e are number of nodes and edges respectively
*   parent[]: array to store parent of nodes. Each index stores its node value
* initially
*   rank1[]: Each node from 1 to n store initial size as 1.
*/

int findRep(int x, int parent[])
{
	if (x == parent[x])
		return x;
	return parent[x]  = findRep(parent[x], parent);
}

void unionDSU(int x, int y, int parent[], int rank1[])
{
	int x_rep = findRep(x, parent);
	int y_rep = findRep(y, parent);

	if (x_rep == y_rep)
		return;
	if (rank1[x_rep] > rank1[y_rep])
		parent[y_rep] = x_rep;
	else if (rank1[x_rep] < rank1[y_rep])
		parent[x_rep] = y_rep;
	else
	{
		parent[x_rep] = y_rep;
		rank1[y_rep]++;
	}
}
bool findCycle(vector<int> adj[], int parent[], int rank1[], int n, int e) {
	for (int i = 1; i <= n; i++)
	{
		for (int nbr : adj[i])
		{
			int x = i;
			int y = nbr;

			int x_rep = findRep(x, parent);
			int y_rep = findRep(y, parent);

			if (x_rep == y_rep)
				return true;
			else {
				unionDSU(x, y, parent, rank1);
				auto f  = find(adj[y].begin(), adj[y].end(), x);
				adj[y].erase(f);
			}
		}
	}
	return false;

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
		int v, e;
		cin >> v >> e;
		vector<int> adj[v + 1];
		for (int i = 0; i < e; i++)
		{
			int u, v;
			cin >> u >> v;
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		int parent[v + 1];
		int rank1[v + 1];
		for (int i = 0; i <= v; i++)
		{
			parent[i] = i;
			rank1[i] = 1;
		}
		bool mili_cyle = findCycle(adj, parent, rank1, v, e);
		if (mili_cyle)
			cout << "FOUND:" << endl;
		else
			cout << "NOT FOUND" << endl;
	}


	return 0;
}