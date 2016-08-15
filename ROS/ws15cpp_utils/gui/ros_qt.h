#ifndef ROSQT_ROS_QT_H
#define ROSQT_ROS_QT_H

#include <QtWidgets/qwidget.h>
#include <QtWidgets/QPushButton>
#include <QtWidgets/qgroupbox.h>


class ROSQt : public QWidget {

Q_OBJECT;

public:
    ROSQt(QWidget *parent = nullptr);

private slots:

    void onBtnSampleClicked();

    void onBtnSaveClicked();

    void onBtnScanClicked();

    void onBtnRecordClicked();


private:

    QGroupBox *createGroup();

    QPushButton *m_sample;
    QPushButton *m_save;
    QPushButton *m_scan;
    QPushButton *m_record;
};

#endif //ROSQT_ROS_QT_H
