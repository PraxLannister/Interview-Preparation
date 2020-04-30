#include<string>
using namespace std;

class TrieNode {
public:
	TrieNode ** child;
	bool isTerminal;

	TrieNode() {
		child = new TrieNode *[26];
		for (int i = 0; i < 26; i++)
			child[i] = NULL;
		isTerminal = false;
	}
	~TrieNode() {

		for (int i = 0; i < 26; i++) {
			delete child[i];
		}
		delete [] child;
	}
};

class Trie
{
	TrieNode * root;
	size_t count;
public:

	Trie() {
		root =  new TrieNode();
		count = 0;
	}

	void insert(std::string &word) {
		TrieNode * temp = root;
		for (int i = 0; i < word.length(); i++) {
			int index = word[i] - 'a';
			if (temp->child[index] == NULL)
				temp->child[index] = new TrieNode();
			temp = temp->child[index];
		}
		temp->isTerminal = true;
		count++;
	}

	bool search(std::string &key) {
		TrieNode *temp = root;
		for (int i = 0; i < key.length(); i++) {
			int index = key[i] - 'a';
			if (temp->child[index] == NULL)
				return false;
			temp = temp->child[index];
		}
		return temp->isTerminal;

	}

	void displayUtil(TrieNode *curr, std::string &output)
	{
		//cout << "Called = " << output << " = " << endl;
		if (curr->isTerminal == true) {
			cout << output << std::endl;
		}
		for (int i = 0; i < 26; i++)
		{
			if (curr->child[i] != NULL) {
				output.push_back(i + 'a');
				displayUtil(curr->child[i], output);
				output.pop_back();
			}
		}
	}

	void remove(string &key) {
		TrieNode *curr = root;
		int level = 0;
		deleteUtil(curr, key, level);

	}

	bool isNodeEmpty(TrieNode *curr) {
		for (int i = 0; i < 26; i++) {
			if (curr->child[i] == NULL)
				return false;
		}
		return true;
	}


	TrieNode *deleteUtil(TrieNode *root, string &key, int level) {
		//Base Case
		//1
		if (root == NULL)
			return root;
		//2
		if (level == key.size())
		{
			//We Have cover all the words of key
			//make this string non terminal
			root->isTerminal = false;

			//check if curr node is empty
			if (isNodeEmpty(root)) {
				//if empty that means it need to be deleted
				delete(root);
				root =  NULL;
			}
			return root;
		}

		int index = key[level] - 'a';
		root->child[index] = deleteUtil(root->child[index], key, level + 1);
		if (isNodeEmpty(root) and root->isTerminal == false) {
			delete(root);
			root = NULL;
		}
		return root;
	}

	void display() {
		std::string output;
		TrieNode *curr = root;
		displayUtil(curr, output);
	}


	size_t size() {
		return count;
	}
	~Trie() {
		delete root;
	}

};