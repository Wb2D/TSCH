#ifndef DIALOGMAIL_H
#define DIALOGMAIL_H

#include <QDialog>

namespace Ui {
class dialogMail;
}

class dialogMail : public QDialog
{
    Q_OBJECT

public:
    explicit dialogMail(QWidget *parent = nullptr);
    ~dialogMail();

private:
    Ui::dialogMail *ui;
};

#endif // DIALOGMAIL_H
