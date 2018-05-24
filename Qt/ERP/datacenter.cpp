﻿#include "datacenter.h"
#include  "orderservice.h"
#include <QDebug>
#include <QDateTime>
#include "userservice.h"


dataCenter::dataCenter(QObject *parent) : QObject(parent)
{
    cur_user.UID="1234";
    cur_user.Author = "admin";
    cur_user.Name = "admin";
    cur_user.CID = "CID001";
    cur_user.CommpanyName="南通公司";

    m_units.append("EA");
    m_units.append("KG");
    m_batch.append("180410001");
    m_batch.append("180410002");
    m_batch.append("180410003");
    m_batch.append("180410004");
    m_batch.append("132645004");
    m_batch.append("52516464");

    Materiel m ;
    m.MaterID = "61013567";
    m.MaterDes="IMCN/5261097/银白色锌铝涂层";
    m.CID ="C102";
    m.CustomName = "上海某某科技公司";
    m.OrderNum = 1;
    m.Unit = "吨";
    m.CreatTime = QString("%1").arg(QDateTime::currentDateTime().toMSecsSinceEpoch());
    m.Status = "0";
    m_maters.append(m);

    Materiel m1 ;
    m1.MaterID = "610134207";
    m1.CID ="C103";
    m1.MaterDes="C924/项目12法兰焊接/银白色锌铝涂层";
    m1.CustomName = "昆山某某科技公司";
    m1.OrderNum = 2;
    m1.Unit = "KG";
    m1.CreatTime = QString("%1").arg(QDateTime::currentDateTime().toMSecsSinceEpoch());
    m1.Status = "0";
    m_maters.append(m1);

    Materiel m2 ;
    m2.MaterID = "61013112";
    m2.CID ="C104";
    m2.CustomName = "昆山某某科技公司";
    m2.OrderNum = 2;
    m2.Unit = "EA";
    m2.CreatTime = QString("%1").arg(QDateTime::currentDateTime().toMSecsSinceEpoch());
    m2.Status = "1";
    m2.MaterDes="IMCN/5261097/银白色锌铝涂层";
    m_maters.append(m2);

    Materiel m3 ;
    m3.MaterID = "61013204";
    m3.CID ="C105";
    m3.CustomName = "张江某某科技公司";
    m3.CustomName = "昆山某某科技公司";
    m3.OrderNum = 12;
    m3.Unit = "EA";
    m3.CreatTime = QString("%1").arg(QDateTime::currentDateTime().toMSecsSinceEpoch());
    m3.Status = "1";
    m3.MaterDes="C407/0SEA003061/黑色锌铝涂层";
    m_maters.append(m3);

    Customer c1;
    c1.CID = "C102";
    c1.Name="上海某某科技公司";

    Customer c2;
    c2.CID = "C103";
    c2.Name="昆山某某科技公司";

    Customer c3;
    c3.CID = "C102";
    c3.Name="南通某某科技公司";
    m_customers.append(c1);
    m_customers.append(c2);
    m_customers.append(c3);


    m_authors.push_back("操作员");
    m_authors.push_back("仓库");
    m_authors.push_back("财务");
    m_authors.push_back("管理员");
    m_authors.push_back("超级管理员");

    m_departments.push_back("生产部");
    m_departments.push_back("仓库部");
    m_departments.push_back("行政部");
    m_departments.push_back("财务部");
    m_departments.push_back("销售部");
}

void dataCenter::newUser(const QJsonObject para)
{
#if 0
    bool isOK   = false;
    User user = UserService::newUser(para,isOK,m_Config.HOST_NAME(),m_Config.HOST_PORT());
    if(isOK){
        this->appendEmployee(user);
        emit sig_newEmployee(user,true);
        return;
    }
    emit sig_newEmployee(user,false);
#endif
#if 1
    User user = UserService::fromJsonObject(para);
    user.UID = QString("%1").arg(QDateTime::currentDateTime().toMSecsSinceEpoch());
    user.CreatTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    user.CID = cur_user.CID;
    user.CommpanyName = cur_user.CommpanyName;
    user.Status = "0";
    this->appendEmployee(user);
    emit sig_newEmployee(user,true);
#endif
}

void dataCenter::modUser(const QJsonObject para)
{
    User user = UserService::fromJsonObject(para);
    for(int i=0;i<m_employee.size();++i){
        if(m_employee[i].UID==user.UID){
            m_employee[i] = user;
            break;
        }
    }
    emit sig_modEmployee(user,true);
}

