#ifndef BATTERYWIDGET_H
#define BATTERYWIDGET_H

#include <QWidget>

#define USE_GLYPH

class QBatteryWidget: public QWidget
{
    Q_OBJECT

private:
    const float DEF_CORNER_RATIO = 15;
    const int DEF_CRITICAL_LEVEL = 10;
    const int DEF_LOW_LEVEL = 30;
    const float DEF_FONT_RATIO = 2.5;

    int mValue = 0;

    int mMax = 100;
    int mMin = 0;

    int mCriticalLevel;
    int mLowLevel;

    bool mCharging = false;

    QRectF mWidgetFrame;
    QRectF mMainBatteryFrame;
    QRectF mTipBatteryFrame;
    QRectF mBatteryLevelFrame;
    QColor mFrameColor;
    QColor mNormalChargeColor;
    QColor mCriticalChargeColor;
    QColor mLowChargeColor;
    QColor mTextColor;
    QColor mChargeGlyphColor;
    QColor mChargeGlyphFillColor;

#ifdef USE_GLYPH
    QPolygon mChargingGlyph;
#else
    QPixmap* mChargingGlyph;
#endif

    void validateValue(int value);
    QRectF getFrame();
    QPointF getWidgetFrameOffset(QSizeF widgetSize);

public:
    explicit QBatteryWidget(QWidget *parent = nullptr);
    ~QBatteryWidget();

    bool getCharging();
    void setCharging(bool state);

    void setValue(int value);
    void setMax(int value);
    void setMin(int value);

    int getValue();
    int getMax();
    int getMin();

    void setNormalChargeColor(QColor value);
    void setCriticalChargeColor(QColor value);
    void setLowChargeColor(QColor value);
    void setFrameColor(QColor value);
    void setTextColor(QColor value);
    void setChargeGlyphColor(QColor value);
    void setChargeGlyphFillColor(QColor value);

    void setCriticalLevel(int value);
    void setLowLevel(int value);

protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
};

#endif // BATTERYWIDGET_H
