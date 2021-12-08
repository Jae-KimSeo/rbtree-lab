#include "rbtree.h"
#include <stdlib.h>
#include <unistd.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  p->nil = (node_t *)calloc(1, sizeof(node_t));
  p->nil->color = RBTREE_BLACK;
  p->root = p->nil;
  // TODO: initialize struct if needed
  return p;
}

void tree_transplant(rbtree *r, node_t *t, node_t *c)
{
    if( t->parent == r->nil)
    {
        r->root    = c;
    }
    else if( t == (t->parent)->left)
    {
        (t->parent)->left    = c;
    }
    else
    {
        (t->parent)->right   = c;
    }
}

void rbtree_delete_node(rbtree *t, node_t *node)
{
  if (node == t->nil)
	return ;
  rbtree_delete_node(t, node->left);
  rbtree_delete_node(t, node->right);
  free(node);
  node = NULL;
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  rbtree_delete_node(t, t->root);
  free(t->nil);
  t->nil = NULL;
  free(t);
  t = NULL;
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
            // process property 4 of the red-black properties.
            if (u->color == RBTREE_RED)
            {
                (x->parent)->color = RBTREE_BLACK;
                u->color      = RBTREE_BLACK;
                (x->parent->parent)->color  = RBTREE_RED;
                x = (x->parent->parent);
            }
            // process property 5
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
            // process property 4 of the red-black properties.
            if( u->color == RBTREE_RED)
            {
                (x->parent)->color = RBTREE_BLACK;
                u->color = RBTREE_BLACK;
                (x->parent->parent)->color = RBTREE_RED;
                x = (x->parent->parent);
			}
            // process property 5
            else
            {
			
                if(x == (x->parent)->left)
                {
                    x = (x->parent);
                    right_rotate( r, x);
					if (x->parent->parent == r->nil)
					  break;
                }
				x->parent->color = RBTREE_BLACK;
				x->parent->parent->color = RBTREE_RED;
				left_rotate(r, x->parent->parent);
			}
		}
	}
}
/*
void insert_node( node_t **, int)
This function inserts a node that contains the key in the tree.
it follows the binary-search trees structure.
*/

node_t *insert_node(rbtree *r, key_t key)
{
    node_t *n; // 추가하는 노드 z
	node_t *temp; // 탐색을 위한 임시 노드
	node_t *p; // 새로운 노드의 부모 노드 

	n = (node_t *)malloc(sizeof(node_t));
	if (n == NULL)
	  return NULL;
	n->left = r->nil;
    n->right = r->nil;
    n->key = key;
	
	n->color = RBTREE_RED;
	temp = r->root;
	p = r->nil; 
	while (temp != r->nil) // temp 가 리프노드에 도달할때까지
    {
        p = temp;
        if (key > temp->key)
            temp = temp->right;
        else
            temp = temp->left;
	}
    n->parent = p; // link new node to p
    if (p == r->nil) // 여기서 루트노드도 추가가 가능한데,, 
        r->root = n;
    else if (key > p->key) // 일단 new_node = n, p는 new_node가 붙는 parent
        p->right = n;
    else{
        p->left = n;
	}
	insert_fixup(r, n);
	r->root->color = RBTREE_BLACK;

	return n;
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  node_t *n;
  n = insert_node(t, key);
  return n;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  node_t *ptr;

  if (t->root == NULL)
	return (NULL);
  if (t->root->key == key)
	return (t->root);

  ptr = t->root;
  while (ptr != t->nil)
  {
	if (ptr->key > key)
	  ptr = ptr->left;
	else if (ptr->key < key)
	  ptr = ptr->right;
	else 
	  return (ptr);
  }
  return (NULL);
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  node_t *node_min;
  
  if (t->root == t->nil){
	return NULL;
  }
  node_min = t->root;
  while (node_min->left != t->nil)
  {
	node_min = node_min->left;
  }
  return node_min;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  node_t *node_max;

  node_max = t->root;
  while (node_max->right != t->nil)
  {
	node_max = node_max->right;
  }
  return node_max;
}

