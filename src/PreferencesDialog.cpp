#include "PreferencesDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

PreferencesDialog::PreferencesDialog(QWidget* parent)
    : QDialog(parent)
{
    setupUI();
    connectSignals();

    // Save initial state
    m_prevDarkMode = isDarkMode();
    m_prevTabSpaces = tabSpaces();
    m_prevFont = selectedFont();
}

void PreferencesDialog::setupUI()
{
    m_darkModeCheck = new QCheckBox("Dark Mode");
    m_tabSpacesSpin = new QSpinBox();
    m_tabSpacesSpin->setRange(1, 8);
    m_fontCombo = new QFontComboBox();

    m_okButton = new QPushButton("OK");
    m_cancelButton = new QPushButton("Cancel");

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_darkModeCheck);
    mainLayout->addWidget(m_tabSpacesSpin);
    mainLayout->addWidget(m_fontCombo);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(m_okButton);
    buttonLayout->addWidget(m_cancelButton);

    mainLayout->addLayout(buttonLayout);
}

void PreferencesDialog::connectSignals()
{
    connect(m_darkModeCheck, &QCheckBox::toggled, [this](bool checked){
        emit preferencesReverted(); // Instant preview handled externally
    });

    connect(m_tabSpacesSpin, QOverload<int>::of(&QSpinBox::valueChanged), [this](int){
        emit preferencesReverted(); // Instant preview handled externally
    });

    connect(m_fontCombo, &QFontComboBox::currentFontChanged, [this](const QFont&){
        emit preferencesReverted(); // Instant preview handled externally
    });

    connect(m_okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(m_cancelButton, &QPushButton::clicked, [this](){
        // Revert state
        setDarkMode(m_prevDarkMode);
        setTabSpaces(m_prevTabSpaces);
        setSelectedFont(m_prevFont);
        emit preferencesReverted();
        reject();
    });
}

// Getters/Setters
bool PreferencesDialog::isDarkMode() const { return m_darkModeCheck->isChecked(); }
void PreferencesDialog::setDarkMode(bool enabled) { m_darkModeCheck->setChecked(enabled); }

int PreferencesDialog::tabSpaces() const { return m_tabSpacesSpin->value(); }
void PreferencesDialog::setTabSpaces(int spaces) { m_tabSpacesSpin->setValue(spaces); }

QFont PreferencesDialog::selectedFont() const { return m_fontCombo->currentFont(); }
void PreferencesDialog::setSelectedFont(const QFont& font) { m_fontCombo->setCurrentFont(font); }
