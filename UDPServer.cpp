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

    if(argc!=2){
        cerr<<"Port number missing!"<<endl;
        exit(0);
    }

    int port=atoi(argv[1]);
    char buffer[100];

    sockaddr_in server,client;
    server.sin_family=AF_INET;
    server.sin_port=htons(port);
    server.sin_addr.s_addr=htonl(INADDR_ANY);

    int ssid=socket(AF_INET,SOCK_DGRAM,0);
    if(ssid<0){
        cerr<<"socket() failed"<<endl;
        exit(0);
    }

    int bindstatus=bind(ssid,(sockaddr*)&server,sizeof(server));
    if(bindstatus<0){
        cerr<<"bind() failed"<<endl;
        exit(0);
    }

    cerr<<"Waiting for a connection..."<<endl;
    
    while(1){
        cerr<<"Client :";
        socklen_t clen=sizeof(client);
        recvfrom(ssid,(char*)&buffer,sizeof(buffer),0,(sockaddr*)&client,&clen);

        cout<<buffer;

        if(buffer[0]=='E'&&buffer[1]=='X'&&buffer[2]=='I'&&buffer[3]=='T'&&buffer[4]=='\n'){
            cout<<"Client left the chat"<<endl;
            continue;
        }
        
        cout<<"Me: ";

        fgets(buffer,100,stdin);
        sendto(ssid,(char*)&buffer,sizeof(buffer),0,(sockaddr*)&client,clen);
        if(buffer[0]=='L'&&buffer[1]=='E'&&buffer[2]=='A'&&buffer[3]=='V'&&buffer[4]=='E'&&buffer[5]=='\n')
            cout<<"Client is removed from the chat!"<<endl;
        if(buffer[0]=='E'&&buffer[1]=='X'&&buffer[2]=='I'&&buffer[3]=='T'&&buffer[4]=='\n'){
            cout<<"Server closed!"<<endl;
            break;
        }
    }

    close(ssid);
}