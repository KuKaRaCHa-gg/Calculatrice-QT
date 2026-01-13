#include "calculatrice.h"
#include "ui_calculatrice.h"

// Inclusion correcte selon votre dossier "Models"
#include "Models/IntRangeValidator.h"
#include "binarydisplay.h"

#include <QRegularExpression>
#include <algorithm>

Calculatrice::Calculatrice(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculatrice)
{
    ui->setupUi(this);

    // 1. Remplissage des vecteurs
    setVector(vIPnetwork, ui->partie1, "leIP");
    setVector(vIPnetworkBinary, ui->partie1, "lBinary");

    // 2. Configuration des validateurs et des connexions
    for (int i = 0; i < vIPnetwork.size(); ++i) {
        QLineEdit *le = qobject_cast<QLineEdit*>(vIPnetwork[i]);
        BinaryDisplay *bin = qobject_cast<BinaryDisplay*>(vIPnetworkBinary[i]);

        if (le && bin) {
            IntRangeValidator *validator = new IntRangeValidator(0, 255, le);
            le->setValidator(validator);

            // Connexion : Changement de texte -> Mise à jour du binaire local
            connect(le, &QLineEdit::textChanged, bin, &BinaryDisplay::updateBinary);
            // Connexion : Binaire valide -> Recalcul de toute l'interface
            connect(bin, &BinaryDisplay::updateValid, this, &Calculatrice::updateUI);
        }
    }

    // Connexion du Slider
    connect(ui->slider, &QSlider::valueChanged, this, &Calculatrice::updateUI);

    // Force l'affichage initial pour que les champs ne soient pas vides au lancement
    if (!vIPnetwork.isEmpty()) {
        QLineEdit *le = qobject_cast<QLineEdit*>(vIPnetwork[0]);
        if(le) emit le->textChanged(le->text());
    }
    updateUI();
}

Calculatrice::~Calculatrice()
{
    delete ui;
}

void Calculatrice::updateUI()
{
    int cidr = ui->slider->value();
    ui->lNetworkSize->setText(QString::number(cidr));

    // Récupération IP
    QVector<int> ipValues;
    for (int i = 0; i < vIPnetwork.size(); ++i) {
        QLineEdit *le = qobject_cast<QLineEdit*>(vIPnetwork[i]);
        if (le) ipValues.append(le->text().toInt());
        else ipValues.append(0);
    }
    unsigned int ipAddress = (ipValues[0] << 24) | (ipValues[1] << 16) | (ipValues[2] << 8) | ipValues[3];

    // Calculs Mathématiques
    unsigned int mask = (cidr == 0) ? 0 : (~0u) << (32 - cidr);
    unsigned int networkAddr = ipAddress & mask;
    unsigned int broadcastAddr = networkAddr | (~mask);
    unsigned int firstHost = networkAddr + 1;
    unsigned int lastHost = broadcastAddr - 1;
    unsigned int numHosts = (cidr > 30) ? 0 : (1 << (32 - cidr)) - 2;

    // Mise à jour des couleurs (Bleu/Jaune)
    for (int i = 0; i < vIPnetworkBinary.size(); ++i) {
        BinaryDisplay *binLabel = qobject_cast<BinaryDisplay*>(vIPnetworkBinary[i]);
        if (binLabel) {
            QString binaire = QString("%1").arg(ipValues[i], 8, 2, '0');
            QString html = "";
            for (int bit = 0; bit < 8; ++bit) {
                if (((i * 8) + bit) < cidr) html += "<font color='#01f0fd'>" + QString(binaire[bit]) + "</font>";
                else html += "<font color='#fdf300'>" + QString(binaire[bit]) + "</font>";
            }
            binLabel->setText(html);
        }
    }

    // Helper (Fonction locale) pour afficher les résultats dans les labels de l'UI
    auto displayResult = [](unsigned int val, QLabel* l1, QLabel* l2, QLabel* l3, QLabel* l4,
                            QLabel* lb1, QLabel* lb2, QLabel* lb3, QLabel* lb4) {
        int o1 = (val >> 24) & 0xFF;
        int o2 = (val >> 16) & 0xFF;
        int o3 = (val >> 8) & 0xFF;
        int o4 = val & 0xFF;

        if(l1) l1->setText(QString::number(o1));
        if(l2) l2->setText(QString::number(o2));
        if(l3) l3->setText(QString::number(o3));
        if(l4) l4->setText(QString::number(o4));

        if(lb1) lb1->setText(QString("%1").arg(o1, 8, 2, '0'));
        if(lb2) lb2->setText(QString("%1").arg(o2, 8, 2, '0'));
        if(lb3) lb3->setText(QString("%1").arg(o3, 8, 2, '0'));
        if(lb4) lb4->setText(QString("%1").arg(o4, 8, 2, '0'));
    };

    // Appel du helper pour chaque section (Masque, Diffusion, Début, Fin)
    displayResult(mask, ui->lResMask1, ui->lResMask2, ui->lResMask3, ui->lResMask4,
                  ui->lResMaskBin1, ui->lResMaskBin2, ui->lResMaskBin3, ui->lResMaskBin4);

    displayResult(broadcastAddr, ui->lResDiff1, ui->lResDiff2, ui->lResDiff3, ui->lResDiff4,
                  ui->lResDiffBin1, ui->lResDiffBin2, ui->lResDiffBin3, ui->lResDiffBin4);

    displayResult(firstHost, ui->lResStart1, ui->lResStart2, ui->lResStart3, ui->lResStart4,
                  ui->lResStartBin1, ui->lResStartBin2, ui->lResStartBin3, ui->lResStartBin4);

    displayResult(lastHost, ui->lResEnd1, ui->lResEnd2, ui->lResEnd3, ui->lResEnd4,
                  ui->lResEndBin1, ui->lResEndBin2, ui->lResEndBin3, ui->lResEndBin4);

    ui->lResHosts->setText(QString::number(numHosts));
}

void Calculatrice::setVector(QVector<QWidget*> &v, const QWidget *w, QString motif)
{
    v.clear();
    QList<QWidget*> childs = w->findChildren<QWidget*>();
    QRegularExpression regExp("^" + motif + ".*");
    foreach (QWidget *child, childs) {
        if (child->objectName().contains(regExp)) v.append(child);
    }
    std::sort(v.begin(), v.end(), [](QWidget* a, QWidget* b) {
        return a->objectName() < b->objectName();
    });
}
