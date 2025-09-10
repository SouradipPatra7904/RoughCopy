#pragma once
#include <QWidget>
#include <QTreeView>
#include <QFileSystemModel>
#include <QVBoxLayout>

class FileExplorer : public QWidget
{
    Q_OBJECT
public:
    explicit FileExplorer(QWidget* parent = nullptr);

signals:
    void fileOpened(const QString& filePath);
    void fileSelected(const QString &filePath);

private slots:
    void onFileClicked(const QModelIndex& index);


private:
    QTreeView* m_treeView;
    QFileSystemModel* m_model;
};
