#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QtWebKit>
#include <QMenu>
#include <QAction>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QUrl>

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	QWidget* centralWidget;
	QGridLayout* layout;

	QPushButton* backButton;
	QPushButton* forwardButton;
	QPushButton* reloadButton;

	QLineEdit* urlLine;

	QWebView* webView;

	QMenu* fileMenu;
	QAction* saveAsImageAction;

	QUrl url;

	void createActions();
	void createMenus();
	void createUi();
	void createConnects();

private slots:
	void saveAsImage();
	void newUrl();
	void urlChanged(QUrl url);
};

#endif // MAINWINDOW_HPP
