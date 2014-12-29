#ifndef USEFULL_H_
#define USEFULL_H_

#include <qmessagebox.h>
#include <QApplication>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>
#include <qmessagebox.h>
#include <unistd.h>
#include <iostream>

namespace Usefull
{
    struct package
    {
      int mtype;
      char message[256];
      char name[30];
    };

    void error(const std::string& msg);
}

#endif
