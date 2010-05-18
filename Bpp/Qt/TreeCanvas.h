//
// File: TreeCanvas.h
// Created by: Julien Dutheil
// Created on: Tue Oct 4 09:20 2006
//

/*
Copyright or © or Copr. CNRS, (November 16, 2004)

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

#ifndef _TREECANVAS_H_
#define _TREECANVAS_H_

#include "QtGraphicDevice.h"
#include "MouseListener.h"

//From the STL:
#include <vector>
#include <map>
#include <string>
#include <algorithm>

//From PhylLib:
#include <Phyl/Tree.h>
#include <Phyl/TreeDrawing.h>
#include <Phyl/AbstractTreeDrawing.h>

//From Qt:
#include <QGraphicsView>

namespace bpp
{

class TreeCanvas;

class NodeMouseEvent:
  public QMouseEvent
{
  private:
    bool hasNode_;
    int nodeId_;

  public:
    NodeMouseEvent(const TreeCanvas& treeCanvas, const QMouseEvent& event);

    bool hasNodeId() const { return hasNode_; }

    int getNodeId() const throw (NodeNotFoundException)
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
 * The graphe used for plotting the tree depends on the TreeDrawing object used.
 * This panel can also capture event when a node is clicked on the tree.
 */
class TreeCanvas:
  public QGraphicsView
{
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

    virtual void redraw();

    virtual void setDrawingSize(unsigned int width, unsigned int height)
    {
      drawingWidth_  = width;
      drawingHeight_ = height;
      redraw();
    }

    virtual unsigned int drawingWidth() const { return drawingWidth_; }
    virtual unsigned int drawingHeight() const { return drawingHeight_; }

    void collapseNode(int nodeId, bool tf) throw (NodeNotFoundException)
    {
      if (!currentTree_) return;
      if (!currentTree_->hasNode(nodeId))
        throw NodeNotFoundException("TreeCanvas::collapseNode.", nodeId);  
      if (treeDrawing_)
        treeDrawing_->collapseNode(nodeId, tf);
      nodeCollapsed_[nodeId] = tf;
    }

    bool isNodeCollapsed(int nodeId) const throw (NodeNotFoundException)
    {
      if (!currentTree_) return false;
      if (!currentTree_->hasNode(nodeId))
        throw NodeNotFoundException("TreeCanvas::isNodeCollapsed.", nodeId);  
      return nodeCollapsed_[nodeId];
    }

    /**
     * @name Mouse handling functions.
     *
     * @{
     */
    void addMouseListener(MouseListener* listener)
    {
      mouseListenerGroup_.addMouseListener(listener);
    }

  protected:
  
    void mouseDoubleClickEvent(QMouseEvent* event)
    {
      std::auto_ptr<NodeMouseEvent> newEvent(new NodeMouseEvent(*this, *event));
      mouseListenerGroup_.processMouseDoubleClickEvent(newEvent.get());
    }

    void mouseMoveEvent(QMouseEvent* event)
    {
      std::auto_ptr<NodeMouseEvent> newEvent(new NodeMouseEvent(*this, *event));
      mouseListenerGroup_.processMouseMoveEvent(newEvent.get());
    }
    void mousePressEvent(QMouseEvent* event)
    {
      std::auto_ptr<NodeMouseEvent> newEvent(new NodeMouseEvent(*this, *event));
      mouseListenerGroup_.processMousePressEvent(newEvent.get());
    }

    void mouseReleaseEvent(QMouseEvent* event)
    {
      std::auto_ptr<NodeMouseEvent> newEvent(new NodeMouseEvent(*this, *event));
      mouseListenerGroup_.processMouseReleaseEvent(newEvent.get());
    }
    /** @} */

};

} //end of namespace bpp.

#endif //_TREECANVAS_H_

