#include <stddef.h>

typedef struct node
{
  void *data;
  struct node *next;
} node;

typedef struct
{
  node *head;
} list;

list list_create(void);
// Create and return empty list.

node * list_next_node(list *l, node *a);
// Return pointer to node following node a in list l, or NULL if a is last.
// If node a is NULL, return pointer to head of l.
// Returned node is not removed from list.

node * list_insert_node(list *l, node *a, node *b);
// Insert node b after node a in list l.
// If node a is NULL, insert new node at head of list.
// Return pointer to newly inserted node.

node * list_insert_data(list *l, node *a, void *d);
// Insert node containing data d after node a in list l.
// If node a is NULL, insert new node at head of list.
// Return pointer to newly inserted node.

node * list_search_data(list *l, void *d, size_t bytes, node **p);
// Search list l for first node containing data at d of size bytes.
// Return pointer to node without removing it, or NULL if not found.
// *p will point to preceeding node, or be NULL if data is at head or not found.

node list_remove_node(list *l, node *a, node *b);
// Remove node b from list l.
// Node a precedes b in the list, or is NULL if b is the head.
// Return node b, or empty node if not in list.

node list_remove_data(list *l, void *d, size_t bytes);
// Remove the first node containing data at d of size bytes from the list l.
// Return node, or empty node if not found.

void * get_data(node *n);
// Return data stored inside node n.
