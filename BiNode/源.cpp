#include <iostream>
using namespace std;
#define OK 0
#define ERROR -1

struct BiNode
{
	char data;
	BiNode* lchild, * rchild;
	bool ltag, rtag;//Ϊ0ʱ��ָ��������Ϊ1ʱ��ָ��ǰ��/���
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

int inTraversal(BiNode* target)//�������
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
BiNode* inClueingold(BiNode* target,BiNode* prev)//������������Ϊ��ǰ�ڵ�����ǰ�������ص�ǰ�����
{
	if (target == NULL)
	{
		return;
	}
	if (prev == target)//���Ŀ������ĺ������������Լ�һ�£�˵�����֧�Ѿ������꣬�߻�ͷ·��
	{
	if (target->rtag == 0)//������������ڣ��ͱ���������
	{
		return inClueing(target->rchild, target);
	}
	else if (target->rtag == 1)//��������������ڣ��ýڵ��Ǹ���Ҷ
	{
		return prev;
	}
	}


	if (target->ltag == 1)//���������������
	{
		target->lchild = prev;//����ǰ��Ϊǰһ��
		if (target->rtag == 1)//��������������
		{
			target->rchild = inClueing(target, target);//�����Լ������ýڵ�
			return target->rchild;
		}
		else if (target->rtag == 0)//�������������
		{
			return inClueing(target, target);//�������Լ��Ҳ����ú��
		}

	}
	else if (target->ltag == 0)//�������������
	{
		if (target->rtag == 1)//��������������
		{
			target->rchild = inClueing(target->lchild, target);//�Ǿͼ��������������������������������Ϊ���
			return target->rchild;
		}
		else if (target->rtag == 0)//��������Ҳ����
		{
			inClueing(target->lchild, target);//��ô�����������������ǲ����ú��
			inClueing(target, target);//Ȼ������Լ�
			inClueing(target->rchild, target);
		}
	}


}
 */


void inClueing(BiNode* target,BiNode*& prev)//��ǰD�����ڵ������������һƬ��Ҷ��һֱ�޷���������ԭ������Ϊprevδ��������ʽ���ݣ����º����ݹ��޷�ʹprevָ��ǰ���������ݹ��˳���prev�ᱻ��ԭ��
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

BiNode* seekNode(BiNode* tree, char val)//���������������Ŀ��ڵ�������̣������ĳɷ���Ŀ��ڵ㱾���������Ҳ�����ˡ�����
{
	BiNode* p = tree;

	while (p->ltag != 1)//���ƶ������������
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

	
	inClueing(tree,prev);//����������

	char target;
	cin >> target;
	//BiNode* p = seekNode(tree, target);
	prev = NULL;
	preTraversal(tree, prev, target);
	cout << "^";

	//if (p!=NULL)//����������β��
	//{
	//	cout << p->data;
	//}
	//else
	//{
	//	cout << "^";
	//}

	return OK;
}

