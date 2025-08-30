#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class CodeEditor;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    // File actions
    void newFile();
    void openFile();
    void saveFile();

    // View actions
    void openPreferences();

    // Search/Replace
    void openSearchReplaceDialog();

private:
    CodeEditor *editor;
    QString currentFile;
};

#endif // MAINWINDOW_H
