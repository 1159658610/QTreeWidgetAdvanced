#ifndef MYTREEUTIL_H
#define MYTREEUTIL_H

#include <QTreeWidget>
#include <QTreeWidgetItem>

#define FIRST_COLUMN 0

enum MyTreeMode
{
    ONLY_CHECKED_ITEMS,
    ALL_ITEMS
};

/**
 * this is an auxiliar function that has no be used directly
 */
template<typename MyObject, typename WidgetType, int mode> void traverse_qtreewidgetitem(QTreeWidget *tree_widget,
                                                                                         QTreeWidgetItem *tree_item,
                                                                                         MyObject object)
{
    QTreeWidgetItem *child_item = nullptr;
    QWidget *item_widget = nullptr;
    WidgetType *widget = nullptr;

    // here we traverse the children of any item (it can be top-level or not)
    if (tree_item->childCount() > 0) {
        const int n_child = tree_item->childCount();
        for (int a = 0; a < n_child; ++a) {
            child_item = tree_item->child(a);
            item_widget = tree_widget->itemWidget(child_item, FIRST_COLUMN);
            widget = static_cast<WidgetType *>(item_widget);
            if (mode == ALL_ITEMS) {
                object->process(tree_widget, child_item);

                // here we traverse recursively the children of the item
                traverse_qtreewidgetitem<MyObject, WidgetType, mode>(tree_widget, child_item, object);
            } else if (mode == ONLY_CHECKED_ITEMS) {
                if (widget) {
                    if (widget->isChecked()) {
                        object->process(tree_widget, child_item);

                        // here we traverse recursively the children of the item
                        traverse_qtreewidgetitem<MyObject, WidgetType, mode>(tree_widget, child_item, object);
                    }
                }
            }
        }
    } else {
        // here it has no children, we can process it directly
        item_widget = tree_widget->itemWidget(tree_item, FIRST_COLUMN);
        widget = static_cast<WidgetType *>(item_widget);
        if (mode == ALL_ITEMS) {
            object->process(tree_widget, tree_item);
        } else if (mode == ONLY_CHECKED_ITEMS) {
            if (widget) {
                if (widget->isChecked()) {
                    object->process(tree_widget, tree_item);
                }
            }
        }
    }
}

/**
 * this function needs a QTreeWidget to traverse it and an object pointer that has the "process" method that has as
 * arguments a "QTreeWidget *" and a "QTreeWidgetItem *"
 *
 * Example:
 * QTreeWidget *tree = new QTreeWidget;
 * ...
 * MyObject *object = new MyObject;
 * traverse_qtreewidget<MyObject, QCheckBox, ONLY_CHECKED_ITEMS>(tree, object);
 */
template<typename MyObject, typename WidgetType, int mode> void traverse_qtreewidget(QTreeWidget *tree_widget,
                                                                                     MyObject object)
{
    QTreeWidgetItem *top_item = nullptr;

    // here we traverse the top-level items to traverse its children
    const int n_tops = tree_widget->topLevelItemCount();
    for (int a = 0; a < n_tops; ++a) {
        top_item = tree_widget->topLevelItem(a);

        // here we traverse the children of the top-level item
        traverse_qtreewidgetitem<MyObject, WidgetType, mode>(tree_widget, top_item, object);
    }
}

/**
 * @brief qtreewidgetitem_assign_qcheckbox
 * @param tree_item
 * @param text
 * this function assigns a QCheckBox to a QTreeWidgetItem
 */
void qtreewidgetitem_assign_qcheckbox(QTreeWidget *tree_widget, QTreeWidgetItem *tree_item);

#endif // MYTREEUTIL_H
