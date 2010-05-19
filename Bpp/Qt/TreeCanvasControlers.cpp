//
// File: TreeCanvasControlers.cpp
// Created by: Julien Dutheil
// Created on: Sun Oct 24 16:31 2006
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

#include "TreeCanvasControlers.h"

//From Qt:
#include <QtGui>
#include <QRadioButton>

using namespace bpp;

void NodeClickableAreasTreeDrawingListener::afterDrawNode(const DrawNodeEvent& event)
{
  const TreeDrawing* td = event.getTreeDrawing();
  double r = td->getDisplaySettings()->pointArea;
  GraphicDevice* gd = event.getGraphicDevice();
  Cursor cursor     = event.getCursor();
  gd->drawRect(cursor.getX() - r, cursor.getY() - r, 2 * r, 2 * r);
}

const int TreeCanvasControlers::ID_WIDTH_CTRL                 = 1;
const int TreeCanvasControlers::ID_HEIGHT_CTRL                = 2;
const int TreeCanvasControlers::ID_DRAWING_CTRL               = 3;
const int TreeCanvasControlers::ID_ORIENTATION_CTRL           = 4;
const int TreeCanvasControlers::ID_DRAW_CLICKABLE_AREAS_CTRL  = 5;
const int TreeCanvasControlers::ID_DRAW_NODE_IDS_CTRL         = 6;
const int TreeCanvasControlers::ID_DRAW_LEAF_NAMES_CTRL     = 7;
const int TreeCanvasControlers::ID_DRAW_BRANCH_LENGTHS_CTRL     = 8;
const int TreeCanvasControlers::ID_DRAW_BOOTSTRAP_VALUES_CTRL = 9;
const std::string TreeCanvasControlers::PROPERTY_CLICKABLE_AREA       = "Clickable area";

TreeCanvasControlers::TreeCanvasControlers(QWidget* parent): treeCanvas_(0)
{
  //Drawing algorithms and controler:
  tdSettings_ = new TreeDrawingSettings();
  phylogram_ = new PhylogramPlot();
  cladogram_ = new CladogramPlot();
  phylogram_->setDisplaySettings(tdSettings_);
  cladogram_->setDisplaySettings(tdSettings_);
  availableTreeDrawings_.append(QString(cladogram_->getName().c_str()));
  availableTreeDrawings_.append(QString(phylogram_->getName().c_str()));
  tdDisplayControler_ = new BasicTreeDrawingDisplayControler(tdSettings_);
  tdDisplayControler_->addListener(PROPERTY_CLICKABLE_AREA, reinterpret_cast<TreeDrawingListener*>(new NodeClickableAreasTreeDrawingListener(true)));
  tdDisplayControler_->registerTreeDrawing(phylogram_);
  tdDisplayControler_->registerTreeDrawing(cladogram_);
  
  //TreeDrawing algorithm choice and options:
  widthCtrl_   = new QSpinBox(parent);
  widthCtrl_->setRange(100, 10000);
  connect(widthCtrl_, SIGNAL(valueChanged(int)), this, SLOT(treeDrawingUnitChanged()));
  heightCtrl_  = new QSpinBox(parent);  
  heightCtrl_->setRange(100, 10000);
  connect(heightCtrl_, SIGNAL(valueChanged(int)), this, SLOT(treeDrawingUnitChanged()));
  drawingCtrl_ = new QComboBox(parent);
  drawingCtrl_->addItems(availableTreeDrawings_);
  connect(drawingCtrl_, SIGNAL(currentIndexChanged(int)), this, SLOT(treeDrawingChanged()));

  orientationCtrl_ = new QGroupBox(parent);
  QRadioButton* leftButton  = new QRadioButton(QString("L"), orientationCtrl_);
  QRadioButton* rightButton = new QRadioButton(QString("R"), orientationCtrl_);
  QRadioButton* upButton    = new QRadioButton(QString("U"), orientationCtrl_);
  QRadioButton* downButton  = new QRadioButton(QString("D"), orientationCtrl_);
  QHBoxLayout *hbox = new QHBoxLayout;
  hbox->addWidget(leftButton);
  hbox->addWidget(rightButton);
  hbox->addWidget(upButton);
  hbox->addWidget(downButton);
  orientationCtrl_->setLayout(hbox);
  orientationLeftRight_ = new QButtonGroup;
  connect(orientationLeftRight_, SIGNAL(buttonClicked(int)), this, SLOT(treeDrawingChanged()));
  orientationUpDown_    = new QButtonGroup;
  connect(orientationUpDown_, SIGNAL(buttonClicked(int)), this, SLOT(treeDrawingChanged()));
  orientationLeftRight_->addButton(leftButton, 1);
  orientationLeftRight_->addButton(rightButton, 2);
  orientationUpDown_->addButton(upButton, 3);
  orientationUpDown_->addButton(downButton, 4);
  leftButton->setChecked(true);
  upButton->setChecked(true);

  //Display options:
  drawClickableAreas_     = new QCheckBox("Clickable areas", parent);
  drawNodesId_            = new QCheckBox("Nodes id", parent);
  drawLeavesNames_        = new QCheckBox("Leaves names", parent);
  drawBranchLengthValues_ = new QCheckBox("Branch lengths", parent);
  drawBootstrapValues_    = new QCheckBox("Boostrap values", parent);
  connect(drawClickableAreas_    , SIGNAL(stateChanged(int)), this, SLOT(treeDrawingChanged()));
  connect(drawNodesId_           , SIGNAL(stateChanged(int)), this, SLOT(treeDrawingChanged()));
  connect(drawLeavesNames_       , SIGNAL(stateChanged(int)), this, SLOT(treeDrawingChanged()));
  connect(drawBranchLengthValues_, SIGNAL(stateChanged(int)), this, SLOT(treeDrawingChanged()));
  connect(drawBootstrapValues_   , SIGNAL(stateChanged(int)), this, SLOT(treeDrawingChanged()));
  drawLeavesNames_->setChecked(true);
  
  blockSignal_ = false;
  actualizeOptions();
}

