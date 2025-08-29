#include "MainWindow.h"
#include "SearchReplaceDialog.h"
#include "CodeEditor.h"

#include <QMenuBar>
#include <QMessageBox>
#include <QTextCursor>
#include <QTextDocument>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    editor = new CodeEditor(this);
    setCentralWidget(editor);

    // Create Edit menu
    QMenu *editMenu = menuBar()->addMenu("&Edit");

    QAction *searchReplaceAct = new QAction("Search/Replace", this);
    editMenu->addAction(searchReplaceAct);

    connect(searchReplaceAct, &QAction::triggered, this, &MainWindow::openSearchReplaceDialog);
}

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
