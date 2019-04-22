#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPoint>
#include <QPointF>

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    RenderArea(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int m_nodeWidth;
    int m_nodeHeight;

    void setNodeWidth(int w)    { m_nodeWidth = w; }
    void setNodeHeight(int h)   { m_nodeHeight = h; }
    int getNodeWidth() const    { return (m_nodeWidth); }
    int getNodeHeight() const   { return (m_nodeHeight); }

    void drawNode(QPainter &painter, QPoint p, int number);
    void connectNode(QPainter &painter, QPoint p1, QPoint p2);
};

#endif // RENDERAREA_H
