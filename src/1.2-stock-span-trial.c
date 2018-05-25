#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include "1.2-stock-span-lib.h"

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
    printf("Out of memory!\n");
    return 0;
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

  // Setup.
  curl_global_init(CURL_GLOBAL_ALL);
  CURL *handle = curl_easy_init();

  char url[127];
  snprintf(url, sizeof(url),
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

  // Process the data.
  printf("%zu bytes received.\n", mem.size);
//printf("%s", mem.base);

/*
TO DO:
Check mem.base for error code from API.
If not API error, extract closing prices from csv.
Pass array of closing prices to stock_span_stack and stock_span_simple.
*/

  // Teardown.
  free(mem.base);
  curl_easy_cleanup(handle);
  curl_global_cleanup();
}
