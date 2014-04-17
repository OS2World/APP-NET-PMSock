

#undef DEBUG
#include <stdio.h>
#include "pmsock.h"

WSADATA WSAData;
#define WSVERSION 0x101


int main(int argc, char *argv[])
{
  int i, err;
  int dayport; 
  SOCKET s;
  SERVENT *pse;    /* pts to "service" data (internally allocated) */
  unsigned long ipa;  // for Internet address of host
  HOSTENT *phe; // pts to host info struct (internally allocated)
  char szHost[255];

#ifdef DEBUG
  printf("Calling WSAStartup\n");
#endif
  if (err = WSAStartup(WSVERSION, &WSAData))
  {
     printf("Error starting up\n");
     exit(1);
  }
#ifdef DEBUG
  printf("Getting service name\n");
#endif
  if (pse = getservbyname("daytime", "tcp"))
  {

    dayport = pse->s_port;
#ifdef DEBUG
    printf("Debug: daytime port is %d\n", ntohs(dayport));
#endif
  }
  
  if (!argv[1]) {
    if (gethostname(szHost, sizeof(szHost))==SOCKET_ERROR) {
      printf("Error getting hostname\n");
      exit(1);
    }
  }
  else 
    strcpy( szHost, argv[1]);

#ifdef DEBUG
  printf("Checking host %s\n", szHost);
#endif
  if ((ipa = inet_addr(szHost)) == INADDR_NONE) 
  {
    if (phe = gethostbyname(szHost))
    {
      ipa = *((u_long *)phe->h_addr);
    }
    else
    {
      printf("can't get inet addr\n");
      exit(1); 
    }
  }
#ifdef DEBUG
  printf( "Found IP for %s = %x\n", szHost, ntohl(ipa)); 
#endif

  if ((s = socket(AF_INET, SOCK_STREAM, 0)) >= 0)
  {
     SOCKADDR_IN server;

     // address of the time server
     memset(&server, 0, sizeof(server));
     server.sin_family = AF_INET;
     server.sin_port = dayport;
     server.sin_addr.s_addr = ipa;

     // establish a stream connection to server
     if (!connect(s, (SOCKADDR *)&server, sizeof(server)))
     {
        char msg[255];
        int msglen;

        strcpy(msg, "\r\n");
        msglen = strlen(msg);
#ifdef DEBUG
        printf( "Socket connected, sending CRLF\n");
#endif

        if (send(s, msg, msglen, 0) == msglen)
        {
           static char buf[500];      // receive buffer
	   int nchars;
#ifdef DEBUG
           printf("Reading result..\n");
#endif
           printf("\n");
	
    	   while (( nchars = recv(s, (char FAR *)&buf,
             sizeof(buf), 0)) > 0)
               printf("%s",buf);             // add chars to display list
           printf("\n");
         }
	 closesocket(s);
      }
   }
}


