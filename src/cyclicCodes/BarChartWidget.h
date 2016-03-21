#ifndef HAMMING_CODES_BAR_CHART_WIDGET_H
#define HAMMING_CODES_BAR_CHART_WIDGET_H

#include <QtWidgets>

class BarChartWidget : public QWidget {

Q_OBJECT

public:
    static const int BAR_COUNT = 6;

    BarChartWidget(std::vector<QString> &labels);
    BarChartWidget(const QString labels[], int count);
    ~BarChartWidget();

    void setValues(const std::vector<int> &values);

protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    static const QColor mainColor;
    static const QColor barColor;
    static constexpr double PADDING = 0.07f;
    static const int SPACING = 20;
    static const int VALUE_LABEL_HEIGHT = 20;
    static const int PADDING_BOTTOM = 25;
    static const int PADDING_TOP = 20;

    std::vector<int> *values;
    std::vector<QString> *labels;

    void fillSizes(std::vector<int> &sizes);
    void drawBaseLine(QPainter &painter);
    void drawBars(QPainter &painter);
    void drawLabel(QPainter &painter);

};


#endif //HAMMING_CODES_BAR_CHART_WIDGET_H
