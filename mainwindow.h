#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <windows.h>
#include <vector>
#include <QQueue>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();



signals:
    void timerChanged();

protected:
    void paintEvent(QPaintEvent *);


private slots:
    void on_doubleSpinBox_Ax_valueChanged(double arg1);

    void on_doubleSpinBox_Wx_valueChanged(double arg1);

    void on_doubleSpinBox_Dx_valueChanged(double arg1);

    void on_doubleSpinBox_Ay_valueChanged(double arg1);

    void on_doubleSpinBox_Wy_valueChanged(double arg1);

    void on_doubleSpinBox_Dy_valueChanged(double arg1);

    void on_pushButton_startX_clicked();

    void on_pushButton_startY_clicked();

    void onTimerTicked();

    void on_pushButton_stopX_clicked();

    void on_pushButton_stopY_clicked();

private:

    Ui::MainWindow *ui;
    QTimer *timer;

};





#endif // MAINWINDOW_H
