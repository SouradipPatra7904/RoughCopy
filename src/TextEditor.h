#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QWidget>
#include <QFont>
#include <QColor>
#include <QString>

class CodeEditor;
class PreferencesDialog;

class TextEditor : public QWidget {
    Q_OBJECT

public:
    explicit TextEditor(QWidget *parent = nullptr);

    // open the preferences dialog
    void openPreferences();

    // simple helpers used by MainWindow
    void clearEditor();
    void setEditorText(const QString &text);
    QString editorText() const;

public slots:
    void applyPreferences(const QFont &font, const QColor &fontColor, const QColor &bgColor, const QString &theme);
    void revertPreferences();

private:
    CodeEditor *m_editor;
    PreferencesDialog *m_prefDialog;
};

#endif // TEXTEDITOR_H
