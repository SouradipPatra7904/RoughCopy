#pragma once
#include <QWidget>
#include <QTextDocument>
#include "CodeEditor.h"
#include "PreferencesDialog.h"

class TextEditor : public QWidget
{
    Q_OBJECT

public:
    explicit TextEditor(QWidget* parent = nullptr);

    void openFile(const QString& path);
    void saveFile();
    void openPreferences();

signals:
    void preferencesReverted();

private:
    CodeEditor* m_editor;
    PreferencesDialog* m_prefDialog;
};