TreeCanvasControlers::~TreeCanvasControlers()
{
  delete widthCtrl_;
  delete heightCtrl_;
  delete drawingCtrl_;
  delete orientationCtrl_;
  delete drawClickableAreas_;
  delete drawNodesId_;
  delete drawLeavesNames_;
  delete drawBranchLengthValues_;
  delete drawBootstrapValues_;
  delete phylogram_;
  delete cladogram_;
  delete tdSettings_;
  delete tdDisplayControler_;
}



void TreeCanvasControlers::setTreeCanvas(TreeCanvas* canvas, bool updateOptions)
{
  treeCanvas_ = canvas;
  if (updateOptions) actualizeOptions();
  else applyOptions(treeCanvas_);
}



void TreeCanvasControlers::applyOptions(TreeCanvas* canvas)
{
  QString selection = drawingCtrl_->currentText();
  if (QString(canvas->getTreeDrawing()->getName().c_str()) != selection)
  {
    if (selection == QString(cladogram_->getName().c_str()))
    {
      canvas->setTreeDrawing(*cladogram_, false);
    }
    else if (selection == QString(phylogram_->getName().c_str()))
    {
      canvas->setTreeDrawing(*phylogram_, false);
    }
  }
  AbstractDendrogramPlot* treeDrawing = dynamic_cast<AbstractDendrogramPlot*>(canvas->getTreeDrawing());
  
  treeDrawing->setHorizontalOrientation(orientationLeftRight_->checkedId() == 1 ? AbstractDendrogramPlot::ORIENTATION_LEFT_TO_RIGHT : AbstractDendrogramPlot::ORIENTATION_RIGHT_TO_LEFT);
  treeDrawing->setVerticalOrientation(orientationUpDown_->checkedId() == 3 ? AbstractDendrogramPlot::ORIENTATION_TOP_TO_BOTTOM : AbstractDendrogramPlot::ORIENTATION_BOTTOM_TO_TOP);

  tdDisplayControler_->enableListener(PROPERTY_CLICKABLE_AREA, drawClickableAreas_->isChecked());
  tdDisplayControler_->enableListener(BasicTreeDrawingDisplayControler::PROPERTY_NODE_IDS, drawNodesId_->isChecked());
  tdDisplayControler_->enableListener(BasicTreeDrawingDisplayControler::PROPERTY_LEAF_NAMES, drawLeavesNames_->isChecked());
  tdDisplayControler_->enableListener(BasicTreeDrawingDisplayControler::PROPERTY_BRANCH_LENGTHS, drawBranchLengthValues_->isChecked());
  tdDisplayControler_->enableListener(BasicTreeDrawingDisplayControler::PROPERTY_BOOTSTRAP_VALUES, drawBootstrapValues_->isChecked());

  //Refresh the drawing(s):
  fireActionEvent_();
}



