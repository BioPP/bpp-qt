//
// File: QtOutputStream.h
// Created by: Julien Dutheil
// Created on: Mon Jan 25 2010
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

#ifndef _QTOUTPUTSTREAM_H_
#define _QTOUTPUTSTREAM_H_

#include "QtTools.h"

#include <Bpp/Io/OutputStream.h>

//From Qt:
#include <QPainter>
#include <Qt>
#include <QTextEdit>

//From the STL:
#include <map>
#include <iostream>

namespace bpp
{

/**
 * @brief Qt output stream: Qt widget that implements the OutputStream interface.
 *
 * The stream is printed as a read-only text. The number of lines to display can be set.
 */
class QtOutputStream :
  public AbstractOutputStream,
  public QTextEdit
{
private:
  unsigned int maxNbLines_;
  QString buffer;

public:
  QtOutputStream(QWidget* parent = 0) :
    QTextEdit(parent),
    maxNbLines_(100)
  {
    setReadOnly(true);
  }

private:
  QtOutputStream(const QtOutputStream& outputstream) {}
  QtOutputStream& operator=(const QtOutputStream& outputstream) { return *this; }

public:
  QtOutputStream& operator<<(const QString& message) { buffer.append(message); return *this; }
  QtOutputStream& operator<<(const std::string& message) { buffer.append(QtTools::toQt(message)); return *this; }
  QtOutputStream& operator<<(const char* message) { buffer.append(QString(message)); return *this; }
  QtOutputStream& operator<<(const char& message) { buffer.append(QtTools::toQt(TextTools::toString(message))); return *this; }
  QtOutputStream& operator<<(const int& message) { buffer.append(QtTools::toQt(TextTools::toString(message))); return *this; }
  QtOutputStream& operator<<(const unsigned int& message) { buffer.append(QtTools::toQt(TextTools::toString(message))); return *this; }
  QtOutputStream& operator<<(const long int& message) { buffer.append(QtTools::toQt(TextTools::toString(message))); return *this; }
  QtOutputStream& operator<<(const unsigned long int& message) { buffer.append(QtTools::toQt(TextTools::toString(message))); return *this; }
  QtOutputStream& operator<<(const double& message) { buffer.append(QtTools::toQt(TextTools::toString(message, getPrecision()))); return *this; }
  QtOutputStream& operator<<(const long double& message) { buffer.append(QtTools::toQt(TextTools::toString(message, getPrecision()))); return *this; }
  QtOutputStream& operator<<(const bool& message) { buffer.append(QtTools::toQt(TextTools::toString(message))); return *this; }
  QtOutputStream& endLine()
  {
    buffer.append("\n");
    return flush();
  }
  QtOutputStream& flush()
  {
    insertPlainText(buffer);
    buffer.fill(' ', 0);
    checkNumberOfLines();
    update();
    return *this;
  }

  QtOutputStream* clone() const { return new QtOutputStream(*this); }

private:
  void checkNumberOfLines();

};



} //end of namespace bpp

#endif //_QTOUTPUTSTREAM_H_

