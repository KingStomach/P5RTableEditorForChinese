#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "ChatLibrary.h"
#include "IReader.h"
#include "IWriter.h"
#include <QComboBox>

const std::string character_path("character.txt");
const std::string icon_path("icon.txt");
const std::string chat_titleName_table("chatTitleName.ctd");
const std::string chat_data_table("chatDataTable.ctd");

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), m_library(ChatLibraryReader::read(std::ifstream(character_path), std::ifstream(icon_path))),
    m_name_table(CTDReader::read(std::ifstream(chat_titleName_table, std::ios::binary))),
    m_icon_table(CTDReader::read(std::ifstream(chat_data_table, std::ios::binary)))
{
    ui->setupUi(this);
}

void MainWindow::init()
{
    auto chats = ChatReader::read(m_name_table, m_icon_table, m_library);
    ui->tableWidget->setRowCount(chats.size());

    for (int i = 0; i < chats.size(); i++)
    {
        addCombobox(m_library.getIconList(), i, chats[i].idxIcon);
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(chats[i].name)));
    }
    connect(ui->tableWidget, &QTableWidget::cellChanged, this, [this](int row, int column)
        {
            if (column != 1)
                return;
            this->m_editItem.insert(row);
        });
    connect(ui->save, &QAbstractButton::clicked, this, &MainWindow::saveCTD);
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

void MainWindow::saveCTD(bool checked)
{
    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        CTD::Data data(2);
        auto* p = ui->tableWidget->cellWidget(i, 0);
        data[1] = reinterpret_cast<QComboBox*>(ui->tableWidget->cellWidget(i, 0))->currentData().toInt();
        m_icon_table.replace(data, i);
    }

    for (int row : m_editItem)
    {
        std::string data = ui->tableWidget->item(row, 1)->text().toStdString();
        auto decodeData = m_library.encodeName(data);
        m_name_table.replace(decodeData, row);
    }

    CTDWrite::write(std::ofstream("output/" + chat_titleName_table, std::ios::binary), m_name_table);
    CTDWrite::write(std::ofstream("output/" + chat_data_table, std::ios::binary), m_icon_table);
    return;
}

MainWindow::~MainWindow()
{
    delete ui;
}

