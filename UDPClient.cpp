#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netdb.h>
#include<sys/time.h>
#include<bits/stdc++.h>
#include<stdio.h>

using namespace std;

int main(int argc, char* argv[]){
    
    if(argc!=3){
        cerr<<"Misiing host name and/or port number!"<<endl;
        exit(0);
    }

    char* hostname=argv[1];
    int port=atoi(argv[2]);
    char buffer[100];

    hostent* host=gethostbyname(hostname);

    sockaddr_in server;
    server.sin_family=AF_INET;
    server.sin_port=htons(port);
    server.sin_addr=**((in_addr **)(host->h_addr_list));

    int csid=socket(AF_INET,SOCK_DGRAM,0);
    socklen_t slen=sizeof(server);
    
    while(1){
        cout<<"Me: ";
        fgets(buffer,100,stdin);
        sendto(csid,(char*)&buffer,sizeof(buffer),0,(sockaddr*)&server,slen);

        if(buffer[0]=='E'&&buffer[1]=='X'&&buffer[2]=='I'&&buffer[3]=='T'&&buffer[4]=='\n')
            break;

        cout<<"Server: ";
        recvfrom(csid,(char*)&buffer,sizeof(buffer),0,(sockaddr*)&server,&slen);
        cout<<buffer;
        
        if(buffer[0]=='L'&&buffer[1]=='E'&&buffer[2]=='A'&&buffer[3]=='V'&&buffer[4]=='E'&&buffer[5]=='\n'){
            cout<<"You are removed from the chat!"<<endl;
            break;
        }
        if(buffer[0]=='E'&&buffer[1]=='X'&&buffer[2]=='I'&&buffer[3]=='T'&&buffer[4]=='\n'){
            cout<<"Server closed!"<<endl;
            break;
        }
    }

    close(csid);
}