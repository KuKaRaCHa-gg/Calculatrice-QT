#ifndef CALCULATRICE_H
#define CALCULATRICE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Calculatrice;
}
QT_END_NAMESPACE

class Calculatrice : public QMainWindow
{
    Q_OBJECT

public:
    Calculatrice(QWidget *parent = nullptr);
    ~Calculatrice();

private:
    Ui::Calculatrice *ui;
};
#endif // CALCULATRICE_H
