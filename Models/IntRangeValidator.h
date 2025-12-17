#ifndef INTRANGEVALIDATOR_H
#define INTRANGEVALIDATOR_H

#include <QValidator>

class IntRangeValidator : public QValidator
{
public:
    // Constructeur : on lui donne le min (0) et le max (255)
    IntRangeValidator(int min, int max, QObject *parent = nullptr);

    // La méthode imposée par le PDF pour valider le texte
    QValidator::State validate(QString &input, int &pos) const override;

    // Méthode fixup (optionnelle mais utile pour corriger à la fin)
    void fixup(QString &input) const override;

private:
    int m_min;
    int m_max;
};

#endif // INTRANGEVALIDATOR_H
