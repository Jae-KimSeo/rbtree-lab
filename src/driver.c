#include "rbtree.h"

int main(int argc, char *argv[]) {
  rbtree *rb_t;
  node_t *new_node;
  rb_t = new_rbtree();
  
  //rb_t = (rbtree*)malloc(sizeof(rbtree));
  new_node = (node_t*)malloc(sizeof(node_t));
  new_node->color = RBTREE_BLACK;
  new_node->key = 11;
  new_node->parent = rb_t->nil;
  new_node->left = rb_t->nil;
  new_node->right = rb_t->nil;

  rb_t->root = new_node;
  rbtree_insert(rb_t, 2);
  rbtree_insert(rb_t, 14);
  rbtree_insert(rb_t, 1);
  rbtree_insert(rb_t, 7);
  rbtree_insert(rb_t, 15);
  rbtree_insert(rb_t, 5);
  rbtree_insert(rb_t, 8);
  rbtree_insert(rb_t, 4);
  rbtree *temp_t = rb_t;
  rbtree_min(temp_t);
  rbtree_max(temp_t);
  node_t *find_node;
  find_node = rbtree_find(rb_t, 11);
  printf("%d %d\n", find_node->key, find_node->color);
  
  //find_node = rbtree_find(rb_t, 1);
  //printf("%d %d\n", find_node->key, find_node->color);
  key_t *arr;
  int size;

  size = 9;
  if (!(arr = (key_t *)malloc(sizeof(key_t) * (size+1))))		
	return 0;
  bzero(arr, sizeof(key_t)*(size+1)); 
  for (int i = 0; i < size; i++)
	printf("%d ", arr[i]);
  printf("\n");
  rbtree_to_array(rb_t, arr, size);
  for (int i = 0; i < size; i++)
	printf("%d ", arr[i]);
  free(arr);
  delete_rbtree(rb_t);
 //rbtree_to_array(rbtree, arr, 9); 
}