static void delete_fixup(rbtree *r, node_t *x)
{
    node_t *s = NULL; // sibling node.

    while( (x != r->root) && ( x->color == RBTREE_BLACK))
    {
        if( x == (x->parent)->left)
        {
            s   = (x->parent)->right;
            // case 1 : x's sibling s is red
            if( s->color == RBTREE_RED)
            {
                s->color      = RBTREE_BLACK;
                (x->parent)->color = RBTREE_RED;
                left_rotate( r, x->parent);
                // update x's sibling
                s   = (x->parent)->right;
            }

            // case 2 : x's sibling s is black, and both of s's children are black.
            if( (s->left)->color == RBTREE_BLACK && (s->right)->color == RBTREE_BLACK)
            {
                s->color  = RBTREE_RED;
                x       = x->parent;
            }
            // case 3 : x's sibling s is black, s's left child is red, another is black.
            else if( (s->left)->color == RBTREE_RED && (s->right)->color == RBTREE_BLACK)
            {
                s->color          = RBTREE_RED;
                (s->left)->color  = RBTREE_BLACK;
                right_rotate( r, s);
                // update x's sibling
                s   = (x->parent)->right;
            }
           
            // case 4 : x's sibling s is black, s's right child is red.
            if( (s->right)->color == RBTREE_RED)
            {
                s->color          = (x->parent)->color;
                (s->right)->color = RBTREE_BLACK;
                (x->parent)->color     = RBTREE_BLACK;
                left_rotate( r, x->parent);
                x   = r->root;
            }
        }
        else
        {
            s   = (x->parent)->left;
            // case 1 : x's sibling s is red
            if( s->color == RBTREE_RED)
            {
                s->color      = RBTREE_BLACK;
                (x->parent)->color = RBTREE_RED;
                right_rotate( r, x->parent);
                // update x's sibling
                s   = (x->parent)->left;
            }

            // case 2 : x's sibling s is black, and both of s's children are black.
            if( (s->left)->color == RBTREE_BLACK && (s->right)->color == RBTREE_BLACK)
            {
                s->color  = RBTREE_RED;
                x       = x->parent;
            }
            // case 3 : x's sibling s is black, s's right child is red, another is black.
            else if( (s->right)->color == RBTREE_RED && (s->left)->color == RBTREE_BLACK)
            {
                s->color          = RBTREE_RED;
                (s->right)->color = RBTREE_BLACK;
                left_rotate( r, s);
                // update x's sibling
                s   = (x->parent)->left;
            }
           
            // case 4 : x's sibling s is black, s's left child is red.
            if( (s->left)->color == RBTREE_RED)
            {
                s->color          = (x->parent)->color;
                (s->left)->color  = RBTREE_BLACK;
                (x->parent)->color     = RBTREE_BLACK;
                right_rotate(r, x->parent);
                x   = r->root;
            }
        }
    }
    x->color  = RBTREE_BLACK;
}

void delete_node(rbtree *r, int key)
{
    node_t *target    = r->root; // the node that we want to remove.
    node_t *temp      = NULL; // the node that is moved or removed.
    node_t *x         = NULL; // temp's original position
    char t_color;
    // find the node that has the key
    while(key != target->key)
    {
        if( target->key > key)
            target  = target->left;
        else
            target  = target->right;
    }
    t_color   = target->color;
    if( target->left == r->nil)
    {
        x   = target->right;
        tree_transplant( r, target, target->right);
    }
    else if( target->right == r->nil)
    {
        x   = target->left;
        tree_transplant( r, target, target->left);
    }
    else
    {
        temp    = target->right;
        while( temp->left != r->nil)
        {
            temp    = temp->left;
        }

        t_color   = temp->color;
        x   = temp->right;

        tree_transplant( r, temp, temp->right);
        temp->right         = target->right;
        (temp->right)->parent    = temp;

        tree_transplant( r, target, temp);
        temp->left      = target->left;
        (temp->left)->parent = temp;
        temp->color       = target->color;
    }
    if( t_color== RBTREE_BLACK)
        delete_fixup( r, x);
    free(target);
	target = NULL;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  delete_node(t, p->key);
  return 0;
}

static void Inorder_array(node_t *pNode, node_t *nil, key_t *arr, size_t *idx, size_t n)
{
  if (pNode == nil || *idx >= n)
	return ;
  Inorder_array(pNode->left, nil, arr, idx, n);
  *(arr + *idx) = pNode->key;
  *idx += 1;
  Inorder_array(pNode->right, nil, arr, idx, n);
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  size_t idx;

  idx = 0;
  if (arr == NULL || n == 0)
	return 0;
  Inorder_array(t->root, t->nil, arr, &idx, n); 
  return 0;
}
