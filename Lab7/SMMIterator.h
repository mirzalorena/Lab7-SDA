#pragma once
#include "SortedMultiMap.h"

#include <stack>
#include <iostream>
using namespace std;


class SMMIterator
{

	friend class SortedMultiMap;
private:

	const SortedMultiMap& smm;
	//std::stack<BSTNode *> myStack;
	BSTNode* currentNode;

public:
	SMMIterator(const SortedMultiMap& smm);

	bool valid();

	void first();

	void next();
	BSTNode* parent(BSTNode* node);
	BSTNode* succesor(BSTNode* node);

	TElem getCurrent();



};