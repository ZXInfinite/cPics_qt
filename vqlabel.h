// Author: ZXInfinite

#ifndef VQLABEL_H
#define VQLABEL_H

#include <QLabel>
#include <QMouseEvent>

class vQLabel : public QLabel
{
public:
    //    vQLabel();
    vQLabel(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    vQLabel(const QString &text, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

private:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

    //    bool m_mlpress = false;
    QPoint m_mlPos;
    QPoint m_lwinPos;

    double m_scaledx = 1.0;
};

#endif // VQLABEL_H
