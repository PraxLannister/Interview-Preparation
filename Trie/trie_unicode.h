#include <unordered_map>
#include <iostream>
#include <string>
using namespace std;

class TrieNode
{
public:
	char ch;
	int isTerminal;
	unordered_map<char, TrieNode*> child;

	TrieNode(char ch) {
		this->ch = ch;
		isTerminal = 0;
	}
	~TrieNode() {
		child.clear();
	}
};

class Trie
{
	TrieNode * root;
	size_t size;
public:
	Trie() {
		root = new TrieNode('\0');
		size = 0;
	}
	/////////////////////////////////////////////
	void insert(string &key ) {
		TrieNode * temp = root;
		for (int i = 0; i < key.size(); i++) {
			char ch = key[i];
			if (temp->child.count(ch) == 0 or temp->child[ch] == nullptr)
				temp->child[ch] = new TrieNode(ch);
			temp = temp->child[ch];
		}
		temp->isTerminal = true;
		size++;
	}
	///////////////////////////////////////////
	int search(string &key) {
		TrieNode * temp = root;
		for (int i = 0; i < key.size(); i++) {
			char ch = key[i];
			if (temp->child.count(ch) == 0 or temp->child[ch] == nullptr)
				return 0;
			temp = temp->child[ch];
		}
		return temp->isTerminal;
	}
	//////////////////////////////////////////
	void displayUtil(TrieNode *curr, string output) {

		if (curr == nullptr)
			return;

		if (curr->isTerminal) {
			cout << output << endl;
		}

		for (auto p : curr->child) {
			output.push_back(p.first);
			displayUtil(p.second, output);
			output.pop_back();
		}
	}
	//////////////////////////////////////////
	void display() {
		TrieNode * temp = root;
		string output;
		displayUtil(temp, output);
	}
	///////////////////////////////////////////
	bool isNodeEmpty(TrieNode * temp) {
		for (auto p : temp->child) {
			if (p.second != nullptr)
				return false;
		}
		return true;
	}
	///////////////////////////////////////////
	bool deleteUtil(TrieNode *curr, string key, int level) {
		if (curr == nullptr )
			return false;//?? Doubt
		if (level == key.size())
		{
			curr->isTerminal = false;
			//if is leaf node and empty
			if (isNodeEmpty(curr))
			{
				delete curr;
				curr = nullptr;
				return true;
			}
			return false;
		}
		char ch = key[level];
		if (curr->child.count(ch))
		{
			if (deleteUtil(curr->child[ch], key, level + 1))
				curr->child[ch] = nullptr;
			if (isNodeEmpty(curr))
			{
				delete curr;
				curr = nullptr;
				return true;
			}

			return false;
		}
		return false;
	}
	///////////////////////////////////////////
	void remove(string &key) {
		TrieNode * temp = root;
		deleteUtil(temp, key, 0);
	}



	~Trie() {
		delete root;
	}

};