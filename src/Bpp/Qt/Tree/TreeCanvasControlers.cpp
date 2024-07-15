// SPDX-FileCopyrightText: The Bio++ Development Group
//
// SPDX-License-Identifier: CECILL-2.1

#include "TreeCanvasControlers.h"

// From Qt:
#include <QtGui>
#include <QRadioButton>
#include <QHBoxLayout>
#include <QButtonGroup>

using namespace bpp;
using namespace std;

void NodeClickableAreasTreeDrawingListener::afterDrawNode(const DrawNodeEvent& event)
{
  const TreeDrawing* td = event.getTreeDrawing();
  double r = td->displaySettings().pointArea;
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
const int TreeCanvasControlers::ID_DRAW_LEAF_NAMES_CTRL       = 7;
const int TreeCanvasControlers::ID_DRAW_BRANCH_LENGTHS_CTRL   = 8;
const int TreeCanvasControlers::ID_DRAW_BOOTSTRAP_VALUES_CTRL = 9;
const std::string TreeCanvasControlers::PROPERTY_CLICKABLE_AREA = "Clickable area";

TreeCanvasControlers::TreeCanvasControlers(QWidget* parent) : treeCanvas_(nullptr)
{
  // Drawing algorithms and controler:
  tdSettings_ = std::make_shared<TreeDrawingSettings>();
  phylogram_.reset(new PhylogramPlot());
  cladogram_.reset(new CladogramPlot());
  phylogram_->setDisplaySettings(tdSettings_);
  cladogram_->setDisplaySettings(tdSettings_);
  availableTreeDrawings_.append(QString(cladogram_->getName().c_str()));
  availableTreeDrawings_.append(QString(phylogram_->getName().c_str()));
  tdDisplayControler_ = std::make_unique<BasicTreeDrawingDisplayControler>(tdSettings_);
  tdDisplayControler_->addListener(PROPERTY_CLICKABLE_AREA, new NodeClickableAreasTreeDrawingListener(true));
  tdDisplayControler_->registerTreeDrawing(phylogram_);
  tdDisplayControler_->registerTreeDrawing(cladogram_);

  // TreeDrawing algorithm choice and options:
  widthCtrl_   = new QSpinBox(parent);
  widthCtrl_->setRange(100, 100000);
  connect(widthCtrl_, &QSpinBox::valueChanged, this, &TreeCanvasControlers::treeDrawingUnitChanged);
  heightCtrl_  = new QSpinBox(parent);
  heightCtrl_->setRange(100, 100000);
  connect(heightCtrl_, &QSpinBox::valueChanged, this, &TreeCanvasControlers::treeDrawingUnitChanged);
  drawingCtrl_ = new QComboBox(parent);
  drawingCtrl_->addItems(availableTreeDrawings_);
  connect(drawingCtrl_, &QComboBox::currentIndexChanged, this, &TreeCanvasControlers::treeDrawingChanged);

  orientationCtrl_ = new QGroupBox(parent);
  QRadioButton* leftButton  = new QRadioButton(QString("L"), orientationCtrl_);
  QRadioButton* rightButton = new QRadioButton(QString("R"), orientationCtrl_);
  QRadioButton* upButton    = new QRadioButton(QString("U"), orientationCtrl_);
  QRadioButton* downButton  = new QRadioButton(QString("D"), orientationCtrl_);
  QHBoxLayout* hbox = new QHBoxLayout;
  hbox->addWidget(leftButton);
  hbox->addWidget(rightButton);
  hbox->addWidget(upButton);
  hbox->addWidget(downButton);
  orientationCtrl_->setLayout(hbox);
  orientationLeftRight_ = new QButtonGroup;
  connect(orientationLeftRight_, &QButtonGroup::buttonClicked, this, &TreeCanvasControlers::treeDrawingChanged);
  orientationUpDown_    = new QButtonGroup;
  connect(orientationUpDown_, &QButtonGroup::buttonClicked, this, &TreeCanvasControlers::treeDrawingChanged);
  orientationLeftRight_->addButton(leftButton, 1);
  orientationLeftRight_->addButton(rightButton, 2);
  orientationUpDown_->addButton(upButton, 3);
  orientationUpDown_->addButton(downButton, 4);
  leftButton->setChecked(true);
  upButton->setChecked(true);

  // Display options:
  drawClickableAreas_     = new QCheckBox("Clickable areas", parent);
  drawNodesId_            = new QCheckBox("Nodes id", parent);
  drawLeavesNames_        = new QCheckBox("Leaves names", parent);
  drawBranchLengthValues_ = new QCheckBox("Branch lengths", parent);
  drawBootstrapValues_    = new QCheckBox("Boostrap values", parent);
  connect(drawClickableAreas_, &QCheckBox::stateChanged, this, &TreeCanvasControlers::treeDrawingChanged);
  connect(drawNodesId_, &QCheckBox::stateChanged, this, &TreeCanvasControlers::treeDrawingChanged);
  connect(drawLeavesNames_, &QCheckBox::stateChanged, this, &TreeCanvasControlers::treeDrawingChanged);
  connect(drawBranchLengthValues_, &QCheckBox::stateChanged, this, &TreeCanvasControlers::treeDrawingChanged);
  connect(drawBootstrapValues_, &QCheckBox::stateChanged, this, &TreeCanvasControlers::treeDrawingChanged);
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
}


void TreeCanvasControlers::setTreeCanvas(TreeCanvas* canvas, bool updateOptions)
{
  treeCanvas_ = canvas;
  if (updateOptions)
    actualizeOptions();
  else
    applyOptions(*treeCanvas_);
}


void TreeCanvasControlers::applyOptions(TreeCanvas& canvas)
{
  QString selection = drawingCtrl_->currentText();
  if (QString(canvas.treeDrawing().getName().c_str()) != selection)
  {
    if (selection == QString(cladogram_->getName().c_str()))
    {
      canvas.setTreeDrawing(*cladogram_, false);
    }
    else if (selection == QString(phylogram_->getName().c_str()))
    {
      canvas.setTreeDrawing(*phylogram_, false);
    }
  }
  auto treeDrawing = std::dynamic_pointer_cast<AbstractDendrogramPlot>(canvas.getTreeDrawing());

  treeDrawing->setHorizontalOrientation(orientationLeftRight_->checkedId() == 1 ? AbstractDendrogramPlot::ORIENTATION_LEFT_TO_RIGHT : AbstractDendrogramPlot::ORIENTATION_RIGHT_TO_LEFT);
  treeDrawing->setVerticalOrientation(orientationUpDown_->checkedId() == 3 ? AbstractDendrogramPlot::ORIENTATION_TOP_TO_BOTTOM : AbstractDendrogramPlot::ORIENTATION_BOTTOM_TO_TOP);

  tdDisplayControler_->enableListener(PROPERTY_CLICKABLE_AREA, drawClickableAreas_->isChecked());
  tdDisplayControler_->enableListener(BasicTreeDrawingDisplayControler::PROPERTY_NODE_IDS, drawNodesId_->isChecked());
  tdDisplayControler_->enableListener(BasicTreeDrawingDisplayControler::PROPERTY_LEAF_NAMES, drawLeavesNames_->isChecked());
  tdDisplayControler_->enableListener(BasicTreeDrawingDisplayControler::PROPERTY_BRANCH_LENGTHS, drawBranchLengthValues_->isChecked());
  tdDisplayControler_->enableListener(BasicTreeDrawingDisplayControler::PROPERTY_BOOTSTRAP_VALUES, drawBootstrapValues_->isChecked());

  // Refresh the drawing(s):
  fireActionEvent_();
}


void TreeCanvasControlers::treeDrawingChanged()
{
  if (!treeCanvas_)
    return;
  if (!blockSignal_)
    applyOptions(*treeCanvas_);
}


void TreeCanvasControlers::treeDrawingUnitChanged()
{
  if (!treeCanvas_)
    return;
  if (!blockSignal_)
  {
    treeCanvas_->setDrawingSize(static_cast<unsigned int>(widthCtrl_->value()),
        static_cast<unsigned int>(heightCtrl_->value()));
  }
}

void TreeCanvasControlers::actualizeOptions()
{
  if (!treeCanvas_)
    return;
  auto current = std::dynamic_pointer_cast<AbstractDendrogramPlot>(treeCanvas_->getTreeDrawing());
  blockSignal_ = true; // Dirty trick but no choice!
  widthCtrl_->setValue(static_cast<int>(treeCanvas_->drawingWidth()));
  heightCtrl_->setValue(static_cast<int>(treeCanvas_->drawingHeight()));
  drawingCtrl_->setCurrentIndex(static_cast<int>(availableTreeDrawings_.indexOf(QString(current->getName().c_str()))));
  if (current->getHorizontalOrientation() == AbstractDendrogramPlot::ORIENTATION_LEFT_TO_RIGHT)
    orientationLeftRight_->buttons()[0]->setChecked(true);
  else
    orientationLeftRight_->buttons()[1]->setChecked(true);
  if (current->getVerticalOrientation() == AbstractDendrogramPlot::ORIENTATION_TOP_TO_BOTTOM)
    orientationUpDown_->buttons()[0]->setChecked(true);
  else
    orientationUpDown_->buttons()[1]->setChecked(true);

  // Not needed as all canvasses share the same controler:
  // drawClickableAreas_    ->setChecked(tdDisplayControler_->isListenerEnabled(PROPERTY_CLICKABLE_AREA));
  // drawNodesId_           ->setChecked(tdDisplayControler_->isListenerEnabled(BasicTreeDrawingDisplayControler::PROPERTY_NODE_IDS));
  // drawLeavesNames_       ->setChecked(tdDisplayControler_->isListenerEnabled(BasicTreeDrawingDisplayControler::PROPERTY_LEAF_NAMES));
  // drawBranchLengthValues_->setChecked(tdDisplayControler_->isListenerEnabled(BasicTreeDrawingDisplayControler::PROPERTY_BRANCH_LENGTHS));
  // drawBootstrapValues_   ->setChecked(tdDisplayControler_->isListenerEnabled(BasicTreeDrawingDisplayControler::PROPERTY_BOOTSTRAP_VALUES));
  blockSignal_ = false;
}

QWidget* TreeCanvasControlers::getControlerById(int id)
{
  if (id == ID_WIDTH_CTRL)
    return widthCtrl_;
  if (id == ID_HEIGHT_CTRL)
    return heightCtrl_;
  if (id == ID_DRAWING_CTRL)
    return drawingCtrl_;
  if (id == ID_ORIENTATION_CTRL)
    return orientationCtrl_;
  if (id == ID_DRAW_CLICKABLE_AREAS_CTRL)
    return drawClickableAreas_;
  if (id == ID_DRAW_NODE_IDS_CTRL)
    return drawNodesId_;
  if (id == ID_DRAW_LEAF_NAMES_CTRL)
    return drawLeavesNames_;
  if (id == ID_DRAW_BRANCH_LENGTHS_CTRL)
    return drawBranchLengthValues_;
  if (id == ID_DRAW_BOOTSTRAP_VALUES_CTRL)
    return drawBootstrapValues_;
  return 0;
}

std::shared_ptr<TreeDrawing> TreeCanvasControlers::getTreeDrawing(unsigned int i)
{
  if (i == 0)
    return cladogram_;
  if (i == 1)
    return phylogram_;
  return nullptr;
}

TreeDrawing& TreeCanvasControlers::treeDrawing(unsigned int i)
{
  if (i == 0)
    return *cladogram_;
  if (i == 1)
    return *phylogram_;
  throw Exception("TreeCanvasControlers::treeDrawing(unsigned int i). No TreeDrawing with this index: " + TextTools::toString(i) + ".");
}

const TreeDrawing& TreeCanvasControlers::treeDrawing(unsigned int i) const
{
  if (i == 0)
    return *cladogram_;
  if (i == 1)
    return *phylogram_;
  throw Exception("TreeCanvasControlers::treeDrawing(unsigned int i) const. No TreeDrawing with this index: " + TextTools::toString(i) + ".");
}



