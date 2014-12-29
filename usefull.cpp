#include "usefull.h"

namespace Usefull
{
    void error(const std::string& msg)
    {
        QMessageBox::critical(NULL, "Error", QString::fromStdString(msg));
        exit(1);
    }
}
