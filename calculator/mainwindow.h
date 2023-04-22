
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>



//QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
//QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;


private slots:
    void NumPressionado();
    void MatButtonPressionado();
    void IgualButton();
    void LimpaTela();
    void MudaSinalNumero();
};

#endif // MAINWINDOW_H
