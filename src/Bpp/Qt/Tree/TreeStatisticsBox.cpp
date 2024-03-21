// SPDX-FileCopyrightText: The Bio++ Development Group
//
// SPDX-License-Identifier: CECILL-2.1

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

