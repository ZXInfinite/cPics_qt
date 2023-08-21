// Author: ZXInfinite

#ifndef VQLABEL_H
#define VQLABEL_H

#include <QLabel>
#include <QMouseEvent>

class vQLabel : public QLabel
{
public:
    vQLabel(const int i, const QString &path, const QString &title = nullptr, const double scaled = 1, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    double GetScaled();

private:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);


public:
    QString m_path;
    int i_num;

private:
    //    bool m_mlpress = false;
    QPoint m_mlPos;
    QPoint m_lwinPos;
    QSize m_sizeOriginal;
    QSize m_sizeLast;

    double m_scaledx = 1.0;
    double scx;
};

#endif // VQLABEL_H
