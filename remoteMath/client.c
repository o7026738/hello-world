#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>

int main() {
	int len, result, sockfd, n =1 ; 
	struct sockaddr_in address; 
	// Create a socket for the client 
	sockfd = socket(AF_INET , SOCK_STREAM, 0); 
	// Name the socket as agreed with the server 
	address.sin_family = AF_INET ; 
	address.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	address.sin_port = htons(19203);
	len = sizeof(address); 

	// Connect the socket to the server's socket 
	result = connect(sockfd, (struct sockaddr *)&address, len); 
	if(result == -1 ) {
		perror(" \n CLIENT ERROR ") ; 
		exit(1) ; 
	}


	int n1,n2,op,res ; 
	printf( " \n ENTER numbers -> \t "); 
	scanf("%d",&n1) ;
	scanf("%d",&n2) ; 
	printf( " \n ENTER number for operation -> 1.ADD 2.SUBTRACT 3.MULTIPLY 4.DIVIDE :- "); 
	scanf("%d",&op) ;
	write(sockfd, &n1, sizeof(int));
	write(sockfd,&n2,sizeof(int)) ;  
	write(sockfd,&op,sizeof(int));
	read(sockfd, &res, sizeof(int)) ;  
	if ( res != 999)
		printf(" RESULT sent back from the sever is ... -  %d ",res) ;
	else 
		printf(" Invalid operation run again ");
	close(sockfd) ; 
}