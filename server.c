#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

#define PORTNO 10200

int main() {
	int n=1 ; 
	int buf[256] ; 
	int i; 

	//create a socket
	int sockfd,newsockfd;
	sockfd = socket(AF_INET,SOCK_STREAM,0);

	//define server address
	struct sockaddr_in seraddr,cliaddr; 
	seraddr.sin_family = AF_INET ; 
	seraddr.sin_addr.s_addr = inet_addr("127.0.0.1") ; 
	seraddr.sin_port = htons(PORTNO); 

	//bind the socket
	bind(sockfd,(struct sockaddr *)&seraddr,sizeof(seraddr)) ; 

	// Create a connection
	listen(sockfd,5) ; 

	int number ; 
	while(1) {

		// Accept a connection 
		int clilen = sizeof( clilen ) ; 
		newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr,&clilen );

		//fork to create a process
		if ( fork() == 0 ) {
			// If you're the child, you can now read/write
			n = read(newsockfd,&number,sizeof(number)) ; 
			int a[number] ,temp ; 

			n = read(newsockfd,a,sizeof(a)) ; 
			for(int i = 0 ; i < number - 1 ; i++) {
				for(int j = 0 ; j < number - i - 1; j++) {
					if( a[j] > a[j+1]) {
						temp  = a[j]; 
						a[j] = a[j+1];
						a[j+1] = temp; 
					}
				}
			}
			for(int i = 0 ; i < number ; i ++) 
				printf(" %d ",a[i]);
			n = write(newsockfd,a,sizeof(a)) ; 
			close(newsockfd) ;
			exit(0) ; 
		}
		else 
			close(newsockfd) ;
	}
}