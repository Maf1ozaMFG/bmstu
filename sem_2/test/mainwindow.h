#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QClipboard>
#include <QAction>
#include "entrypoint.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

    Ui::MainWindow *ui;

    AppContext context;

    void onClearClicked();
    void onStartConvertClicked();
    void onSwapClicked();
    void onCopyClicked();
    void dataEntered();

    void swapRadixTo(AppParams* params);
    void swapRadixFrom(AppParams* params);

    void swapRadixes(AppParams* params);

    void getAppParams(AppParams* params);
};

#endif // MAINWINDOW_H
