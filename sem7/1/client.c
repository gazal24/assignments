#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netdb.h>

#define PORT 34567 /* the port client will be connecting to */
#define MAXDATASIZE 1000 /* max number of bytes we can get at once */



int main(int argc, char *argv[])
{
  int sockfd, numbytes;
  int i=0;
  char input[MAXDATASIZE], result[100];
  struct hostent *he;
  struct sockaddr_in their_addr; /* client's address information */
  if (argc != 2)
    {
      fprintf(stderr,"usage: client hostname\n");
      exit(1);
    }
  if ((he=gethostbyname(argv[1])) == NULL) /* get the host info */
    {
      herror("gethostbyname");
      exit(1);
    }
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror("socket");
      exit(1);
    }
  their_addr.sin_family = AF_INET;
  their_addr.sin_port = htons(PORT);
  their_addr.sin_addr = *((struct in_addr *)he->h_addr);
  bzero(&(their_addr.sin_zero), 8);
  if (connect(sockfd,(struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1)
    {
      perror("connect");
      exit(1);
    }
  printf ("Enter a paragraph\n");
  int size = scanf ("%[^\n]s", input);
  printf ("input taken\n");
  if (send (sockfd, input, strlen(input), 0) == -1)
    {
      perror("send:");
      exit(0);
    }
  if ((numbytes=recv(sockfd, result, 100, 0)) == -1)
    {
      perror("recv");
      exit(1);
    }


  result[numbytes] = '\0';
  printf("Info Received: %s\n",result);
  close(sockfd);
  return 0;
}
