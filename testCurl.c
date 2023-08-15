#include <curl/curl.h> // Include libcurl
#include <stdio.h>

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
  // This function simply prints the received data to stdout
  size_t totalSize = size * nmemb;
  fwrite(contents, 1, totalSize, stdout);
  return totalSize;
}

int main() {
  CURL *curl = curl_easy_init();
  if (!curl) {
    fprintf(stderr, "Error initializing libcurl\n");
    return 1;
  }

  // Set the URL for the API request
  curl_easy_setopt(curl, CURLOPT_URL,
                   "https://v2.jokeapi.dev/joke/Any?format=txt&type=single");

  // Set the write callback to print the received data to stdout
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

  // Perform the HTTP request
  CURLcode res = curl_easy_perform(curl);
  if (res != CURLE_OK) {
    fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
    return 1;
  }

  // Clean up libcurl
  curl_easy_cleanup(curl);

  return 0;
}
