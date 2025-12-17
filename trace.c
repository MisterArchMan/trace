#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

struct buffer {
    char *data;
    size_t size;
};

static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t total = size * nmemb;
    struct buffer *buf = (struct buffer *)userp;

    char *tmp = realloc(buf->data, buf->size + total + 1);
    if (!tmp) return 0;

    buf->data = tmp;
    memcpy(&(buf->data[buf->size]), contents, total);
    buf->size += total;
    buf->data[buf->size] = '\0';

    return total;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <ip>\n", argv[0]);
        return 1;
    }

    CURL *curl;
    CURLcode res;
    struct buffer buf = {0};

    char url[256];
    snprintf(url, sizeof(url), "https://ipinfo.io/%s/json", argv[1]);

    curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Failed to init curl\n");
        return 1;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buf);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "geolocate/1.0");
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

    res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        fprintf(stderr, "curl error: %s\n", curl_easy_strerror(res));
        curl_easy_cleanup(curl);
        free(buf.data);
        return 1;
    }

    printf("%s\n", buf.data);

    curl_easy_cleanup(curl);
    free(buf.data);
    return 0;
}
