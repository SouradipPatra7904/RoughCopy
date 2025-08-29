#pragma once

#include <QDialog>
#include <QString>

class CodeEditor;

class FindDialog : public QDialog {
    Q_OBJECT
public:
    explicit FindDialog(CodeEditor *editor, QWidget *parent = nullptr);

    void findNext(const QString &text, bool caseSensitive);
    void replace(const QString &text, const QString &replacement, bool caseSensitive);
    void replaceAll(const QString &text, const QString &replacement, bool caseSensitive);

private:
    CodeEditor *m_editor;
};
