#include <iostream>
using namespace std;
#define OK 0
#define ERROR -1

struct BiNode
{
	char data;
	BiNode* lchild, * rchild;
	bool ltag, rtag;//为0时，指向子树，为1时，指向前驱/后继
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
		if (newtree->lchild == NULL)
		{
			newtree->ltag = 1;
		}
		else if(newtree->lchild != NULL)
		{
			newtree->ltag = 0;
		}

		newtree->rchild = createTree();
		if (newtree->rchild == NULL)
		{
			newtree->rtag = 1;
		}
		else if (newtree->rchild != NULL)
		{
			newtree->rtag = 0;
		}

		return newtree;
	}
	else if (*val == '#')
	{
		return NULL;
	}
}

int inTraversal(BiNode* target)//中序遍历
{
	if (target == NULL)
	{
		return OK;
	}

	inTraversal(target->lchild);
	cout << target->data;
	inTraversal(target->rchild);
}

/*
BiNode* inClueingold(BiNode* target,BiNode* prev)//中序线索化，为当前节点设置前驱，返回当前结点后继
{
	if (target == NULL)
	{
		return;
	}
	if (prev == target)//如果目标遍历的和左子树或者自己一致，说明左分支已经遍历完，走回头路了
	{
	if (target->rtag == 0)//如果右子树存在，就遍历右子树
	{
		return inClueing(target->rchild, target);
	}
	else if (target->rtag == 1)//如果右子树不存在，该节点是个树叶
	{
		return prev;
	}
	}


	if (target->ltag == 1)//如果左子树不存在
	{
		target->lchild = prev;//设置前驱为前一项
		if (target->rtag == 1)//且右子树不存在
		{
			target->rchild = inClueing(target, target);//遍历自己并设置节点
			return target->rchild;
		}
		else if (target->rtag == 0)//如果右子树存在
		{
			return inClueing(target, target);//仅遍历自己且不设置后继
		}

	}
	else if (target->ltag == 0)//如果左子树存在
	{
		if (target->rtag == 1)//且右子树不存在
		{
			target->rchild = inClueing(target->lchild, target);//那就继续中序遍历他的左子树，并将其设置为后继
			return target->rchild;
		}
		else if (target->rtag == 0)//且右子树也存在
		{
			inClueing(target->lchild, target);//那么仅遍历左子树，但是不设置后继
			inClueing(target, target);//然后遍历自己
			inClueing(target->rchild, target);
		}
	}


}
 */


void inClueing(BiNode* target,BiNode*& prev)//先前D（根节点左子树的最后一片树叶）一直无法线索化，原因是因为prev未以引用形式传递，导致后续递归无法使prev指针前进（后续递归退出后prev会被复原）
{

	if (target == NULL)
	{
		return;
	}

	inClueing(target->lchild,prev);

	if (target->lchild== NULL)
	{
		target->ltag = 1;
		target->lchild = prev;
	}

	if (prev != NULL)
	{
		if (prev->rchild == NULL)
		{
			prev->rtag = 1;
			prev->rchild = target;
		}
	}
	prev = target;

	inClueing(target->rchild,prev);
}

BiNode* seekNode(BiNode* tree, char val)//这个函数本来返回目标节点的中序后继，后来改成返回目标节点本身。这个函数也废弃了。。。
{
	BiNode* p = tree;

	while (p->ltag != 1)//先移动到线索化起点
	{
		p = p->lchild;
	}
	BiNode* prev = p;
	p = p->rchild;
	while (p != NULL)
	{
		
		if (prev->data == val)
		{
			return prev;
		}
			
		else
		{
			prev = p;
			p = p->rchild;
		}
	}

	return prev;

}

void preTraversal(BiNode* tree, BiNode*& pre,char val)
{
	if (tree == NULL)
	{
		return;
	}

	if (pre != NULL)
	{
		if (pre->data == val)
		{
			cout << tree->data;
			exit(0);
		}
	}
	

	if (tree->ltag == 0 && tree->rtag == 0)
	{
		pre = tree;
		preTraversal(tree->lchild, pre, val);
		preTraversal(tree->rchild, pre, val);
	}
	else if (tree->ltag == 1 && tree->rtag == 0)
	{
		pre = tree;
		preTraversal(tree->rchild, pre, val);
	}
	else if (tree->ltag == 0 && tree->rtag == 1)
	{
		pre = tree;
		preTraversal(tree->lchild, pre, val);
	}
	else
	{
		pre = tree;
		return;
	}
}

int main()
{
	BiNode* tree = createTree();
	BiNode* prev = tree;
	//inTraversal(tree);

	
	inClueing(tree,prev);//中序线索化

	char target;
	cin >> target;
	//BiNode* p = seekNode(tree, target);
	prev = NULL;
	preTraversal(tree, prev, target);
	cout << "^";

	//if (p!=NULL)//线索树到结尾后
	//{
	//	cout << p->data;
	//}
	//else
	//{
	//	cout << "^";
	//}

	return OK;
}

