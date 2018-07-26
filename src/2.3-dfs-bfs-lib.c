#include "2.3-dfs-bfs-lib.h"
#include <stdlib.h>

graph_l graph_l_initialize(size_t vertex_count)
{
  list* adjacent = calloc(vertex_count, sizeof *adjacent);
  return (graph_l){.adjacent=adjacent, .vertex_count=vertex_count};
}

graph_m graph_m_initialize(size_t vertex_count)
{
  bool* adjacent = calloc(vertex_count * vertex_count, sizeof *adjacent);
  return (graph_m){.adjacent=adjacent, .vertex_count=vertex_count};
}

void graph_l_destroy(graph_l* g)
{
  free(g->adjacent); g->adjacent = NULL; g->vertex_count = 0;
}

void graph_m_destroy(graph_m* g)
{
  free(g->adjacent); g->adjacent = NULL; g->vertex_count = 0;
}

///void dfs_matrix_recursive(graph_m* g, size_t start_vertex, bool* visited)
///{
///}

void dfs_list_recursive(graph_l* g, size_t start_vertex, bool* visited)
{
  visited[start_vertex] = true;
  node* n = list_next_node(&g->adjacent[start_vertex], NULL);
  while (n)
  {
    size_t next_vertex = *(size_t*)get_data(n);
    if (!visited[next_vertex])
    {
      dfs_list_recursive(g, next_vertex, visited);
    }
    n = list_next_node(&g->adjacent[start_vertex], n);
  }
}

//void dfs_matrix_stack(graph_m* g, size_t start_vertex, bool* visited)
//{
//}

//void dfs_list_stack(graph_l* g, size_t start_vertex, bool* visited)
//{
//}

//void bfs_matrix(graph_m* g, size_t start_vertex, bool* visited)
//{
//}

//void bfs_list(graph_l* g, size_t start_vertex, bool* visited)
//{
//}
