#include "FindDialog.h"
#include "CodeEditor.h"
#include <QTextDocument>
#include <QTextCursor>

FindDialog::FindDialog(CodeEditor *editor, QWidget *parent)
    : QDialog(parent), m_editor(editor)
{
    // Setup UI here if needed
}

void FindDialog::findNext(const QString &text, bool caseSensitive)
{
    if (!m_editor) return;

    QTextDocument::FindFlags flags;
    if (caseSensitive) flags |= QTextDocument::FindCaseSensitively;

    QTextCursor cursor = m_editor->textCursor();
    cursor = m_editor->document()->find(text, cursor, flags);

    if (!cursor.isNull()) {
        m_editor->setTextCursor(cursor);
    }
}

void FindDialog::replace(const QString &text, const QString &replacement, bool caseSensitive)
{
    if (!m_editor) return;

    QTextCursor cursor = m_editor->textCursor();
    QTextDocument::FindFlags flags;
    if (caseSensitive) flags |= QTextDocument::FindCaseSensitively;

    if (cursor.selectedText() == text) {
        cursor.insertText(replacement);
    } else {
        cursor = m_editor->document()->find(text, cursor, flags);
        if (!cursor.isNull()) {
            m_editor->setTextCursor(cursor);
            cursor.insertText(replacement);
        }
    }
}

void FindDialog::replaceAll(const QString &text, const QString &replacement, bool caseSensitive)
{
    if (!m_editor) return;

    QTextDocument *doc = m_editor->document();
    QTextCursor cursor(doc);

    QTextDocument::FindFlags flags;
    if (caseSensitive) flags |= QTextDocument::FindCaseSensitively;

    cursor.beginEditBlock();
    while (!cursor.isNull() && !cursor.atEnd()) {
        cursor = doc->find(text, cursor, flags);
        if (!cursor.isNull()) {
            cursor.insertText(replacement);
        }
    }
    cursor.endEditBlock();
}
