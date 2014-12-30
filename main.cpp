#include "login.h"
#include "chat.h"

char names[100][30];
int sd;
int currentlyOn;

struct threadHelp
{
    int sockd;
    Chat* c;
};

void* receiving(void* args)
{
    struct package buffer;
    struct threadHelp help = *(threadHelp*) args;
    int sockd = help.sockd;
    Chat* c = help.c;

    while (1)
    {
        int retCode;
        if ((retCode = recv(sockd, &buffer, sizeof(struct package), 0)) == -1)
            error("Error receiving the message.\n");
        else if (retCode == 0)
        {
            close(sd);
            break;
        }
        else
        {
            if (buffer.mtype == 0)
            {        
                std::string nameStr(buffer.name);
                std::string messageStr(buffer.message);
                c->setMessage(nameStr + ": " + messageStr);
            }
            else if (buffer.mtype == 1)
            {
                strcpy(names[currentlyOn], buffer.name);               
                currentlyOn++;
                c->clearOnline();
                c->populateOnline(names, currentlyOn);
            }
            else if (buffer.mtype == 2)
            {
                int i;
                for (i = 0; i < currentlyOn; i++){
                    if (strcmp(names[i], buffer.name) == 0)
                    {
                        int j;
                        for (j = i; j < currentlyOn - 1; j++)
                            strcpy(names[j], names[j + 1]);
                        strcpy(names[j], "");
                        currentlyOn--;
                        break;
                    }
                }

                c->clearOnline();
                c->populateOnline(names, currentlyOn);
            }
        }
    }
    exit(0);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    char name[30];
    char ip[20];
    struct package mainInfo;
    struct sockaddr_in server_address;
    pthread_t receiver;

    memset(&server_address, 0, sizeof(server_address));
    memset(&name, 0, sizeof(name));
    memset(&ip, 0, sizeof(ip));
    memset(&names, 0, sizeof(names));

    Chat c(&sd, &mainInfo, name);
    Login l(ip, name);
    l.show();
    a.exec();

    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd < 0)
        error("Error opening socket.\n");

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(6666);

    if (strcmp(ip, "") == 0)    //then we are connecting to the main server
    {
        if (strcmp(name, "") == 0)  //if the name is also empty it's clear that the user pressed X
            exit(0);
        else
            if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr.s_addr) < 0)
                error("Error on inet_pton.\n");
    }
    else                        //we are connecting to the specified ip
    {
        if (inet_pton(AF_INET, ip, &server_address.sin_addr.s_addr) < 0)
            error("Error on inet_pton.\n");
    }

    if (connect(sd, (struct sockaddr*) &server_address, sizeof(server_address)) < 0)
        error("Error on connect.\n");

    mainInfo.mtype = 1;
    strcpy(mainInfo.name, name);

    struct threadHelp help;
    help.c = &c;
    help.sockd =sd;

    pthread_create(&receiver, NULL, &receiving, &help);

    if (send(sd, &mainInfo, sizeof(struct package), 0) < 0)
        error("Error sending the message");

    if (strcmp(name, "") != 0)
    {
        mainInfo.mtype = 0;
        c.show();
        a.exec();
    }

    return 0;
}
