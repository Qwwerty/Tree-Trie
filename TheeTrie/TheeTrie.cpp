// TheeTrie.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])

//Alphabet size( of symbols)
#define ALPHABET_SIZE (26)

//Converts key current character into index
// use only 'a' through 'z' and lower case
#define CHAR_TO_INDEX(c) ((int) c - (int)'a')



///Trie node
struct TrieNode
{
	struct TrieNode *children[ALPHABET_SIZE];

	///isEndOfWord is true if the node 
	///Represent end of a word
	bool isEndOfWord;
};

//Return new trie node(initialized to NULLs)
struct TrieNode *getNode(void)
{
	struct TrieNode *pNode = NULL;
	pNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));
	if (pNode) {
		int i;
		pNode->isEndOfWord = false;
		for (i = 0; i < ALPHABET_SIZE; i++)
		{
			pNode->children[i] = NULL;
		}
	}
	return pNode;
};

//If not present, inserts key into trie
//If the key is prefix of trie node, just marks leaf node
void insert(struct TrieNode *root, const char *key) {
	int level;
	int length = strlen(key);
	int index;
	
	struct TrieNode *pCrawl = root;

	for (level = 0; level < length; level++)
	{
		index = CHAR_TO_INDEX(key[level]);
		if (!pCrawl->children[index])
			pCrawl->children[index] = getNode();
		pCrawl = pCrawl->children[index];
	}
	//Mark last node as leaf
	pCrawl->isEndOfWord = true;
}

//Return true if key presents in trie, else false
bool search(struct TrieNode *root, const char *key) {
	int level;
	int lenght = strlen(key);
	int index;

	struct TrieNode *pCrawl = root;
	for (level = 0; level < lenght; level++)
	{
		index = CHAR_TO_INDEX(key[level]);
		if (!pCrawl->children[index])
			return false;
		pCrawl = pCrawl->children[index];
	}

	return (pCrawl != NULL && pCrawl->isEndOfWord);
}



int main()
{
    return 0;
}

