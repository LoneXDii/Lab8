#include "stdafx.h"
#include "qtwidgetsapplication1.h"

extern "C" int add_node(unsigned int root_ptr, unsigned int node_ptr, int key, int value);
extern "C" int SetRoot(unsigned int root_ptr, int key, int value);
extern "C" int update_height(unsigned int node_ptr);
extern "C" int go_pre_order(unsigned int root_ptr, unsigned int memory_ptr);
extern "C" unsigned int delete_node(unsigned int root_ptr, int key);
extern "C" unsigned int get_max_node(unsigned int root_ptr);

QtWidgetsApplication1::QtWidgetsApplication1(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    is_tree_empty = true;

    QFile file("file.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
    file.close();
}

QtWidgetsApplication1::~QtWidgetsApplication1()
{
    
}

void QtWidgetsApplication1::on_add_item_clicked()
{
    if (avl_tree->root != nullptr) {

        void* memory_buffer = malloc(1000);
        int count_nodes = go_pre_order(reinterpret_cast <unsigned int> (avl_tree->root), reinterpret_cast <unsigned int> (memory_buffer));
        std::vector <std::pair<int, int>> vec;
        int* iter = (int*)memory_buffer;
        for (int i = 0; i < count_nodes; i++) {
            vec.push_back(std::make_pair(*iter, *(iter + 1)));
            iter += 3;
        }
        QString str;
        str += "|";
        for (int i = 0; i < count_nodes; i++) {
            str += QString::number(vec[i].first) + "-" + QString::number(vec[i].second) + "|";
        }

        QFile file("file.txt");
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
            return;
        }
        QTextStream out(&file);
        out << str;
        file.close();
    }

    ui.label_status->setText("Element added");

    if (ui.lineEdit_key->text().isEmpty() || ui.lineEdit_value->text().isEmpty()) {
        QMessageBox::warning(this, "Oops", "You enter invalid data");
        return;
    }

    is_tree_empty = false;

    int key = ui.lineEdit_key->text().toInt();
    int value = ui.lineEdit_value->text().toInt();

    ui.label_status_2->setText(ui.lineEdit_key->text() + " " + ui.lineEdit_value->text());
    
    void* root = avl_tree->root;
    avl_tree->number_nodes += 1;
    int status = 0;

    if (root == nullptr) {
        root = malloc(30); // íàäî 20
        avl_tree->root = root;
        status = SetRoot(reinterpret_cast <unsigned int> (root), key, value);
    }
    else {
        void* node_ptr = malloc(30); // íàäî 20
        status = add_node(reinterpret_cast <unsigned int> (root), reinterpret_cast <unsigned int> (node_ptr), key, value);
    }

    ui.lineEdit_key->clear();
    ui.lineEdit_value->clear();
}

void QtWidgetsApplication1::on_show_pre_order_clicked() {
    ui.label_status->clear();
    ui.label_status_2->clear();
    ui.lineEdit_pre_order->clear();

    void* memory_buffer = malloc(1000);

    if (is_tree_empty) {
        ui.label_status->setText("Tree is clear");
    }
    else {
        int count_nodes = go_pre_order(reinterpret_cast <unsigned int> (avl_tree->root), reinterpret_cast <unsigned int> (memory_buffer));

        ui.label_status->setText("Count nodes = " + QString::number(count_nodes));

        std::vector <std::pair<int, int>> vec;

        int* iter = (int*)memory_buffer;

        for (int i = 0; i < count_nodes; i++) {
            vec.push_back(std::make_pair(*iter, *(iter + 1)));
            iter += 3;
        }

        QString str;
        str += "| ";
        for (int i = 0; i < count_nodes; i++) {
            str += QString::number(vec[i].first) + "-" + QString::number(vec[i].second) + " | ";
        }
        ui.lineEdit_pre_order->setText(str);
    }
}

