
// 复杂链表的复制
//
//        +-----------+
//        |           |
//        v           |
//  A --> B --> C --> D --> E
//  |     |     ^           ^
//  |     |     |           |
//  +-----+-----+           |
//        |                 |
//        +-----------------+
//
struct Node {
	Node() : next(NULL), sibling(NULL) {}
	int val;
	Node *next;
	Node *sibling;
};

void cloneNodes(Node *head){
	Node *node = head;
	while(node){
		Node *clone = new Node;
		clone->val = node->val;
		clone->next = node->next;
		node->next = clone;
		node = clone->next;
	}
}

void connectSiblingNodes(Node *head){
	Node *node = head;
	while(node){
		Node *clone = node->next;
		if(node->sibling){
			clone->sibling = node->sibling->next;
		}
		node = clone->next;
	}
}

Node *reconnectNodes(Node *head){
	Node *node = head;
	Node *cloneHead = NULL;
	Node *cloneNode = NULL;
	if(node != NULL){
		cloneHead = cloneNode = node->next;
		node->next = cloneNode->next;
		node = node->next;
	}
	while(node){
		cloneNode->next = node->next;
		cloneNode = cloneNode->next;
		node->next = cloneNode->next;
		node = node->next;
	}
	return cloneHead;
}
