// Copyright or © or Copr. Bio++ Develomment Team, (2010)
// SPDX-FileCopyrightText: The Bio++ Development Group
//
// SPDX-License-Identifier: CECILL-2.1

#ifndef _MOUSELISTENINGWIDGET_H_
#define _MOUSELISTENINGWIDGET_H_

#include "MouseListener.h"

//From Qt:
#include <QWidget>

namespace bpp {

/**
 * @brief A simple QWidget object which adds support for mouse listeners.
 */
class MouseListeningWidget:
  public QWidget
{
  Q_OBJECT

  private:
    MouseListenerGroup mouseListenerGroup_;

  public:
    void addMouseListener(MouseListener* listener)
    {
      mouseListenerGroup_.addMouseListener(listener);
    }

  protected:
  
    void mouseDoubleClickEvent(QMouseEvent* event)
    {
      mouseListenerGroup_.processMouseDoubleClickEvent(event);
    }

    void mouseMoveEvent(QMouseEvent* event)
    {
      mouseListenerGroup_.processMouseMoveEvent(event);
    }
    void mousePressEvent(QMouseEvent* event)
    {
      mouseListenerGroup_.processMousePressEvent(event);
    }

    void mouseReleaseEvent(QMouseEvent* event)
    {
      mouseListenerGroup_.processMouseReleaseEvent(event);
    }
};

} //end of namespace bpp.

#endif //_MOUSELISTENINGWIDGET_H_