void dataCenter::outUser(const QJsonObject para)
{
    User user = UserService::fromJsonObject(para);
    user.Status ="1";
    user.OutTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    for(int i=0;i<m_employee.size();++i){
        if(m_employee[i].UID==user.UID){
            m_employee[i] = user;
            break;
        }
    }
    emit sig_outEmployee(user,true);
}

void dataCenter::delUser(const QJsonObject para)
{
    User user = UserService::fromJsonObject(para);
    user.Status ="-1";
    user.OutTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    for(int i=0;i<m_employee.size();++i){
        if(m_employee[i].UID==user.UID){
            m_employee.remove(i);
            break;
        }
    }
    emit sig_delEmployee(user,true);
}

void dataCenter::newOrder(const QJsonObject para)
{
#if 0
    bool isOK   = false;
    Order order = OrderService::newOrder(para,isOK,m_Config.HOST_NAME(),m_Config.HOST_PORT());
    if(isOK){
        this->appendOrder(order);
        emit sig_newOrder(order,true);
        return;
    }
    emit sig_newOrder(order,false);
#endif
#if 1
    Order order = OrderService::fromJsonObject(para);
    order.OrderID = QString("%1").arg(QDateTime::currentDateTime().toMSecsSinceEpoch());
    order.ProduceID =  QString("%1").arg(QDateTime::currentDateTime().toMSecsSinceEpoch()/130);
    order.CreatTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    OderFlow flow;
    flow.UserName =cur_user.Name;
    flow.Action="新建订单";
    flow.Status = Status_New;
    flow.OpreatTime =order.CreatTime;
    order.Current = flow;
    order.Flow.push_back(flow);

    this->appendOrder(order);
    emit sig_newOrder(order,true);
#endif
}

void dataCenter::modOrder(const QJsonObject para)
{
#if 0
    bool isOK   = false;
    Order order = OrderService::modOrder(para,isOK,m_Config.HOST_NAME(),m_Config.HOST_PORT());
    if(isOK){
        for(int i=0;i<m_orders.size();++i){
            if(m_orders[i].OrderID==order.OrderID){
                m_orders[i] = order;
                break;
            }
        }
        emit sig_modOrder(order,true);
        return;
    }
    emit sig_modOrder(order,false);
#endif
#if 1
    Order order = OrderService::fromJsonObject(para);
    OderFlow flow;
    flow.UserName =cur_user.Name;
    flow.Action="订单修改";
    flow.Status = order.Current.Status;
    flow.OpreatTime =QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    order.Current = flow;
    order.Flow.push_back(flow);
    for(int i=0;i<m_orders.size();++i){
        if(m_orders[i].OrderID==order.OrderID){
            m_orders[i] = order;
            break;
        }
    }
    emit sig_modOrder(order,true);
#endif
}

void dataCenter::cancleOrder(const QJsonObject para)
{
#if 0
    bool isOK   = false;
    Order order = OrderService::cancleOrder(para,isOK,m_Config.HOST_NAME(),m_Config.HOST_PORT());
    if(isOK){
        for(int i=0;i<m_orders.size();++i){
            if(m_orders[i].OrderID==order.OrderID){
                m_orders[i] = order;
                break;
            }
        }
        emit sig_cancleOrder(order,true);
        return;
    }
    emit sig_cancleOrder(order,false);
#endif
#if 1
    Order order = OrderService::fromJsonObject(para);
    OderFlow flow;
    flow.UserName =cur_user.Name;
    flow.Action=" 取消订单";
    flow.Status = Status_Cancle;
    flow.OpreatTime =QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    order.Current = flow;
    order.Flow.push_back(flow);
    for(int i=0;i<m_orders.size();++i){
        if(m_orders[i].OrderID==order.OrderID){
            m_orders[i] = order;
            break;
        }
    }
    emit sig_cancleOrder(order,true);
#endif
}

void dataCenter::finishOrder(const QJsonObject para)
{
#if 0
    bool isOK   = false;
    Order order = OrderService::finishOrder(para,isOK,m_Config.HOST_NAME(),m_Config.HOST_PORT());
    if(isOK){
        for(int i=0;i<m_orders.size();++i){
            if(m_orders[i].OrderID==order.OrderID){
                m_orders[i] = order;
                break;
            }
        }
        emit sig_finishOrder(order,true);
        return;
    }
    emit sig_finishOrder(order,false);
#endif
#if 1
    Order order = OrderService::fromJsonObject(para);
    OderFlow flow;
    flow.UserName =cur_user.Name;
    flow.Action="订单出库";
    flow.Status = Status_Success;
    flow.OpreatTime =QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    order.Current = flow;
    order.Flow.push_back(flow);
    order.SuccessTime =QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    for(int i=0;i<m_orders.size();++i){
        if(m_orders[i].OrderID==order.OrderID){
            m_orders[i] = order;
            break;
        }
    }
    emit sig_finishOrder(order,true);
#endif
}

