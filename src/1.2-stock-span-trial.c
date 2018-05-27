#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include "1.2-stock-span-lib.h"
extern char * strtok_r(char *string, const char *delimiter, char **bookmark);
// strtok_r is POSIX.

typedef struct
{
  char *base;
  size_t size;
} memory;

static size_t write_mem(void *buffer, size_t size, size_t nmemb, void *userdata)
/* Callback funtion called by libcurl as soon as there is data received that
needs to be saved. *buffer points to delivered data, and size of that data is
size * nmemb. The user/programmer can pass in/out data to/from this function via
the userdata argument, which can be set with the CURLOPT_WRITEDATA option. */
{
  size_t num_bytes_received = size * nmemb;
  memory *mem = (memory *)userdata;

  // Re-size mem to fit more data, plus extra byte for null terminator.
  mem->base = realloc(mem->base, mem->size + num_bytes_received + 1);
  if (!mem->base)
  {
    fprintf(stderr, "Out of memory!\n");
    exit(EXIT_FAILURE);
  }
  // Copy the data to mem, update struct, and add null terminator.
  memcpy(&(mem->base[mem->size]), buffer, num_bytes_received);
  mem->size += num_bytes_received;
  mem->base[mem->size] = '\0';

  /* "Your callback should return the number of bytes actually taken care of.
  If that amount differs from the amount passed to your callback function, it'll
  signal an error condition to the library. This will cause the transfer to get
  aborted and the libcurl function used will return CURLE_WRITE_ERROR." */
  return num_bytes_received;
}

int main(int argc, char **argv)
{
  if (argc != 3)
  {
    fprintf(stderr,
      "Wrong number of arguments. Provide a stock symbol and API key.\n");
    exit(EXIT_FAILURE);
  }

  char *stock_symbol = argv[1];
  if (strlen(stock_symbol) > 5)
  {
    fprintf(stderr,
      "Stock symbol '%s' is more than 5 characters.\n", stock_symbol);
    exit(EXIT_FAILURE);
  }

  char *api_key = argv[2];
  if (strlen(api_key) != 16)
  {
    fprintf(stderr, "API key '%s' is not 16 characters.\n", api_key);
    exit(EXIT_FAILURE);
  }

  // libcurl setup.
  curl_global_init(CURL_GLOBAL_ALL);
  CURL *handle = curl_easy_init();

  char url[127];
  snprintf(url, sizeof url,
    "https://www.alphavantage.co/query"
    "?function=TIME_SERIES_DAILY"
    "&symbol=%s"
    "&outputsize=full"
    "&datatype=csv"
    "&apikey=%s",
    stock_symbol, api_key
  );
  curl_easy_setopt(handle, CURLOPT_URL, url);

  curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_mem);
  memory mem = {.base=malloc(1), .size=0};
  curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *)&mem);

  // Get the data.
  printf("Downloading quotes...\n");
  CURLcode res = curl_easy_perform(handle);

  if (res != CURLE_OK)
  {
    fprintf(stderr, "Downloading quotes failed: %s\n", curl_easy_strerror(res));
    exit(EXIT_FAILURE);
  }

  if (mem.base[0] == '{' || mem.base[0] == '<')
  // The website returns API errors in JSON format.
  // Heroku returns an HTML page for application errors at their end.
  {
    fprintf(stderr, "%s\n", mem.base);
    exit(EXIT_FAILURE);
  }

  printf("%zu bytes received.\n", mem.size);

  // libcurl teardown.
  curl_easy_cleanup(handle);
  curl_global_cleanup();

  // Copy closing quotes from csv to array.
  enum csv_header
  {
    TIMESTAMP, OPEN, HIGH, LOW, CLOSE, VOLUME
  };

  char *bookmark_line;
  char *line = strtok_r(mem.base, "\n", &bookmark_line);
  line = strtok_r(NULL, "\n", &bookmark_line); // Skip header.
  double *closing_quotes = NULL;
  size_t cq_size = 0;
  while (line)
  {
    char *bookmark_cell;
    char *cell = strtok_r(line, ",", &bookmark_cell);
    size_t column = TIMESTAMP;
    while (cell)
    {
      if (column == CLOSE)
      {
        cq_size++;
        closing_quotes = realloc(closing_quotes, cq_size * sizeof(double));
        closing_quotes[cq_size-1] = atof(cell);
      }
      column++;
      cell = strtok_r(NULL, ",", &bookmark_cell);
    }
    line = strtok_r(NULL, "\n", &bookmark_line);
  }
  free(mem.base);

  // Reverse the array, to put it in chronological order.
  double *base = closing_quotes;
  double *top = closing_quotes + cq_size - 1;
  double tmp;
  for (; base < top; base++ && top--)
  {
    tmp = *base;
    *base = *top;
    *top = tmp;
  }

  // Run the two algorithms on the data. Profile this!
  size_t *spans = malloc(cq_size * sizeof(size_t));
  printf("Running stock_span_stack... ");
  stock_span_stack(closing_quotes, spans, cq_size);
  printf("DONE.\n");
  printf("Running stock_span_simple... ");
  stock_span_simple(closing_quotes, spans, cq_size);
  printf("DONE.\n");

  for (size_t i=0; i<cq_size; i++)
  {
    printf("Quote: %.4f, Span: %zu\n", closing_quotes[i], spans[i]);
  }

  free(spans);
  free(closing_quotes);
}
