#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logic.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    doOperation(NULL, &context, INITCON);
    ui->lineEditEnterData->setMaxLength(32);
    ui->lineEditPersonalFrom->setMaxLength(2);
    ui->lineEditPersonalTo->setMaxLength(2);

    connect(ui->pushButtonClear, &QPushButton::clicked, this, &MainWindow::onClearClicked);
    connect(ui->pushButtonStartConvert, &QPushButton::clicked, this, &MainWindow::onStartConvertClicked);
    connect(ui->pushButtonCopy, &QPushButton::clicked, this, &MainWindow::onCopyClicked);
    connect(ui->pushButtonSwap, &QPushButton::clicked, this, &MainWindow::onSwapClicked);

    connect(ui->radioButtonFrom2, &QRadioButton::released, this, &MainWindow::getValidationState);
    connect(ui->radioButtonFrom10, &QRadioButton::released, this, &MainWindow::getValidationState);
    connect(ui->radioButtonFrom16, &QRadioButton::released, this, &MainWindow::getValidationState);
    connect(ui->lineEditPersonalFrom, &QLineEdit::textChanged, this, &MainWindow::getValidationState);

    connect(ui->radioButtonTo2, &QRadioButton::released, this, &MainWindow::getValidationState);
    connect(ui->radioButtonTo10, &QRadioButton::released, this, &MainWindow::getValidationState);
    connect(ui->radioButtonTo16, &QRadioButton::released, this, &MainWindow::getValidationState);
    connect(ui->lineEditPersonalTo, &QLineEdit::textChanged, this, &MainWindow::getValidationState);

    connect(ui->lineEditEnterData, &QLineEdit::textChanged, this, &MainWindow::getValidationState);
    connect(ui->pushButtonSwap, &QPushButton::clicked, this, &MainWindow::getValidationState);

}

MainWindow::~MainWindow()
{
    doOperation(NULL, &context, DEINITCON);
    doOperation(&params, NULL, DEINITPARAM);
    delete ui;
}

void MainWindow::onCopyClicked() { //&&&&&&&&&&&
    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(ui->lineEditResult->text());
}

void MainWindow::onClearClicked() { //&&&&&&&&&&&
    doOperation(NULL, &context, CLEAR);
    ui->lineEditEnterData->setText("");
    ui->lineEditResult->setText("");
    ui->lineEditPersonalFrom->setText("");
    ui->lineEditPersonalTo->setText("");
}

void MainWindow::onStartConvertClicked() { //&&&&&&&&&&&
    ui->lineEditResult->setText("");
    doOperation(&params, NULL, INITPARAM);
    getAppParams(&params);
    doOperation(&params, &context, VALIDATE);
    getValidationState();
    doOperation(&params, &context, CONVERT);
    ui->lineEditResult->setText(QString::fromStdString(context.resultValue));

    doOperation(&params, NULL, DEINITPARAM);
}



void MainWindow::onSwapClicked() {
    doOperation(&params, NULL, INITPARAM);
    getAppParams(&params);

    doOperation(&params, &context, VALIDATE);


    if (params.validationState) {
        swapLineEdits(&params);
        swapRadixFrom(&params);
        swapRadixTo(&params);
    } else {
        ui->lineEditResult->setText(QString::fromStdString(context.resultValue));
    }

    doOperation(&params, NULL, DEINITPARAM);
}

void MainWindow::getValidationState() {
    doOperation(&params, NULL, INITPARAM);

    getAppParams(&params);
    doOperation(&params, &context, VALIDATE);

    ui->label->setText(QString::fromStdString(context.validationState));
}

//void MainWindow::swap(AppParams* params) { //&&&&&&&&&&&


void MainWindow::getRadixes(AppParams* params) { //&&&&&&&&&&&
    if (ui->radioButtonFrom2->isChecked())
        strncpy(params->radixFrom, BIN, SIZE);
    else if (ui->radioButtonFrom10->isChecked())
        strncpy(params->radixFrom, DEC, SIZE);
    else if (ui->radioButtonFrom16->isChecked())
        strncpy(params->radixFrom, HEX, SIZE);
    else if (ui->radioButtonFromPersonal->isChecked()) {
        strncpy(params->radixFrom, ui->lineEditPersonalFrom->text().toStdString().c_str(), SIZE);
    }

    if (ui->radioButtonTo2->isChecked())
        strncpy(params->radixTo, BIN, SIZE);
    else if (ui->radioButtonTo10->isChecked())
        strncpy(params->radixTo, DEC, SIZE);
    else if (ui->radioButtonTo16->isChecked())
        strncpy(params->radixTo, HEX, SIZE);
    else if (ui->radioButtonToPersonal->isChecked()) {
        strncpy(params->radixTo, ui->lineEditPersonalTo->text().toStdString().c_str(), SIZE);
    }
}

void MainWindow::getAppParams(AppParams *params) {

    getRadixes(params);
    strncpy(params->initValue, ui->lineEditEnterData->text().toUpper().toStdString().c_str(), SIZE);
    params->validationState = SUCCESS;
}

void MainWindow::swapRadixFrom(AppParams* params) { //&&&&&&&&&&&
    if (strcmp(params->radixTo, BIN) == 0) {
        ui->radioButtonFrom2->setChecked(true);
    } else if (strcmp(params->radixTo, DEC) == 0) {
        ui->radioButtonFrom10->setChecked(true);
    } else if (strcmp(params->radixTo, HEX) == 0) {
        ui->radioButtonFrom16->setChecked(true);
    } else if (strcmp(params->radixTo, "") != 0) {
        ui->radioButtonFromPersonal->setChecked(true);
        ui->lineEditPersonalFrom->setText(QString::fromStdString(params->radixTo));
        if (strcmp(params->radixFrom, BIN) == 0 || strcmp(params->radixFrom, DEC) == 0 || strcmp(params->radixFrom, HEX) == 0) {
            ui->lineEditPersonalTo->setText("");
        }
    }
}

void MainWindow::swapRadixTo(AppParams* params) { //&&&&&&&&&&&
    if (strcmp(params->radixFrom, BIN) == 0) {
        ui->radioButtonTo2->setChecked(true);
    } else if (strcmp(params->radixFrom, DEC) == 0) {
        ui->radioButtonTo10->setChecked(true);
    } else if (strcmp(params->radixFrom, HEX) == 0) {
        ui->radioButtonTo16->setChecked(true);
    } else if (strcmp(params->radixFrom, "") != 0) {
        ui->radioButtonToPersonal->setChecked(true);
        ui->lineEditPersonalTo->setText(QString::fromStdString(params->radixFrom));
        if (strcmp(params->radixTo, BIN) == 0 || strcmp(params->radixTo, DEC) == 0 || strcmp(params->radixTo, HEX) == 0) {
            ui->lineEditPersonalFrom->setText("");
        }
    }
}

void MainWindow::swapLineEdits(AppParams *params) {
    QString temp;
    doOperation(params, &context, VALIDATE);
    if (params->validationState && ui->lineEditResult->text() != "") {
        temp = ui->lineEditResult->text();
        ui->lineEditResult->setText(ui->lineEditEnterData->text());
        ui->lineEditEnterData->setText(temp);
    }
}
