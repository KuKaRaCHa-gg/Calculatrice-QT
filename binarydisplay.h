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
    void updateValid();
};

#endif // BINARYDISPLAY_H
