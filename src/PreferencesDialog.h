#pragma once
#include <QDialog>
#include <QFont>
#include <QCheckBox>
#include <QSpinBox>
#include <QFontComboBox>
#include <QPushButton>

class PreferencesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PreferencesDialog(QWidget* parent = nullptr);

    bool isDarkMode() const;
    void setDarkMode(bool enabled);

    int tabSpaces() const;
    void setTabSpaces(int spaces);

    QFont selectedFont() const;
    void setSelectedFont(const QFont& font);

signals:
    void preferencesReverted();

private:
    void setupUI();
    void connectSignals();

private:
    QCheckBox* m_darkModeCheck;
    QSpinBox* m_tabSpacesSpin;
    QFontComboBox* m_fontCombo;

    QPushButton* m_okButton;
    QPushButton* m_cancelButton;

    // Saved state for revert
    bool m_prevDarkMode;
    int m_prevTabSpaces;
    QFont m_prevFont;
};
