// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <QTime>
#include <QPixmap>
#include <QtMath>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    QColor getRandomColor();

private:
    QTimer timer;
    QPixmap backgroundPixmap;
};

#endif // MAINWINDOW_H
