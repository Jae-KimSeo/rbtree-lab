#include "rbtree.h"

/*
void tree_transplant( rbtree->root *, node_t *, node_t *)
It maintains the propertise of the tree.
*/

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

    c->parent    = t->parent; // link target's parent to child's parent.
}
/*
void left_rotate( node_t **, node_t *)
This function transforms the configuration of the two nodes on the right
into the configuration on the left by changing a constant number of pointers.
*/
void left_rotate( rbtree *r, node_t *x)
{
    node_t *temp;

    temp        = x->right;
    // turn temp's left subtree into x's right subtree
    x->right    = temp->left;

    if( temp->left != r->nil)
    {
        (temp->left)->parent = x;
    }

    temp->parent = x->parent; // link x's parent to temp

    if( x->parent == r->nil)
    {
        r->root    = temp;
    }
    else if( x == (x->parent)->left)
    {
        (x->parent)->left    = temp;
    }
    else
    {
        (x->parent)->right   = temp;
    }

    temp->left  = x; // put x on temp's left
    x->parent        = temp;
}
/*
void right_rotate( node_t **, node_t *)
This function transforms the configuration of the two nodes on the left
into the configuration on the right by changing a constant number of pointers.
*/
void right_rotate( rbtree *r, node_t *y)
{
    node_t *temp;

    temp        = y->left;
    // turn temp's right subtree into y's left subtree
    y->left     = temp->right;

    if( temp->right != r->nil)
        (temp->right)->parent = y;
    temp->parent = y->parent; // link y's parent to temp
    if( y->parent == r->nil)
        r->root    = temp;
    else if( y == (y->parent)->left)
        (y->parent)->left    = temp;
    else
        (y->parent)->right   = temp;
    temp->right = y; // put y on temp's right
    y->parent        = temp;
}
/*
void delete_node( rbtree->root *, int)
remove the node that has the key from the tree.
*/
void delete_fixup(rbtree *r, node_t *x)
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
