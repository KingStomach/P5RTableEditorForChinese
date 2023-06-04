#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "ChatLibrary.h"
#include "IReader.h"
#include <QComboBox>

const std::string character_path("character.txt");
const std::string icon_path("icon.txt");
const std::string chat_titleName_table("chatTitleName.ctd");
const std::string chat_data_table("chatDataTable.ctd");

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), m_library(std::make_unique<ChatLibrary>(ChatLibraryReader::read(std::ifstream(character_path), std::ifstream(icon_path))))
{
    ui->setupUi(this);
    auto chats = ChatReader::read(std::ifstream(chat_titleName_table, std::ios::binary), std::ifstream(chat_data_table, std::ios::binary), *m_library);
    ui->tableWidget->setRowCount(chats.size());

    for (int i = 0; i < chats.size(); i++)
    {
        addCombobox(m_library->getIconList(), i, chats[i].idxIcon);
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(chats[i].name)));
    }
    int y = 0;
}

void MainWindow::addCombobox(const std::vector<std::pair<uint8_t, std::string>>& icons, int row, int idxIcon)
{
    QComboBox* combox = new QComboBox();
    for (int i = 0; i < icons.size(); i++)
    {
        combox->insertItem(i, QString::fromStdString(icons[i].second), QVariant::fromValue(icons[i].first));
    }
    ui->tableWidget->setCellWidget(row, 0, combox);
    combox->setCurrentIndex(combox->findData(idxIcon));
}

MainWindow::~MainWindow()
{
    delete ui;
}

