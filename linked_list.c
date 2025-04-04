#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value) 
{ 
  struct list_node * n = malloc(sizeof(struct list_node));
  n -> value = value;
  n -> next = NULL;
  return n;
}

void insert_at_head(struct linked_list *list, size_t value) 
{
  struct list_node * n = new_node(value);
  if (list->head == NULL) {list->head = n; return;}
  n->next = list->head;
  list->head = n;
}

void insert_at_tail(struct linked_list *list, size_t value) 
{
  struct list_node * n = new_node(value);
  if(list->head == NULL) {list->head = n; return;}
  struct list_node *p = list->head;
  while(p -> next != NULL)
  {
    p = p -> next;
  }
  p -> next = n;

}

size_t remove_from_head(struct linked_list *list) 
{ 
  if (list->head == NULL) return 0;
  size_t retVal = list->head->value;
  struct list_node * n = list->head;
  list->head = list->head->next;
  free(n);
  return retVal;

}

size_t remove_from_tail(struct linked_list *list) 
{ 
  if (list->head == NULL) return 0;
  struct list_node * n = list->head;
  size_t retVal;
  if(n->next == NULL)
  {
    retVal = n->value;
    list->head = NULL;
    free(n);
    return retVal;
  }
  while (n->next->next != NULL)
  {
    n = n->next;
  }
  retVal = n->next->value;
  free(n->next);
  n->next = NULL;
  return retVal;
}

void free_list(struct linked_list list) 
{
  while (list.head != NULL)
  {
    remove_from_head(&list);
  }
}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
