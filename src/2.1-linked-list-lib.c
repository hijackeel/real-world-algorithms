#include "2.1-linked-list-lib.h"
#include <stdlib.h>
#include <string.h>

list list_create(void)
// Create and return empty list.
{
  return (list){.head=NULL};
}

node * list_next_node(list *l, node *a)
// Return pointer to node following node a in list l, or NULL if a is last.
// If node a is NULL, return pointer to head of l.
// Returned node is not removed from list.
{
  return a ? a->next : l->head;
}

node * list_insert_node(list *l, node *a, node *b)
// Insert node b after node a in list l.
// If node a is NULL, insert new node at head of list.
// Return pointer to newly inserted node.
{
  b->next = list_next_node(l, a);
  return a ? (a->next = b) : (l->head = b);
}

node * list_insert_data(list *l, node *a, void *d)
// Insert node containing data d after node a in list l.
// If node a is NULL, insert new node at head of list.
// Return pointer to newly inserted node.
{
  node *b = malloc(sizeof *b);
  *b = (node){.data=d, .next=NULL};
  return list_insert_node(l, a, b);
}

node * list_search_data(list *l, void *d, size_t bytes, node **p)
// Search list l for first node containing data at d of size bytes.
// Return pointer to node without removing it, or NULL if not found.
// *p will point to preceeding node, or be NULL if data is at head or not found.
{
  *p = NULL;
  node *n = list_next_node(l, NULL);
  while (n && memcmp(n->data, d, bytes))
  {
    *p = n;
    n = list_next_node(l, n);
  }
  *p = n ? *p : NULL;
  return n;
}

node list_remove_node(list *l, node *a, node *b)
// Remove node b from list l.
// Node a precedes b in the list, or is NULL if b is the head.
// Return node b, or empty node if not in list.
{
  if (list_next_node(l, a) != b)
  // Node b is either not after node a, or is not the head.
  {
    return (node){.data=NULL, .next=NULL};
  }

  node *c = list_next_node(l, b);
  a ? (a->next = c) : (l->head = c);
  b->next = NULL;
  node f = *b;
  free(b);
  return f;
}

node list_remove_data(list *l, void *d, size_t bytes)
// Remove the first node containing data at d of size bytes from the list l.
// Return node, or empty node if not found.
{
  node *a = NULL;
  node *b = list_search_data(l, d, bytes, &a);
  return b ? list_remove_node(l, a, b) : (node){.data=NULL, .next=NULL};
}

void * get_data(node *n)
// Return data stored inside node n.
{
  return n->data;
}
