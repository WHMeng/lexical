
struct Node{
	Node() : lchild(NULL), rchild(NULL) {}
	char val;
	Node *lchild;
	Node *rchild;
};

// 二叉搜索数与双向链表的转换
Node *transform(Node *root){
	Node *lastNode = NULL;
	transformNodes(root, lastNode);
	Node *listHead = lastNode;
	while(listHead && listHead->lchild)
		listHead = listHead->lchild;
	return listHead;
}

void transformNodes(Node *root, Node *&lastNode){
	if(root == NULL)
		return;
	Node *cur = root;
	if(cur->lchild)
		transformNodes(cur->lchild, lastNode);
	cur->lchild = lastNode;
	if(lastNode)
		lastNode->rchild = cur;
	lastNode = cur;
	if(cur->rchild)
		transformNodes(cur->rchild, lastNode);
}
