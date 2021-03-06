﻿#ifndef DIALOGMATERIALMANAGE_H
#define DIALOGMATERIALMANAGE_H

#include <QDialog>
#include <QCheckBox>
#include "service_global.h"


namespace Ui {
class DialogMaterialManage;
}

class DialogMaterialManage : public QDialog
{
    Q_OBJECT

public:
    explicit DialogMaterialManage(QWidget *parent = 0);
    ~DialogMaterialManage();
    void closeAllStatus();
     void initData();
private slots:
    void on_pushButton_exit_clicked();

    void on_pushButton_export_clicked();

    void checkBox();

    void exportCb(bool ok);

    void checkAll();

    void onCellClick(int row,int col);

    void changeCol();
signals:
    void sig_exportCb(bool);
private:
    void setRowData(Materiel ma,int row);
    void removeOne(Materiel ma);
    void appendOne(Materiel ma);
    void doExport(QVector<Materiel> ls, QString filepath);
private:
    Ui::DialogMaterialManage *ui;
    QVector<QCheckBox*> m_boxs;
};

#endif // DIALOGMATERIALMANAGE_H
