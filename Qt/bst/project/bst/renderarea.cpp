#include "renderarea.h"

#include <QPainter>
#include <QString>
#include "bst.h"

#define DEF_NODE_WIDTH  (80)
#define DEF_NODE_HEIGHT (50)

extern bst_t *m_bst;

RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
    , m_nodeWidth(DEF_NODE_WIDTH)
    , m_nodeHeight(DEF_NODE_HEIGHT)
{
    this->setBackgroundRole(QPalette::Base);
    this->setAutoFillBackground(true);
}

//void RenderArea::paintEvent(QPaintEvent * /* event */)
//{
//    QPainter painter(this);
//    painter.setRenderHint(QPainter::Antialiasing, true);
//    painter.setPen(QPen(Qt::black)); //, 12, Qt::DashDotLine, Qt::RoundCap));
//    painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));

//    int ellipseWidth = 80;
//    int ellipsHeight = 50;
//    painter.drawEllipse(80, 80, ellipseWidth, ellipsHeight);
//    int width = this->width();
//    painter.drawText(95, 85, 40, 40, Qt::AlignCenter, QString::number(width));

//    painter.drawEllipse(160, 160, ellipseWidth, ellipsHeight);
//    int height = this->height();
//    painter.drawText(175, 165, 40, 40, Qt::AlignCenter, QString::number(height));

//    painter.drawLine((80+ellipseWidth/2), (80+ellipsHeight), (160+ellipseWidth/2), 160);
//    //painter.setPen(QPen(Qt::green, 12));
//    //painter.drawPoint((80+25), (80+30));
//    //painter.drawPoint((160+25), (160));

//}

//void RenderArea::paintEvent(QPaintEvent * /* event */)
//{
//    QPainter painter(this);
//    painter.setRenderHint(QPainter::Antialiasing, true);
//    painter.setPen(QPen(Qt::black)); //, 12, Qt::DashDotLine, Qt::RoundCap));
//    painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));


//    int width = this->width();
//    int height = this->height();
//    int centerX = width/2 - m_nodeWidth/2;

//    this->drawNode(painter, QPoint(centerX,80), width);
//    this->drawNode(painter, QPoint(centerX+80,160), height);
//    this->connectNode(painter, QPoint(centerX,80), QPoint(centerX+80,160));
//}

//void RenderArea::paintEvent(QPaintEvent * /* event */)
//{
//    QPainter painter(this);
//    painter.setRenderHint(QPainter::Antialiasing, true);
//    painter.setPen(QPen(Qt::black)); //, 12, Qt::DashDotLine, Qt::RoundCap));
//    painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));


//    int width = this->width();
//    //int height = this->height();
//    int centerX = width/2 - m_nodeWidth/2;
//    int xDiff = 80;
//    int yDiff = 80;
//    int currentX = centerX;
//    int currentY = yDiff;
//    bool prevLeft = false;

//    bst_node_t *run = m_bst->root_node;
//    stack_t *st = ::create_stack();
//    res_t res = STACK_SUCCESS;
//    Q_ASSERT(run);

//    //printf("[beg]<->");

//    while(TRUE)
//    {
//        //walk through LST,  keep printing and pushing
//        while(run != NULL)
//        {
//            //printf("[%d]<->", run->data);
//            this->drawNode(painter, QPoint(currentX,currentY), run->data);
//            push(st, run);
//            run = run->left;
//            currentX = currentX - xDiff;
//            currentY = currentY + yDiff;
//        }
//        currentX = currentX + xDiff;
//        currentY = currentY - yDiff;

//        //check if each and every node is processed
//        //if yes, break the loop
//        res = pop(st, &run);
//        Q_ASSERT(res == STACK_SUCCESS || res == STACK_EMPTY);
//        if(res == BST_EMPTY)
//            break;
//        currentX = (run == m_bst->root_node) ?
//                    (currentX + xDiff):
//                    (run == run->parent->right) ? (currentX - xDiff):(currentX + xDiff);
//        currentY = currentY - yDiff;

//        //if no, walk through RST
//        run = run->right;
//        currentX = currentX + xDiff;
//        currentY = currentY + yDiff;
//    }
//}

void RenderArea::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::black)); //, 12, Qt::DashDotLine, Qt::RoundCap));
    painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));


    int width = this->width();
    //int height = this->height();
    int centerX = width/2 - m_nodeWidth/2;
    int xDiff = 80;
    int yDiff = 80;
    int currentX = centerX;
    int currentY = yDiff;

    bst_node_t *run = m_bst->root_node;
    stack_t *st = ::create_stack();
    res_t res = STACK_SUCCESS;
    Q_ASSERT(run);


    while(TRUE)
    {

        this->drawNode(painter, QPoint(currentX,currentY), run->data);
        //push(st, run);

        if(run->left != NULL)
        {
            currentX = currentX - xDiff;
            currentY = currentY + yDiff;
            this->drawNode(painter, QPoint(currentX,currentY), run->left->data);
            currentX = currentX + xDiff;
            currentY = currentY - yDiff;
            push(st, run->left);
        }

        if(run->right != NULL)
        {
            currentX += xDiff;
            currentY += yDiff;
            this->drawNode(painter, QPoint(currentX,currentY), run->right->data);
            currentX -= xDiff;
            currentY -= yDiff;
            push(st, run->right);
        }


        res = pop(st, &run);
        Q_ASSERT(res == STACK_SUCCESS || res == STACK_EMPTY);
        if(res == BST_EMPTY)
            break;

    }
}

void RenderArea::drawNode(QPainter &painter, QPoint p, int number)
{
    painter.drawEllipse(p.x(), p.y(), m_nodeWidth, m_nodeHeight);
    int textW = m_nodeWidth/2;
    int textH = m_nodeHeight/2;
    int textX = p.x() + (m_nodeWidth-textW)/2;
    int textY = p.y() + (m_nodeHeight-textH)/2;
    painter.drawText(textX, textY, textW, textH, Qt::AlignCenter, QString::number(number));
}

void RenderArea::connectNode(QPainter &painter, QPoint p1, QPoint p2)
{
    int x1 = p1.x() + m_nodeWidth/2; //x=mid of node
    int y1 = p1.y() + m_nodeHeight;  //y=bottom of the node
    int x2 = p2.x() + m_nodeWidth/2; //x=mid of node
    int y2 = p2.y();    //top of node

    painter.drawLine(x1, y1, x2, y2);
}
