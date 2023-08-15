#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <curl/curl.h> // Include libcurl

// Define a macro to determine the maximum response size
#define MAX_RESPONSE_SIZE 200

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    // This function processes the received data and removes newline characters
    size_t totalSize = size * nmemb;
    size_t processedSize = 0;
    for (size_t i = 0; i < totalSize; i++) {
        char c = ((char *)contents)[i];
        if (c != '\n' && c != '\r') {
            ((char *)userp)[processedSize++] = c;
        }
    }
    return processedSize;
}

int main() {
    initscr();
    start_color();
    cbreak();  // Disable line buffering
    noecho();  // Disable automatic echoing of typed characters
    keypad(stdscr, TRUE); // Enable special keys (e.g., arrow keys)

    init_pair(1, COLOR_GREEN, COLOR_BLACK); // Green on black
    init_pair(2, COLOR_RED, COLOR_BLACK);   // Red on black

    char text[MAX_RESPONSE_SIZE] = ""; // Initialize the text array

    CURL *curl = curl_easy_init();
    if (!curl) {
        endwin();
        fprintf(stderr, "Error initializing libcurl\n");
        return 1;
    }

    // Set the URL for the API request
    curl_easy_setopt(curl, CURLOPT_URL, "https://v2.jokeapi.dev/joke/Any?format=txt&type=single");

    // Set the write callback to populate the 'text' array
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, text);

    // Perform the HTTP request
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        endwin();
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        return 1;
    }

    curl_easy_cleanup(curl);

    int ch;
    int position = 0; // Current position in the text

    mvprintw(0, 0, "%s", text);
    move(1, 0); // Move cursor to the second line

    while ((ch = getch()) != '\n' && text[position] != '\0') {
        if (ch == text[position]) {
            attron(COLOR_PAIR(1)); // Change to green color
            addch(ch);
            attroff(COLOR_PAIR(1)); // Restore color
            position++;
        } 
    }

    endwin();
    return 0;
}

