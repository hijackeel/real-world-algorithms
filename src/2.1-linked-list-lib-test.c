#include "2.1-linked-list-lib.h"
#include "run_test.h"
#include <assert.h>


static void test_list()
{
  char a = 'a';
  char b = 'b';
  char c = 'c';
  node *p = NULL;

  // l -> NULL
  list l = list_create();
  assert(list_next_node(&l, NULL) == NULL);
  assert(list_search_data(&l, &a, sizeof a, &p) == NULL && p == NULL);
  assert(list_search_data(&l, &b, sizeof b, &p) == NULL && p == NULL);
  assert(list_search_data(&l, &c, sizeof c, &p) == NULL && p == NULL);

  // l -> x(a) -> NULL
  node *x = list_insert_data(&l, NULL, &a);
  assert(get_data(x) == &a);
  assert(list_next_node(&l, NULL) == x);
  assert(list_next_node(&l, x) == NULL);
  assert(list_search_data(&l, &a, sizeof a, &p) == x && p == NULL);
  assert(list_search_data(&l, &b, sizeof b, &p) == NULL && p == NULL);
  assert(list_search_data(&l, &c, sizeof c, &p) == NULL && p == NULL);

  // l -> x(a) -> y(b) -> NULL
  node *y = list_insert_data(&l, x, &b);
  assert(get_data(y) == &b);
  assert(list_next_node(&l, NULL) == x);
  assert(list_next_node(&l, x) == y);
  assert(list_next_node(&l, y) == NULL);
  assert(list_search_data(&l, &a, sizeof a, &p) == x && p == NULL);
  assert(list_search_data(&l, &b, sizeof b, &p) == y && p == x);
  assert(list_search_data(&l, &c, sizeof c, &p) == NULL && p == NULL);

  // l -> x(a) -> y(b) -> z(c) -> NULL
  node *z = list_insert_data(&l, y, &c);
  assert(get_data(z) == &c);
  assert(list_next_node(&l, NULL) == x);
  assert(list_next_node(&l, x) == y);
  assert(list_next_node(&l, y) == z);
  assert(list_next_node(&l, z) == NULL);
  assert(list_search_data(&l, &a, sizeof a, &p) == x && p == NULL);
  assert(list_search_data(&l, &b, sizeof b, &p) == y && p == x);
  assert(list_search_data(&l, &c, sizeof c, &p) == z && p == y);

  // l -> x(a) -> z(c) -> NULL
  node null_node = list_remove_node(&l, NULL, y); // y != head node.
  assert(get_data(&null_node) == NULL);
  node yn = list_remove_node(&l, x, y);//Test list_remove_node on non-head node.
  y = &yn;
  assert(get_data(y) == &b);
  null_node = list_remove_node(&l, x, y); // Already removed.
  assert(get_data(&null_node) == NULL);
  null_node = list_remove_data(&l, &b, sizeof b); // Already removed.
  assert(get_data(&null_node) == NULL);
  assert(list_next_node(&l, NULL) == x);
  assert(list_next_node(&l, x) == z);
  assert(list_next_node(&l, z) == NULL);
  assert(list_next_node(&l, y) == NULL);
  assert(list_search_data(&l, &a, sizeof a, &p) == x && p == NULL);
  assert(list_search_data(&l, &b, sizeof b, &p) == NULL && p == NULL);
  assert(list_search_data(&l, &c, sizeof c, &p) == z && p == x);

  // l -> z(c) -> NULL
  null_node = list_remove_node(&l, z, x); // x is head node.
  assert(get_data(&null_node) == NULL);
  node xn = list_remove_node(&l, NULL, x); // Test list_remove_node on head.
  x = &xn;
  assert(get_data(x) == &a);
  null_node = list_remove_node(&l, NULL, x); // Already removed.
  assert(get_data(&null_node) == NULL);
  null_node = list_remove_data(&l, &a, sizeof a); // Already removed.
  assert(get_data(&null_node) == NULL);
  assert(list_next_node(&l, NULL) == z);
  assert(list_next_node(&l, z) == NULL);
  assert(list_next_node(&l, y) == NULL);
  assert(list_next_node(&l, x) == NULL);
  assert(list_search_data(&l, &a, sizeof a, &p) == NULL && p == NULL);
  assert(list_search_data(&l, &b, sizeof b, &p) == NULL && p == NULL);
  assert(list_search_data(&l, &c, sizeof c, &p) == z && p == NULL);

  // l -> NULL
  node zn = list_remove_data(&l, &c, sizeof c); // Test list_remove_data.
  z = &zn;
  assert(get_data(z) == &c);
  null_node = list_remove_node(&l, NULL, z); // Already removed.
  assert(get_data(&null_node) == NULL);
  null_node = list_remove_data(&l, &c, sizeof c); // Already removed.
  assert(get_data(&null_node) == NULL);
  assert(list_next_node(&l, NULL) == NULL);
  assert(list_next_node(&l, z) == NULL);
  assert(list_next_node(&l, y) == NULL);
  assert(list_next_node(&l, x) == NULL);
  assert(list_search_data(&l, &c, sizeof c, &p) == NULL && p == NULL);
  assert(list_search_data(&l, &b, sizeof b, &p) == NULL && p == NULL);
  assert(list_search_data(&l, &a, sizeof a, &p) == NULL && p == NULL);

  // l -> z(c) -> NULL
  list_insert_node(&l, NULL, z);
  assert(list_next_node(&l, NULL) == z);
  assert(list_next_node(&l, z) == NULL);
  assert(list_next_node(&l, y) == NULL);
  assert(list_next_node(&l, x) == NULL);
  assert(list_search_data(&l, &c, sizeof c, &p) == z && p == NULL);
  assert(list_search_data(&l, &b, sizeof b, &p) == NULL && p == NULL);
  assert(list_search_data(&l, &a, sizeof a, &p) == NULL && p == NULL);

  // l -> z(c) -> y(b) -> NULL
  list_insert_node(&l, z, y);
  assert(list_next_node(&l, NULL) == z);
  assert(list_next_node(&l, z) == y);
  assert(list_next_node(&l, y) == NULL);
  assert(list_next_node(&l, x) == NULL);
  assert(list_search_data(&l, &c, sizeof c, &p) == z && p == NULL);
  assert(list_search_data(&l, &b, sizeof b, &p) == y && p == z);
  assert(list_search_data(&l, &a, sizeof a, &p) == NULL && p == NULL);

  // l -> z(c) -> y(b) -> x(a) -> NULL
  list_insert_node(&l, y, x);
  assert(list_next_node(&l, NULL) == z);
  assert(list_next_node(&l, z) == y);
  assert(list_next_node(&l, y) == x);
  assert(list_next_node(&l, x) == NULL);
  assert(list_search_data(&l, &c, sizeof c, &p) == z && p == NULL);
  assert(list_search_data(&l, &b, sizeof b, &p) == y && p == z);
  assert(list_search_data(&l, &a, sizeof a, &p) == x && p == y);
}

int main()
{
  run_test(test_list);
  printf("\nOK\n\n");
}
