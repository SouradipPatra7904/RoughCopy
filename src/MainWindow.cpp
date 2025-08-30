#include "MainWindow.h"
#include "CodeEditor.h"
#include "SearchReplaceDialog.h"

#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QTextDocument>
#include <QTextCursor>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    editor = new CodeEditor(this);
    setCentralWidget(editor);

    // ---- FILE Menu ----
    QMenu *fileMenu = menuBar()->addMenu("&File");

    QAction *newAct = new QAction("&New", this);
    QAction *openAct = new QAction("&Open...", this);
    QAction *saveAct = new QAction("&Save", this);

    connect(newAct, &QAction::triggered, this, &MainWindow::newFile);
    connect(openAct, &QAction::triggered, this, &MainWindow::openFile);
    connect(saveAct, &QAction::triggered, this, &MainWindow::saveFile);

    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);

    // ---- EDIT Menu ----
    QMenu *editMenu = menuBar()->addMenu("&Edit");

    QAction *searchReplaceAct = new QAction("Search/Replace", this);
    connect(searchReplaceAct, &QAction::triggered, this, &MainWindow::openSearchReplaceDialog);
    editMenu->addAction(searchReplaceAct);

    // ---- VIEW Menu ----
    QMenu *viewMenu = menuBar()->addMenu("&View");

    QAction *preferencesAct = new QAction("&Preferences", this);
    connect(preferencesAct, &QAction::triggered, this, &MainWindow::openPreferences);
    viewMenu->addAction(preferencesAct);
}

// ---------------- FILE ----------------

void MainWindow::newFile() {
    editor->clear();
    currentFile.clear();
}

void MainWindow::openFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open File");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            editor->setPlainText(in.readAll());
            currentFile = fileName;
        } else {
            QMessageBox::warning(this, "Error", "Cannot open file.");
        }
    }
}

void MainWindow::saveFile() {
    QString fileName = currentFile;
    if (fileName.isEmpty()) {
        fileName = QFileDialog::getSaveFileName(this, "Save File");
        if (fileName.isEmpty())
            return;
        currentFile = fileName;
    }

    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << editor->toPlainText();
    } else {
        QMessageBox::warning(this, "Error", "Cannot save file.");
    }
}

// ---------------- VIEW ----------------

void MainWindow::openPreferences() {
    QMessageBox::information(this, "Preferences", "Preferences dialog placeholder.");
}

// ---------------- SEARCH/REPLACE ----------------

void MainWindow::openSearchReplaceDialog() {
    SearchReplaceDialog dialog(this);

    // Find Next
    connect(&dialog, &SearchReplaceDialog::findNext,
            this, [this](const QString &text, bool caseSensitive) {
                QTextDocument::FindFlags flags;
                if (caseSensitive)
                    flags |= QTextDocument::FindCaseSensitively;

                if (!editor->find(text, flags)) {
                    QMessageBox::information(this, "Find", "No more matches found.");
                }
            });

    // Replace current
    connect(&dialog, &SearchReplaceDialog::replace,
            this, [this](const QString &text, const QString &replacement, bool caseSensitive) {
                QTextCursor cursor = editor->textCursor();

                if (cursor.hasSelection() && cursor.selectedText() == text) {
                    cursor.insertText(replacement);
                }

                QTextDocument::FindFlags flags;
                if (caseSensitive)
                    flags |= QTextDocument::FindCaseSensitively;

                editor->find(text, flags);
            });

    // Replace all
    connect(&dialog, &SearchReplaceDialog::replaceAll,
            this, [this](const QString &text, const QString &replacement, bool caseSensitive) {
                editor->moveCursor(QTextCursor::Start);
                QTextDocument::FindFlags flags;
                if (caseSensitive)
                    flags |= QTextDocument::FindCaseSensitively;

                while (editor->find(text, flags)) {
                    QTextCursor cursor = editor->textCursor();
                    cursor.insertText(replacement);
                }
            });

    dialog.exec();
}
