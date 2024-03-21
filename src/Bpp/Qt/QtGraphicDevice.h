// SPDX-FileCopyrightText: The Bio++ Development Group
//
// SPDX-License-Identifier: CECILL-2.1

#ifndef _QTGRAPHICDEVICE_H_
#define _QTGRAPHICDEVICE_H_

#include <Bpp/Graphics/AbstractGraphicDevice.h>

//From Qt:
#include <QGraphicsScene>
#include <Qt>

//From the STL:
#include <map>
#include <memory>

/**
 * @mainpage
 *
 * @par
 * This library provides graphic classes for Bio++ developed using the Qt library.
 * The class QtGraphicDevice implements the GraphicDevice interface of the bpp-core library, allowing output in a Qt widget.
 * Similarly, the QtOutputStream implemente the OutputStream interface, and allows to redirect outputs to a widget.
 *
 * @par
 * For now, only phylogeny-oriented widgets are available. Sequence-oriented widgets will be developed in the future.
 */

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
    std::unique_ptr<QGraphicsScene> scene_;
    std::map<short int, Qt::PenStyle> supportedLineTypes_;
    QPen currentPen_;
    QBrush currentBrush_;
    QFont currentFont_;

  public:
    QtGraphicDevice();
    virtual ~QtGraphicDevice();

  public:
    QGraphicsScene& getScene() { return *scene_; }

    void begin();
    void end();

    void setCurrentForegroundColor(const RGBColor& color);
    void setCurrentBackgroundColor(const RGBColor& color);
    void setCurrentFont(const Font& font);
    void setCurrentPointSize(unsigned int size);
    void setCurrentLineType(short type);

    void drawLine(double x1, double y1, double x2, double y2);
    void drawRect(double x, double y, double width, double height, short fill = FILL_EMPTY);
    void drawCircle(double x, double y, double radius, short fill = FILL_EMPTY);
    void drawText(double x, double y, const std::string& text, short hpos = TEXT_HORIZONTAL_LEFT, short vpos = TEXT_VERTICAL_BOTTOM, double angle = 0);
    
    void comment(const std::string& comment) {}

  public:
    int xpos(double x) const { return static_cast<int>(round(x_(x))); }
    int ypos(double y) const { return static_cast<int>(round(y_(y))); }
    double revx(int xpos) const { return revx_(static_cast<double>(xpos)); }
    double revy(int ypos) const { return revy_(static_cast<double>(ypos)); }
    double revx(double xpos) const { return revx_(xpos); }
    double revy(double ypos) const { return revy_(ypos); }

 
};

} //end of namespace bpp

#endif //_QTGRAPHICDEVICE_H_

