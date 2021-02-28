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

int main(int argc, char *argv[]){

    if(argc!=3){
        cout<<"Missing host name and/or port number"<<endl;
        exit(0);
    }

    char* serverName=argv[1];
    int port=atoi(argv[2]);
    char buffer[100];

    hostent* host=gethostbyname(serverName);

    sockaddr_in server;
    server.sin_family=AF_INET;
    server.sin_port=htons(port);
    server.sin_addr=**((in_addr **)(host->h_addr_list));

    int myID=socket(AF_INET,SOCK_STREAM,0);

    int connectSatus=connect(myID,(sockaddr*)&server,sizeof(server));
    if(connect<0){
        cerr<<"connect() failed"<<endl;
        exit(0);
    }
    cout<<"Connection successful!"<<endl;

    while(1){

        cout<<"Server: ";
        recv(myID,(char*)&buffer,sizeof(buffer),0);
        cout<<buffer;
        if(buffer[0]=='E'&&buffer[1]=='X'&&buffer[2]=='I'&&buffer[3]=='T'&&buffer[4]=='\n'){
            cout<<"Session terminated"<<endl;
            break;
        }

        cout<<"Me: ";
        char data[100];
        fgets(data,100,stdin);
        send(myID,(char*)data,sizeof(data),0);
        if(data[0]=='E'&&data[1]=='X'&&data[2]=='I'&&data[3]=='T'&&data[4]=='\n'){
            cout<<"Session terminated"<<endl;
            break;
        }
    }

    close(myID);
}