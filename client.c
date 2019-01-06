#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>

int main() {
	int n =1 ; 

	// Create a socket
	int sockfd; 
	sockfd = socket(AF_INET , SOCK_STREAM, 0);

	// define the socket
	struct sockaddr_in address;
	address.sin_family = AF_INET ; 
	address.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	address.sin_port = htons(10200);

	//connect the socket
	int len = sizeof(address); 
	int result = connect(sockfd, (struct sockaddr *)&address, len); 

	//check for error with the connection
	if(result == -1 ) {
		perror(" \n CLIENT ERROR ") ; 
		exit(1) ; 
	}

	//read and write
	int number ;  
	printf( " \n ENTER number of elements in the array -> \t "); 
	scanf("%d",&number) ; 

	int array[number],buf[number] ;
	printf(" Enter the elements of the array -> \t"); 
	for(int i = 0 ; i < number ; i++)
		scanf("%d",&array[i]); 

	write(sockfd, &number, sizeof(number));
	write(sockfd,array,sizeof(array)) ;  

	printf(" SORTED ARRAY sent back from the sever is ... - ") ;
	read(sockfd, buf, sizeof(buf)) ; 
	for(int i = 0 ; i < number ; i++ )
		printf(" %d ", buf[i]) ;  
		
	close(sockfd) ; 
}