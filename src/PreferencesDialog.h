#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QDialog>
#include <QFont>
#include <QString>

class QComboBox;
class QSpinBox;
class QPushButton;

class PreferencesDialog : public QDialog {
    Q_OBJECT

public:
    explicit PreferencesDialog(QWidget *parent = nullptr);

    QFont getSelectedFont() const;
    QString getTheme() const;

signals:
    void preferencesApplied(const QFont &font, const QColor &fontColor, const QColor &bgColor, const QString &theme);
    void preferencesReverted();

private slots:
    void onApply();
    void onRestoreDefaults();
    void onOk();
    void onCancel();
    void previewChanges();
    void onThemeChanged(const QString &theme);

private:
    void setupUI();
    void loadDefaults();
    void loadCurrent();

    // UI widgets
    QComboBox *fontCombo;
    QSpinBox *fontSizeSpin;
    QComboBox *themeCombo;
    QPushButton *applyBtn;
    QPushButton *okBtn;
    QPushButton *cancelBtn;
    QPushButton *restoreBtn;

    // State
    QFont currentFont;
    QString currentTheme;

    QFont defaultFont;
    QString defaultTheme;
};

#endif // PREFERENCESDIALOG_H
