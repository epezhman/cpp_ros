#include <QtWidgets/qgridlayout.h>
#include <QtWidgets/qmessagebox.h>
#include <QtCore/qprocess.h>


#include "ros_qt.h"


ROSQt::ROSQt(QWidget *parent)
        : QWidget(parent), m_sample(nullptr), m_save(nullptr), m_scan(nullptr), m_record(nullptr) {


    QGridLayout *grid = new QGridLayout();

    grid->addWidget(createGroup(), 0, 0);

    setLayout(grid);

    setWindowTitle("ROS Qt");
}

QGroupBox *ROSQt::createGroup() {

    QGroupBox *groupBox = new QGroupBox(tr("Control Panel"));
    groupBox->setStyleSheet("QGroupBox {  border: 1px solid gray; padding:20px 5px;}");
    groupBox->setFixedWidth(300);

    m_sample = new QPushButton("Sample");
    m_save = new QPushButton("Save");
    m_scan = new QPushButton("Scan");
    m_record = new QPushButton("Record");

    QVBoxLayout *layout = new QVBoxLayout();

    layout->addWidget(m_sample);
    layout->addWidget(m_save);
    layout->addWidget(m_scan);
    layout->addWidget(m_record);

    groupBox->setLayout(layout);


    connect(m_sample, SIGNAL(clicked()), this, SLOT(onBtnSampleClicked()));
    connect(m_save, SIGNAL(clicked()), this, SLOT(onBtnSaveClicked()));
    connect(m_scan, SIGNAL(clicked()), this, SLOT(onBtnScanClicked()));
    connect(m_record, SIGNAL(clicked()), this, SLOT(onBtnRecordClicked()));

    return groupBox;
}

void ROSQt::onBtnSampleClicked() {


}


void ROSQt::onBtnSaveClicked() {
    QMessageBox::information(
            this,
            "Hello Save",
            QString("Hello From Save")
    );
}


void ROSQt::onBtnScanClicked() {
    QMessageBox::information(
            this,
            "Hello Scan",
            QString("Hello From Scan")
    );
}


void ROSQt::onBtnRecordClicked() {
    QMessageBox::information(
            this,
            "Hello Record",
            QString("Hello From Record")
    );
}
