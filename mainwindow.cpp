#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string.h>
#include <bits/stdc++.h>
#include <QTextStream>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_ShowWithoutActivating);
    QPushButton *greekButtons[96];
    for(int i = 0; i < 96; i++){
        QString buttonName = "pushButton_" + QString::number(i + 1);
        greekButtons[i] = MainWindow::findChild<QPushButton*>(buttonName);
        connect(greekButtons[i], SIGNAL(clicked()), this, SLOT(buttonClicked()));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::buttonClicked(){
    QPushButton *button = (QPushButton *) sender();

    //QString windowID = getCommandOutput("xdotool search --name \"Google Sheets\"");
    QString windowID = "67110440";
    QTextStream out(stdout);
    out << button->text();
    QString command = "xdotool windowfocus " + windowID + " ; xdotool type --window " + windowID + " \"" + button->text() + "\"";
    QByteArray commandArray = command.toLocal8Bit();
    const char *charCommand = commandArray.data();
    system(charCommand);



}
QString MainWindow::getCommandOutput(QString command){

    QString output;
    FILE * stream;
    char buffer[256];
    //command.append(" 2>&1");
    QByteArray commandArray = command.toLocal8Bit();
    QTextStream out(stdout);
    out << commandArray.data() << endl;
    stream = popen(commandArray.data(), "r");

    if(stream){
    while(!feof(stream))
        if(fgets(buffer, 256, stream) != NULL) output.append(buffer);
    pclose(stream);
    }
    out << output;
    return output;
}


