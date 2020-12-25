#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netdb.h>
#include<sys/time.h>
#include<bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]){

    if(argc!=2){
        cerr<<"Missing port number"<<endl; 
        exit(0);
    }

    int port=atoi(argv[1]);
    char buffer[100];

    sockaddr_in welcomeSocket;
    welcomeSocket.sin_family=AF_INET;
    welcomeSocket.sin_port=htons(port);
    welcomeSocket.sin_addr.s_addr=htonl(INADDR_ANY);

    int welcomeSocketID=socket(AF_INET,SOCK_STREAM,0);
    if(welcomeSocketID<0){
        cerr<<"socket() failed"<<endl;
        exit(0);
    }

    int bindStatus=bind(welcomeSocketID,(sockaddr *) &welcomeSocket,sizeof(welcomeSocket));
    if(bindStatus<0){
        cerr<<"bind() failed"<<endl;
        exit(0);
    }

    cout <<"Waiting for a listener..."<<endl;

    listen(welcomeSocketID,1);
    
    sockaddr_in connectionSocket;
    socklen_t len=sizeof(connectionSocket);

    int connectionSocketID=accept(welcomeSocketID,(sockaddr *) &connectionSocket,& len);
    if(connectionSocketID<0){
        cerr<<"accept() failed"<<endl;
        exit(0);
    }
    cout<<"Client connected successfully!"<<endl;

    while(1){
        cout<<"Waiting for a message from client"<<endl;

        recv(connectionSocketID,&buffer,sizeof(buffer),0);
        if(strcmp(buffer,"exit")){
            cout<<"Session terminated"<<endl;
            break;
        }
        cout<<buffer<<endl;

        // char data[100];
        cin>>buffer;
        if(strcmp(buffer,"exit")){
            cout<<"Session terminated"<<endl;
            break;
        }

        send(connectionSocketID,&buffer,strlen(buffer),0);
    }

    close(connectionSocketID);
    close(welcomeSocketID);
}