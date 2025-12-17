#include "binarydisplay.h"

BinaryDisplay::BinaryDisplay(QWidget *parent) : QLabel(parent)
{
    setText("00000000");
    setStyleSheet("color: #4dd0e1; font-family: Consolas, Monospace;");
    setAlignment(Qt::AlignCenter);
}

void BinaryDisplay::updateBinary(const QString &text)
{
    if (text.isEmpty()) {
        setText("00000000");
        return;
    }

    bool ok;
    int val = text.toInt(&ok);

    if (ok) {
        QString bin = QString("%1").arg(val, 8, 2, '0');

        // [OPTIONNEL : COULEURS]
        // Le PDF (page 4) demande d'afficher en jaune/bleu selon le masque.
        // Pour l'instant on affiche tout en simple, on fera la couleur plus tard.
        setText(bin);

        // IMPORTANT : On prévient le reste du programme !
        // C'est ici qu'on suit le chemin du schéma vers "updateUI"
        emit updateValid();
    }
}
