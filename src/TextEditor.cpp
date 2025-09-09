#include "TextEditor.h"
#include "CodeEditor.h"
#include "PreferencesDialog.h"
#include <QVBoxLayout>

TextEditor::TextEditor(QWidget *parent)
    : QWidget(parent),
      m_editor(new CodeEditor(this)),
      m_prefDialog(nullptr)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(m_editor);
    setLayout(layout);
}

void TextEditor::openPreferences() {
    if (!m_prefDialog) {
        m_prefDialog = new PreferencesDialog(this);

        // preview/apply
        connect(m_prefDialog, &PreferencesDialog::preferencesApplied,
                this, &TextEditor::applyPreferences);

        // revert to defaults
        connect(m_prefDialog, &PreferencesDialog::preferencesReverted,
                this, &TextEditor::revertPreferences);
    }

    m_prefDialog->exec();
}

void TextEditor::applyPreferences(const QFont &font,
                                  const QColor &fontColor,
                                  const QColor &bgColor,
                                  const QString &theme)
{
    // Apply strict theme rules for the three fixed themes:
    // Light:  background = #ffe4c4 (bisque), text = #000000
    // Dark (Classic) / Dark (Blue): background = #001e42, text = #00f0ff
    QFont appliedFont = font;
    QColor appliedFontColor = fontColor;
    QColor appliedBgColor = bgColor;
    bool dark = false;

    if (theme == "Light") {
        appliedBgColor = QColor("#ffe4c4");
        appliedFontColor = QColor("#000000");
        dark = false;
    } 
    
    else if (theme == "Dark (Classic)") {
        appliedBgColor = QColor("#000000");
        appliedFontColor = QColor("#ffe4c4");
        dark = true;
    } 
    else if (theme == "Dark (Blue)") {
        appliedBgColor = QColor("#001e42");
        appliedFontColor = QColor("#00f0ff");
        dark = true;
    }
    else {
        // fallback = Light
        appliedBgColor   = QColor("#ffe4c4");
        appliedFontColor = QColor("#000000");
        dark = false;
    }

    // apply to CodeEditor
    m_editor->setEditorFont(appliedFont);
    m_editor->setEditorColors(appliedFontColor, appliedBgColor, dark, theme);
    m_editor->setCaretColor(appliedFontColor);
}

void TextEditor::revertPreferences() {
    // Defaults = Light theme (bisque / black)
    QFont defFont("Courier New", 12);
    QColor defFontColor("#000000");
    QColor defBgColor("#ffe4c4");
    bool dark = false;
    QString theme = "Light";

    m_editor->setEditorFont(defFont);
    m_editor->setEditorColors(defFontColor, defBgColor, dark, theme);
    m_editor->setCaretColor(defFontColor);
}

// ----------------------
// Simple editor helpers
// ----------------------
void TextEditor::clearEditor() {
    if (m_editor) m_editor->clear();
}

void TextEditor::setEditorText(const QString &text) {
    if (m_editor) m_editor->setPlainText(text);
}

QString TextEditor::editorText() const {
    if (m_editor) return m_editor->toPlainText();
    return QString();
}
