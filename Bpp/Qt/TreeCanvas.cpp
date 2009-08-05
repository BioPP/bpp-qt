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

//From PhyLib:
#include <Phyl/CladogramPlot.h>

using namespace bpp;

TreeCanvas::TreeCanvas(QWidget* parent) :
  QWidget(parent),
  device_(),
  currentTree_(0)
{
  device_.setMargins(10,10,10,10);
  device_.setPaintDevice(this);
  defaultTreeDrawing_ = new CladogramPlot();
  treeDrawing_ = defaultTreeDrawing_;
}

void TreeCanvas::paintEvent(QPaintEvent* paintEvent)
{
  if (treeDrawing_ && treeDrawing_->hasTree())
  {
    device_.begin();
    treeDrawing_->setXUnit((static_cast<double>(width()) - device_.getMarginLeft() - device_.getMarginRight()) / treeDrawing_->getWidth());
    treeDrawing_->setYUnit((static_cast<double>(height()) - device_.getMarginTop() - device_.getMarginBottom()) / treeDrawing_->getHeight());
    treeDrawing_->plot(device_);
    for (unsigned int i = 0; i < drawableProperties_.size(); i++)
    {
      treeDrawing_->drawProperty(device_, drawableProperties_[i]);
    }
    device_.end();
  }
}

void TreeCanvas::setTree(const Tree* tree)
{
  currentTree_ = tree;
  treeDrawing_->setTree(tree);
  repaint();
}