void dataCenter::modOrderPrice(const QJsonObject para)
{
#if 0
    bool isOK   = false;
    Order order = OrderService::modOrderPrice(para,isOK,m_Config.HOST_NAME(),m_Config.HOST_PORT());
    if(isOK){
        for(int i=0;i<m_orders.size();++i){
            if(m_orders[i].OrderID==order.OrderID){
                m_orders[i] = order;
                break;
            }
        }
        emit sig_modOrderPrice(order,true);
        return;
    }
    emit sig_modOrderPrice(order,false);
#endif
#if 1
    Order order = OrderService::fromJsonObject(para);
    OderFlow flow;
    flow.UserName =cur_user.Name;
    flow.Action="订单定价";
    flow.Status = order.Current.Status;
    flow.OpreatTime =QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    order.Current = flow;
    order.Flow.push_back(flow);
    for(int i=0;i<m_orders.size();++i){
        if(m_orders[i].OrderID==order.OrderID){
            m_orders[i] = order;
            break;
        }
    }
    emit sig_modOrderPrice(order,true);
#endif
}


void dataCenter::showMessage(QString msg, int sec)
{
    emit showStatusMessage(msg,sec);
}


void dataCenter::showLoadding(QString str,int sec,QColor c )
{
    m_load.showTime(str,sec,c);
}

void dataCenter::hideLoadding()
{
    m_load.showOver();
}


void dataCenter::setCurUser(User u)
{
    cur_user = u;
}

User dataCenter::CurUser()
{
    return cur_user;
}

QVector<Order> dataCenter::StatusOrders(QString status)
{
    QVector<Order > ls;
    if (status==""){
        return ls;
    }
    if(status==Status_All){
        return m_orders;
    }

    for(Order o: m_orders) {
        if (o.Current.Status.compare(status)==0){
            ls.append(o);
        }
    }
    return ls;
}

//获取单个订单
Order dataCenter::getOrder(QString OrderID, bool &ok)
{
    Order a;
    for(Order o: m_orders) {
        if (o.OrderID.compare(OrderID)==0){
            ok = true;
            return o;
        }
    }
    ok = false;
    return a;
}

void dataCenter::appendOrder(Order order)
{
    m_orders.append(order);
}

void dataCenter::appendUnit(QString u)
{
    m_units.append(u);
}

QVector<QString> dataCenter::Units()
{
    return m_units;
}

bool dataCenter::checkUnitExist(QString unit)
{
    for(QString m:m_units){
        if (m==unit){
            return true;
        }
    }
    return false;
}

void dataCenter::appendMaters(Materiel m)
{
    m_maters.append(m);
}

QVector<Materiel> dataCenter::Materiels()
{
    return m_maters;
}

bool dataCenter::checkMaterielID(QString id)
{
    for(Materiel m:m_maters){
        if (m.MaterID==id){
            return true;
        }
    }
    return false;
}

Materiel dataCenter::getMateriel(QString MID, bool &ok)
{
    ok = true;
    for(Materiel m:m_maters){
        if (m.MaterID==MID){
            ok = true;
            return m;
        }
    }
    ok = false;
    Materiel s;
    return s;
}

void dataCenter::appendBatch(QString b)
{
    m_batch.append(b);
}

QVector<QString> dataCenter::Batchs()
{
    return m_batch;
}


void dataCenter::appendCustomer(Customer c)
{
    m_customers.append(c);
}


QVector<QString> dataCenter::getAuthors() const
{
    return m_authors;
}

QVector<User> dataCenter::employees() const
{
    return m_employee;
}

User dataCenter::getUser(QString UID, bool &ok)
{
    User a;
    for(User o: m_employee) {
        if (o.UID.compare(UID)==0){
            ok = true;
            return o;
        }
    }
    ok = false;
    return a;
}

void dataCenter::appendEmployee(User user)
{
    m_employee.append(user);
}

QVector<QString> dataCenter::getDepartments() const
{
    return m_departments;
}

QVector<Customer> dataCenter::Customers()
{
    return m_customers;
}

bool dataCenter::checkCustomerExist(QString name)
{
    for(Customer m:m_customers){
        if (m.Name==name){
            return true;
        }
    }
    return false;
}
