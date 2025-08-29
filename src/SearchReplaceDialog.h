#ifndef SEARCHREPLACEDIALOG_H
#define SEARCHREPLACEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>

class SearchReplaceDialog : public QDialog {
    Q_OBJECT

public:
    SearchReplaceDialog(QWidget *parent = nullptr);

    QString getSearchText() const;
    QString getReplaceText() const;
    bool isCaseSensitive() const;

signals:
    void findNext(const QString &text, bool caseSensitive);
    void replace(const QString &text, const QString &replacement, bool caseSensitive);
    void replaceAll(const QString &text, const QString &replacement, bool caseSensitive);

private slots:
    void onFindNext();
    void onReplace();
    void onReplaceAll();

private:
    QLineEdit *searchEdit;
    QLineEdit *replaceEdit;
    QCheckBox *caseCheck;
    QPushButton *findNextBtn;
    QPushButton *replaceBtn;
    QPushButton *replaceAllBtn;
};

#endif // SEARCHREPLACEDIALOG_H
