/* ---- A CONCURRENT SERVER performs mathematical operations as asked by the client and returns the result ---- */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>

#define PORTNO 19203

int main() {
	int sockfd,newsockfd,portno,clilen,n=1 ; 
	int buf[256] ; 
	struct sockaddr_in seraddr,cliaddr; 
	int i,value; 
	sockfd = socket(AF_INET,SOCK_STREAM,0) ; 
	seraddr.sin_family = AF_INET ; 
	seraddr.sin_addr.s_addr = inet_addr("127.0.0.1") ; 
	seraddr.sin_port = htons(PORTNO) ; 
	bind(sockfd,(struct sockaddr *)&seraddr,sizeof(seraddr)) ; 
	// Create a connection queue ; ignore child exit details and wait for the clients 
	listen(sockfd,5) ; 

	int number ; 
	while(1) {
		// Accept a connection 
		clilen = sizeof( clilen ) ; 
		newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr,&clilen ) ; 
		// Fork to create a process for this client and perform a test to see whether you're the parent or the child 
		if ( fork() == 0 ) {
			// If you're the child, you can now read/write to the client on newsockfd 
			int n1,n2,op,res = 999 ; 

			n = read(newsockfd,&n1,sizeof(n1)) ; 
			n = read(newsockfd,&n2,sizeof(n2)) ;
			n = read(newsockfd,&op,sizeof(op)) ;
			if(op == 1)
				res = n1+n2 ; 
			else if(op == 2)	
				res = n1 - n2 ; 
			else if (op == 3)
				res = n1*n2 ; 
			else if (op == 4)
				res = n1/n2 ;
			n = write(newsockfd,&res,sizeof(res)) ;  
			close(newsockfd) ;
			exit(0) ; 
		}
		else 
			close(newsockfd) ;
	}
}