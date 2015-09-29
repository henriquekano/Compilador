#ifndef TREE_H_DEFINED
#define TREE_H_DEFINED
#include "bool.h"
#include "list.h"

// a common function used to free malloc'd objects
typedef void (*freeFunction)(void *);
 
typedef bool (*treeIterator)(void *, int, int);
typedef int (*treeComparator)(void *, void *);
 
typedef struct _treeNode {
  void *data;
  struct List *elementList;
} treeNode;
 
typedef struct {
  int logicalLength;
  int elementSize;
  treeNode *root;
  freeFunction freeFn;
  treeComparator conparisonFn;
} Tree;
 
void tree_new(Tree *tree, int elementSize, treeComparator comparisonFn, freeFunction freeFn);
void tree_destroy(Tree *tree);
 
void tree_insert(Tree *tree, void *element);
int tree_size(Tree *tree);
 
void tree_for_each(Tree *tree, treeIterator iterator);
 
#endif