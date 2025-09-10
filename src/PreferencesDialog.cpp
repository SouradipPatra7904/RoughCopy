#include "PreferencesDialog.h"
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFontDatabase>

// -------------------------
// Constructor
// -------------------------
PreferencesDialog::PreferencesDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUI();
    loadDefaults();
    loadCurrent();
}

// -------------------------
// Setup UI
// -------------------------
void PreferencesDialog::setupUI() {
    setWindowTitle("Preferences");
    QVBoxLayout *main = new QVBoxLayout(this);

    // Font family + size
    QHBoxLayout *fontRow = new QHBoxLayout();
    fontRow->addWidget(new QLabel("Font:"));

    // Current font label (below dropdown)
    currentFontLabel = new QLabel(this);
    currentFontLabel->setText("Current Font: Courier New");  // default
    main->addWidget(currentFontLabel);

    fontCombo = new QComboBox(this);
    fontCombo->addItems(QFontDatabase().families());
    fontRow->addWidget(fontCombo);

    fontRow->addWidget(new QLabel("Size:"));
    fontSizeSpin = new QSpinBox(this);
    fontSizeSpin->setRange(8, 48);
    fontSizeSpin->setValue(12);
    fontRow->addWidget(fontSizeSpin);
    main->addLayout(fontRow);

    // Theme
    QHBoxLayout *themeRow = new QHBoxLayout();
    themeRow->addWidget(new QLabel("Theme:"));
    themeCombo = new QComboBox(this);
    themeCombo->addItems({"Light", "Dark", "Night Sky"}); // Theme name placehoders
    themeRow->addWidget(themeCombo);
    main->addLayout(themeRow);

    // Buttons
    QHBoxLayout *btnRow = new QHBoxLayout();
    applyBtn = new QPushButton("Apply", this);
    okBtn = new QPushButton("OK", this);
    cancelBtn = new QPushButton("Cancel", this);
    restoreBtn = new QPushButton("Restore Defaults", this);
    btnRow->addStretch();
    btnRow->addWidget(applyBtn);
    btnRow->addWidget(okBtn);
    btnRow->addWidget(cancelBtn);
    btnRow->addWidget(restoreBtn);
    main->addLayout(btnRow);

    // Connections
    connect(applyBtn, &QPushButton::clicked, this, &PreferencesDialog::onApply);
    connect(okBtn, &QPushButton::clicked, this, &PreferencesDialog::onOk);
    connect(cancelBtn, &QPushButton::clicked, this, &PreferencesDialog::onCancel);
    connect(restoreBtn, &QPushButton::clicked, this, &PreferencesDialog::onRestoreDefaults);

    // live preview
    connect(fontCombo, &QComboBox::currentTextChanged, this, &PreferencesDialog::previewChanges);
    connect(fontSizeSpin, qOverload<int>(&QSpinBox::valueChanged), this, &PreferencesDialog::previewChanges);
    connect(themeCombo, &QComboBox::currentTextChanged, this, &PreferencesDialog::onThemeChanged);
}

// -------------------------
// Defaults
// -------------------------
void PreferencesDialog::loadDefaults() {
    defaultFont = QFont("Courier New", 18);
    defaultTheme = "Light";
}

// -------------------------
// Load Current
// -------------------------
void PreferencesDialog::loadCurrent() {
    currentFont = defaultFont;
    currentTheme = defaultTheme;

    currentFontLabel->setText(
        QString("Current Font: %1, %2pt")
            .arg(currentFont.family())
            .arg(currentFont.pointSize())
    );

    fontCombo->setCurrentText(currentFont.family());
    fontSizeSpin->setValue(currentFont.pointSize());
    themeCombo->setCurrentText(currentTheme);

    onThemeChanged(currentTheme);
}

// -------------------------
// Accessors
// -------------------------
QFont PreferencesDialog::getSelectedFont() const {
    return QFont(fontCombo->currentText(), fontSizeSpin->value());
}

QString PreferencesDialog::getTheme() const {
    return themeCombo->currentText();
}

// -------------------------
// Slots
// -------------------------
void PreferencesDialog::onApply() {
    emit preferencesApplied(getSelectedFont(), Qt::black, Qt::white, getTheme());
}

void PreferencesDialog::onRestoreDefaults() {
    loadDefaults();
    loadCurrent();
    emit preferencesReverted();
}

void PreferencesDialog::onOk() {
    emit preferencesApplied(getSelectedFont(), Qt::black, Qt::white, getTheme());
    accept();
}

void PreferencesDialog::onCancel() {
    emit preferencesReverted();
    reject();
}

void PreferencesDialog::previewChanges() {
    QString family = fontCombo->currentText();
    int size = fontSizeSpin->value();

    currentFontLabel->setText(
        QString("Current Font: %1, %2pt").arg(family).arg(size)
    );
    emit preferencesApplied(getSelectedFont(), Qt::black, Qt::white, getTheme());
}

// -------------------------
// Theme-specific behavior
// -------------------------
void PreferencesDialog::onThemeChanged(const QString &theme) {
    currentTheme = theme;
    previewChanges();
}
