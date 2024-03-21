// Copyright or (c) or Copr. CNRS, (November 16, 2004)
// SPDX-FileCopyrightText: The Bio++ Development Group
//
// SPDX-License-Identifier: CECILL-2.1

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

