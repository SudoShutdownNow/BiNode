#include <iostream>
using namespace std;
#define OK 0
#define ERROR -1

struct BiNode
{
	char data;
	BiNode* lchild, * rchild;


	BiNode() :lchild(NULL), rchild(NULL) {};
	BiNode(BiNode* myr, char myd) :lchild(NULL), rchild(myr), data(myd) {};
	BiNode(BiNode* myl, BiNode* myr, char myd) :lchild(myl), rchild(myr), data(myd) {};

	


};

BiNode* createTree()
{
	BiNode* newtree = new BiNode();
	char *val = new char;
	*val = getchar();
	if ( *val != '#')
	{
		newtree->data = *val;
		newtree->lchild = createTree();
		newtree->rchild = createTree();
		return newtree;
	}
	else if (*val == '#')
	{
		return NULL;
	}
}

int inTraversal(BiNode* target)
{
	if (target == NULL)
	{
		return OK;
	}

	inTraversal(target->lchild);
	cout << target->data;
	inTraversal(target->rchild);
}

int main()
{
	BiNode* tree = createTree();
	inTraversal(tree);
	return OK;
}

