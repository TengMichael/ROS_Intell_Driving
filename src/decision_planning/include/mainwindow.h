#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
  int _timerld;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);

protected:
    void timerEvent(QTimerEvent* e);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
