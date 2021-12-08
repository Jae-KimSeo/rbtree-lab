#include "./traversal.h"
#include "unistd.h"

void Preorder_Traversal(t_data *pNode)
{
  if (!pNode)
    return;
  printf(" %d ", pNode->key);
  Preorder_Traversal(pNode->left);
  Preorder_Traversal(pNode->right);
}

void Inorder_Traversal(t_data *pNode, rbtree *tree)
{
  if (pNode == tree->nil)
	return;
  if (pNode->left != tree->nil)
	Inorder_Traversal(pNode->left, tree);
  printf(" %d ", pNode->key);
  if (pNode->right != tree->nil)
	Inorder_Traversal(pNode->right, tree);
}

void Postorder_Traversal(t_data *pNode)
{
  if (!pNode)
    return;
  Postorder_Traversal(pNode->left);
  Postorder_Traversal(pNode->right);
  printf(" %d ", pNode->key);
}

void Level_Traversal(t_data *pNode, rbtree *tree)
{
  ArrayQueue *queue;
  t_data  key;

  if (pNode == tree->nil)
    return; 
  queue = createArrayQueue(100);
  enqueue(queue, *pNode);
  while (is_empty(queue) == FALSE)
  {
    key = dequeue(queue);
	pNode = &key;
	if (pNode == tree->nil)
	  continue;
	// nil출력 생략
//printf(" %d ", pNode->key);
	write(1, &pNode->key, sizeof(pNode->key));	
	//if (pNode == tree->nil)
//	  continue ;
	if (pNode->left != tree->nil)
	  enqueue(queue, *(pNode->left));
	if (pNode->right != tree->nil)
	  enqueue(queue, *(pNode->right));
  }
  delete_queue(queue);
}
