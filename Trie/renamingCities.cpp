#include <iostream>
#include<string>

using namespace std;

class TrieNode
{

public:

	int isEndCount;
	TrieNode **child;

	TrieNode() {
		isEndCount = 0;
		child = new TrieNode*[26];
		for (int i = 0; i < 26; i++)
			child[i] = NULL;
	}
	~TrieNode() {
		for (int i = 0; i < 26; i++)
			delete child[i];
		delete [] child;
	}
};

class Trie
{
	TrieNode *root;
public:

	Trie() {
		root = new TrieNode();
	}

	string insertAndPrint(string &word)
	{
		TrieNode *curr = root;
		string output;
		bool flag = true;
		for (int i = 0; i < word.length(); i++)
		{
			int index = word[i] - 'a';
			if (flag) {
				output = output + word[i];
			}
			if (curr->child[index] == NULL) {
				//cout << "creatinf new NOde for :" << word[i] << endl;
				curr->child[index] = new TrieNode();
				flag = false;
			}
			curr = curr->child[index];
		}
		curr->isEndCount += 1;;
		if (curr->isEndCount >= 2) {
			output += ' ';
			output += curr->isEndCount + '0';
		}

		//cout << "return :" << endl;
		return output;

	}
	// string insertAndPrint(string &word)
	// {
	// 	string output;
	// 	TrieNode * temp = root;
	// 	bool flag = true;
	// 	for (int i = 0; i < word.size(); i++)
	// 	{
	// 		int index = word[i] - 'a';
	// 		if (flag)
	// 			output = output + word[i];
	// 		if (temp->child[index] == NULL) {
	// 			flag = false;
	// 			temp->child[index] = new TrieNode();
	// 		}
	// 		temp = temp->child[index];
	// 	}
	// 	temp->isEndCount += 1 ;
	// 	if (temp->isEndCount > 1) {
	// 		output += ' ';
	// 		output += temp->isEndCount + '0';
	// 	}

	// 	return output;

	// }
	~Trie() {
		delete root;
	}

};

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


	int t;
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;
		string city;
		string stationCode;
		Trie cities;
		for (int i = 0; i < n; i++)
		{
			cin >> city;
			stationCode = cities.insertAndPrint(city);
			cout << stationCode << endl;
		}
	}


	return 0;
}

