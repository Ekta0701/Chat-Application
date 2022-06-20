#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
int main()
{
        char buffer[256];
        int client_socket;
        client_socket=socket(AF_INET, SOCK_STREAM,0);
        if(client_socket<0)
        {
        printf("error in opening socket");
        exit(0);
        }
        struct sockaddr_in server_address;
        bzero(&server_address,sizeof(server_address));
        server_address.sin_family=AF_INET;
        server_address.sin_port=htons(9001);
        server_address.sin_addr.s_addr=inet_addr("127.0.0.1");

	//connect function	
	int connection_status= connect(client_socket, (struct sockaddr *) &server_address, sizeof(server_address));
        //char server_resp[256];
        if(connection_status<0)
        {
                printf("error here");
        }
        
        //recv(client_socket, &server_resp, sizeof(server_resp),0);
        // printf("%s", server_resp);
        while(1)
        {
          bzero(buffer,sizeof(buffer));
          int n;
           printf("client : ");
            n = 0;
            while ((buffer[n++] = getchar()) != '\n')
            ;
	  write(client_socket,buffer,sizeof(buffer));
          bzero(buffer,sizeof(buffer));
	  read(client_socket,buffer,sizeof(buffer));
	  printf("Server: %s",buffer);
	  int i=strncmp("bye",buffer,3);
	  if(i==0)
	   {
	      break;
	   }
        }
        close(client_socket);
	return 0;
}