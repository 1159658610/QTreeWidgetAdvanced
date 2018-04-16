#include "mycheckbox.h"
#include "qtreewidgetutil.h"

#include <QTreeWidget>
#include <QTreeWidgetItem>

MyCheckBox::MyCheckBox(QTreeWidgetItem *item)
    : QCheckBox(item->treeWidget())
{
    m_tree_item = item;
    setText(m_tree_item->text(FIRST_COLUMN));
    m_tree_item->setText(FIRST_COLUMN, "");

    connect(this, &MyCheckBox::clicked, this, [&]()
    {
        set_children_checked_unchecked(m_tree_item);
        if (isChecked()) {
            set_parent_checked(m_tree_item);
        }
        set_parent_checked_unchecked_based_on_siblings(this);
    });
}

void MyCheckBox::set_children_checked_unchecked(QTreeWidgetItem *my_item) const
{
    // variables
    QWidget *item_widget = nullptr;
    QTreeWidget *tree_widget = nullptr;
    QTreeWidgetItem *child_item = nullptr;
    MyCheckBox *my_checkbox = nullptr;
    MyCheckBox *item_checkbox = nullptr;

    // algorithm
    tree_widget = my_item->treeWidget();
    my_checkbox = static_cast<MyCheckBox *>(tree_widget->itemWidget(my_item, FIRST_COLUMN));
    const int n_child = my_item->childCount();
    for (int a = 0; a < n_child; ++a) {
        child_item = my_item->child(a);
        item_widget = tree_widget->itemWidget(child_item, FIRST_COLUMN);
        item_checkbox = static_cast<MyCheckBox *>(item_widget);
        item_checkbox->setChecked(my_checkbox->isChecked());
        set_children_checked_unchecked(child_item);
    }
}

void MyCheckBox::set_parent_checked(QTreeWidgetItem *my_tree_item) const
{
    // variables
    QWidget *parent_widget = nullptr;
    QTreeWidget *tree_widget = nullptr;
    QTreeWidgetItem *parent_item = nullptr;
    MyCheckBox *parent_checkbox = nullptr;

    // algorithm
    tree_widget = my_tree_item->treeWidget();
    parent_item = my_tree_item->parent();
    if (parent_item) {
        parent_widget = tree_widget->itemWidget(parent_item, FIRST_COLUMN);
        parent_checkbox = static_cast<MyCheckBox *>(parent_widget);
        parent_checkbox->setChecked(true);
        set_parent_checked(parent_item);
    }
}

void MyCheckBox::set_parent_checked_unchecked_based_on_siblings(MyCheckBox *my_checkbox) const
{
    // variables
    QWidget *item_widget = nullptr;
    QWidget *parent_item_widget = nullptr;
    QTreeWidgetItem *item_parent = nullptr;
    QTreeWidgetItem *child_item = nullptr;
    QTreeWidget *tree_widget = nullptr;
    MyCheckBox *child_checkbox = nullptr;
    MyCheckBox *my_checkbox_parent = nullptr;
    int checked_unchecked_count = 0;

    // algorithm
    item_parent = my_checkbox->m_tree_item->parent();
    if (item_parent) {
        tree_widget = item_parent->treeWidget();
        parent_item_widget = tree_widget->itemWidget(item_parent, FIRST_COLUMN);
        my_checkbox_parent = static_cast<MyCheckBox *>(parent_item_widget);
        const int n_child = item_parent->childCount();
        checked_unchecked_count = 0;
        for (int a = 0; a < n_child; ++a) {
            child_item = item_parent->child(a);
            item_widget = tree_widget->itemWidget(child_item, FIRST_COLUMN);
            child_checkbox = static_cast<MyCheckBox *>(item_widget);
            if (child_checkbox->isChecked() == my_checkbox->isChecked()) {
                ++checked_unchecked_count;
            }
        }
        if (checked_unchecked_count == n_child) {
            my_checkbox_parent->setChecked(my_checkbox->isChecked());
            set_parent_checked_unchecked_based_on_siblings(my_checkbox_parent);
        }
    }
}
