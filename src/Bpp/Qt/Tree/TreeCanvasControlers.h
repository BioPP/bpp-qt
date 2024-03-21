// Copyright or (c) or Copr. Bio++ Development Team, (November 16, 2004)
// SPDX-FileCopyrightText: The Bio++ Development Group
//
// SPDX-License-Identifier: CECILL-2.1

#ifndef _TREECANVASCONTROLERS_H_
#define _TREECANVASCONTROLERS_H_


#include "TreeCanvas.h"

//From Phylib:
#include <Bpp/Phyl/Graphics/CladogramPlot.h>
#include <Bpp/Phyl/Graphics/PhylogramPlot.h>
#include <Bpp/Phyl/Graphics/TreeDrawingDisplayControler.h>

//From Qt:
#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QSpinBox>
#include <QGroupBox>

namespace bpp
{

/**
 * @brief A TreeDrawingListener implementation that draw the clickable areas around nodes.
 *
 * This listener works with TreeDrawing classes, but is more efficient when used with a class that fires DrawINodeEvent events.
 */
class NodeClickableAreasTreeDrawingListener :
  public TreeDrawingListenerAdapter
{
public:
  NodeClickableAreasTreeDrawingListener(bool autonomous = false) :
    TreeDrawingListenerAdapter(autonomous) {}

  NodeClickableAreasTreeDrawingListener* clone() const { return new NodeClickableAreasTreeDrawingListener(*this); }

public :    
  void afterDrawNode(const DrawNodeEvent& event);

};



/**
 * @brief Listener interface for TreeCanvasControlers.
 */
class TreeCanvasControlersListener
{
  public:
    virtual ~TreeCanvasControlersListener() {}

  public:
    virtual void controlerTakesAction() = 0;
};

/**
 * @brief Manage controlers widgets to interact with a tree canvas.
 */
class TreeCanvasControlers:
  public QObject
{
  Q_OBJECT

  private:
    TreeCanvas* treeCanvas_;
    QSpinBox* widthCtrl_;
    QSpinBox* heightCtrl_;
    QComboBox* drawingCtrl_;
    QGroupBox* orientationCtrl_;

    QButtonGroup* orientationLeftRight_;
    QButtonGroup* orientationUpDown_;


    QCheckBox* drawClickableAreas_;
    QCheckBox* drawNodesId_;
    QCheckBox* drawLeavesNames_;
    QCheckBox* drawBranchLengthValues_;
    QCheckBox* drawBootstrapValues_;

    CladogramPlot* cladogram_;
    PhylogramPlot* phylogram_;
    QStringList availableTreeDrawings_;
    TreeDrawingSettings* tdSettings_;
    TreeDrawingDisplayControler* tdDisplayControler_;
    
    // Other controls may be added later.

    std::vector<TreeCanvasControlersListener*> listeners_;
    
    bool blockSignal_;
    
  public:
    /**
     * @param parent The parent widget to pass to all controlers.
     * This should be set to null if you do not intend to use all the controlers,
     * or intend to use them witht different parent windows.
     */
    TreeCanvasControlers(QWidget* parent = 0);
    virtual ~TreeCanvasControlers();

  public:

    /**
     * @brief Actualize the controls according to the current tree canvas.
     */
    void actualizeOptions();

    /**
     * @brief Get a specific control according to its id.
     *
     * @param id The id of the control.
     * @return The specified control, or NULL if no control corresponds to the specified id.
     */
    QWidget* getControlerById(int id);

    void setTreeCanvas(TreeCanvas* canvas, bool updateOptions = true);
    TreeCanvas* getTreeCanvas() { return treeCanvas_; }
    const TreeCanvas* getTreeCanvas() const { return treeCanvas_; }

    TreeDrawing* getTreeDrawing(unsigned int i);
    
    TreeDrawing* getSelectedTreeDrawing() { return getTreeDrawing(static_cast<unsigned int>(drawingCtrl_->currentIndex())); }

    unsigned int getNumberOfTreeDrawings() const { return 2; }

    void applyOptions(TreeCanvas* canvas);

    void addActionListener(TreeCanvasControlersListener* listener)
    {
      listeners_.push_back(listener);
    }

  protected:
    void fireActionEvent_()
    {
      for (unsigned int i = 0; i < listeners_.size(); ++i)
        listeners_[i]->controlerTakesAction();
    }

  private slots:
    void treeDrawingChanged();
    void treeDrawingUnitChanged();

  public:
    static const int ID_WIDTH_CTRL;
    static const int ID_HEIGHT_CTRL;
    static const int ID_DRAWING_CTRL;
    static const int ID_ORIENTATION_CTRL;
    static const int ID_DRAW_CLICKABLE_AREAS_CTRL;
    static const int ID_DRAW_NODE_IDS_CTRL;
    static const int ID_DRAW_LEAF_NAMES_CTRL;
    static const int ID_DRAW_BRANCH_LENGTHS_CTRL;
    static const int ID_DRAW_BOOTSTRAP_VALUES_CTRL;
    static const std::string PROPERTY_CLICKABLE_AREA;

};

} //end of namespace bpp.

#endif // _TREECANVASCONTROLERS_H_

