#include "SortedMultiMap.h"
#include "SMMIterator.h"

SortedMultiMap::SortedMultiMap(Relation r)
{
	this->relation = r;
	this->root = NULL;
	this->sizeSMM = 0;
}

SortedMultiMap::SortedMultiMap(const SortedMultiMap &smm)
{
	this->relation = smm.relation;
	this->root = smm.root;
	this->sizeSMM = smm.sizeSMM;
}

BSTNode* SortedMultiMap::initNode(TKey c, TValue v)
{
	BSTNode *newNode = new BSTNode{};
	newNode->data.first = c;
	//newNode->data.second = v;
	newNode->values.add(v);
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;

	//theta(1)
}

BSTNode* SortedMultiMap::insert(BSTNode *node, TKey c, TValue v)
{
	if (node == NULL)
		node = this->initNode(c, v);
	else if (node->data.first == c)
	{
		//BSTNode* aux = node;
		node->values.add(v);
	}
	else if (this->relation(node->data.first, c))
		node->right = this->insert(node->right, c, v);
	else
		node->left = this->insert(node->left, c, v);

	return node;

	//O(n)
}

void SortedMultiMap::add(TKey c, TValue v)
{
	if (this->root == NULL)
		this->root = this->insert(this->root, c, v);
	else
		this->insert(this->root, c, v);
	this->sizeSMM++;

	//O(n)
}


vector<TValue> SortedMultiMap::search(TKey c)
{
	BSTNode *currentNode;
	currentNode = this->root;
	vector<TValue> values;
	bool found = false;
	while (currentNode != NULL && !found)
	{
		if (currentNode->data.first == c)
		{
			found = true;
			int i = 0;
			while (i<currentNode->values.getSize())
			{
				values.push_back(currentNode->values.get(i));
				i++;
			}
			//values.push_back(currentNode->data.second);
		}
		else if (this->relation(currentNode->data.first, c))
			currentNode = currentNode->right;
		else
			currentNode = currentNode->left;
	}
	return values;

	//O(n)
}

BSTNode* SortedMultiMap::minimum(BSTNode* node)
{
	BSTNode *currentNode = node;
	if (currentNode == NULL)
		return NULL;
	else
	{
		while (currentNode->left != NULL)
			currentNode = currentNode->left;
		return currentNode;
	}

	//O(n)
}

int SortedMultiMap::size() const
{
	return this->sizeSMM;

	//theta(1)
}

bool SortedMultiMap::isEmpty() const
{
	return (this->sizeSMM == 0);

	//theta(1)
}

SMMIterator SortedMultiMap::iterator() const
{
	return SMMIterator(*this);

	//theta(1)
}

int SortedMultiMap::getValueRange() const
{
	if (this->isEmpty())
		return -1;

	int diff = 0;
	int max = 0;
	int min = 1000;

	BSTNode *currentNode;
	currentNode = this->root;

	while (currentNode != NULL)
	{
		int i = 0;
		while (i<currentNode->values.getSize())
		{
			if (currentNode->values.get(i) > max)
				max = currentNode->values.get(i);
			else if (currentNode->values.get(i) < min)
				min = currentNode->values.get(i);
			i++;
		}

		currentNode = currentNode->right;
	}
	
	return max - min;

}

SortedMultiMap::~SortedMultiMap()
{
	delete[] this->root;
	
	//theta(1)
}

BSTNode* SortedMultiMap::_remove(BSTNode* node, TKey c, int pos)
{
	if (node == NULL)
		return NULL;
	else if (node->data.first == c)
	{
		if (node->left == NULL && node->right == NULL)
		{
			if (node->values.getSize() == 1)
			{
				node = NULL;
				return NULL;
			}
			else if(node->values.getSize()!=0 && node->values.getSize()>1)
			{
				node->values.remove(pos);
				return node;
			}
		}
		else if (node->left == NULL)
		{
			//node = node->right;
			//return node;
			if (node->values.getSize() == 1)
			{
				node = node->right;
				return node;
			}
			else if (node->values.getSize() != 0 && node->values.getSize() > 1)
			{
				node->values.remove(pos);
				return node;
			}
		}
		else if (node->right == NULL)
		{
			//node = node->left;
			//return node;
			if (node->values.getSize() == 1)
			{
				node = node->left;
				return node;
			}
			else if (node->values.getSize() != 0 && node->values.getSize() > 1)
			{
				node->values.remove(pos);
				return node;
			}
		}
		else
		{
			BSTNode* min = this->minimum(node->right);
			node->data = min->data;
			node->right = this->_remove(node->right, min->data.first, min->data.second);
			return node;
		}
	}
	else if (this->relation(node->data.first, c))
	{
		node->right = this->_remove(node->right, c, pos);
		return node;
	}
	else
	{
		node->left = this->_remove(node->left, c, pos);
		return node;
	}

	//O(n)
}

bool SortedMultiMap::remove(TKey c, TValue v)
{
	int isThere = 0;
	vector<TValue> values = this->search(c);
	int pos = 0;
	for(int i=0;i<values.size();i++)
		if (values[i] == v)
		{
			isThere = 1;
			pos = i;
		}
	if (isThere == 1)
	{
		if (this->root != NULL && this->root->data.first == c) {
			this->root = this->_remove(this->root, c, pos);
		}
		else
			this->_remove(this->root, c, pos);
		if (isThere == 1)
		{
			this->sizeSMM--;
			return true;
		}
		else
			return false;
	}
	return false;
	
	//O(n+m)
}