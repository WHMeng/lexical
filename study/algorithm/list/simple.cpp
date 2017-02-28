
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
//

// 有序(假设升序)插入
void increaseInsert(Node **link, const Type &val){
	Node *cur;
	while((cur = *link) != NULL && cur->val < val)
		link = &cur->next;
	Node *new_node = new Node;
	new_node->val = val;
	new_node->next = cur;
	*link = new_node;
}

// 删除链表中的第一个 val
void deleteFirstVal(Node **link, const Type &val){
	Node *cur;
	while((cur = *link) != NULL && cur->val != val)
		link = &cur->next;
	if(cur){
		*link = cur->next;
		delete cur;
	}
}

// 反转链表
void reverseList(Node *head){
	if(head == NULL || head->next == NULL) return;
	Node *cur = head->next;
	Node *per = head;
	while(cur){
		per->next = cur->next;
		cur->next = head;
		head = cur;
		cur = per->next;
	}
}

// 合并有序链表(假设升序) 递归
Node *mergeList(Node *head1, Node *head2){
	if(head1 == NULL) return head2;
	if(head2 == NULL) return head1;
	Node *new_head = NULL;
	if(head1->val < head2->val){
		new_head = head1;
		new_head->next = mergeList(head1->next, head2);
	}else{
		new_head = head2;
		new_head->next = mergeList(head1, head2->next);
	}
	return new_head;
}

// 合并有序链表(假设升序) 非递归
Node *mergeList(Node *head1, Node *head2){
	if(head1 == NULL) return head2;
	if(head2 == NULL) return head1;
	Node *new_head = NULL;
	Node **link = &new_head;

	while(head1 && head2){
		if(head1->val < head2->val){
			*link = head1;
			link = &head1->next;
			head1 = head1->next;
		}else{
			*link = head2;
			link = &head2->next;
			head2 = head2->next;
		}
	}
	*link = (head1 != NULL ? head1 : head2);
}


