#include<iostream>
#include<string>

using namespace std;


struct TrieNode {
    int isEnd;
    TrieNode **child;

    TrieNode() {
        isEnd = 0;
        child = new TrieNode *[26];
        for (int i = 0; i < 26; i++)
            child[i] = NULL;
    }
};

void insert(TrieNode *root, string &word) {
    TrieNode *curr = root;
    //cout << "Insertnig : " << word << endl;
    for (int i = 0; i < word.length(); i++)
    {
        int index = word[i] - 'a';
        if (curr->child[index] == NULL)
            curr->child[index] = new TrieNode();
        curr = curr->child[index];
    }
    curr->isEnd = 1;
}
int search(TrieNode *root, string &key) {
    //cout << " searching: " << key << endl;
    TrieNode *curr = root;
    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (curr->child[index] == NULL) {
            return 0;
        }
        curr = curr->child[index];
    }
    return curr->isEnd;

}

int main() {
#ifndef ONLINE_JUDGE

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);

#endif
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        TrieNode *root = new TrieNode();
        for (int i = 0; i < n; i++) {
            string str;
            cin >> str;
            insert(root, str);
        }
        string key;
        cin >> key;
        cout << search(root, key) << endl;
    }

    return 0;
}
