//
// File: QtGraphicDevice.h
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

#ifndef _QTGRAPHICDEVICE_H_
#define _QTGRAPHICDEVICE_H_

#include <Bpp/Graphics/AbstractGraphicDevice.h>

//From Qt:
#include <QGraphicsScene>
#include <Qt>

//From the STL:
#include <map>

namespace bpp
{

/**
 * @brief Bio++ wrapper for the QPainter class.
 *
 * This class implements the GraphicDevice interface from the bio++ core library, and calls the corresponding QPainter methods.
 */
class QtGraphicDevice:
  public AbstractGraphicDevice
{
  private:
    QGraphicsScene* scene_;
    std::map<short int, Qt::PenStyle> supportedLineTypes_;
    QPen currentPen_;
    QBrush currentBrush_;
    QFont currentFont_;

  public:
    QtGraphicDevice();
    virtual ~QtGraphicDevice();

  public:
    QGraphicsScene& getScene() { return *scene_; }

    void begin() throw (Exception);
    void end();

    void setCurrentForegroundColor(const RGBColor& color);
    void setCurrentBackgroundColor(const RGBColor& color);
    void setCurrentFont(const Font& font);
    void setCurrentPointSize(unsigned int size);
    void setCurrentLineType(short type) throw (Exception);

    void drawLine(double x1, double y1, double x2, double y2);
    void drawRect(double x, double y, double width, double height, short fill = FILL_EMPTY);
    void drawCircle(double x, double y, double radius, short fill = FILL_EMPTY);
    void drawText(double x, double y, const std::string& text, short hpos = TEXT_HORIZONTAL_LEFT, short vpos = TEXT_VERTICAL_BOTTOM, double angle = 0) throw (UnvalidFlagException);
    
    void comment(const std::string& comment) {}

  public:
    int xpos(double x) const { return static_cast<int>(round(x_(x))); }
    int ypos(double y) const { return static_cast<int>(round(y_(y))); }
    double revx(int xpos) const { return revx_(static_cast<double>(xpos)); }
    double revy(int ypos) const { return revy_(static_cast<double>(ypos)); }

 
};

} //end of namespace bpp

#endif //_QTGRAPHICDEVICE_H_

