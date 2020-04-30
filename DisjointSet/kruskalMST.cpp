#include<bits/stdc++.h>
#define ll long long int
using namespace std;
struct  Edge
{
	int src;
	int dest;
	ll weight;
};
void edgeListPrint(Edge EdgeList[], int E)
{
	for (int i = 0; i < E; i++) {
		cout << EdgeList[i].src << " - ";
		cout << EdgeList[i].dest << " [ ";
		cout << EdgeList[i].weight << " ] ";
		cout << endl;
	}
	cout << endl;
}
bool cmp(Edge e1, Edge e2)
{
	return e1.weight < e2.weight;
}
int findRep(int x, int parent[])
{
	if (x == parent[x])
		return x;
	return parent[x] = findRep(parent[x], parent);
}
void unionDSU(int parent[], int rank[], int u, int v)
{
	int u_rep = findRep(u, parent);
	int v_rep = findRep(v, parent);

	if (u_rep == v_rep)
		return;
	if (rank[u_rep] < rank[v_rep])
		parent[u_rep] = v_rep;
	else if (rank[v_rep] < rank[u_rep])
		parent[v_rep] = u_rep;
	else {
		parent[v_rep] = u_rep;
		rank[u_rep]++;
	}

}

ll kruskalDSU(vector<pair<int, ll>> adj[], int V, int E) {
	Edge EdgeList[E];
	int e = 0;
	for (int i = 1; i <= V; i++)
	{
		int u = i;
		for ( auto v_pair : adj[i]) {
			int v = v_pair.first;
			ll wt = v_pair.second;
			auto f = find(adj[v].begin(), adj[v].end(), make_pair(u, wt));
			adj[v].erase(f);
			EdgeList[e].src = u;
			EdgeList[e].dest = v;
			EdgeList[e].weight = wt;
			e++;
		}
	}
	sort(EdgeList, EdgeList + E, cmp);
	//edgeListPrint(EdgeList, E);
	int parent[V + 1];
	int rank[V + 1];
	for (int i = 0; i <= V; i++) {
		parent[i] = i;
		rank[i] = 0;
	}
	int count = 0;
	ll mstWt = 0l;
	for (int i = 0; i < E; i++) {
		int u = EdgeList[i].src;
		int v = EdgeList[i].dest ;
		int u_rep = findRep(u, parent);
		int v_rep = findRep(v, parent);
		if (u_rep != v_rep) {
			unionDSU(parent, rank, u, v);
			ll wt = EdgeList[i].weight;
			mstWt += wt;
			count++;
		}

	}
	return mstWt;



}
void addEdge(vector<pair<int, ll>> adj[], int u, int v, ll w) {
	adj[u].push_back(make_pair(v, w));
	adj[v].push_back(make_pair(u, w));

}
void showGraph(vector<pair<int, ll> > adj[], int V)
{
	for (int i = 1; i <= V; i++)
	{
		cout << i << " -> ";
		for ( auto v_pair : adj[i])
			cout << v_pair.first << "( " << v_pair.second << " ),";
		cout << endl;
	}
	cout << "\n=============\n";

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
		int V, E;
		cin >> V >> E;
		vector<pair<int , ll> >adj[V + 1];
		for (int i = 0; i < E; i++)
		{
			int u, v;
			ll w;
			cin >> u >> v >> w;
			addEdge(adj, u, v, w);
		}
		cout << kruskalDSU(adj, V, E) << endl;

	}


	return 0;

}