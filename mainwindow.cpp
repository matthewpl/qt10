#include "mainwindow.hpp"

#include <QTextCodec>
#include <QMenuBar>
#include <QFileDialog>
#include <QImage>
#include <QPaintEngine>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	QTextCodec::setCodecForTr (QTextCodec::codecForName ("UTF-8"));

	url.setUrl("http://blog.matthew.org.pl/");

	createActions();
	createMenus();
	createUi();
	createConnects();
}

MainWindow::~MainWindow()
{
}

void MainWindow::createActions()
{
	saveAsImageAction = new QAction(tr("Save as image..."), this);
	saveAsImageAction->setShortcut(QKeySequence::Save);
}

void MainWindow::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));

	fileMenu->addAction(saveAsImageAction);
}

void MainWindow::createUi()
{
	centralWidget = new QWidget(this);

	layout = new QGridLayout(centralWidget);

	backButton = new QPushButton("<", this);
	forwardButton = new QPushButton(">", this);
	reloadButton = new QPushButton("R", this);

	urlLine = new QLineEdit(url.toString(), this);

	webView = new QWebView(this);
	webView->setUrl(url);

	layout->addWidget(backButton, 0, 0, 1, 1);
	layout->addWidget(forwardButton, 0, 1, 1, 1);
	layout->addWidget(reloadButton, 0, 2, 1, 1);
	layout->addWidget(urlLine, 0, 3, 1, 1);
	layout->addWidget(webView, 1, 0, 1, 4);

	setCentralWidget(centralWidget);
}

void MainWindow::createConnects()
{
	connect(saveAsImageAction, SIGNAL(triggered()), this, SLOT(saveAsImage()));
	connect(backButton, SIGNAL(clicked()), webView, SLOT(back()));
	connect(forwardButton, SIGNAL(clicked()), webView, SLOT(forward()));
	connect(reloadButton, SIGNAL(clicked()), webView, SLOT(reload()));
	connect(urlLine, SIGNAL(returnPressed()), this, SLOT(newUrl()));
	connect(webView, SIGNAL(urlChanged(QUrl)), this, SLOT(urlChanged(QUrl)));
}

void MainWindow::saveAsImage()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save as image..."), QDir::homePath(), tr("PNG Image Files (*.png)"));

	QImage image(webView->page()->mainFrame()->contentsSize(), QImage::Format_ARGB32_Premultiplied); //"PNG"
	image.fill(QColor(Qt::white).rgba());

	QPainter painter(&image);

	QSize viewportSize = webView->page()->viewportSize();
	webView->page()->setViewportSize(webView->page()->mainFrame()->contentsSize());
	webView->page()->mainFrame()->render(&painter);
	painter.end();

	image.save(fileName, "PNG");

	webView->page()->setViewportSize(viewportSize);
}

void MainWindow::newUrl()
{
	url.setUrl(urlLine->text());

	webView->load(url);
}

void MainWindow::urlChanged(QUrl _url)
{
	url = _url;

	urlLine->setText(url.toString());
}
