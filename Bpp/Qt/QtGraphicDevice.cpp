//
// File: QtGraphicDevice.cpp
// Created by: Julien Dutheil
// Created on: Thu Jul 16 2009
//

/*
Copyright or © or Copr. CNRS, (November 16, 2006)

This software is a computer program whose purpose is to provide 
graphical components using the Qt library.
This file belongs to the Bio++ Project.

This software is governed by the CeCILL  license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL license and that you accept its terms.
*/

#include "QtGraphicDevice.h"
#include <iostream>
using namespace std;

using namespace bpp;

QtGraphicDevice::QtGraphicDevice(): painter_(), device_(NULL) {}

void QtGraphicDevice::setPaintDevice(QPaintDevice* device)
{
  device_ = device;
  setXUnit(1.);
  setYUnit(1.);
}

QtGraphicDevice::~QtGraphicDevice() {}

void QtGraphicDevice::begin() throw (Exception)
{
  if (!device_) throw Exception("QtGraphicDevice::begin(). No QPaintDevice was specified.");
  if (!painter_.begin(device_))
    throw Exception("QtGraphicDevice::begin(). Cannot print on device.");
}

void QtGraphicDevice::end()
{
  painter_.end();
}

void QtGraphicDevice::setCurrentForegroundColor(const RGBColor& color)
{
  
}

void QtGraphicDevice::setCurrentBackgroundColor(const RGBColor& color)
{

}

void QtGraphicDevice::setCurrentFont(const Font& font)
{

}

void QtGraphicDevice::setCurrentPointSize(unsigned int size)
{
  QPen pen = painter_.pen();
  pen.setWidth(static_cast<uint>(size));
  painter_.setPen(pen);
}

void QtGraphicDevice::setCurrentLineType(short type)
{

}

void QtGraphicDevice::setCurrentLayer(int layerIndex)
{

}

void QtGraphicDevice::drawLine(double x1, double y1, double x2, double y2)
{
  painter_.drawLine(xpos(x1), ypos(y1), xpos(x2), ypos(y2));
}


void QtGraphicDevice::drawRect(double x, double y, double width, double height, short fill)
{
  painter_.drawRect(xpos(x), ypos(y), xpos(width), ypos(height));
}

void QtGraphicDevice::drawCircle(double x, double y, double radius, short fill)
{

}

void QtGraphicDevice::drawText(double x, double y, const std::string& text, short hpos, short vpos, double angle) throw (UnvalidFlagException)
{
  int xset = 0, yset = 0;
  QString qtext = text.c_str();
  QSize fsize = painter_.fontMetrics().size(0, qtext);
  if (hpos ==  TEXT_HORIZONTAL_LEFT)
    xset = 0;
  else if (hpos ==  TEXT_HORIZONTAL_RIGHT)
    xset = -fsize.rwidth();
  else if (hpos ==  TEXT_HORIZONTAL_CENTER)
    xset = -fsize.rwidth() / 2;
  else throw UnvalidFlagException("QtGraphicDevice::drawText(). Unvalid horizontal alignment option.");

  if (vpos ==  TEXT_VERTICAL_TOP)
    yset = fsize.rheight();
  else if (vpos ==  TEXT_VERTICAL_BOTTOM)
    yset = 0;
  else if (vpos ==  TEXT_VERTICAL_CENTER)
    yset = fsize.rheight() / 2;
  else throw UnvalidFlagException("QtGraphicDevice::drawText(). Unvalid vertical alignment option.");

  painter_.drawText(xpos(x) + xset, ypos(y) + yset/2, qtext); //Dunno why, but apparently we need an additional factor of 2 here :s
}

