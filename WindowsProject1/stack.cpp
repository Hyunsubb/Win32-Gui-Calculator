#include<stdio.h>
#include<windows.h>
#include"stack.h"

StackList::StackList() {
	List = NULL;
}

bool StackList::SIsEmpty() {
	if (!List) {
		return true;
	}
	return false;
}

void StackList::SPush(SData Data) {
	Node* NewNode = (Node*)malloc(sizeof(Node));
	NewNode->Data = Data;
	NewNode->Next = List;
	List = NewNode;
}

SData StackList::SPop() {
	if (SIsEmpty()) {
		puts("Stack is Empty!!!");
		exit(-1);
	}
	Node* rpos = List;
	SData BData = rpos->Data;
	List = List->Next;
	return BData;
}

SData StackList::SPeek() {
	return List->Data;
}