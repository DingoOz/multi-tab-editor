#include <QApplication>
#include <QStyleFactory>
#include <QDir>
#include "src/MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    app.setApplicationName("Multi-Tab Editor");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("TextEditor");
    app.setOrganizationDomain("texteditor.local");
    
    MainWindow window;
    window.show();
    
    return app.exec();
}