#include "calculatrice.h"
#include "ui_calculatrice.h"
#include <QRegularExpression>
#include <algorithm>
#include "intrangevalidator.h"

// --- CONSTRUCTEUR ---
Calculatrice::Calculatrice(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculatrice)
{
    ui->setupUi(this);

    // 1. Initialisation des vecteurs
    setVector(vIPnetwork, ui->partie1, "leIP");
    setVector(vIPnetworkBinary, ui->partie1, "lBinary");

    // 2. Application du validateur (Sécurité 0-255)
    for (int i = 0; i < vIPnetwork.size(); ++i) {
        // On récupère la case (QLineEdit)
        QLineEdit *le = qobject_cast<QLineEdit*>(vIPnetwork[i]);

        // Si la récupération a fonctionné
        if (le) {
            // On crée le validateur (min 0, max 255)
            IntRangeValidator *validator = new IntRangeValidator(0, 255, le);
            le->setValidator(validator);
        }
    }
}

Calculatrice::~Calculatrice()
{
    delete ui;
}

// --- FONCTION SETVECTOR ---
void Calculatrice::setVector(QVector<QWidget*> &v, const QWidget *w, QString motif)
{
    v.clear();

    // Récupérer les enfants
    QList<QWidget*> childs = w->findChildren<QWidget*>();
    QRegularExpression regExp("^" + motif + ".*");

    // Filtrer
    foreach (QWidget *child, childs) {
        if (child->objectName().contains(regExp)) {
            v.append(child);
        }
    }

    // Trier
    std::sort(v.begin(), v.end(), [](QWidget* a, QWidget* b) {
        return a->objectName() < b->objectName();
    });
}
