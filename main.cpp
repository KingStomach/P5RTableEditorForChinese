#include "mainwindow.h"
#include <QApplication>

const std::string character_path("character.txt");
const std::string icon_path("icon.txt");
const std::string chat_titleName_table("chatTitleName.ctd");
const std::string chat_data_table("chatDataTable.ctd");

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();

	return 0;
}