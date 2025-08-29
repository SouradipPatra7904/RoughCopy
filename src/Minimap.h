#pragma once
#include <QWidget>
#include <QPlainTextEdit>
#include <QPainter>

class Minimap : public QWidget
{
    Q_OBJECT
public:
    explicit Minimap(QPlainTextEdit* editor, QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QPlainTextEdit* m_editor;
};
