#include "qbatterywidget.h"

#include <QPainter>
#include <QPainterPath>

QBatteryWidget::QBatteryWidget(QWidget* parent)
    : QWidget(parent)
{
    Q_UNUSED(parent);

    mNormalChargeColor = Qt::green;
    mCriticalChargeColor = Qt::red;
    mLowChargeColor = Qt::yellow;
    mFrameColor = Qt::gray;
    mTextColor = Qt::white;
    mChargeGlyphColor = Qt::white;
    mChargeGlyphFillColor = QColor(255,165,0,255);

    mCriticalLevel = DEF_CRITICAL_LEVEL;
    mLowLevel = DEF_LOW_LEVEL;

    mMax = 100;

#ifdef USE_GLYPH
    mChargingGlyph << QPoint(4,0) << QPoint(0,6) << QPoint(3,6) << QPoint(3,11) << QPoint(7,6) << QPoint(4,6) << QPoint(4,0);
#else
    mChargingGlyph = new QPixmap("");
#endif
}

QBatteryWidget::~QBatteryWidget()
{
#ifndef USE_GLYPH
    delete mChargingGlyph;
#endif
}

QRectF QBatteryWidget::getFrame()
{
    QRectF frame = QRectF();

    QSizeF widgetSize;

    if (this->width() > this->height())
    {
        widgetSize = QSizeF(this->height()*0.95,this->height()*0.95);
        frame.setSize(widgetSize);

        QPointF widgetFrameOffsetPoint = getWidgetFrameOffset(widgetSize);
        frame.moveTopLeft(widgetFrameOffsetPoint);
    }
    else
    {
        widgetSize = QSizeF(this->width()*0.95,this->width() * 0.95);
        frame.setSize(widgetSize);

        QPointF widgetOffsetPoint = getWidgetFrameOffset(widgetSize);
        frame.moveTopLeft(widgetOffsetPoint);
    }

    return frame;
}

QPointF QBatteryWidget::getWidgetFrameOffset(QSizeF size)
{
    float xOffset = this->width()/2-size.width()/2;
    float yOffset = this->height()/2-size.height()/2;

    return QPointF(xOffset,yOffset);
}

void QBatteryWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    mWidgetFrame = getFrame();

    mWidgetFrame.setSize(QSize(mWidgetFrame.width(),mWidgetFrame.height()/2));
    mWidgetFrame.moveTop(mWidgetFrame.center().y());

    float scale = 0.95;

    QSizeF mainBatteryFrameSize = QSizeF(mWidgetFrame.width()*scale ,mWidgetFrame.height());

    mMainBatteryFrame.setSize(mainBatteryFrameSize);

    mMainBatteryFrame.moveTopLeft(mWidgetFrame.topLeft());

    QSizeF tipBatteryFrameSize = QSizeF(mWidgetFrame.width()/3,mWidgetFrame.height()/2);

    mTipBatteryFrame.setSize(tipBatteryFrameSize);

    QPointF tipBatteryFramePoint = QPointF(mWidgetFrame.topRight().x()-tipBatteryFrameSize.width(), mWidgetFrame.topRight().y()+tipBatteryFrameSize.height()/2);

    mTipBatteryFrame.moveTopLeft(tipBatteryFramePoint);

    float batteryLevelOffset = mMainBatteryFrame.height()/20;

    QSizeF batteryLevelFrameSize = QSizeF(mMainBatteryFrame.width() - 2*batteryLevelOffset, mMainBatteryFrame.height() - 2*batteryLevelOffset);

    mBatteryLevelFrame.setSize(batteryLevelFrameSize);

    QPointF batteryFramePoint = QPointF(mMainBatteryFrame.topLeft().x() + batteryLevelOffset,mMainBatteryFrame.topLeft().y() + batteryLevelOffset);

    mBatteryLevelFrame.moveTopLeft(batteryFramePoint);
}

void QBatteryWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    painter.setRenderHint( QPainter::Antialiasing, true);

    float widgetCorner = mWidgetFrame.height()/DEF_CORNER_RATIO;

    QPainterPath framePath;

    framePath.setFillRule(Qt::WindingFill);
    framePath.addRoundedRect(mMainBatteryFrame,widgetCorner, widgetCorner);
    framePath.addRoundedRect(mTipBatteryFrame, widgetCorner,widgetCorner);
    framePath = framePath.simplified();

    QPen pen;

    pen.setColor(mFrameColor);
    pen.setWidth(mWidgetFrame.width()/75);

    painter.setPen(pen);
    painter.drawPath(framePath);

    if(mValue >= mLowLevel)
        painter.setBrush(QBrush(mNormalChargeColor));
    else if(mValue < mLowLevel && mValue > mCriticalLevel)
        painter.setBrush(QBrush(mLowChargeColor));
    else if(mValue <= mCriticalLevel)
        painter.setBrush(QBrush(mCriticalChargeColor));

    painter.setPen(Qt::NoPen);

    QRectF batteryLevelRect = QRectF();
    QSize batterySizeRect = QSize(mBatteryLevelFrame.width() * mValue/mMax, mBatteryLevelFrame.height());

    batteryLevelRect.setSize(batterySizeRect);
    batteryLevelRect.moveTo(mBatteryLevelFrame.topLeft());
    painter.drawRoundedRect(batteryLevelRect, widgetCorner,widgetCorner);

    pen.setColor(mTextColor);
    painter.setPen(pen);

    QFont textFont = QFont();

    textFont.setPixelSize(mWidgetFrame.height()/DEF_FONT_RATIO);
    painter.setFont(textFont);

    QFontMetricsF fm(textFont);

    QString percentageLevelString = QString("%1%").arg(mValue);

    //float textWidth = fm.maxWidth(percentageLevelString);
    float textHeight = fm.height();

    //QPointF textPosition = QPointF(mWidgetFrame.center().x()-textWidth/2,mWidgetFrame.center().y()+textHeight/3);

    //painter.drawText(textPosition, percentageLevelString);

    if (mCharging)
    {
#ifdef USE_GLYPH
        //TODO: set brush etc...
        QTransform transform;
        QBrush glyph_brush(mChargeGlyphFillColor);

        float xScale = (mWidgetFrame.width()/48)*1.2;
        float yScale = (mWidgetFrame.height()/24)*1.2;

        transform.translate(mWidgetFrame.center().x(), mWidgetFrame.center().y());
        transform.translate(-mChargingGlyph.boundingRect().width()*xScale/2, -mChargingGlyph.boundingRect().height()*yScale/2);
        transform.translate(-mWidgetFrame.width()/3,0);

        transform.scale(xScale, yScale);

        painter.setPen(mChargeGlyphColor);
        painter.setBrush(glyph_brush);
        painter.drawPolygon(transform.map(mChargingGlyph));
#else
        float _chargerSize = mWidgetFrame.height() / 2;
        _painter.drawPixmap(mWidgetFrame.center().x() - _chargerSize*1.5, mWidgetFrame.top() + _chargerSize/2 ,_chargerSize,_chargerSize, *mChargingGlyph);
#endif
    }
}

void QBatteryWidget::validateValue(int value)
{
    if ((value >= mMin) && (value <=mMax)){
        mValue = value;
    } else if (value < mMin) {
        mValue = mMin;
    } else if (value > mMax) {
        mValue = mMax;
    }
}

void QBatteryWidget::setValue(int value)
{
    if(mValue == value)
        return;

    validateValue(value);

    repaint();
}

int QBatteryWidget::getValue()
{
    return mValue;
}

void QBatteryWidget::setMax(int value)
{
    if(mMax == value)
        return;

    mMax = value;
    repaint();
}

int QBatteryWidget::getMax()
{
    return mMax;
}

void QBatteryWidget::setMin(int value)
{
    if(mMin == value)
        return;

    mMin = value;
    repaint();
}

int QBatteryWidget::getMin()
{
    return mMin;
}

void QBatteryWidget::setCharging(bool state)
{
    if(mCharging == state)
        return;

    mCharging = state;
    repaint();
}

bool QBatteryWidget::getCharging()
{
    return mCharging;
}

void QBatteryWidget::setNormalChargeColor(QColor value)
{
    if(mNormalChargeColor==value)
        return;

    mNormalChargeColor=value;
    repaint();
}

void QBatteryWidget::setCriticalChargeColor(QColor value)
{
    if(mCriticalChargeColor==value)
        return;

    mCriticalChargeColor=value;
    repaint();
}

void QBatteryWidget::setLowChargeColor(QColor value)
{
    if(mLowChargeColor==value)
        return;

    mLowChargeColor=value;
    repaint();
}

void QBatteryWidget::setFrameColor(QColor value)
{
    if(mFrameColor==value)
        return;

    mFrameColor=value;
    repaint();
}

void QBatteryWidget::setTextColor(QColor value)
{
    if(mTextColor==value)
        return;

    mTextColor=value;
    repaint();
}

void QBatteryWidget::setCriticalLevel(int value)
{
    if(mCriticalLevel==value)
        return;

    mCriticalLevel=value;
    repaint();
}

void QBatteryWidget::setLowLevel(int value)
{
    if(mLowLevel==value)
        return;

    mLowLevel=value;
    repaint();
}

void QBatteryWidget::setChargeGlyphColor(QColor value)
{
    if(mChargeGlyphColor == value)
        return;

    mChargeGlyphColor = value;
    repaint();
}

void QBatteryWidget::setChargeGlyphFillColor(QColor value)
{
    if(mChargeGlyphFillColor == value)
        return;

    mChargeGlyphFillColor = value;
    repaint();
}
