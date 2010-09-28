//
// File: TreeStatisticsBox.cpp
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

#include "TreeStatisticsBox.h"

#include <Bpp/Text/TextTools.h>
#include <Bpp/Numeric/VectorTools.h>

//From Qt:
#include <QFormLayout>

using namespace bpp;

TreeStatisticsBox::TreeStatisticsBox(QWidget* parent):
  QGroupBox(parent),
  leavesNumber_(this),
  ancestorsNumber_(this),
  maxFurcation_(this),
  depth_(this),
  height_(this)
{
  QFormLayout* layout = new QFormLayout();
  layout->addRow(tr("# Leaves:"), &leavesNumber_);
  layout->addRow(tr("# Ancestors:"), &ancestorsNumber_);
  layout->addRow(tr("Max n-furcation:"), &maxFurcation_);
  layout->addRow(tr("Depth:"), &depth_);
  layout->addRow(tr("Height:"), &height_);
  setLayout(layout);
}

void TreeStatisticsBox::updateTree(const Tree& tree)
{
  stats_.setTree(tree);
  leavesNumber_.setText(tr(TextTools::toString(stats_.getNumberOfLeaves()).c_str()));
  ancestorsNumber_.setText(tr(TextTools::toString(stats_.getNumberOfAncestors()).c_str()));
  maxFurcation_.setText(tr(TextTools::toString(VectorTools::max(stats_.getNodeNumberOfSons())).c_str()));
  depth_.setText(tr(TextTools::toString(*stats_.getNodeDepths().rbegin()).c_str()));
  height_.setText(tr(TextTools::toString(*stats_.getNodeHeights().rbegin()).c_str()));
}