void QtWidgetsApplication1::on_delete_item_clicked()
{
    if (avl_tree->root != nullptr) {
        void* memory_buffer = malloc(1000);
        int count_nodes = go_pre_order(reinterpret_cast <unsigned int> (avl_tree->root), reinterpret_cast <unsigned int> (memory_buffer));
        std::vector <std::pair<int, int>> vec;
        int* iter = (int*)memory_buffer;
        for (int i = 0; i < count_nodes; i++) {
            vec.push_back(std::make_pair(*iter, *(iter + 1)));
            iter += 3;
        }
        QString str;
        str += "|";
        for (int i = 0; i < count_nodes; i++) {
            str += QString::number(vec[i].first) + "-" + QString::number(vec[i].second) + "|";
        }

        QFile file("file.txt");
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
            return;
        }
        QTextStream out(&file);
        out << str;
        file.close();
    }


    ui.label_status->clear();
    ui.label_status_2->clear();

    if (ui.lineEdit_key_del->text().isEmpty()) {
        QMessageBox::warning(this, "Oops", "You enter invalid data");
        return;
    }

    int key = ui.lineEdit_key_del->text().toInt();
    void* root = avl_tree->root;
    if (root == nullptr) {
        QMessageBox::warning(this, "Oops", "AVL tree is empty");
        ui.lineEdit_key_del->clear();
        return;
    }
    else {
        delete_node(reinterpret_cast <unsigned int> (root), key);
    }

    avl_tree->number_nodes -= 1;

    void* memory_buffer = malloc(1000);
    int count_nodes = go_pre_order(reinterpret_cast <unsigned int> (avl_tree->root), reinterpret_cast <unsigned int> (memory_buffer));
    if (count_nodes >= 2) {
        avl_tree->number_nodes = count_nodes;
    }
    if (avl_tree->number_nodes == 0) {
        is_tree_empty = true;
        avl_tree->root = nullptr;
    }
    ui.lineEdit_key_del->clear();
}

void QtWidgetsApplication1::on_restore_clicked()
{
    QFile file("file.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    QTextStream in(&file);
    QString text;
    while (!in.atEnd()) {
        text = in.readLine();
    }

    file.close();

    if (text.isEmpty()) {
        QMessageBox::warning(this, "Oops", "Backup is empty");
        return;
    }

    std::vector <std::pair<int, int>> vec;
    
    QStringList list1 = text.split("|");
    list1.pop_back();
    list1.pop_front();
    for (int i = 0; i < list1.size(); i++) {
        QString str1 = list1[i];
        QStringList list2 = str1.split('-');
        vec.push_back(std::make_pair(list2[0].toInt(), list2[1].toInt()));
    }

    avl_tree->root = nullptr;
    avl_tree->number_nodes = vec.size();

    void* root = avl_tree->root;
    int status = 0;

    for (int i = 0; i < vec.size(); i++) {
        if (root == nullptr) {
            root = malloc(30);  // íàäî 20
            avl_tree->root = root;
            status = SetRoot(reinterpret_cast <unsigned int> (root), vec[i].first, vec[i].second);
        }
        else {
            void* node_ptr = malloc(30);  // íàäî 20
            status = add_node(reinterpret_cast <unsigned int> (root), reinterpret_cast <unsigned int> (node_ptr), vec[i].first, vec[i].second);
        }
    }

}

void QtWidgetsApplication1::on_show_tree_clicked()
{
    void* memory_buffer = malloc(1000);

    ui.treeWidget->clear();

    if (is_tree_empty) {
        QMessageBox::warning(this, "Oops", "AVL tree is empty");
        return;
    }
    else {
        int count_nodes = go_pre_order(reinterpret_cast <unsigned int> (avl_tree->root), reinterpret_cast <unsigned int> (memory_buffer));

        ui.label_status->setText("Count nodes = " + QString::number(count_nodes));

        QTreeWidgetItem* root = new QTreeWidgetItem(ui.treeWidget);
        root->setText(0, "Root");
        add_node_tree(root, reinterpret_cast<unsigned int>(avl_tree->root));
        ui.treeWidget->expandAll();
    }
}

void QtWidgetsApplication1::add_node_tree(QTreeWidgetItem* parent, unsigned int node_ptr)
{
    if (node_ptr == 0) {
        return;
    }
    int* ptr = reinterpret_cast<int*>(node_ptr);

    QTreeWidgetItem* item = new QTreeWidgetItem(parent);
    item->setText(0, QString::number(*(ptr + 2)));
    item->setText(1, QString::number(*(ptr + 3)));

    add_node_tree(item, *(ptr));
    add_node_tree(item, *(ptr + 1));
}
