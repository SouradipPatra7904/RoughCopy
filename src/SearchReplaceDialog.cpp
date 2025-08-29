#include "SearchReplaceDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

SearchReplaceDialog::SearchReplaceDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Search and Replace");

    QLabel *searchLabel = new QLabel("Search:");
    searchEdit = new QLineEdit(this);

    QLabel *replaceLabel = new QLabel("Replace:");
    replaceEdit = new QLineEdit(this);

    caseCheck = new QCheckBox("Case Sensitive", this);

    findNextBtn = new QPushButton("Find Next", this);
    replaceBtn = new QPushButton("Replace", this);
    replaceAllBtn = new QPushButton("Replace All", this);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QHBoxLayout *searchLayout = new QHBoxLayout();
    searchLayout->addWidget(searchLabel);
    searchLayout->addWidget(searchEdit);

    QHBoxLayout *replaceLayout = new QHBoxLayout();
    replaceLayout->addWidget(replaceLabel);
    replaceLayout->addWidget(replaceEdit);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(findNextBtn);
    buttonLayout->addWidget(replaceBtn);
    buttonLayout->addWidget(replaceAllBtn);

    mainLayout->addLayout(searchLayout);
    mainLayout->addLayout(replaceLayout);
    mainLayout->addWidget(caseCheck);
    mainLayout->addLayout(buttonLayout);

    connect(findNextBtn, &QPushButton::clicked, this, &SearchReplaceDialog::onFindNext);
    connect(replaceBtn, &QPushButton::clicked, this, &SearchReplaceDialog::onReplace);
    connect(replaceAllBtn, &QPushButton::clicked, this, &SearchReplaceDialog::onReplaceAll);
}

QString SearchReplaceDialog::getSearchText() const {
    return searchEdit->text();
}

QString SearchReplaceDialog::getReplaceText() const {
    return replaceEdit->text();
}

bool SearchReplaceDialog::isCaseSensitive() const {
    return caseCheck->isChecked();
}

void SearchReplaceDialog::onFindNext() {
    emit findNext(searchEdit->text(), caseCheck->isChecked());
}

void SearchReplaceDialog::onReplace() {
    emit replace(searchEdit->text(), replaceEdit->text(), caseCheck->isChecked());
}

void SearchReplaceDialog::onReplaceAll() {
    emit replaceAll(searchEdit->text(), replaceEdit->text(), caseCheck->isChecked());
}
