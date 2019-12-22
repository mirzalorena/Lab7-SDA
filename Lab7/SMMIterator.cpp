#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap &smm):smm(smm)
{
	this->currentNode = smm.root;

	//theta(1)
}

bool SMMIterator::valid()
{
	if (currentNode == NULL)
		return false;
	return true;

	//theta(1)
}

void SMMIterator::first()
{
	this->currentNode = this->smm.root;

	//theta(1)
}

void SMMIterator::next()
{
	this->currentNode = this->succesor(this->currentNode);

	//O(n^2)

}

BSTNode * SMMIterator::parent(BSTNode * node)
{
	BSTNode* current = this->smm.root;
	if (current == node)
		return NULL;
	else
	{
		while (current != NULL && current->left != node && current->right != node)
		{
			if (!this->smm.relation(current->data.first, node->data.first))
				current = current->left;
			else
				current = current->right;
		}
		return current;
	}

	//O(n)
}

BSTNode * SMMIterator::succesor(BSTNode * node)
{
	BSTNode* current;
	if (node->right != NULL)
	{
		current = node->right;
		while (current->left != NULL)
			current = current->left;
		return current;
	}
	else
	{
		current = node;
		BSTNode* par = this->parent(current);
		while (par != NULL && par->left != current)
		{
			current = par;
			par = this->parent(par);
		}
		return par;
	}

	//O(n^2)
}

TElem SMMIterator::getCurrent()
{
	return currentNode->data;

	//theta(1)
}
