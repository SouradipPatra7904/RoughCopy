#include "FileExplorer.h"

FileExplorer::FileExplorer(QWidget* parent)
    : QWidget(parent)
{
    m_treeView = new QTreeView(this);
    m_model = new QFileSystemModel(this);
    m_model->setRootPath(QDir::homePath());
    m_model->setFilter(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);

    m_treeView->setModel(m_model);
    m_treeView->setRootIndex(m_model->index(QDir::homePath()));
    m_treeView->setHeaderHidden(true);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(m_treeView);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    connect(m_treeView, &QTreeView::doubleClicked,
            this, &FileExplorer::onFileClicked);
}

void FileExplorer::onFileClicked(const QModelIndex& index)
{
    QString filePath = m_model->filePath(index);
    if (QFileInfo(filePath).isFile()) {
        emit fileSelected(filePath);

        emit fileOpened(filePath);
        
    }
}
