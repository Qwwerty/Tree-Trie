// TheeTrie.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

//Menu
int  Menu() {
	printf("1 - INSERIR\n");
	printf("2 - BUSCAR\n");
	printf("0 - SAIR\n\n");
	printf("ESCOLHA: ");
	int escolha = scanf("%d", &escolha);
	return escolha;
}

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
/*
	line 40 - Função *getNome vai retorna um struct do tipo TrieNode...
	line 41 - Cria um *pNode que é um ponteiro d Struct TrieNode...
	line 44 - Verifica se pNode foi criado a memória...
	line 47 - Dentro do struct TrieNode tem um boolean para verificar se já foi lida a palavra toda... 
	line 49 a 52 - Vai inserir NULL em todos os indices filho...
*/

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
/*
	Função de busca...
	line 67- São os níveis...
	line 68 - Pega o tamanho da key, no parametro é passado a key...
	line 69 - Apenas o index de posição do elemento...
	line 70 -  Declara a variavel *pCrawl do tipo struct TrieNode e faz *pCrawl apontar para ponteiro de root...
	line 75 - For para ir descendo os niveis de acordo com o tamanho da key...
	line 78 - O index vai receber a função CHAR_TO_INDEX e transforma aquele charactere em index;
	line 79 - Pergunta se aquele children[index] não existe, se não existir chama a função getNode e insere o elemento
	line 80 - so vai seguindo ponteiro de ponteiro;

	
*/

void insert(struct TrieNode *root, char *key) {
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
    //Input keys (use only 'a' through 'z'
	// and lower case
	char keys[][10] = { "rhalf", "souza" };

	char output[][32] = { "No present in trie", "Present in trie" };

	struct TrieNode *root = getNode();

	int i;
	for (i = 0; i < ARRAY_SIZE(keys); i++)
		insert(root, keys[i]);
	
	// Search for different keys
	printf("%s --- %s\n", "rhalf", output[search(root, "rhalf")]);
	printf("%s --- %s\n", "souza", output[search(root, "souzaa")]);

	system("\n\npause");
	return 0;
}
