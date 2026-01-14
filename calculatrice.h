#ifndef CALCULATRICE_H
#define CALCULATRICE_H

#include <QMainWindow>
#include <QVector>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculatrice; }
QT_END_NAMESPACE

class Calculatrice : public QMainWindow
{
    Q_OBJECT

public:
    Calculatrice(QWidget *parent = nullptr);
    ~Calculatrice();

public slots:
    void updateUI();
    void updateHost();

private:
    Ui::Calculatrice *ui;

    QVector<QWidget*> vIPnetwork;       // leIP1_1, leIP1_2...
    QVector<QWidget*> vIPnetworkBinary; // lBinary1_1, lBinary1_2...
    QVector<QWidget*> vIPtest; // leTest1, leTest2...
    QVector<QWidget*> vIPtestBinary; // lResTestBin1, lResTestBin2...

    void setVector(QVector<QWidget*> &v, const QWidget *w, QString motif);
};
#endif // CALCULATRICE_H
