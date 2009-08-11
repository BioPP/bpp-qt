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

//From the STL:
#include <vector>
#include <string>
#include <algorithm>

//From PhylLib:
#include <Phyl/Tree.h>
#include <Phyl/TreeDrawing.h>

//From Qt:
#include <QWidget>

namespace bpp
{

/**
 * @brief Panel for plotting phylogenetic trees.
 *
 * The graphe used for plotting the tree depends on the TreeDrawing object used.
 * This panel can also capture event when a node is clicked on the tree.
 */
class TreeCanvas:
  public QWidget
{
  protected:
    const Tree* currentTree_;
    TreeDrawing* treeDrawing_;
    TreeDrawing* defaultTreeDrawing_;
    QtGraphicDevice device_;
    std::vector<std::string> drawableProperties_;

  public:
    TreeCanvas(QWidget* parent = 0);
    virtual ~TreeCanvas()
    {
      delete defaultTreeDrawing_;
    }

  protected:
    void paintEvent(QPaintEvent* paintEvent);

  public:
    virtual void setTree(const Tree* tree);
    
    virtual const Tree* getTree() const { return currentTree_; }

    virtual void setTreeDrawing(const TreeDrawing& treeDrawing)
    {
      if (treeDrawing_ != defaultTreeDrawing_)
        delete treeDrawing_;
      treeDrawing_ = dynamic_cast<TreeDrawing *>(treeDrawing.clone());
      treeDrawing_->setTree(currentTree_);
      repaint();
    }

    virtual void setDrawPropertyOn(const std::string& property)
    {
      if (std::find(drawableProperties_.begin(), drawableProperties_.end(), property) == drawableProperties_.end())
        drawableProperties_.push_back(property);
    }
    
    virtual void setDrawPropertyOff(const std::string& property)
    {
      std::vector<std::string>::iterator it = std::find(drawableProperties_.begin(), drawableProperties_.end(), property);
      if (it != drawableProperties_.end())
        drawableProperties_.erase(it);
    }

    virtual void setDrawProperty(const std::string& property, bool drawPpt)
    {
      if (drawPpt)
        setDrawPropertyOn(property);
      else
        setDrawPropertyOff(property);
    }

    virtual bool isPropertyDrawn(const std::string& property) const
    {
      return std::find(drawableProperties_.begin(), drawableProperties_.end(), property) != drawableProperties_.end();
    }

    virtual TreeDrawing* getTreeDrawing() { return treeDrawing_; }
    virtual const TreeDrawing* GetTreeDrawing() const { return treeDrawing_; }

    virtual QtGraphicDevice& getDevice() { return device_; }
    virtual const QtGraphicDevice& getDevice() const { return device_; }

    

};

} //end of namespace bpp.

#endif //_TREECANVAS_H_

