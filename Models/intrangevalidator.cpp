#include "intrangevalidator.h"

IntRangeValidator::IntRangeValidator(int min, int max, QObject *parent)
    : QValidator(parent), m_min(min), m_max(max)
{
}

QValidator::State IntRangeValidator::validate(QString &input, int &pos) const
{
    Q_UNUSED(pos); // Supprime l'avertissement "unused parameter"

    // Si vide -> Intermédiaire (on attend la saisie)
    if (input.isEmpty())
        return QValidator::Intermediate;

    bool ok;
    int value = input.toInt(&ok);

    // Si ce n'est pas un nombre -> Invalide
    if (!ok)
        return QValidator::Invalid;

    // Si dans l'intervalle [0-255] -> Acceptable
    if (value >= m_min && value <= m_max)
        return QValidator::Acceptable;

    // Sinon -> Invalide
    return QValidator::Invalid;
}

void IntRangeValidator::fixup(QString &input) const
{
    Q_UNUSED(input); // Supprime l'avertissement
}
