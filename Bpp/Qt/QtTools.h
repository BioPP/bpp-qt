//
// File: QtTools.h
// Created by: Julien Dutheil
// Created on: Wed Dec 30 2009
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

#ifndef _QTTOOLS_H_
#define _QTTOOLS_H_

//From Utils:
#include <Utils/RGBColor.h>
#include <Utils/Font.h>
#include <Utils/BppString.h>
#include <Utils/Number.h>

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
    return QColor(color[0], color[1], color[2]);
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

