/* PMSOCK.C--PM Sockets interface to IBM TCP/IP
 *
 * This file corresponds to version 1.0 of the PM Sockets specification,
 * which is based on version 1.1 of the Windows Sockets
 * specification.  
 *
 * This file includes parts which are Copyright (c) 1982-1986 Regents
 * of the University of California.  All rights reserved.  The
 * Berkeley Software License Agreement specifies the terms and
 * conditions for redistribution.
 *
 * Change log:
 *
 * Fri Sept 2 1994 Don Loflin
 *      Changing to be less direct
 * Sun Aug 21 1994 Don Loflin
 *	Redid to use IBM TCP routines directly
 * Fri Aug 11 1994 Don Loflin (loflin@mail.utexas.edu)
 * 	Created PMSOCK.C from PMSOCK.H
 * Mon Aug 8 1994  Don Loflin (loflin@mail.utexas.edu)
 *	Created PMSOCK.H from WINSOCK.H
 */

#include "pmsock.h"

/* IBM routines used here, from tcpip/include/sys/socket.h */
extern int soclose( int );
extern int sock_errno( void );
extern int ioctl(int, int, char *, int);

#if 0
int __WSAFDIsSet(SOCKET fd, fd_set *set)
{
  int i = set->fd_count;

   while (i--)
       if (set->fd_array[i] == fd)
           return 1;

   return 0;

}

#endif
/* Socket functions - IBM compat. routines are commented out */
#undef IBMSOCK

#ifdef IBMSOCK
SOCKET accept (SOCKET s, struct sockaddr *addr, 
                          int *addrlen);

int bind (SOCKET s, const struct sockaddr *addr, int namelen);
#endif

int closesocket (SOCKET s)
{
/*   return (soclose(s)); */
}

#ifdef IBMSOCK
int connect (SOCKET s, const struct sockaddr *name, int namelen);
#endif
int ioctlsocket (SOCKET s, long cmd, u_long *argp)
{
   /* WinSock ioctlsocket only allows param to be u_long, so just pass that */
   /*size to IBM ioctl */
  /* return(ioctl(s, cmd, (char *) argp, sizeof(u_long)) );*/
}

#ifdef IBMSOCK
int getpeername (SOCKET s, struct sockaddr *name,
                            int * namelen);

int getsockname (SOCKET s, struct sockaddr *name,
                            int * namelen);

int getsockopt (SOCKET s, int level, int optname,
                           char *optval, int *optlen);

u_long PASCAL FAR htonl (u_long hostlong);

u_short PASCAL FAR htons (u_short hostshort);

unsigned long PASCAL FAR inet_addr (const char FAR * cp);

char FAR * PASCAL FAR inet_ntoa (struct in_addr in);

int PASCAL FAR listen (SOCKET s, int backlog);

u_long PASCAL FAR ntohl (u_long netlong);

u_short PASCAL FAR ntohs (u_short netshort);

int PASCAL FAR recv (SOCKET s, char FAR * buf, int len, int flags);

int PASCAL FAR recvfrom (SOCKET s, char FAR * buf, int len, int flags,
                         struct sockaddr FAR *from, int FAR * fromlen);

#endif
#ifndef USEIBMSELECT
int PASCAL FAR select (int nfds, fd_set FAR *readfds, fd_set FAR *writefds,
                       fd_set FAR *exceptfds, const struct timeval FAR *timeout) 
{
// put pmsock fd_set's into ibm fd_set's, then  
} 
#endif
#ifdef IBMSOCK
int PASCAL FAR send (SOCKET s, const char FAR * buf, int len, int flags);

int PASCAL FAR sendto (SOCKET s, const char FAR * buf, int len, int flags,
                       const struct sockaddr FAR *to, int tolen);

int PASCAL FAR setsockopt (SOCKET s, int level, int optname,
                           const char FAR * optval, int optlen);

int PASCAL FAR shutdown (SOCKET s, int how);

SOCKET PASCAL FAR socket (int af, int type, int protocol);

/* Database function prototypes */

struct hostent FAR * PASCAL FAR gethostbyaddr(const char FAR * addr,
                                              int len, int type);

struct hostent FAR * PASCAL FAR gethostbyname(const char FAR * name);

int PASCAL FAR gethostname (char FAR * name, int namelen);

struct servent FAR * PASCAL FAR getservbyport(int port, const char FAR * proto);

struct servent FAR * PASCAL FAR getservbyname(const char FAR * name,
                                              const char FAR * proto);

struct protoent FAR * PASCAL FAR getprotobynumber(int proto);

struct protoent FAR * PASCAL FAR getprotobyname(const char FAR * name);

#endif /* IBMSOCK */
/* Microsoft Windows Extension function prototypes */

int WSAStartup(WORD wVersionRequired, LPWSADATA lpWSAData)
{
   return(sock_init());
}


int WSACleanup(void)
{
/* null - IBM TCP doesn't require anything */
}

void WSASetLastError(int iError)
{
/* not allowed */
}

int WSAGetLastError(void)
{
/*   return (sock_errno()); */
}

/*
 * Aync calls optional
 */
#undef PMSAAsync
#ifdef PMSAAsync 

BOOL PASCAL FAR WSAIsBlocking(void);

int PASCAL FAR WSAUnhookBlockingHook(void);

FARPROC PASCAL FAR WSASetBlockingHook(FARPROC lpBlockFunc);

int PASCAL FAR WSACancelBlockingCall(void);

HANDLE PASCAL FAR WSAAsyncGetServByName(HWND hWnd, u_int wMsg,
                                        const char FAR * name, 
                                        const char FAR * proto,
                                        char FAR * buf, int buflen);

HANDLE PASCAL FAR WSAAsyncGetServByPort(HWND hWnd, u_int wMsg, int port,
                                        const char FAR * proto, char FAR * buf,
                                        int buflen);

HANDLE PASCAL FAR WSAAsyncGetProtoByName(HWND hWnd, u_int wMsg,
                                         const char FAR * name, char FAR * buf,
                                         int buflen);

HANDLE PASCAL FAR WSAAsyncGetProtoByNumber(HWND hWnd, u_int wMsg,
                                           int number, char FAR * buf,
                                           int buflen);

HANDLE PASCAL FAR WSAAsyncGetHostByName(HWND hWnd, u_int wMsg,
                                        const char FAR * name, char FAR * buf,
                                        int buflen);

HANDLE PASCAL FAR WSAAsyncGetHostByAddr(HWND hWnd, u_int wMsg,
                                        const char FAR * addr, int len, int type,
                                        char FAR * buf, int buflen);

int PASCAL FAR WSACancelAsyncRequest(HANDLE hAsyncTaskHandle);

int PASCAL FAR WSAAsyncSelect(SOCKET s, HWND hWnd, u_int wMsg,
                               long lEvent);

#endif /* PMSAAsync */


