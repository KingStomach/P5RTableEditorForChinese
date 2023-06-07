#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ChatLibrary.h"
#include "CTD.h"
#include <QMainWindow>
#include <qset.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void init();

private:
    Ui::MainWindow *ui;
    ChatLibrary m_library;
    CTD m_name_table;
    CTD m_icon_table;
    QSet<int> m_editItem;

    void saveCTD(bool checked);
    void addCombobox(const std::vector<std::pair<uint8_t, std::string>>& icons, int row, int idxIcon);
};
#endif // MAINWINDOW_H
