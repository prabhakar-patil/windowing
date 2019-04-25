#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QInputDialog>
#include <QGridLayout>

#include "bst.h"

bst_t *m_bst=NULL;

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

    //Create BST Data Structure
    m_bst = ::create_bst();
    Q_ASSERT(m_bst);
    ::insert_bst(m_bst, 100);
    ::insert_bst(m_bst, 50);
    ::insert_bst(m_bst, 25);
    ::insert_bst(m_bst, 75);
    ::insert_bst(m_bst, 65);
    ::insert_bst(m_bst, 150);
    ::insert_bst(m_bst, 125);
    ::insert_bst(m_bst, 130);
    ::insert_bst(m_bst, 175);

    printf("IN-ORDER  : ");
    ::inorder(m_bst);
    printf("PRE-ORDER : ");
    ::preorder(m_bst);
    printf("POST-ORDER: ");
    ::postorder(m_bst);
}

MainWindow::~MainWindow()
{
    //delete ui;
    Q_ASSERT(::destroy_bst(&m_bst) == BST_SUCCESS && m_bst == NULL);
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
