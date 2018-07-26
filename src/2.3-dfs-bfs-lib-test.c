#include "2.3-dfs-bfs-lib.h"
#include "run_test.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
  size_t index;
  size_t split;
  bool* output;
  bool* case_1;
  bool* case_2;
  size_t bytes;
} md_arg; // Arguments for memcmp_disconnected().

static void memcmp_disconnected(md_arg* a)
{
  if (a->index < a->split)
  {
    assert(!memcmp(a->output, a->case_1, a->bytes));
  }
  else
  {
    assert(!memcmp(a->output, a->case_2, a->bytes));
  }
}

typedef void (*graph_m_search)(graph_m*, size_t, bool*);

//static void test_dfs_matrix(graph_m_search search, graph_m* graph, md_arg* mda)
//{
//}

typedef void (*graph_l_search)(graph_l*, size_t, bool*);

static void test_dfs_list(graph_l_search search, graph_l* graph, md_arg* mda)
{
  for(size_t start_vertex=0; start_vertex < graph->vertex_count; start_vertex++)
  {
    bool* visited = calloc(graph->vertex_count, sizeof *visited);
    search(graph, start_vertex, visited);
    mda->index = start_vertex;
    mda->output = visited;
    memcmp_disconnected(mda);
    free(visited);
  }
}

//static void test_dfs_matrix_recursive(graph_m* graph, md_arg* mda)
//{
//  test_dfs_matrix(&dfs_matrix_recursive, graph, mda);
//}

static void test_dfs_list_recursive(graph_l* graph, md_arg* mda)
{
  test_dfs_list(&dfs_list_recursive, graph, mda);
}

/*
static void test_dfs_matrix_stack(graph_m* graph, md_arg* mda)
{
  test_dfs_matrix(&dfs_matrix_stack, graph, mda);
}

static void test_dfs_list_stack(graph_l* graph, md_arg* mda)
{
  test_dfs_list(&dfs_list_stack, graph, mda);
}

static void test_bfs_matrix(graph_m* graph, md_arg* mda)
{
}

static void test_bfs_list(graph_l* graph, md_arg* mda)
{
}
*/

int main()
{
  /* Create initial human-friendly representation of test graph.

     (0)
    / | \
  (1)(2)(3)
   |     |
  (4)    |
    \   /
     (5)-(7)
      \
      (6)

  (8)-(9) <= Graph is disconnected.

  */
  size_t v0[] = {1,2,3};
  size_t v1[] = {0,4};
  size_t v2[] = {0};
  size_t v3[] = {0,5};
  size_t v4[] = {1,5};
  size_t v5[] = {3,4,6,7};
  size_t v6[] = {5};
  size_t v7[] = {5};
  size_t v8[] = {9};
  size_t v9[] = {8};
  size_t v_lengths[] = {3, 2, 1, 2, 2, 4, 1, 1, 1, 1};
  size_t* gi[] = {v0, v1, v2, v3, v4, v5, v6, v7, v8, v9};
  size_t vertex_count = sizeof gi / sizeof *gi;
  bool visited_0_7[] = {true, true, true, true, true, true, true, true,
    false, false};
  bool visited_8_9[] = {false, false, false, false, false, false, false, false,
    true, true};

  md_arg mda = {
    .index = 0,
    .split = 8,
    .output = NULL,
    .case_1 = visited_0_7,
    .case_2 = visited_8_9,
    .bytes = vertex_count * sizeof(bool)
  };

  // Create linked list and matrix representations of test graph.
  graph_l gl = graph_l_initialize(vertex_count);
//graph_m gm = graph_m_initialize(vertex_count);
  for (size_t v=0; v < vertex_count; v++)
  {
    gl.adjacent[v] = list_create();
    for (size_t e=0; e < v_lengths[v]; e++)
    {
      list_insert_data(&gl.adjacent[v], NULL, &gi[v][e]);
 //   *(gm.adjacent + (v * vertex_count) + e) = true;
    }
  }

  //Run tests.
//run_test_with_args(test_dfs_matrix_recursive(&gm, &mda));
  run_test_with_args(test_dfs_list_recursive(&gl, &mda));
//run_test_with_args(test_dfs_matrix_stack(gm, &mda));
//run_test_with_args(test_dfs_list_stack(gl, &mda));
//run_test_with_args(test_bfs_matrix(gm, &mda));
//run_test_with_args(test_bfs_list(gl, &mda));
  printf("\nOK\n\n");

  //Tear-down.
  graph_l_destroy(&gl);
//graph_m_destroy(&gm);
}
