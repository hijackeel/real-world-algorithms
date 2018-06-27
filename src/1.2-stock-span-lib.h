#include <stddef.h>

void stock_span_stack (double *quotes, size_t *spans, size_t length);
// Calculate the span of each stock quote in an array of quotes, in O(n) time.
// Provide array of quotes, same-length empty array for spans, and array length.

void stock_span_simple (double *quotes, size_t *spans, size_t length);
// Calculate the span of each stock quote in an array of quotes, in O(n^2) time.
// Provide array of quotes, same-length empty array for spans, and array length.
