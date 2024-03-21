// Copyright or © or Copr. CNRS, (November 16, 2006)
// SPDX-FileCopyrightText: The Bio++ Development Group
//
// SPDX-License-Identifier: CECILL-2.1

#ifndef _QTTOOLS_H_
#define _QTTOOLS_H_

#include <Bpp/Graphics/RgbColor.h>
#include <Bpp/Graphics/Font/Font.h>
#include <Bpp/BppString.h>
#include <Bpp/Numeric/Number.h>

//From Qt:
#include <QColor>
#include <QFont>

namespace bpp
{

/**
 * @brief Utilitary functions for working with Qt.
 *
 * Contains mostly conversion tools.
 */
class QtTools
{
public:

  static QString toQt(const char* str)
  {
    return QString(str);
  }

   static QString toQt(const std::string& str)
  {
    return QString(str.c_str());
  }

  static QString toQt(const BppString& str)
  {
    return QString(str.toSTL().c_str());
  }

  template<class T>
  static QString toQt(const Number<T>& number)
  {
    return toQt(TextTools::toString(number.getValue()));
  }

  static QColor toQt(const RGBColor& color)
  {
    return QColor(static_cast<int>(color[0]),
		  static_cast<int>(color[1]),
		  static_cast<int>(color[2]));
  }

  static QFont toQt(const Font& font)
  {
    QFont qFont(toQt(font.getFamily()), static_cast<int>(font.getSize()));
    
    if (font.getStyle() == Font::STYLE_NORMAL)
      qFont.setStyle(QFont::StyleNormal); 
    else if(font.getStyle() == Font::STYLE_ITALIC)
      qFont.setStyle(QFont::StyleItalic); 
    
    if (font.getWeight() == Font::WEIGHT_NORMAL)
      qFont.setWeight(QFont::Normal); 
    else if (font.getWeight() == Font::WEIGHT_BOLD)
      qFont.setWeight(QFont::Bold); 
    
    return qFont;
 }

};

} //end of namespace bpp;

#endif //_QTTOOLS_H_