void TreeCanvasControlers::treeDrawingChanged()
{
  if (!treeCanvas_) return;
  if (! blockSignal_) applyOptions(treeCanvas_);
}


void TreeCanvasControlers::treeDrawingUnitChanged()
{
  if (!treeCanvas_) return;
  if (! blockSignal_)
  {
    treeCanvas_->setDrawingSize(widthCtrl_->value(), heightCtrl_->value());
  }
}

void TreeCanvasControlers::actualizeOptions()
{
  if (!treeCanvas_) return;
  AbstractDendrogramPlot* current = dynamic_cast<AbstractDendrogramPlot*>(treeCanvas_->getTreeDrawing());
  blockSignal_ = true; //Dirty trick but no choice!
  widthCtrl_->setValue(treeCanvas_->drawingWidth());
  heightCtrl_->setValue(treeCanvas_->drawingHeight());
  drawingCtrl_->setCurrentIndex(availableTreeDrawings_.indexOf(QString(current->getName().c_str())));
  if (current->getHorizontalOrientation() == AbstractDendrogramPlot::ORIENTATION_LEFT_TO_RIGHT)
    orientationLeftRight_->buttons()[0]->setChecked(true);
  else
    orientationLeftRight_->buttons()[1]->setChecked(true);
  if (current->getVerticalOrientation() == AbstractDendrogramPlot::ORIENTATION_TOP_TO_BOTTOM)
    orientationUpDown_->buttons()[0]->setChecked(true);
  else  
    orientationUpDown_->buttons()[1]->setChecked(true);
  
  //Not needed as all canvasses share the same controler:
  //drawClickableAreas_    ->setChecked(tdDisplayControler_->isListenerEnabled(PROPERTY_CLICKABLE_AREA));
  //drawNodesId_           ->setChecked(tdDisplayControler_->isListenerEnabled(BasicTreeDrawingDisplayControler::PROPERTY_NODE_IDS));
  //drawLeavesNames_       ->setChecked(tdDisplayControler_->isListenerEnabled(BasicTreeDrawingDisplayControler::PROPERTY_LEAF_NAMES));
  //drawBranchLengthValues_->setChecked(tdDisplayControler_->isListenerEnabled(BasicTreeDrawingDisplayControler::PROPERTY_BRANCH_LENGTHS));
  //drawBootstrapValues_   ->setChecked(tdDisplayControler_->isListenerEnabled(BasicTreeDrawingDisplayControler::PROPERTY_BOOTSTRAP_VALUES));
  blockSignal_ = false;
}

QWidget* TreeCanvasControlers::getControlerById(int id)
{
  if (id == ID_WIDTH_CTRL)                 return widthCtrl_;
  if (id == ID_HEIGHT_CTRL)                return heightCtrl_;
  if (id == ID_DRAWING_CTRL)               return drawingCtrl_;
  if (id == ID_ORIENTATION_CTRL)           return orientationCtrl_;
  if (id == ID_DRAW_CLICKABLE_AREAS_CTRL)  return drawClickableAreas_;
  if (id == ID_DRAW_NODE_IDS_CTRL)         return drawNodesId_;
  if (id == ID_DRAW_LEAF_NAMES_CTRL)       return drawLeavesNames_;
  if (id == ID_DRAW_BRANCH_LENGTHS_CTRL)   return drawBranchLengthValues_;
  if (id == ID_DRAW_BOOTSTRAP_VALUES_CTRL) return drawBootstrapValues_;
  return 0;
}

TreeDrawing* TreeCanvasControlers::getTreeDrawing(unsigned int i)
{
  if (i == 0) return cladogram_;
  if (i == 1) return phylogram_;
  return 0;
}

