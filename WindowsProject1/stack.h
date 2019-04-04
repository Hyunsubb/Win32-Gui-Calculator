#pragma once

typedef TCHAR SData;

typedef struct _node {
	SData Data;
	_node* Next;
}Node;

class StackList {
private:
	Node * List;
public:
	StackList();
	bool SIsEmpty();
	void SPush(SData);
	SData SPop();
	SData SPeek();
};

typedef StackList Stack;