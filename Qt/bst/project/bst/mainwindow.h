#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "renderarea.h"
#include "bst.h"

class RenderArea;

//namespace Ui {
//class MainWindow;
//}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
     int openInputDialog(const QString &label);

private slots:
    void addNewNode();
    void deleteNode();

private:
    void createActions();
    void createToolBar();

//    Ui::MainWindow *ui;
    RenderArea *renderArea;
    QToolBar *toolBar;
    QAction *addNodeAction;
    QAction *deleteNodeAction;
    QAction *clearAllNodesAction;

    //bst_t *m_bst;
};

#endif // MAINWINDOW_H
