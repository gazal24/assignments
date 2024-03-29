#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>


#define MYPORT 34567 /* the port users will be connecting to */
#define BACKLOG 10 /* number of pending connections */
#define MAXDATASIZE 1000


main(int argc, char *argv[])
{
  int sockfd, new_fd; /* listen on sock_fd,
			 new connection on new_fd */
  struct sockaddr_in my_addr; /* my address information */
  struct sockaddr_in their_addr; /* client's address info */
  int sin_size;
  int num_words=0, num_chars=0, num_sentences=0, numbytes=0;
  char buf[MAXDATASIZE];
  char output [100];
  int i=0;

  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror("socket");
      exit(1);
    }
  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(MYPORT);
  my_addr.sin_addr.s_addr = INADDR_ANY; /* auto-fill with my IP */
  bzero(&(my_addr.sin_zero), 8); /* zero the rest */
  if (bind(sockfd,(struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
    {
      perror("bind");
      exit(1);
    }
  if (listen(sockfd, BACKLOG) == -1)
    {
      perror("listen");
      exit(1);
    }
  while(1) /* main accept() loop */
    {
      sin_size = sizeof(struct sockaddr_in);
      if ((new_fd = accept(sockfd,(struct sockaddr *)&their_addr,&sin_size)) ==-1)
	{
	  perror("accept");
	  continue;
	}
      printf("server: got connection from %s\n", inet_ntoa(their_addr.sin_addr));
      if (!fork()) /* this is the child process */
	{
	  if ((numbytes=recv(new_fd, buf, MAXDATASIZE, 0)) == -1)
	    {
	      perror  ("Recieve:");
	    }
	  else 
	    {
	      buf[numbytes] = '\0';
	      printf ("%s\n", buf);
	      for (i=0; i<strlen(buf);i++)
		{
		  if (buf[i]=='.')
		    {
		      num_sentences++;
		      num_words++;
		      num_chars++;
		    }
		  else if (buf[i]==' ' || buf[i]=='\t')
		    {
		      num_words++;
		      num_chars++;
		    }
		  else 
		    {
		      num_chars++;
		    }
		}
	      i=0;
	      int size = sprintf(output, "chars: %d, words: %d, sentences: %d", num_chars, num_words,num_sentences);
	      printf ("%s\n",output);
	      if (send(new_fd, output, strlen(output), 0) == -1)
		perror("send");
	    }
	  close(new_fd);
	  exit(0);
	}
      close(new_fd); /* parent doesn't need this */
    }
}


