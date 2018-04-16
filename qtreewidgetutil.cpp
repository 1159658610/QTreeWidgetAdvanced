#include "qtreewidgetutil.h"
#include "mycheckbox.h"
#include <QTreeWidget>

void qtreewidgetitem_assign_qcheckbox(QTreeWidget *tree_widget, QTreeWidgetItem *tree_item)
{
    MyCheckBox *my_check_box = new MyCheckBox(tree_item);
    tree_widget->setItemWidget(tree_item, FIRST_COLUMN, my_check_box);
}
