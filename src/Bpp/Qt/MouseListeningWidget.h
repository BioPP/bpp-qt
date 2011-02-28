//
// File: MouseListeningWidget.h
// Created by: Julien Dutheil
// Created on: Tue May 11 13:22 2010
//

/*
Copyright or © or Copr. Bio++ Develomment Team, (2010)

This software is a computer program whose purpose is to provide
graphic components to develop bioinformatics applications.

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

