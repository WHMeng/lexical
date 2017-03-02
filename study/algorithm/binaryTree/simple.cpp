
struct Node{
	Node() : lchild(NULL), rchild(NULL) {}
	char val;
	Node *lchild;
	Node *rchild;
};

// pre   = DBACEGF
// mid   = ABCDEFG
// after = ACBFGED

// 由先序和中序建立二叉树
void pre_mid(Node *&node, int len, char *pre, char *mid){
	if(len <= 0) return;
	node = new Node;
	node->val = *pre;
	char *pmid = strchr(mid, *pre);
	int l_len = pmid - mid;
	int r_len = len - l_len - 1;
	pre_mid(node->lchild, l_len, pre+1, mid);
	pre_mid(node->rchild, r_len, pre+l_len+1, pmid+1);
}

// 由中序和后序建立二叉树
void mid_after(Node *&node, int len, char *mid, char *after){
	if(len <= 0) return;
	node = new Node;
	node->val = *(after+len-1);
	char *pmid = strchr(mid, node->val);
	int l_len = pmid - mid;
	int r_len = len - l_len - 1;
	mid_after(node->lchild, l_len, mid, after);
	mid_after(node->rchild, r_len, pmid+1, after+l_len);
}

// 先序遍历(非递归)
void preorder(Node *root){
	if(root == NULL) return;
	stack<Node *> nodes;
	nodes.push(root);
	while(!nodes.empty()){
		Node *cur = nodes.top();
		nodes.pop();
		print(cur);
		if(cur->rchild)
			nodes.push(cur->rchild);
		if(cur->lchild)
			nodes.push(cur->lchild);
	}
}

// 中序遍历(非递归)
void midorder(Node *root){
	if(root == NULL) return;
	stack<Node *> nodes;
	Node *cur = note;
	while(cur || !nodes.empty()){
		while(cur){
			nodes.push(cur);
			cur = cur->lchild;
		}
		if(!nodes.empty()){
			cur = nodes.top();
			nodes.pop();
			print(cur);
			cur = cur->rchild;
		}
	}
}

// 后序遍历(非递归)
struct Point{
	Point() : node(NULL), flag(false) {}
	Point(Node *nd, bool f)
		: node(nd)
		, flag(f)
	{}
	Node *node;
	bool flag;
};

void afterorder(Node *root){
	if(root == NULL) return;
	stack<Point> nodes;
	nodes.push(Point(node, false));
	while(!nodes.empty()){
		Point &cur = nodes.top();
		if(cur.flag){
			print(cur);
			nodes.pop();
			continue;
		}
		if(cur.node->rchild)
			nodes.push(Point(cur.node->rchild, false));
		if(cur.node->lchild)
			nodes.push(Point(cur.node->lchild, false));
		cur.flag = true;
	}
}

// 二叉树最近公共祖先(假设给出的两个结点值存在于二叉树中)
Node *firstCommonNode(Node *root, char x, char y){
	if(root == NULL)
		return NULL;
	if(root->val == x || root->val == y)
		return root;
	Node *left = firstCommonNode(root->lchild, x, y);
	Node *right = firstCommonNode(root->rchild, x, y);
	if(left && right)
		return root;
	return left ? left : right;
}

// 二叉树的深度
int  getDepth(Node *root){
	if(root == NULL)
		return 0;
	int leftDepth = getDepth(root->lchild);
	int rightDepth = getDepth(root->rchild);
	return ((leftDepth > rightDepth ? leftDepth : rightDepth) + 1);
}

// 判断一颗二叉树是否是平衡二叉树(每个结点的左右子树的深度相差都不超过1))
bool isBalanced(Node *root){ // 低性能
	if(root == NULL)
		return true;
	int leftDepth = getDepth(root->lchild);
	int rightDepth = getDepth(root->rchild);
	int diff = leftDepth - rightDepth;
	if(diff > 1 || diff < -1)
		return false;
	return isBalanced(root->lchild) && isBalanced(root->rchild);
}

// ---------------------------------------  较好性能
bool isBalanced(Node *root, int &depth){
	if(root == NULL){
		depth = 0;
		return true;
	}
	int leftDepth, rightDepth;
	if(isBalanced(root->lchild, leftDepth)
			&& isBalanced(root->rchild, rightDepth)){
		int diff = leftDepth - rightDepth;
		if(diff <= 1 && diff >= -1){
			depth = (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
			return true;
		}
	}
	return false;
}

bool isBalanced(Node *root){
	int depth = 0;
	return isBalanced(root, depth);
}
