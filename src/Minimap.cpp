#include "Minimap.h"
#include <QScrollBar>
#include <QTextBlock>

Minimap::Minimap(QPlainTextEdit* editor, QWidget* parent)
    : QWidget(parent), m_editor(editor)
{
    setFixedWidth(150);
    // Update minimap when editor updates
    connect(editor, &QPlainTextEdit::updateRequest, this, [this](){ update(); });
    connect(editor->verticalScrollBar(), &QScrollBar::valueChanged, this, [this](){ update(); });
}

void Minimap::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.fillRect(rect(), Qt::lightGray);

    QTextBlock block = m_editor->document()->firstBlock();
    int y = 0;
    while (block.isValid()) {
        QRectF blockRect = m_editor->document()->documentLayout()->blockBoundingRect(block);
        float blockHeightRatio = blockRect.height() / m_editor->document()->size().height();
        float minimapHeight = blockHeightRatio * height();

        painter.fillRect(0, y, width(), minimapHeight, Qt::darkGray);
        y += minimapHeight;
        block = block.next();
    }

    // Draw viewport rectangle
    float viewportRatio = (float)m_editor->viewport()->height() / m_editor->document()->size().height();
    float viewportY = (float)m_editor->verticalScrollBar()->value() / m_editor->document()->size().height() * height();
    painter.setPen(Qt::red);
    painter.drawRect(0, viewportY, width()-1, viewportRatio*height());
}
