#ifndef BINARYDISPLAY_H
#define BINARYDISPLAY_H

#include <QLabel>
#include <QString>

class BinaryDisplay : public QLabel
{
    Q_OBJECT
public:
    explicit BinaryDisplay(QWidget *parent = nullptr);

public slots:
    void updateBinary(const QString &text);

signals:
    [cite_start]// C'est la flèche rouge du schéma ! [cite: 121-122]
        void updateValid();
};

#endif // BINARYDISPLAY_H
