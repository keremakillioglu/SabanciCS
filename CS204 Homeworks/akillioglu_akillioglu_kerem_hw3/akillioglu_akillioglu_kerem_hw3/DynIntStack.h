struct StackNode
{
	int xvalue;
	int yvalue;
	StackNode *next;
};

class DynIntStack
{
private:
	

public:
	StackNode *top;
	DynIntStack(void);
	void push(int, int);
	void pop(int, int);
	bool isEmpty(void);

	StackNode *getnode(int, int);
};
