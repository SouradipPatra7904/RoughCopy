#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "TextEditor.h"
#include "SearchReplaceDialog.h"
#include <QMainWindow>
#include <QString>

class TextEditor;
class SearchReplaceDialog;


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void newFile();
    void openFile();
    void saveFile();
    void openPreferences();
    void openFindReplace();
    void openManPage();


private:
    TextEditor *m_textEditor;
    QString currentFile;
    SearchReplaceDialog *m_searchDialog;

    // track current theme for man-page / theme-aware help UI
    QString m_currentTheme;


};

#endif // MAINWINDOW_H
