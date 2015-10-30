#ifndef LIST_H_DEFINED
#define LIST_H_DEFINED
 #include "bool.h"

// a common function used to free malloc'd objects
typedef void (*freeFunction)(void *);
 
typedef bool (*listIterator)(void *);
 
typedef struct _listNode {
  void *data;
  struct _listNode *next;
} listNode;
 
typedef struct List{
  int logicalLength;
  int elementSize;
  listNode *head;
  listNode *tail;
  freeFunction freeFn;
}List;
 
void list_new(List *list, int elementSize, freeFunction freeFn);
void list_destroy(List *list);
 
void list_prepend(List *list, void *element);
void list_append(List *list, void *element);

void *list_get_first(List *list);

int list_size(List *list);
 
void list_for_each(List *list, listIterator iterator);
void list_head(List *list, void *element, bool removeFromList);
void list_tail(List *list, void *element);

char *list_to_char_array(List *list);
 
#endif