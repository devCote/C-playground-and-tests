#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h> // Include libcurl

int main() {
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);

    // Initialize libcurl
    CURL *curl = curl_easy_init();
    if (!curl) {
        endwin();
        fprintf(stderr, "Error initializing libcurl\n");
        return 1;
    }

    char text[1000]; // Adjust the size based on your expected API response size

    // Set the URL for the API request
    curl_easy_setopt(curl, CURLOPT_URL, "https://v2.jokeapi.dev/joke/Any?format=txt&type=single");

    // Set the write callback to receive the response directly into 'text' array
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL); // No custom write callback
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, text);

    // Perform the HTTP request
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        endwin();
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        return 1;
    }

    // Clean up libcurl
    curl_easy_cleanup(curl);

    int ch;
    int position = 0;

    mvprintw(0, 0, "%s", text);
    move(1, 0);

    while ((ch = getch()) != '\n' && text[position] != '\0') {
        if (ch == text[position]) {
            attron(COLOR_PAIR(1));
            addch(ch);
            attroff(COLOR_PAIR(1));
            position++;
        }
    }

    endwin();
    return 0;
}

