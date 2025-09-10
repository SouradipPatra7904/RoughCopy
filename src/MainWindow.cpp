#include "MainWindow.h"
#include "TextEditor.h"
#include "PreferencesDialog.h"
#include "SearchReplaceDialog.h"

#include <QPlainTextEdit>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QDialog>

// --------------------------------
// Constructor
// --------------------------------
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_searchDialog(nullptr)
{
    m_textEditor = new TextEditor(this);
    setCentralWidget(m_textEditor);

    // Force startup theme = Light
    QFont defFont("JetBrains Mono Medium", 20);
    QColor defFontColor("#000000");
    QColor defBgColor("#ffe4c4");
    QString defTheme = "Light";

    m_textEditor->applyPreferences(defFont, defFontColor, defBgColor, defTheme);

    // File menu
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

    // Edit menu
    QMenu *editMenu = menuBar()->addMenu("&Edit");

    // View menu
    QMenu *viewMenu = menuBar()->addMenu("&View");
    QAction *prefAct = viewMenu->addAction("&Preferences");
    connect(prefAct, &QAction::triggered, this, &MainWindow::openPreferences);

    // Find / Replace
    QAction *findReplaceAct = editMenu->addAction("&Find/Replace");
    connect(findReplaceAct, &QAction::triggered, this, &MainWindow::openFindReplace);

    // Help menu
    QMenu *helpMenu = menuBar()->addMenu("&Help");
    QAction *manAct = helpMenu->addAction("&Man Page");
    connect(manAct, &QAction::triggered, this, &MainWindow::openManPage);

    // Default theme
    m_currentTheme = "Light";

    
}

// --------------------------------
// Manual Page
// --------------------------------
void MainWindow::openManPage() {
    QString text;
    text += "RoughCopy - Minimalist Editor\n\n";
    text += "USAGE:\n";
    text += "  - File > Open : Open a file\n";
    text += "  - File > Save : Save current file\n";
    text += "  - View > Preferences : Change theme, font, colors\n";
    text += "  - View > Find/Replace : Search and replace text\n";
    text += "  - Help > Man Page : Show this help\n";

    QTextEdit *helpView = new QTextEdit;
    helpView->setReadOnly(true);
    helpView->setText(text);

    if (m_currentTheme == "Light") {
        helpView->setStyleSheet("QTextEdit { background: #ffe4c4; color: #000000; }");
    }
    else if (m_currentTheme == "Dark") {
        helpView->setStyleSheet("QTextEdit { background: #000000; color: #ffe4c4; }");
    }
    else if (m_currentTheme == "Starry Night") {
        helpView->setStyleSheet("QTextEdit { background: #001e42; color: #00f0ff; }");
    }

    QDialog dlg(this);
    dlg.setWindowTitle("Man Page");
    QVBoxLayout layout;
    layout.addWidget(helpView);
    dlg.setLayout(&layout);
    dlg.resize(500, 400);
    dlg.exec();
}

// --------------------------------
// File actions
// --------------------------------
void MainWindow::newFile() {
    TextEditor *te = qobject_cast<TextEditor*>(centralWidget());
    if (te) te->clearEditor();
    currentFile.clear();
}

void MainWindow::openFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open File");
    if (fileName.isEmpty()) return;

    QFile f(fileName);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Cannot open file: " + f.errorString());
        return;
    }

    QTextStream in(&f);
    QString content = in.readAll();
    f.close();

    TextEditor *te = qobject_cast<TextEditor*>(centralWidget());
    if (te) te->setEditorText(content);

    currentFile = fileName;
}

void MainWindow::saveFile() {
    QString fileName = currentFile;
    if (fileName.isEmpty()) {
        fileName = QFileDialog::getSaveFileName(this, "Save File As");
        if (fileName.isEmpty()) return;
        currentFile = fileName;
    }

    TextEditor *te = qobject_cast<TextEditor*>(centralWidget());
    if (!te) return;

    QFile f(fileName);
    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Cannot save file: " + f.errorString());
        return;
    }

    QTextStream out(&f);
    out << te->editorText();
    f.close();
}

// --------------------------------
// Preferences
// --------------------------------
void MainWindow::openPreferences() {
    PreferencesDialog pref(this);

    connect(&pref, &PreferencesDialog::preferencesApplied,
            this, [this](const QFont &font, const QColor &fontColor, const QColor &bgColor, const QString &theme) {
        TextEditor *te = qobject_cast<TextEditor*>(centralWidget());
        if (te) te->applyPreferences(font, fontColor, bgColor, theme);
        m_currentTheme = theme;
    });

    pref.exec();
}

// --------------------------------
// Find / Replace
// --------------------------------
void MainWindow::openFindReplace() {
    if (!m_searchDialog) {
        m_searchDialog = new SearchReplaceDialog(this);
        auto editor = centralWidget()->findChild<QPlainTextEdit*>();

        connect(m_searchDialog, &SearchReplaceDialog::findNext,
                [editor](const QString &text, bool caseSensitive) {
            if (!editor) return;
            QTextDocument::FindFlags flags;
            if (caseSensitive) flags |= QTextDocument::FindCaseSensitively;
            if (!editor->find(text, flags)) {
                editor->moveCursor(QTextCursor::Start);
                if (!editor->find(text, flags)) {
                    QMessageBox::information(editor, "Find", "No more matches found.");
                }
            }
        });

        connect(m_searchDialog, &SearchReplaceDialog::replace,
                [editor](const QString &text, const QString &replacement, bool caseSensitive) {
            if (!editor) return;
            QTextCursor cursor = editor->textCursor();
            if (cursor.hasSelection() && cursor.selectedText() == text) {
                cursor.insertText(replacement);
            }
        });

        connect(m_searchDialog, &SearchReplaceDialog::replaceAll,
                [editor](const QString &text, const QString &replacement, bool caseSensitive) {
            if (!editor) return;
            QTextDocument::FindFlags flags;
            if (caseSensitive) flags |= QTextDocument::FindCaseSensitively;
            editor->moveCursor(QTextCursor::Start);
            while (editor->find(text, flags)) {
                QTextCursor cursor = editor->textCursor();
                cursor.insertText(replacement);
            }
        });
    }
    m_searchDialog->show();
    m_searchDialog->raise();
    m_searchDialog->activateWindow();
}
