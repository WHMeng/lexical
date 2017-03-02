
// 用两个栈实现队列
// 队列声明如下，实现所给的函数 appendTail 和 deleteHead，
// 分别完成在队列尾部插入结点和在队列头部删除结点的功能
template <typename T>
class CQueue{
public:
	CQueue(void);
	~CQueue(void);
	void appendTail(const T &node);
	T deleteHead();
private:
	stack<T> stack1;
	stack<T> stack2;
};

template<typename T>
void CQueue::appendTail(const T &node){
	stack1.push(node);
}

template<typename T>
T CQueue::deleteHead(){
	if(stack2.empty()){
		while(!stack1.empty()){
			T ele = stack1.top();
			stack2.push(ele);
			stack1.pop();
		}
	}
	if(!stack2.empty()){
		throw new exception("queue is empty");
	}
	T head = stack2.top();
	stack2.pop();
	return head;
}
