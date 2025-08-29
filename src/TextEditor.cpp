#include "TextEditor.h"
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>

TextEditor::TextEditor(QWidget* parent)
    : QWidget(parent)
{
    m_editor = new CodeEditor(this);
    m_prefDialog = new PreferencesDialog(this);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(m_editor);
    setLayout(layout);

    // Connect preferences reverted
    connect(m_prefDialog, &PreferencesDialog::preferencesReverted, this, &TextEditor::preferencesReverted);
}

void TextEditor::openFile(const QString& path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    m_editor->setPlainText(in.readAll());
    file.close();
}

void TextEditor::saveFile()
{
    // Implement file save logic here
}

void TextEditor::openPreferences()
{
    // Save current state for revert
    bool prevDark = m_editor->isDarkMode();
    int prevTabs = m_editor->tabSpaces();
    QFont prevFont = m_editor->font();

    if (m_prefDialog->exec() == QDialog::Accepted) {
        // Apply preferences
        m_editor->setDarkMode(m_prefDialog->isDarkMode());
        m_editor->setTabSpaces(m_prefDialog->tabSpaces());
        m_editor->setFont(m_prefDialog->selectedFont());
        m_editor->triggerBracketHighlight();
    } else {
        // Revert on cancel
        m_editor->setDarkMode(prevDark);
        m_editor->setTabSpaces(prevTabs);
        m_editor->setFont(prevFont);
        emit preferencesReverted();
    }
}
