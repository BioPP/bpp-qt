// SPDX-FileCopyrightText: The Bio++ Development Group
//
// SPDX-License-Identifier: CECILL-2.1

#include "QtGraphicDevice.h"
#include "QtTools.h"

// From Qt:
#include <QGraphicsLineItem>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QTextDocument>
#include <QFontInfo>

// From the STL:
#include <iostream>
using namespace std;

using namespace bpp;

QtGraphicDevice::QtGraphicDevice() :
  scene_(), supportedLineTypes_(), currentPen_(), currentBrush_(Qt::SolidPattern), currentFont_()
{
  supportedLineTypes_[GraphicDevice::LINE_SOLID] = Qt::SolidLine;
  supportedLineTypes_[GraphicDevice::LINE_DASHED] = Qt::DashLine;
  supportedLineTypes_[GraphicDevice::LINE_DOTTED] = Qt::DotLine;
  setXUnit(1.);
  setYUnit(1.);
}

QtGraphicDevice::~QtGraphicDevice() {}

void QtGraphicDevice::begin()
{
  scene_.reset(new QGraphicsScene());
}

void QtGraphicDevice::end()
{
}

void QtGraphicDevice::setCurrentForegroundColor(const RGBColor& color)
{
  AbstractGraphicDevice::setCurrentForegroundColor(color);
  currentPen_.setColor(QtTools::toQt(color));
}

void QtGraphicDevice::setCurrentBackgroundColor(const RGBColor& color)
{
  AbstractGraphicDevice::setCurrentBackgroundColor(color);
  currentBrush_.setColor(QtTools::toQt(color));
}

void QtGraphicDevice::setCurrentFont(const Font& font)
{
  AbstractGraphicDevice::setCurrentFont(font);
  currentFont_ = QtTools::toQt(font);
}

void QtGraphicDevice::setCurrentPointSize(unsigned int size)
{
  AbstractGraphicDevice::setCurrentPointSize(size);
  currentPen_.setWidth(static_cast<int>(size));
}

void QtGraphicDevice::setCurrentLineType(short type)
{
  AbstractGraphicDevice::setCurrentLineType(type);
  currentPen_.setStyle(supportedLineTypes_[type]);
}

// void QtGraphicDevice::setCurrentLayer(int layerIndex)
// {
//
// }

void QtGraphicDevice::drawLine(double x1, double y1, double x2, double y2)
{
  QGraphicsLineItem* item = scene_->addLine(xpos(x1), ypos(y1), xpos(x2), ypos(y2), currentPen_);
  item->setZValue(-qreal(getCurrentLayer()));
}


void QtGraphicDevice::drawRect(double x, double y, double width, double height, short fill)
{
  QGraphicsRectItem* item = scene_->addRect(xpos(x), ypos(y), width * getXUnit(), height * getYUnit(), currentPen_, currentBrush_);
  item->setZValue(-qreal(getCurrentLayer()));
}

void QtGraphicDevice::drawCircle(double x, double y, double radius, short fill)
{
}

void QtGraphicDevice::drawText(double x, double y, const std::string& text, short hpos, short vpos, double angle)
{
  qreal xset = 0, yset = 0;
  QString qtext = text.c_str();
  QGraphicsTextItem* item = scene_->addText(qtext, currentFont_);
  QSizeF fsize = item->document()->size();
  QFontInfo fi(currentFont_);
  double mar = (fsize.rheight() - fi.pixelSize()) / 2;
  if (hpos ==  TEXT_HORIZONTAL_LEFT)
    xset = 0;
  else if (hpos ==  TEXT_HORIZONTAL_RIGHT)
    xset = -fsize.rwidth();
  else if (hpos ==  TEXT_HORIZONTAL_CENTER)
    xset = -fsize.rwidth() / 2;
  else
    throw UnvalidFlagException("QtGraphicDevice::drawText(). Unvalid horizontal alignment option.");

  if (vpos ==  TEXT_VERTICAL_TOP)
  {
    yset = mar;
  }
  else if (vpos ==  TEXT_VERTICAL_BOTTOM)
  {
    yset = fi.pixelSize() + mar;
  }
  else if (vpos ==  TEXT_VERTICAL_CENTER)
  {
    yset = fi.pixelSize() / 2 + mar;
  }
  else
    throw UnvalidFlagException("QtGraphicDevice::drawText(). Unvalid vertical alignment option.");

  item->setPos(xpos(x) + xset, ypos(y) - yset);
  item->setDefaultTextColor(currentPen_.color());
  item->setZValue(-qreal(getCurrentLayer()));
}
