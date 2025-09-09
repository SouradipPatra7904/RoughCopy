#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>
#include <QWidget>
#include <QColor>
#include <QFont>

class CodeEditor : public QPlainTextEdit {
    Q_OBJECT

public:
    explicit CodeEditor(QWidget *parent = nullptr);

    // Preferences API
    void setEditorFont(const QFont &font);
    void setEditorColors(const QColor &fontColor, const QColor &bgColor, bool darkMode, const QString &theme);
    void setTabSpaces(int spaces);
    void setCaretColor(const QColor &color); // caret = text cursor color

private:
    int m_tabSpaces = 4;
};

#endif // CODEEDITOR_H
