//
// File: TreeStatisticsBox.h
// Created by: Julien Dutheil
// Created on: Sun Aug 9 12:27 2009
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

#ifndef _TREESTATISTICSBOX_H_
#define _TREESTATISTICSBOX_H_


//From PhylLib:
#include <Bpp/Phyl/PhyloStatistics.h>

//From Qt:
#include <QWidget>
#include <QGroupBox>
#include <QLabel>

namespace bpp
{

/**
 * @brief Panel that display a few statistics on a tree.
 */
class TreeStatisticsBox:
  public QGroupBox
{
  Q_OBJECT

  protected:
    PhyloStatistics stats_;
    QLabel leavesNumber_;
    QLabel ancestorsNumber_;
    QLabel maxFurcation_;
    QLabel depth_;
    QLabel height_;

  public:
    TreeStatisticsBox(QWidget* parent = 0);
    virtual ~TreeStatisticsBox() {}

  public:
    virtual void updateTree(const Tree& tree);
    
};

} //end of namespace bpp.

#endif //_TREESTATISTICSBOX_H_

