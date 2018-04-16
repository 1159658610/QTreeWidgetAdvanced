#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qtreewidgetutil.h"
#include "mycheckbox.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTreeWidgetItem *top1 = new QTreeWidgetItem({"Grupo 1"});
    QTreeWidgetItem *top2 = new QTreeWidgetItem({"Grupo 2"});
    QTreeWidgetItem *top3 = new QTreeWidgetItem({"Grupo 3"});

    QList<QTreeWidgetItem *> children1;
    QList<QTreeWidgetItem *> children2;
    QList<QTreeWidgetItem *> children3;

    children1.append(new QTreeWidgetItem({"Perro"}));
    children1.append(new QTreeWidgetItem({"Gato"}));
    children1.append(new QTreeWidgetItem({"Conejo"}));

    children2.append(new QTreeWidgetItem({"Ratón"}));
    children2.append(new QTreeWidgetItem({"Pez"}));
    children2.append(new QTreeWidgetItem({"Canguro"}));

    children3.append(new QTreeWidgetItem({"Elefante"}));
    children3.append(new QTreeWidgetItem({"León"}));
    children3.append(new QTreeWidgetItem({"Oso"}));

    top1->addChildren(children1);
    top2->addChildren(children2);
    top3->addChildren(children3);

    ui->treeWidget->addTopLevelItem(top1);
    ui->treeWidget->addTopLevelItem(top2);
    ui->treeWidget->addTopLevelItem(top3);

    const int n_tops = ui->treeWidget->topLevelItemCount();
    for (int a = 0; a < n_tops; ++a) {
        const int n_child = ui->treeWidget->topLevelItem(a)->childCount();
        qtreewidgetitem_assign_qcheckbox(ui->treeWidget, ui->treeWidget->topLevelItem(a));
        for (int b = 0; b < n_child; ++b) {
            qtreewidgetitem_assign_qcheckbox(ui->treeWidget, ui->treeWidget->topLevelItem(a)->child(b));
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::process(QTreeWidget *tree_widget, QTreeWidgetItem *tree_item)
{
    MyCheckBox *checkbox = static_cast<MyCheckBox *>(ui->treeWidget->itemWidget(tree_item, FIRST_COLUMN));

    if (!listwidget_exists_item(checkbox->text())) {
        ui->listWidget->addItem(checkbox->text());
    }

    (void) tree_widget;
}

void MainWindow::on_process_pushbutton_clicked()
{
    ui->listWidget->clear();

    traverse_qtreewidget<MainWindow *, MyCheckBox, ONLY_CHECKED_ITEMS>(ui->treeWidget, this);
}

bool MainWindow::listwidget_exists_item(const QString &item) const
{
    const int n_items = ui->listWidget->count();
    for (int a = 0; a < n_items; ++a) {
        if (ui->listWidget->item(a)->text() == item) {
            return true;
        }
    }
    return false;
}
