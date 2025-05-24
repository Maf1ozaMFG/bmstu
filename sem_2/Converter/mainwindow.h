#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QClipboard>
#include <QAction>
#include "mymalloc.h"
#include "entrypoint.h"
#include "string.h"

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
    AppParams params;

    void onClearClicked();
    void onStartConvertClicked();
    void onSwapClicked();
    void onCopyClicked();

    void swap(AppParams* params);
    void swapRadixFrom(AppParams* params);
    void swapRadixTo(AppParams* params);
    void swapLineEdits(AppParams* params);

    void getRadixes(AppParams* params);
    void getAppParams(AppParams* params);
    void getValidationState();
};

#endif // MAINWINDOW_H
