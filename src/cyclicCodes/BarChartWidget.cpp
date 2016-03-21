#include "BarChartWidget.h"

const QColor BarChartWidget::mainColor(85, 85, 85);
const QColor BarChartWidget::barColor(190, 180, 170);

BarChartWidget::BarChartWidget(std::vector<QString> &labels) : values(new std::vector<int>(BAR_COUNT, 0)),
                                                               labels(new std::vector<QString>(labels)) {
    setMinimumWidth(100);
    setMinimumHeight(140);
}

BarChartWidget::BarChartWidget(const QString labels[], int count) : values(new std::vector<int>(BAR_COUNT, 0)) {
    if (count != BAR_COUNT) {
        throw std::logic_error("Different bar count is not implemented yet");
    }

    this->labels = new std::vector<QString>();
    for (int i = 0; i < count; ++i) {
        this->labels->push_back(labels[i]);
    }

    setMinimumWidth(100);
    setMinimumHeight(140);
}

BarChartWidget::~BarChartWidget() {
    delete values;
    delete labels;
}

void BarChartWidget::setValues(const std::vector<int> &values) {
    *(this->values) = values;
    update();
}

void BarChartWidget::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);

    QPainter painter(this);

    drawLabel(painter);
    drawBaseLine(painter);
    drawBars(painter);
}

void BarChartWidget::fillSizes(std::vector<int> &sizes) {
    int maxValue = 100;
    for (unsigned long i = 0; i < values->size(); ++i) {
        if (values->at(i) > maxValue) {
            maxValue = values->at(i);
        }
    }

    if (maxValue == 0) {
        for (unsigned long i = 0; i < sizes.size(); ++i) {
            sizes.at(i) = 0;
        }

        return;
    }

    QRect baseRect = rect();
    int maxPixelHeight = baseRect.height() - PADDING_BOTTOM - PADDING_TOP - VALUE_LABEL_HEIGHT;
    double factor = (double) maxPixelHeight / (double) maxValue;

    for (unsigned long i = 0; i < sizes.size(); ++i) {
        sizes.at(i) = (int) std::floor(values->at(i) * factor);
    }
}

void BarChartWidget::drawBaseLine(QPainter &painter) {
    QRect baseRectangle = rect();

    int y = (int) std::floor(baseRectangle.bottom() - PADDING_BOTTOM);
    int x1 = (int) std::floor(baseRectangle.left() + baseRectangle.width() * PADDING);
    int x2 = (int) std::floor(baseRectangle.right() - baseRectangle.width() * PADDING);

    QPen pen(mainColor, 2);
    painter.setPen(pen);

    QLine line(x1, y, x2, y);
    painter.drawLine(line);
}

void BarChartWidget::drawBars(QPainter &painter) {
    std::vector<int> sizes(BAR_COUNT, 0);
    fillSizes(sizes);

    QRect baseRectangle = rect();
    int activeWidth = (int) std::floor( baseRectangle.width() * (1 - 2 * PADDING) );
    int singleBarWidth = (int) std::floor((activeWidth - (BAR_COUNT + 1) * SPACING) / BAR_COUNT);

    int baseLineY = (int) std::floor(baseRectangle.bottom() - PADDING_BOTTOM);
    int currX = (int) std::floor(baseRectangle.left() + baseRectangle.width() * PADDING);

    currX += SPACING;
    for (int i = 0; i < BAR_COUNT; i++) {
        QPoint pointTopLeft(currX, baseLineY - sizes.at((unsigned long) i));
        QPoint pointBottomRight(currX + singleBarWidth, baseLineY - 1);
        QRect bar(pointTopLeft, pointBottomRight);
        painter.setPen(mainColor);
        painter.drawRect(bar);
        painter.fillRect(bar, barColor);

        QPoint textTopLeft(currX, baseLineY);
        QPoint textBottomRight(currX + singleBarWidth, baseRectangle.bottom());
        QRect textRect(textTopLeft, textBottomRight);
        painter.setPen(mainColor);
        painter.drawText(textRect, Qt::AlignCenter, labels->at((unsigned long) i));
        
        QPoint valueTopLeft(currX, baseLineY - sizes.at((unsigned long) i) - VALUE_LABEL_HEIGHT);
        QPoint valueBottomRight(currX + singleBarWidth, baseLineY);
        QRect valueLabelRect(valueTopLeft, valueBottomRight);
        QString textValue = QString::number(values->at((unsigned long) i));
        painter.drawText(valueLabelRect, Qt::AlignHCenter | Qt::AlignTop, textValue);
        
        currX += singleBarWidth + SPACING;
    }
}

void BarChartWidget::drawLabel(QPainter &painter) {
    QRect baseRectangle = rect();
    painter.setPen(mainColor);

    int topY = (int) std::floor(baseRectangle.top());
    QPoint pointTopLeft(baseRectangle.left(), topY);
    QPoint pointBottomRight(baseRectangle.right(), topY + PADDING_TOP);
    QRect textRectangle(pointTopLeft, pointBottomRight);
    painter.drawText(textRectangle, Qt::AlignHCenter | Qt::AlignBottom, "Кратность пропущенных ошибок");
}
