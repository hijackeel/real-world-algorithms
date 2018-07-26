#include "2.1-linked-list-lib.h"
#include <stdbool.h>

typedef struct
{
  bool* adjacent;
  size_t vertex_count;
} graph_m;

typedef struct
{
  list* adjacent;
  size_t vertex_count;
} graph_l;

graph_l graph_l_initialize(size_t vertex_count);

graph_m graph_m_initialize(size_t vertex_count);

void graph_l_destroy(graph_l* g);

void graph_m_destroy(graph_m* g);

void dfs_matrix_recursive(graph_m* g, size_t start_vertex, bool* visited);

void dfs_list_recursive(graph_l* g, size_t start_vertex, bool* visited);

//void dfs_matrix_stack(graph_m* g, size_t start_vertex, bool* visited);

//void dfs_list_stack(graph_l* g, size_t start_vertex, bool* visited);

//void bfs_matrix(graph_m* g, size_t start_vertex, bool* visited);

//void bfs_list(graph_l* g, size_t start_vertex, bool* visited);
