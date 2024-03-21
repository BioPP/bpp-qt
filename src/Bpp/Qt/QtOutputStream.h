// SPDX-FileCopyrightText: The Bio++ Development Group
//
// SPDX-License-Identifier: CECILL-2.1

#ifndef _QTOUTPUTSTREAM_H_
#define _QTOUTPUTSTREAM_H_

#include "QtTools.h"

#include <Bpp/Io/OutputStream.h>

// From Qt:
#include <QPainter>
#include <Qt>
#include <QTextEdit>

// From the STL:
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
} // end of namespace bpp

#endif // _QTOUTPUTSTREAM_H_
