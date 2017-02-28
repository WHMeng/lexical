
typedef int Type

struct Node {
	Node() : next(NULL) {}
	Type val;
	Node *next;
};

//     +------+   +------+   +------+   +------+   +------+
//     |  #---+-->|  #---+-->|  #---+-->|  #---+-->|  #---+-->null
// #-->|      |   |      |   |      |   |      |   |      |
//     |  @   |   |  @   |   |  @   |   |  @   |   |  @   |
//     +------+   +------+   +------+   +------+   +------+


// 从尾到头打印链表的值(不允许修改链表结构) 非递归
void reversePrint(Node *head){
	stack<Node *> nodes;
	Node *cur = head;
	while(cur){
		nodes.push(cur);
		cur = cur->next;
	}
	while(!nodes.empty()){
		Node *tmp = nodes.top();
		printNode(tmp);
		nodes.pop();
	}
}

// 从尾到头打印链表的值(不允许修改链表结构) 递归
void reversePrint(Node *head){
	if(head == NULL) return;
	reversePrint(head->next);
	printNode(head);
}

// 给定一个节点指针(并假设其存在于链表内)和指向链表头结点指针的指针，在 O(1) 时间复杂度内删除给定结点

void deleteNode(Node **link, Node *dNode){
	Node *head = *link;
	if(head == NULL || dNode == NULL) return;
	else if(head == dNode){
		delete head;
		head = NULL
	}else if(dNode->next){
		Node *nextNode = dNode->next;
		dNode->val = nextNode->val;
		dNode->next = nextNode->next;
		delete nextNode;
		nextNode = NULL;
	}else{
		Node *perNode = head;
		while(perNode->next != dNode)
			perNode = perNode->next;
		perNode->next = NULL;
		delete dNode;
		dNode = NULL;
	}
}

// 链表中倒数第 k 个结点
Node *findKthToTail(Node *head, int k){
	if(head == NULL || k == 0)
		return NULL;
	Node *ptrA = head;
	Node *ptrB = head;
	for(int i = 0; i < k; i++){
		if(ptrA){
			ptrA = ptrA->next;
		}else{
			return NULL;
		}
	}
	while(ptrA){
		ptrA = ptrA->next;
		ptrB = ptrB->next;
	}
	return ptrB;
}
