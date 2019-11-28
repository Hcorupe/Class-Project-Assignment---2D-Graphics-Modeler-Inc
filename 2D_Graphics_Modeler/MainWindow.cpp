#include "MainWindow.h"
#include "login.h"
#include "ui_MainWindow.h"
#include "shape.h"
#include "rectangle.h"
#include "square.h"
#include "ellipse.h"
#include "circle.h"
#include "line.h"
#include "polygon.h"
#include "polyline.h"
#include "text.h"
#include "vector.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{



    login = new Login;
    login->show();

    ui->setupUi(this);


    connect(login, SIGNAL(finished(int)), this, SLOT(show()));
    connect(login, SIGNAL(finished(int)), this, SLOT(disableEdit()));

    // Add shape types to new shape combobox
    ui->newShapeComboBox->addItem("Rectangle");
    ui->newShapeComboBox->addItem("Square");
    ui->newShapeComboBox->addItem("Ellipse");
    ui->newShapeComboBox->addItem("Circle");
    ui->newShapeComboBox->addItem("Polygon");
    ui->newShapeComboBox->addItem("Polyline");
    ui->newShapeComboBox->addItem("Line");
    ui->newShapeComboBox->addItem("Text");



    // Add shape ids to combobox
    for (int i = 0; i < ui->renderArea->shapes.size(); i++)
    {
        ui->idComboBox->addItem(QString::number((ui->renderArea->shapes[i]->getShapeId())));
    }






}

void MainWindow::disableEdit()
{
       // Disable editing forms if user is not admin
       if(login->result() == 0)
       {
           ui->MainTab->findChild<QWidget*>("xSpinBox")->setDisabled(true);
           ui->MainTab->findChild<QWidget*>("ySpinBox")->setDisabled(true);
           ui->MainTab->findChild<QWidget*>("newShapeButton")->setDisabled(true);
           ui->MainTab->findChild<QWidget*>("deleteShapeButton")->setDisabled(true);

       }

}

MainWindow::~MainWindow()
{
    delete ui;
    delete login;
}


// Change selected shape depending on combobox selected
void MainWindow::on_idComboBox_currentIndexChanged(int index)
{
    selectedShape = ui->renderArea->shapes[index];
    selectedShapeLabel = ui->renderArea->shapeLabels[index];
    ui->xSpinBox->setValue(selectedShape->getStartPoint().x());
    ui->ySpinBox->setValue(selectedShape->getStartPoint().y());
}

void MainWindow::on_xSpinBox_valueChanged(int arg1)
{

    // Move shape y-value
    QPoint newPoint(selectedShape->getStartPoint());
    newPoint.setX(arg1);

    selectedShape->move(newPoint);

    // Move shape label y-value
    newPoint = selectedShapeLabel->getStartPoint();
    newPoint.setX(arg1 - 10);
    selectedShapeLabel->setStartPoint(newPoint);

    ui->renderArea->update();

}

void MainWindow::on_ySpinBox_valueChanged(int arg1)
{
    // Move shape x-value
    QPoint newPoint(selectedShape->getStartPoint());
    newPoint.setY(arg1);

    selectedShape->move(newPoint);

    // Move shape label x-value
    newPoint = selectedShapeLabel->getStartPoint();
    newPoint.setY(arg1 + 10);
    selectedShapeLabel->setStartPoint(newPoint);

    ui->renderArea->update();
}

void MainWindow::on_deleteShapeButton_clicked()
{
    for (int i = 0; i < ui->renderArea->shapes.size(); i++)
    {

        if (ui->renderArea->shapes[i] == selectedShape)
        {
            // Erase shape from shape vect
            ui->renderArea->shapes.erase(&(ui->renderArea->shapes[i]));
            // Erase shape label
            ui->renderArea->shapeLabels.erase(&(ui->renderArea->shapeLabels[i]));
        }
    }

    ui->idComboBox->removeItem(ui->idComboBox->currentIndex());

    ui->renderArea->update();
}

void MainWindow::on_newShapeButton_clicked()
{

}
