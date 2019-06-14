#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>

static QTimer timer;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto centerChanged = [this](int) {
        ui->drawWidget->setCenterPoint(QPoint(ui->cx->value(), ui->cy->value()));
    };
    connect(ui->radius, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            ui->drawWidget, &XYRotateText::setRadius);
    connect(ui->angle, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            ui->drawWidget, &XYRotateText::setRotate);
    connect(ui->startAngle, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            ui->drawWidget, &XYRotateText::setStartAngle);
    connect(ui->cx, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            centerChanged);
    connect(ui->cx, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            centerChanged);
    connect(ui->cy, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            centerChanged);
    connect(ui->type, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            ui->drawWidget, &XYRotateText::setType);

    connect(ui->text, &QLineEdit::textChanged,
            ui->drawWidget, &XYRotateText::setText);

    ui->text->textChanged(ui->text->text());
    ui->radius->valueChanged(ui->radius->value());
    ui->angle->valueChanged(ui->angle->value());
    ui->cx->valueChanged(ui->cx->value());
    ui->cy->valueChanged(ui->cy->value());
    ui->type->currentIndexChanged(0);

    timer.setSingleShot(false);
    connect(&timer, &QTimer::timeout, [this](){
        ui->drawWidget->setRotateAngle(int(ui->drawWidget->rotateAngle() + 1) % 360);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if (timer.isActive()) {
        timer.stop();
    } else {
        timer.start(ui->timer->value());
    }
}
