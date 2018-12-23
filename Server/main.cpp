#define _WIN32_WINNT 0x501
#define PORT "1338"

#include "functii_socket.cpp"
#include <cstring>

///SERVER


int main(){

    while(1){

        initSockLibrary();
        SOCKET serverSocket, client1, client2;

        serverSocketBind(serverSocket, INADDR_ANY, PORT);

        serverSocketListen(serverSocket, 2);
        cout<<"Listening activated"<<endl;

        acceptClient(serverSocket, client1);
        cout<<"Client1 accepted!"<<endl;

        acceptClient(serverSocket, client2);
        cout<<"Client2 accepted!"<<endl;

        char inp1[512];
        char inp2[512];

        inp1[511] = '\0';
        inp2[511] = '\0';
        int result_sendTo1,  result_recvFrom1;
        int result_sendTo2,  result_recvFrom2;

        //trimit cifrurile secrete intre clienti
        result_recvFrom1 = recv(client1, inp1, 512, 0);
        result_recvFrom2 = recv(client2, inp2, 512, 0);

        inp1[result_recvFrom1] = '\0';
        inp2[result_recvFrom2] = '\0';

        //de la client 2 pentru client 1
        result_sendTo1 = send(client1, inp2, (int)strlen(inp2), 0);
        //de la client 1 pentru client 2
        result_sendTo2 = send(client2, inp1, (int)strlen(inp1), 0);

        cout<<"Client1:"<<inp1<<endl;
        cout<<"Client2:"<<inp2<<endl;
        cout<<"\n";

        inp1[511] = '\0';
        inp2[511] = '\0';

        //trimitere continua intre cei doi clienti.
        do{
            //ascult de la clienti
            result_recvFrom1 = recv(client1, inp1, 512, 0);
            result_recvFrom2 = recv(client2, inp2, 512, 0);

            inp1[result_recvFrom1] = '\0';
            inp2[result_recvFrom2] = '\0';

            result_sendTo1 = send(client1, inp2, (int)strlen(inp2), 0);
            result_sendTo2 = send(client2, inp1, (int)strlen(inp1), 0);

            cout<<"Client1:"<<inp1<<endl;
            cout<<"Client2:"<<inp2<<endl;
            cout<<"\n";
            inp1[511] = '\0';
            inp2[511] = '\0';


        }while( strcmp(inp1, "1") != 0 &&
                strcmp(inp2, "1") != 0 &&
                strcmp(inp1, "-1") != 0 &&
                strcmp(inp2, "-1") != 0);
        closesocket(serverSocket);
        closesocket(client1);
        closesocket(client2);
    }


	return 0;
}
