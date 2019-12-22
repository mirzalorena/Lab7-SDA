#pragma once
#include "DynamicVector.h"
#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <assert.h>

typedef int TKey;

typedef int TValue;

typedef std::pair<TKey, TValue> TElem;

using namespace std;

typedef bool(*Relation)(TKey, TKey);

class SMMIterator;

struct BSTNode {
	TElem data;
	BSTNode *left;
	BSTNode *right;

	DynamicVector<TValue> values;
};

class SortedMultiMap {

	friend class SMMIterator;

private:

	BSTNode* root;
	int sizeSMM;
	Relation relation;

public:
	SortedMultiMap(Relation r);
	SortedMultiMap(const SortedMultiMap& smm);

	BSTNode* initNode(TKey c, TValue v);

	void add(TKey c, TValue v);
	BSTNode* insert(BSTNode *node, TKey key, TValue v);

	vector<TValue> search(TKey c);

	bool remove(TKey c, TValue v);
	BSTNode* _remove(BSTNode* node, TKey c,int pos);
	BSTNode* minimum(BSTNode* node);

	int size() const;

	bool isEmpty() const;

	SMMIterator iterator() const;

	int getValueRange() const;

	~SortedMultiMap();

};
