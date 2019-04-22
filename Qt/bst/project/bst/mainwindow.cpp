#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QInputDialog>
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
    //ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
    this->setWindowTitle("2D-QPainter: Binary Search Tree");
    this->resize(800, 600);

    this->createActions();
    this->createToolBar();

    renderArea = new RenderArea(this);
    this->setCentralWidget(renderArea);
}

MainWindow::~MainWindow()
{
    //delete ui;
}

int MainWindow::openInputDialog(const QString &label)
{
    bool ok;
    int i = QInputDialog::getInt(this, tr("Enter Value"), label, 0, 0, 199, 1, &ok);
    if (ok)
       return (i);
    return (-1);
}

void MainWindow::addNewNode()
{
    int nodeVal = 0;
    nodeVal = this->openInputDialog("Insert Node Value");
    qDebug() << "addNewNode()="<<nodeVal;
}

void MainWindow::deleteNode()
{
    int nodeVal = 0;
    nodeVal = this->openInputDialog("Delete Node Value");
    qDebug() << "deleteNode()="<<nodeVal;
}

void MainWindow::createActions()
{
    addNodeAction = new QAction(tr("&Add"), this);
    addNodeAction->setIcon(QIcon(":/resources/add.png"));
    addNodeAction->setIconText(tr("Add"));
    addNodeAction->setShortcut(tr("Ctrl+N"));
    addNodeAction->setToolTip("Insert BST Node");
    connect(addNodeAction, SIGNAL(triggered()), this, SLOT(addNewNode()));

    deleteNodeAction = new QAction(tr("&Delete"), this);
    deleteNodeAction->setIcon(QIcon(":/resources/delete.png"));
    deleteNodeAction->setIconText(tr("Delete"));
    deleteNodeAction->setShortcut(tr("Ctrl+D"));
    deleteNodeAction->setToolTip("Delete BST Node");
    connect(deleteNodeAction, SIGNAL(triggered()), this, SLOT(deleteNode()));
}

void MainWindow::createToolBar()
{
    toolBar = this->addToolBar(tr("&Tool"));
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar->addAction(addNodeAction);
    toolBar->addAction(deleteNodeAction);
}
