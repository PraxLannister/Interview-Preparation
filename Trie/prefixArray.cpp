#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct TrieNode
{
	int visitCount;
	int isTerminal;
	unordered_map<char, TrieNode*> child_map;

	TrieNode()
	{
		isTerminal = 0;
		visitCount = 0;
	}

};

class Trie
{
	TrieNode *root;
public:
	Trie()
	{
		root = new TrieNode();
	}
	void insert(string &word) {
		// cout << "called for :" << word << endl;
		TrieNode *curr = root;
		curr->visitCount++;
		for (char ch : word) {
			// cout << ch << " -- ";
			if (curr->child_map.count(ch) == 0 or curr->child_map[ch] == nullptr) {
				// cout << "New Node for : " << ch << endl;
				curr->child_map[ch] = new TrieNode();
			}
			curr = curr->child_map[ch];
			curr->visitCount++;
		}
		curr->isTerminal = true;
	}
	int search(string &word) {
		TrieNode *curr = root;
		for (char ch : word) {
			if (curr->child_map.count(ch) == 0)
				return 0;
			curr = curr->child_map[ch];
		}
		return 1;
	}
	vector<string> display() {
		TrieNode * curr = root;
		vector<string> output;
		string helper;
		if (!isNodeEmpty(curr))
			displayUtil(curr, output, helper);
		return output;
	}
	void displayUtil(TrieNode *curr, vector<string> &output, string &helper) {
		if (curr->isTerminal) {
			output.push_back(helper);
		}

		for (auto p : curr->child_map) {
			if (p.second != nullptr) {
				char ch = p.first;
				helper.push_back(ch);
				displayUtil(p.second, output, helper);
				helper.pop_back();
			}
		}



	}
	void remove(string &word) {
		//cout << "called FOR :" << word << endl;
		TrieNode * curr = root;
		if (!isNodeEmpty(root) and !word.empty())
			removeUtil(curr, word, 0);
	}

	TrieNode* removeUtil(TrieNode *curr, string &word, int level) {
		if (curr == nullptr)
			return curr;  //----------------------------------  1
		if (level == word.size()) {
			curr->isTerminal = false;
			curr->visitCount--;
			if (isNodeEmpty(curr)) {
				delete curr;
				curr = nullptr;
			}
			return curr;
		}
		char ch = word[level];
		if (curr->child_map.count(ch)) {
			curr->child_map[ch] = removeUtil(curr->child_map[ch], word, level + 1);
			if (curr->child_map[ch] == nullptr) {
				curr->child_map.erase(ch);
			}
			curr->visitCount--;
			if (isNodeEmpty(curr) and !curr->isTerminal) {
				delete curr;
				curr = nullptr;
			}
		}
		return curr;


	}
	string printPrefixes(string &word) {
		TrieNode *curr = root;
		string prefix;
		if (!isNodeEmpty(curr))
			printPrefixesUtil(curr, word, prefix, 0);
		return prefix;

	}
	void printPrefixesUtil(TrieNode*curr, string &word, string &prefix, int level) {
		if (curr == nullptr)
			return;
		if (curr->visitCount <= 1) {
			return;
		}
		if (level == word.size()) {
			prefix.clear();
			return;
		}
		char ch =  word[level];
		if (curr->child_map.count(ch) == 0 or curr->child_map[ch] == nullptr) {
			prefix.clear();
			return;
		}
		else {
			prefix.push_back(ch);
			printPrefixesUtil(curr->child_map[ch], word, prefix, level + 1);
		}

	}
	bool isNodeEmpty(TrieNode *curr) {
		for (auto p : curr->child_map) {
			if (p.second != nullptr)
				return false;
		}
		return true;
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


	int n;
	string str;
	Trie t;
	cin >> n;
	while (n--) {
		cin >> str;
		t.insert(str);
	}
	vector<string> output = t.display();
	sort(output.begin(), output.end());
	for (string str : output)
	{
		cout << str << " - " << t.printPrefixes(str) << endl;
	}
	cout << "\n-------------\n";
	t.remove(str);
	output = t.display();
	for (string str : output)
	{
		cout << str << " - " << t.printPrefixes(str) << endl;
	}

	return 0;
}