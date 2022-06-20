#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
int main()
{
	char buffer[256]="you have reached the server";
        int server_socket;
        server_socket=socket(AF_INET, SOCK_STREAM,0);
        if(server_socket==-1)
        {
        printf("socket creation failed");
        exit(0);
        }
        //socklen_t clilen;
        struct sockaddr_in server_address,client_address;
        bzero(&server_address,sizeof(server_address));
        server_address.sin_family=AF_INET;
        server_address.sin_port=htons(9001);
        server_address.sin_addr.s_addr=htonl(INADDR_ANY);

	// bind function
	 if(bind(server_socket,(struct sockaddr *) &server_address, sizeof(server_address))!=0)
	 {
	 printf("bind failed");
	 exit(0);
	 }
	//listen function 
        if (listen(server_socket,5)<0)
        {
        printf("listen failed");
        exit(0);
        }
       
        //accept function
        int len=sizeof(client_address);
        int client_socket= accept(server_socket,(struct sockaddr*) &client_address,&len);
        if(client_socket<0)
        {
          printf("Accept failed");
          exit(0);
	}
        while(1)
        {
        	        bzero(buffer,sizeof(buffer));
        	        read(client_socket,buffer,256);
			printf("Client: %s",buffer);
			bzero(buffer,256);
			int n=0;
			 printf("server :");
			while ((buffer[n++] = getchar()) != '\n')
                        ;
			write(client_socket,buffer,sizeof(buffer));
			int i=strncmp("bye",buffer,3);
			if(i==0)
			{
				break;
			}
	}
		close(server_socket);
        return 0;
}

