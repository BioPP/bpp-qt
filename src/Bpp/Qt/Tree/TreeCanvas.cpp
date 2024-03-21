// Copyright or (C) or Copr. Bio++ Development Team, (November 16, 2004)
// SPDX-FileCopyrightText: The Bio++ Development Group
//
// SPDX-License-Identifier: CECILL-2.1

#include "TreeCanvas.h"
#include <QGraphicsItem>

//From PhyLib:
#include <Bpp/Phyl/Graphics/CladogramPlot.h>

using namespace bpp;

#include <iostream>
using namespace std;

NodeMouseEvent::NodeMouseEvent(const TreeCanvas& treeCanvas, const QMouseEvent& event):
  QMouseEvent(event), hasNode_(false), nodeId_(0)
{
  QPointF scenePos = treeCanvas.mapToScene(event.pos());
  Point2D<double> pos(
      treeCanvas.getDevice().revx(scenePos.x()),
      treeCanvas.getDevice().revy(scenePos.y()));
  try {
    nodeId_ = treeCanvas.getTreeDrawing()->getNodeAt(pos);
    hasNode_ = true;
  } catch (std::exception& e) {
    hasNode_ = false;
  }
}

TreeCanvas::TreeCanvas(QWidget* parent) :
  QGraphicsView(parent),
  currentTree_(0),
  treeDrawing_(),
  defaultTreeDrawing_(new CladogramPlot()),
  device_(),
  drawingWidth_(600),
  drawingHeight_(800),
  mouseListenerGroup_(),
  nodeCollapsed_()
{
  treeDrawing_ = defaultTreeDrawing_;
}

void TreeCanvas::redraw()
{
  if (treeDrawing_ && treeDrawing_->hasTree())
  {
    QPointF p = mapToScene(contentsRect().center());
    device_.begin();
    treeDrawing_->setXUnit(static_cast<double>(drawingWidth()) / treeDrawing_->getWidth());
    treeDrawing_->setYUnit(static_cast<double>(drawingHeight()) / treeDrawing_->getHeight());
    treeDrawing_->plot(device_);    
    device_.end();
    QGraphicsScene* scene = &device_.getScene();
    
    //Need to do that because line have can have a bounding box with null dimension.
    QRectF rect;
    QList<QGraphicsItem*> items = scene->items();
    for (int i = 0; i < items.size(); i++) {
      QRectF bb = items[i]->boundingRegion(items[i]->sceneTransform()).boundingRect();
      if (i == 0) rect = bb;
      else {
        rect.setLeft(min(rect.left(), bb.left()));
        rect.setRight(max(rect.right(), bb.right()));
        rect.setBottom(max(rect.bottom(), bb.bottom()));
        rect.setTop(min(rect.top(), bb.top()));
      }
    }
    rect.setLeft(rect.left() - 5);
    rect.setRight(rect.right() + 5);
    rect.setBottom(rect.bottom() + 5);
    rect.setTop(rect.top() - 5);
    scene->setSceneRect(rect);
    setScene(scene);
    centerOn(p);
    emit drawingChanged();
  }
}

void TreeCanvas::setTree(const Tree* tree)
{
  currentTree_ = tree;
  treeDrawing_->setTree(tree);
  nodeCollapsed_.clear();
  redraw();
}

void TreeCanvas::setTreeDrawing(const TreeDrawing& treeDrawing, bool repaint)
{
  if (treeDrawing_ != defaultTreeDrawing_)
    delete treeDrawing_;
  treeDrawing_ = dynamic_cast<TreeDrawing*>(treeDrawing.clone());
  treeDrawing_->setTree(currentTree_);
  vector<int> ids = currentTree_->getNodesId();
  for (size_t i = 0; i < ids.size(); i++) {
    treeDrawing_->collapseNode(ids[i], nodeCollapsed_[ids[i]]);
  }
  if (repaint) {
    this->repaint();
  }
}

QList<QGraphicsTextItem*> TreeCanvas::searchText(const QString& text)
{
  QList<QGraphicsTextItem*> match;
  QList<QGraphicsItem*> items = device_.getScene().items();
  for (int i = 0; i < items.size(); ++i) {
    QGraphicsTextItem* item = dynamic_cast<QGraphicsTextItem*>(items[i]);
    if (item) {
      if (item->toPlainText().indexOf(text) > -1) {
        match.append(item);
      }
    } //Else not a text item
  }
  return match;
}
