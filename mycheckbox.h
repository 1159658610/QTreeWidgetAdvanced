#ifndef MYCHECKBOX_H
#define MYCHECKBOX_H

#include <QCheckBox>

class QTreeWidgetItem;

class MyCheckBox : public QCheckBox
{
    Q_OBJECT
public:
    MyCheckBox(QTreeWidgetItem *item);

    QTreeWidgetItem *tree_item() const
    {
        return m_tree_item;
    }
private:
    QTreeWidgetItem *m_tree_item;

    void set_children_checked_unchecked(QTreeWidgetItem *my_item) const;
    void set_parent_checked(QTreeWidgetItem *_tree_item) const;
    void set_parent_checked_unchecked_based_on_siblings(MyCheckBox *my_checkbox) const;
};

#endif // MYCHECKBOX_H
