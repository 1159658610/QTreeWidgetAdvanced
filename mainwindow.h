#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QTreeWidget;
class QTreeWidgetItem;

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    virtual void process(QTreeWidget *tree_widget, QTreeWidgetItem *tree_item);
private slots:
    void on_process_pushbutton_clicked();

private:
    Ui::MainWindow *ui;

    bool listwidget_exists_item(const QString &item) const;
};

#endif // MAINWINDOW_H
