#ifndef NEWANDUPDATEPROJECTWINDOW_H
#define NEWANDUPDATEPROJECTWINDOW_H

#include <QMainWindow>

namespace Ui {
class NewAndUpdateProjectWindow;
}

class NewAndUpdateProjectWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewAndUpdateProjectWindow(QWidget *parent = 0);
    ~NewAndUpdateProjectWindow();

private:
    Ui::NewAndUpdateProjectWindow *ui;
};

#endif // NEWANDUPDATEPROJECTWINDOW_H
