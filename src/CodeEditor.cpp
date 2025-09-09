#include "CodeEditor.h"
#include <QFontMetrics>
#include <QTextOption>

CodeEditor::CodeEditor(QWidget *parent)
    : QPlainTextEdit(parent)
{
    // default monospace font
    QFont f("Courier New", 12);
    setEditorFont(f);

    // default tab stop
    QFontMetrics metrics(font());
    setTabStopDistance(m_tabSpaces * metrics.horizontalAdvance(' '));

    setWordWrapMode(QTextOption::NoWrap);
    setCursorWidth(2);
}

void CodeEditor::setEditorFont(const QFont &font) {
    QFont f = font;
    setFont(f);
    QFontMetrics metrics(f);
    setTabStopDistance(m_tabSpaces * metrics.horizontalAdvance(' '));
}

void CodeEditor::setEditorColors(const QColor &fontColor, const QColor &bgColor, bool darkMode, const QString &theme) {
    QPalette p = palette();
    p.setColor(QPalette::Text, fontColor);
    p.setColor(QPalette::WindowText, fontColor);
    p.setColor(QPalette::Base, bgColor);
    p.setColor(QPalette::Window, bgColor);

    QColor selBg, selText;
    if (theme == "Light") {
        selBg = QColor("#FFB347");   // amber
        selText = Qt::black;
    } else if (theme == "Dark (Classic)") {
        selBg = QColor("#3A6EA5");   // mid-blue
        selText = Qt::white;
    } else if (theme == "Dark (Blue)") {
        selBg = QColor("#8000FF");   // bright violet/magenta
        selText = Qt::white;
    } else {
        // fallback: just contrast with background
        selBg = darkMode ? fontColor.darker(200) : fontColor.lighter(150);
        selText = darkMode ? Qt::white : Qt::black;
    }

    p.setColor(QPalette::Highlight, selBg);
    p.setColor(QPalette::HighlightedText, selText);

    setPalette(p);

    // stylesheet: caret = font color, selection = highlight
    setStyleSheet(QString(
        "QPlainTextEdit { "
        "color: %1; "
        "background-color: %2; "
        "selection-background-color: %3; "
        "selection-color: %4; }"
    ).arg(fontColor.name(), bgColor.name(), selBg.name(), selText.name()));
}


void CodeEditor::setTabSpaces(int spaces) {
    m_tabSpaces = qMax(1, spaces);
    QFontMetrics metrics(font());
    setTabStopDistance(m_tabSpaces * metrics.horizontalAdvance(' '));
}

void CodeEditor::setCaretColor(const QColor &color) {
    // caret already matches text color through setEditorColors
    QPalette p = palette();
    p.setColor(QPalette::Text, color);
    p.setColor(QPalette::WindowText, color);
    setPalette(p);
}
