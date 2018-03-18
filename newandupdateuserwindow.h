#ifndef NEWANDUPDATEUSERWINDOW_H
#define NEWANDUPDATEUSERWINDOW_H

#include <QMainWindow>

namespace Ui {
class NewAndUpdateUserWindow;
}

class NewAndUpdateUserWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewAndUpdateUserWindow(QWidget *parent = 0);
    ~NewAndUpdateUserWindow();

private:
    Ui::NewAndUpdateUserWindow *ui;
};

#endif // NEWANDUPDATEUSERWINDOW_H
