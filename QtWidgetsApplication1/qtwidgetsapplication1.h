#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_qtwidgetsapplication1.h"
#include <qabstractbutton.h>
#include "AvlTree.h"

class QtWidgetsApplication1 : public QMainWindow
{
    Q_OBJECT

public:
    QtWidgetsApplication1(QWidget *parent = nullptr);
    ~QtWidgetsApplication1();

    AvlTree* avl_tree = new AvlTree();

private slots:
    void on_add_item_clicked();

    void on_show_pre_order_clicked();

    void on_delete_item_clicked();

    void on_restore_clicked();
    
    void on_show_tree_clicked();

    void add_node_tree(QTreeWidgetItem* parent, unsigned int node_ptr);

private:
    Ui::QtWidgetsApplication1Class ui;

    bool is_tree_empty;

};
