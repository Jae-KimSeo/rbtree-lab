#include "rbtree.h"

staitc void create_nilnode(rbtree *r)
{
    r->nil  = (node_t*)malloc(sizeof(node_t));
    (r->nil)->color = RBTREE_BLACK;
    (r->nil)->key = '\0';
	(r->nil)->parent = NULL;
	(r->nil)->left = NULL;
	(r->nil)->right = NULL;

	r->root = r->nil;
}
static void left_rotate(rbtree *r, node_t *x)
{
    node_t *temp;

    temp = x->right;
    x->right = temp->left;
    if (temp->left != r->nil)
	{
        (temp->left)->parent = x;
	}
	temp->parent = x->parent; // link x's parent to temp
    if (x->parent == r->nil)  
	  r->root = temp;
    else if(x == (x->parent)->left)
        (x->parent)->left = temp;
    else
        (x->parent)->right = temp;
    temp->left = x; // put x on temp's left
    x->parent = temp;
}
static void right_rotate(rbtree *r, node_t *y)
{
    node_t *temp;

    temp = y->left;
    y->left = temp->right;
    if (temp->right != r->nil)
        (temp->right)->parent = y;
    temp->parent = y->parent; // link y's parent to temp
    if (y->parent == r->nil)
        r->root    = temp;
    else if( y == (y->parent)->left)
        (y->parent)->left    = temp;
    else
        (y->parent)->right   = temp;
    temp->right = y; // put y on temp's right
    y->parent        = temp;
}

void tree_transplant(rbtree *r, node_t *t, node_t *c)
{
    if( t->parent == r->nil)
        r->root    = c;
    else if( t == (t->parent)->left)
        (t->parent)->left    = c;
    else
        (t->parent)->right   = c;
    c->parent    = t->parent; // link target's parent to child's parent.
}
static void insert_fixup(rbtree *r, node_t *x)
{
    node_t *u = NULL;
	
    while (x->parent->color == RBTREE_RED)
    {
        if (x->parent->parent == r->nil)
		  break;
		if (x->parent == (x->parent->parent)->left)
        {
            u = (x->parent->parent)->right;
            if (u->color == RBTREE_RED)
            {
                (x->parent)->color = RBTREE_BLACK;
                u->color      = RBTREE_BLACK;
                (x->parent->parent)->color  = RBTREE_RED;
                x = (x->parent->parent);
            }
            else
            {
                if(x == (x->parent)->right)
                {
                    x = (x->parent);
                    left_rotate( r, x);
                }
                (x->parent)->color = RBTREE_BLACK;
                (x->parent->parent)->color = RBTREE_RED;
                right_rotate(r, (x->parent->parent));
				if (x->parent->parent == r->nil)
				  break;
			}
        }
        else
        {
            u = (x->parent->parent)->left;
            if( u->color == RBTREE_RED)
            {
                (x->parent)->color = RBTREE_BLACK;
                u->color = RBTREE_BLACK;
                (x->parent->parent)->color = RBTREE_RED;
                x = (x->parent->parent);
			}
            else
            {
                if(x == (x->parent)->left)
                {
                    x = (x->parent);
                    right_rotate( r, x);
					if (x->parent->parent == r->nil)
					  break;
                }
			}
		}
	}
}
void insert_node(rbtree *r, key_t key)
{
  // r = T, n = z, y = 
    node_t *n; // 추가하는 노드 z
	node_t *temp; // 탐색을 위한 임시 노드
	node_t *p; // 새로운 노드의 부모 노드 

	n = (node_t *)malloc(sizeof(node_t));
	if (n == NULL)
	  return ;
    n->left = r->nil;
    n->right = r->nil;
    n->color = RBTREE_RED;
    n->key = key;
	temp = r->root;
	p = r->nil; 
    int level_cnt = 0;
	while (temp != r->nil) // temp 가 리프노드에 도달할때까지
    {
        p = temp;
        if (key > temp->key)
            temp = temp->right;
        else
            temp = temp->left;
		level_cnt++;
	}
    n->parent = p; // link new node to p
    if (p == r->nil) // 여기서 루트노드도 추가가 가능한데,, 
        r->root = n;
    else if (key > p->key) // 일단 new_node = n, p는 new_node가 붙는 parent
        p->right = n;
    else
        p->left = n;
	insert_fixup(r, n);
}
