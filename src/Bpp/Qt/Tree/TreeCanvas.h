// Copyright or (C) or Copr. Bio++ Development Team, (November 16, 2004)
// SPDX-FileCopyrightText: The Bio++ Development Group
//
// SPDX-License-Identifier: CECILL-2.1

#ifndef _TREECANVAS_H_
#define _TREECANVAS_H_

#include "../QtGraphicDevice.h"
#include "../MouseListener.h"

//From the STL:
#include <vector>
#include <map>
#include <string>
#include <algorithm>

//From bpp-phyl:
#include <Bpp/Phyl/Tree/Tree.h>
#include <Bpp/Phyl/Graphics/TreeDrawing.h>
#include <Bpp/Phyl/Graphics/AbstractTreeDrawing.h>

//From Qt:
#include <QGraphicsView>

namespace bpp
{

class TreeCanvas;

/**
 * @brief A simple mouse event.
 */
class NodeMouseEvent:
  public QMouseEvent
{
  private:
    bool hasNode_;
    int nodeId_;

  public:
    NodeMouseEvent(const TreeCanvas& treeCanvas, const QMouseEvent& event);

    bool hasNodeId() const { return hasNode_; }

    int getNodeId() const
    {
      if (!hasNode_)
        throw NodeNotFoundException("NodeMouseEvent::getNodeId().", "");
      else
        return nodeId_;
    }

};

/**
 * @brief Panel for plotting phylogenetic trees.
 *
 * The graph used for plotting the tree depends on the TreeDrawing object used.
 * This panel can also capture event when a node is clicked on the tree.
 */
class TreeCanvas:
  public QGraphicsView
{
  Q_OBJECT

  private:
    const Tree* currentTree_;
    TreeDrawing* treeDrawing_;
    TreeDrawing* defaultTreeDrawing_;
    mutable QtGraphicDevice device_;
    unsigned int drawingWidth_;
    unsigned int drawingHeight_;
    MouseListenerGroup mouseListenerGroup_;
    mutable std::map<int, bool> nodeCollapsed_;

  public:
    TreeCanvas(QWidget* parent = 0);

  private:
    //No copy allowed
    TreeCanvas(const TreeCanvas& tc):
      currentTree_(), treeDrawing_(), defaultTreeDrawing_(), device_(),
      drawingWidth_(), drawingHeight_(), mouseListenerGroup_(), nodeCollapsed_()
    {}
    TreeCanvas& operator=(const TreeCanvas& tc) { return *this; }
      
  public:
    virtual ~TreeCanvas()
    {
      delete defaultTreeDrawing_;
    }

  public:
    virtual void setTree(const Tree* tree);
    
    virtual const Tree* getTree() const { return currentTree_; }

    virtual void setTreeDrawing(const TreeDrawing& treeDrawing, bool repaint = true);

    virtual TreeDrawing* getTreeDrawing() { return treeDrawing_; }
    virtual const TreeDrawing* getTreeDrawing() const { return treeDrawing_; }

    virtual QtGraphicDevice& getDevice() { return device_; }
    virtual const QtGraphicDevice& getDevice() const { return device_; }

    virtual void setDrawingSize(unsigned int width, unsigned int height)
    {
      drawingWidth_  = width;
      drawingHeight_ = height;
      redraw();
    }

    virtual unsigned int drawingWidth() const { return drawingWidth_; }
    virtual unsigned int drawingHeight() const { return drawingHeight_; }

    void collapseNode(int nodeId, bool tf)
    {
      if (!currentTree_) return;
      if (!currentTree_->hasNode(nodeId))
        throw NodeNotFoundException("TreeCanvas::collapseNode.", nodeId);  
      if (treeDrawing_)
        treeDrawing_->collapseNode(nodeId, tf);
      nodeCollapsed_[nodeId] = tf;
    }

    bool isNodeCollapsed(int nodeId) const
    {
      if (!currentTree_) return false;
      if (!currentTree_->hasNode(nodeId))
        throw NodeNotFoundException("TreeCanvas::isNodeCollapsed.", nodeId);  
      return nodeCollapsed_[nodeId];
    }

    /**
     * @brief Loop for some text in the drawing and get the corresponding coordinates.
     *
     * @todo We might want to use some proper indexing for this function to work properly...
     */
    QList<QGraphicsTextItem*> searchText(const QString& text);

    /**
     * @name Mouse handling functions.
     *
     * @{
     */
    void addMouseListener(MouseListener* listener)
    {
      mouseListenerGroup_.addMouseListener(listener);
    }

    virtual void redraw();

  protected:
  
    void mouseDoubleClickEvent(QMouseEvent* event)
    {
      std::unique_ptr<NodeMouseEvent> newEvent(new NodeMouseEvent(*this, *event));
      mouseListenerGroup_.processMouseDoubleClickEvent(newEvent.get());
    }

    void mouseMoveEvent(QMouseEvent* event)
    {
      std::unique_ptr<NodeMouseEvent> newEvent(new NodeMouseEvent(*this, *event));
      mouseListenerGroup_.processMouseMoveEvent(newEvent.get());
    }
    void mousePressEvent(QMouseEvent* event)
    {
      std::unique_ptr<NodeMouseEvent> newEvent(new NodeMouseEvent(*this, *event));
      mouseListenerGroup_.processMousePressEvent(newEvent.get());
    }

    void mouseReleaseEvent(QMouseEvent* event)
    {
      std::unique_ptr<NodeMouseEvent> newEvent(new NodeMouseEvent(*this, *event));
      mouseListenerGroup_.processMouseReleaseEvent(newEvent.get());
    }
    /** @} */

  signals:
    void drawingChanged();

};

} //end of namespace bpp.

#endif //_TREECANVAS_H_

