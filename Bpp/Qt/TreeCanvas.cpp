//
// File: TreeCanvas.cpp
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

#include "TreeCanvas.h"
#include <QGraphicsItem>
//From PhyLib:
#include <Phyl/CladogramPlot.h>

using namespace bpp;

#include <iostream>
using namespace std;

TreeCanvas::TreeCanvas(QWidget* parent) :
  QGraphicsView(parent),
  currentTree_(0),
  device_(),
  drawingWidth_(600),
  drawingHeight_(800)
{
  defaultTreeDrawing_ = new CladogramPlot();
  treeDrawing_ = defaultTreeDrawing_;
}

void TreeCanvas::redraw()
{
  if (treeDrawing_ && treeDrawing_->hasTree())
  {
    device_.begin();
    treeDrawing_->setXUnit(static_cast<double>(drawingWidth()) / treeDrawing_->getWidth());
    treeDrawing_->setYUnit(static_cast<double>(drawingHeight()) / treeDrawing_->getHeight());
    treeDrawing_->plot(device_);
    for (unsigned int i = 0; i < drawableProperties_.size(); i++) {
      treeDrawing_->drawProperty(device_, drawableProperties_[i]);
    }
    device_.end();
    QGraphicsScene* scene = &device_.getScene();
    
    //Need to do that because line have can have a bounding box width null dimension.
    QRectF rect;
    QList<QGraphicsItem*> items = scene->items();
    for(int i = 0; i < items.size(); i++) {
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
  }
}

void TreeCanvas::setTree(const Tree* tree)
{
  currentTree_ = tree;
  treeDrawing_->setTree(tree);
  redraw();
}

