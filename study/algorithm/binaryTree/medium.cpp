
struct Node{
	Node() : lchild(NULL), rchild(NULL) {}
	int val;
	Node *lchild;
	Node *rchild;
};

// 完成一个函数，输入一个二叉树，该函数输出它的镜像
//
//       8                 8
//      / \               / \
//     /   \             /   \
//    6    10           10    6
//   / \   / \         /  \  / \
//  5  7  9  11       11  9  7  5
//      (1)                (2)
//  (2)为(1)的镜像
//

void mirrorBinaryTree(Node *root){ // 修改原结构
	if(root == NULL || (root->lchild == NULL && root->rchild == NULL))
		return;
	Node *tmp = root->lchild;
	root->lchild = root->rchild;
	root->rchild = tmp;
	if(root->lchild)
		mirrorBinaryTree(root->lchild);
	if(root->rchild)
		mirrorBinaryTree(root->rchild);
}

Node *mirrorBinaryTree(Node *root){ // 创建拷贝镜像
	if(root == NULL)
		return NULL;
	Node *mirror = new Node;
	mirror->val = root->val;
	mirror->lchild = mirrorBinaryTree(root->rchild);
	mirror->rchild = mirrorBinaryTree(root->lchild);
	return mirror;
}

// 二叉树层次遍历
void upToDownOrder(Nodt *root){
	if(root == NULL)
		return;
	queue<Node *> nodes;
	nodes.push(root);
	while(!nodes.empty()){
		Node *cur = nodes.front();
		nodes.pop();
		print(cur);
		if(cur->lchild)
			nodes.push(cur->lchild)
		if(cur->rchild)
			nodes.push(cur->rchild)
	}
}

// 输入一个整型数组，判断该数组是不是某二叉搜索数的后序遍历结果
// 假设输入的数组的任意两个数字都互不相同

bool judgeBST(int arr[], int len){
	if(arr == NULL || len <= 0)
		return false;
	int root = arr[len-1];
	int i = 0;
	for(; i < len-1; i++){
		if(arr[i] > root)
			break;
	}
	int j = i;
	for(; j < len-1; j++){
		if(arr[j] < root)
			return false;
	}
	bool left = true;
	if(i > 0)
		left = judgeBST(arr, i);
	bool right = true;
	if(i < len-1)
		right = judgeBST(arr+i, len-i-1);
	return (left && right);
}

// 二叉树中和为某一值的路径
// 输入一颗二叉树和一个整数，打印出二叉树中结点值的和为输入整数的所有路径
// 从数的根结点开始往下一直到叶结点所经过的结点形成一条路径
//
void findPath(Node *root, int expSum, vector<int> &path, int curSum){
	curSum += root->val;
	path.push_back(root->val);
	bool isLeaf = root->lchild == NULL && root->rchild == NULL;
	if(curSum == expSum){
		print(path);
	}
	if(root->lchild != NULL)
		findPath(root->lchild, expSum, path, curSum);
	if(root->rchild != NULL)
		findPath(root->rchild, expSum, path, curSum);
	path.pop_back();
}

void findPath(Node *root, int expSum){
	if(root == NULL)
		return;
	vector<int> path;
	int curSum = 0;
	findPath(root, expSum, path, curSum);
}
