//
// File: MouseListener.h
// Created by: Julien Dutheil
// Created on: Tue May 11 13:04 2010
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

#ifndef _MOUSELISTENER_H_
#define _MOUSELISTENER_H_

#include <Bpp/Clonable.h>

//From the STL:
#include <vector>

//From Qt:
#include <QMouseEvent>

namespace bpp {

/**
 * @brief a general interface to grab mouse events associated to a widget.
 */
class MouseListener:
  public virtual Clonable
{
  public:
#ifndef NO_VIRTUALCOV
    MouseListener* clone() const = 0;
#endif

  public:
    virtual void mouseDoubleClickEvent(QMouseEvent* event) = 0;
    virtual void mouseMoveEvent(QMouseEvent* event) = 0;
    virtual void mousePressEvent(QMouseEvent *event) = 0;
    virtual void mouseReleaseEvent(QMouseEvent *event) = 0;

    virtual bool isAutonomous() const = 0;
};

/**
 * @brief an empty implementation of the MouseListener interface.
 */
class MouseAdapter:
  public virtual MouseListener
{
  public:
    void mouseDoubleClickEvent(QMouseEvent* event) {}
    void mouseMoveEvent(QMouseEvent* event) {}
    void mousePressEvent(QMouseEvent *event) {}
    void mouseReleaseEvent(QMouseEvent *event) {}
};

/**
 * @brief a helper class that deal with several MouseListener classes.
 */
class MouseListenerGroup
{
  private:
    std::vector<MouseListener*> mouseListeners_;

  public:
    MouseListenerGroup(): mouseListeners_() {}

    MouseListenerGroup(const MouseListenerGroup& mlg):
      mouseListeners_(mlg.mouseListeners_)
    {
      for (unsigned int i = 0; i < mlg.mouseListeners_.size(); i++)
        if (!mlg.mouseListeners_[i]->isAutonomous())
          mouseListeners_[i] = dynamic_cast<MouseListener*>(mlg.mouseListeners_[i]->clone());
    }

    MouseListenerGroup& operator=(const MouseListenerGroup& mlg)
    {
      mouseListeners_ = mlg.mouseListeners_;
      for (unsigned int i = 0; i < mlg.mouseListeners_.size(); i++)
        if (!mlg.mouseListeners_[i]->isAutonomous())
          mouseListeners_[i] = dynamic_cast<MouseListener*>(mlg.mouseListeners_[i]->clone());
      return *this;
    }

    virtual ~MouseListenerGroup()
    {
      for (unsigned int i = 0; i < mouseListeners_.size(); i++)
        if (!mouseListeners_[i]->isAutonomous())
          delete mouseListeners_[i];
    }

  public:
    void addMouseListener(MouseListener* listener)
    {
      mouseListeners_.push_back(listener);
    }

    void processMouseDoubleClickEvent(QMouseEvent* event)
    {
      for (unsigned int i = 0; i < mouseListeners_.size(); i++)
        mouseListeners_[i]->mouseDoubleClickEvent(event);
    }

    void processMouseMoveEvent(QMouseEvent* event)
    {
      for (unsigned int i = 0; i < mouseListeners_.size(); i++)
        mouseListeners_[i]->mouseMoveEvent(event);
    }
    void processMousePressEvent(QMouseEvent* event)
    {
      for (unsigned int i = 0; i < mouseListeners_.size(); i++)
        mouseListeners_[i]->mousePressEvent(event);
    }

    void processMouseReleaseEvent(QMouseEvent* event)
    {
      for (unsigned int i = 0; i < mouseListeners_.size(); i++)
        mouseListeners_[i]->mouseReleaseEvent(event);
    }
    
};

} //end of namespace bpp.

#endif //_MOUSELISTENER_H_

