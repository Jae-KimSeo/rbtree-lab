#ifndef  TRAVERSAL_H
# define TRAVERSAL_H

#include "./circular_queue.h"

void Preorder_Traversal(t_data *pNode);
void Inorder_Traversal(t_data *pNode, rbtree *tree);
void Postorder_Traversal(t_data *pNode);
void Level_Traversal(t_data *pNode, rbtree *tree);
#endif
