#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>

namespace Ui {
class SearchDialog;
}

class SearchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchDialog(int type,QWidget *parent = 0);
    ~SearchDialog();

private:
    int type;
    Ui::SearchDialog *ui;
    void connects();
    void initDialog();
    void SetType(int);

signals:
    void signalReturnText(int,QString);
private slots:
    void slotPushButtonClickedFinished();
};

#endif // SEARCHDIALOG_H
