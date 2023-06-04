#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ChatLibrary.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<ChatLibrary> m_library;

    void addCombobox(const std::vector<std::pair<uint8_t, std::string>>& icons, int row, int idxIcon);
};
#endif // MAINWINDOW_H
