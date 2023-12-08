/********************************************************************************
** Form generated from reading UI file 'qtwidgetsapplication1.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTWIDGETSAPPLICATION1_H
#define UI_QTWIDGETSAPPLICATION1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtWidgetsApplication1Class
{
public:
    QWidget *centralWidget;
    QPushButton *add_item;
    QLineEdit *lineEdit_key;
    QLineEdit *lineEdit_value;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_status;
    QLabel *label_status_2;
    QPushButton *show_pre_order;
    QLineEdit *lineEdit_pre_order;
    QLineEdit *lineEdit_key_del;
    QLabel *label_3;
    QPushButton *delete_item;
    QPushButton *restore;
    QTreeWidget *treeWidget;
    QPushButton *show_tree;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtWidgetsApplication1Class)
    {
        if (QtWidgetsApplication1Class->objectName().isEmpty())
            QtWidgetsApplication1Class->setObjectName(QString::fromUtf8("QtWidgetsApplication1Class"));
        QtWidgetsApplication1Class->resize(1183, 475);
        centralWidget = new QWidget(QtWidgetsApplication1Class);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        add_item = new QPushButton(centralWidget);
        add_item->setObjectName(QString::fromUtf8("add_item"));
        add_item->setGeometry(QRect(520, 210, 181, 41));
        QFont font;
        font.setPointSize(10);
        add_item->setFont(font);
        lineEdit_key = new QLineEdit(centralWidget);
        lineEdit_key->setObjectName(QString::fromUtf8("lineEdit_key"));
        lineEdit_key->setGeometry(QRect(500, 50, 221, 41));
        lineEdit_value = new QLineEdit(centralWidget);
        lineEdit_value->setObjectName(QString::fromUtf8("lineEdit_value"));
        lineEdit_value->setGeometry(QRect(500, 140, 221, 41));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(580, 20, 81, 21));
        QFont font1;
        font1.setPointSize(12);
        label->setFont(font1);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(570, 110, 111, 21));
        label_2->setFont(font1);
        label_status = new QLabel(centralWidget);
        label_status->setObjectName(QString::fromUtf8("label_status"));
        label_status->setGeometry(QRect(50, 140, 181, 41));
        QFont font2;
        font2.setPointSize(8);
        label_status->setFont(font2);
        label_status_2 = new QLabel(centralWidget);
        label_status_2->setObjectName(QString::fromUtf8("label_status_2"));
        label_status_2->setGeometry(QRect(260, 140, 171, 41));
        label_status_2->setFont(font2);
        show_pre_order = new QPushButton(centralWidget);
        show_pre_order->setObjectName(QString::fromUtf8("show_pre_order"));
        show_pre_order->setGeometry(QRect(150, 330, 171, 51));
        show_pre_order->setFont(font);
        lineEdit_pre_order = new QLineEdit(centralWidget);
        lineEdit_pre_order->setObjectName(QString::fromUtf8("lineEdit_pre_order"));
        lineEdit_pre_order->setGeometry(QRect(30, 230, 421, 71));
        QFont font3;
        font3.setPointSize(14);
        lineEdit_pre_order->setFont(font3);
        lineEdit_key_del = new QLineEdit(centralWidget);
        lineEdit_key_del->setObjectName(QString::fromUtf8("lineEdit_key_del"));
        lineEdit_key_del->setGeometry(QRect(500, 320, 221, 41));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(590, 290, 71, 21));
        label_3->setFont(font1);
        delete_item = new QPushButton(centralWidget);
        delete_item->setObjectName(QString::fromUtf8("delete_item"));
        delete_item->setGeometry(QRect(520, 380, 181, 41));
        delete_item->setFont(font);
        restore = new QPushButton(centralWidget);
        restore->setObjectName(QString::fromUtf8("restore"));
        restore->setGeometry(QRect(130, 50, 231, 41));
        restore->setFont(font);
        treeWidget = new QTreeWidget(centralWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(1, QString::fromUtf8("2"));
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setGeometry(QRect(790, 30, 321, 321));
        treeWidget->setColumnCount(2);
        show_tree = new QPushButton(centralWidget);
        show_tree->setObjectName(QString::fromUtf8("show_tree"));
        show_tree->setGeometry(QRect(850, 370, 191, 41));
        QtWidgetsApplication1Class->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(QtWidgetsApplication1Class);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QtWidgetsApplication1Class->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QtWidgetsApplication1Class);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QtWidgetsApplication1Class->setStatusBar(statusBar);

        retranslateUi(QtWidgetsApplication1Class);
        QObject::connect(add_item, SIGNAL(clicked()), QtWidgetsApplication1Class, SLOT(slot1()));

        QMetaObject::connectSlotsByName(QtWidgetsApplication1Class);
    } // setupUi

    void retranslateUi(QMainWindow *QtWidgetsApplication1Class)
    {
        QtWidgetsApplication1Class->setWindowTitle(QCoreApplication::translate("QtWidgetsApplication1Class", "QtWidgetsApplication1", nullptr));
        add_item->setText(QCoreApplication::translate("QtWidgetsApplication1Class", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\215\320\273\320\265\320\274\320\265\320\275\321\202", nullptr));
        label->setText(QCoreApplication::translate("QtWidgetsApplication1Class", "\320\232\320\273\321\216\321\207", nullptr));
        label_2->setText(QCoreApplication::translate("QtWidgetsApplication1Class", "\320\227\320\275\320\260\321\207\320\265\320\275\320\270\320\265", nullptr));
        label_status->setText(QString());
        label_status_2->setText(QString());
        show_pre_order->setText(QCoreApplication::translate("QtWidgetsApplication1Class", "\320\237\321\200\321\217\320\274\320\276\320\271 \320\276\320\261\321\205\320\276\320\264", nullptr));
        label_3->setText(QCoreApplication::translate("QtWidgetsApplication1Class", "\320\232\320\273\321\216\321\207", nullptr));
        delete_item->setText(QCoreApplication::translate("QtWidgetsApplication1Class", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \321\215\320\273\320\265\320\274\320\265\320\275\321\202", nullptr));
        restore->setText(QCoreApplication::translate("QtWidgetsApplication1Class", "\320\222\320\276\321\201\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214 \320\270\320\267 \320\261\321\215\320\272\320\260\320\277\320\260", nullptr));
        show_tree->setText(QCoreApplication::translate("QtWidgetsApplication1Class", "\320\237\320\276\320\272\320\260\320\267\320\260\321\202\321\214 \320\264\320\265\321\200\320\265\320\262\320\276", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtWidgetsApplication1Class: public Ui_QtWidgetsApplication1Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTWIDGETSAPPLICATION1_H
