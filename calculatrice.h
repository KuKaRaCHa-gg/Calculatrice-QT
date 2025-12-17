#ifndef CALCULATRICE_H
#define CALCULATRICE_H

#include <QMainWindow>
#include <QVector>
#include <QWidget>
#include <QLineEdit> // Utile pour manipuler les champs
#include <QLabel>    // Utile pour les affichages

QT_BEGIN_NAMESPACE
namespace Ui { class Calculatrice; }
QT_END_NAMESPACE

class Calculatrice : public QMainWindow
{
    Q_OBJECT

public:
    Calculatrice(QWidget *parent = nullptr);
    ~Calculatrice();

private:
    Ui::Calculatrice *ui;


    QVector<QWidget*> vIPnetwork;       //leIP1_1, leIP1_2, etc.
    QVector<QWidget*> vIPnetworkBinary; // lBinary1_1, lBinary1_2, etc.


    void setVector(QVector<QWidget*> &v, const QWidget *w, QString motif);
};
#endif
