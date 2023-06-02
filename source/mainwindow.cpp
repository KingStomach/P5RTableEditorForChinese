#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "ChatLibraryReader.h"
#include "ChatReader.h"

const std::string character_path("character.txt");
const std::string icon_path("icon.txt");
const std::string chat_titleName_table("chatTitleName.ctd");
const std::string chat_data_table("chatDataTable.ctd");

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto library = ChatLibraryReader(character_path, icon_path).readData();
    auto chats = ChatReader(chat_titleName_table, chat_data_table, library).readData();
    ui->tableWidget->setRowCount(chats.size());
    for (int i = 0; i < chats.size();i++)
    {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(chats[i].icon)));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(chats[i].name)));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

