// Copyright or © or Copr. Bio++ Develomment Team, (2010)
// SPDX-FileCopyrightText: The Bio++ Development Group
//
// SPDX-License-Identifier: CECILL-2.1

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

