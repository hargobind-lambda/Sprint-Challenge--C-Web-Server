#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "lib.h"

#define DEBUG

#define BUFSIZE 4096 // max number of bytes we can get at once

/**
 * Struct to hold all three pieces of a URL
 */
typedef struct urlinfo_t {
  char *hostname;
  char *port;
  char *path;
} urlinfo_t;

/**
 * Tokenize the given URL into hostname, path, and port.
 *
 * url: The input URL to parse.
 *
 * Store hostname, path, and port in a urlinfo_t struct and return the struct.
*/
urlinfo_t *parse_url(char *url)
{
  // copy the input URL so as not to mutate the original
  char *hostname = strdup(url);
  char *port;
  char *path;

  urlinfo_t *urlinfo = malloc(sizeof(urlinfo_t));

  /*
    We can parse the input URL by doing the following:

    1. Use strchr to find the first backslash in the URL (this is assuming there is no http:// or https:// in the URL).
    2. Set the path pointer to 1 character after the spot returned by strchr.
    3. Overwrite the backslash with a '\0' so that we are no longer considering anything after the backslash.
    4. Use strchr to find the first colon in the URL.
    5. Set the port pointer to 1 character after the spot returned by strchr.
    6. Overwrite the colon with a '\0' so that we are just left with the hostname.
  */

  ///////////////////
  // IMPLEMENT ME! //
  ///////////////////
  path = strchr(hostname, '/');
  *(path) = '\0';
  path++;
  port = strchr(hostname, ':');
  *port = '\0';
  port++;

#ifdef DEBUG
  printf("parsed url. hostname: %s, port: %s, path: %s\n", hostname, port, path);
#endif

  urlinfo->hostname = hostname;
  urlinfo->path = path;
  urlinfo->port = port;

  return urlinfo;
}

/**
 * Constructs and sends an HTTP request
 *
 * fd:       The file descriptor of the connection.
 * hostname: The hostname string.
 * port:     The port string.
 * path:     The path string.
 *
 * Return the value from the send() function.
*/
int send_request(int fd, char *hostname, char *port, char *path)
{
  const int max_request_size = 16384;
  char request[max_request_size];
  int rv;

  ///////////////////
  // IMPLEMENT ME! //
  ///////////////////
#ifdef DEBUG
  printf("sending request\n");
#endif

  int request_length = snprintf(request, max_request_size,
  "GET /%s HTTP/1.1\n"
  "Host: %s:%s\n"
  "Connection: close\n"
  "\n",
  path, hostname, port);

  int bytes_sent = send(fd, request, request_length, 0);
#ifdef DEBUG
  printf("request: \n%s\n---. Num bytes %d\n", request, bytes_sent);
#endif

  return 0;
}

int main(int argc, char *argv[])
{  
  int sockfd, numbytes;  
  char buf[BUFSIZE];

  if (argc != 2) {
    fprintf(stderr,"usage: client HOSTNAME:PORT/PATH\n");
    exit(1);
  }

  /*
    1. Parse the input URL
    2. Initialize a socket by calling the `get_socket` function from lib.c
    3. Call `send_request` to construct the request and send it
    4. Call `recv` in a loop until there is no more data to receive from the server. Print the received response to stdout.
    5. Clean up any allocated memory and open file descriptors.
  */
  ///////////////////
  // IMPLEMENT ME! //
  ///////////////////

#ifdef DEBUG
  printf("input: %s\n", argv[1]);
#endif

  struct urlinfo_t * url = parse_url(argv[1]);


#ifdef DEBUG
  printf("getting socket and sending request\n");
#endif

  sockfd = get_socket(url->hostname, url->port);

  int requested = send_request(sockfd, url->hostname, url->port, url->path);

#ifdef DEBUG
  printf("reading in returned data\n");
#endif

  while ( (numbytes = recv(sockfd, buf, BUFSIZE -1 ,0)) > 0)
  {
    printf("%s\n", buf);
  }

#ifdef DEBUG
  printf("freeing memory\n");
#endif
  free(url);
  close(sockfd);

#ifdef DEBUG

#endif

#ifdef DEBUG

#endif

#ifdef DEBUG

#endif

  return 0;
}
