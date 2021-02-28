#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netdb.h>
#include<sys/time.h>
#include<bits/stdc++.h>
#include<stdio.h>
#include<chrono>
#include<thread>
#include<fcntl.h>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

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

    listen(welcomeSocketID,100);
    
    // int status = fcntl(welcomeSocketID, F_SETFL, fcntl(welcomeSocketID, F_GETFL, 0) | O_NONBLOCK);
    // if (status == -1){
    //     cerr<<"fcntl() failed"<<endl;
    //     exit(0);
    // }

    // int curr=-1;
    // set<int> present;
    // sockaddr_in cs[100];
    // socklen_t len[100];
    // int csid[100];
    
    // do{
    //     curr++;
    //     len[curr]=sizeof(cs[curr]);
    //     csid[curr]=accept(welcomeSocketID,(sockaddr*)&cs[curr],&len[curr]);
    //     cerr<<csid[curr]<<" ";
    // }while(csid[curr]>=0&&curr<100);
    
    sockaddr_in cs;
    socklen_t len=sizeof(cs);
    int csid=accept(welcomeSocketID,(sockaddr*)&cs,&len);

    cout<<"Client connected successfully!"<<endl;

    while(1){
        cout<<"Me: ";
        char data[100];
        fgets(data,100,stdin);

        // for(int i=0;i<=curr;i++)
        //     send(csid[i],data,sizeof(data),0);
        send(csid,data,sizeof(data),0);
        
        if(data[0]=='E'&&data[1]=='X'&&data[2]=='I'&&data[3]=='T'&&data[4]=='\n'){
            cout<<"Session terminated"<<endl;
            break;
        }

        // for(int i=0;i<curr;i++){
        //     cout<<"Client "<<i<<": ";
        //     recv(csid[i],(char*)&buffer,sizeof(buffer),0);
        //     cout<<buffer<<endl;
        // }

        // recv(csid,(char*)&buffer,sizeof(buffer),0);

        cout<<"Client: ";
        recv(csid,(char*)&buffer,sizeof(buffer),0);
        cout<<buffer;
        if(buffer[0]=='E'&&buffer[1]=='X'&&buffer[2]=='I'&&buffer[3]=='T'&&buffer[4]=='\n'){
            cout<<"Session terminated"<<endl;
            break;
        }

        // cout<<"Client 2: ";
        // recv(csID2,(char*)&buffer,sizeof(buffer),0);
        // cout<<buffer;
        // if(buffer[0]=='E'&&buffer[1]=='X'&&buffer[2]=='I'&&buffer[3]=='T'&&buffer[4]=='\n'){
        //     cout<<"Session terminated"<<endl;
        //     break;
        // }
    }

    // for(int i=0;i<=curr;i++)
    //     close(csid[i]);
    close(csid);
    // close(csID2);
    close(welcomeSocketID);
}