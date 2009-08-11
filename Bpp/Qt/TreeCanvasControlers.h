//
// File: TreeCanvasControls.h
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

#ifndef _TREECANVASCONTROLERS_H_
#define _TREECANVASCONTROLERS_H_


#include "TreeCanvas.h"

//From Phylib:
#include <Phyl/CladogramPlot.h>
#include <Phyl/PhylogramPlot.h>

//From Qt:
#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QSpinBox>
#include <QGroupBox>

namespace bpp
{

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
    
    // Other controls may be added later.
    
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

    void applyOptions(TreeCanvas* canvas) const;

  private slots:
    void treeDrawingChanged();
    void treeDrawingUnitChanged();

  public:
    static const int ID_WIDTH_CTRL;
    static const int ID_HEIGHT_CTRL;
    static const int ID_DRAWING_CTRL;
    static const int ID_ORIENTATION_CTRL;
    static const int ID_DRAW_CLICKABLE_AREAS_CTRL;
    static const int ID_DRAW_NODES_ID_CTRL;
    static const int ID_DRAW_LEAVES_NAMES_CTRL;
    static const int ID_DRAW_BRLEN_VALUES_CTRL;
    static const int ID_DRAW_BOOTSTRAP_VALUES_CTRL;

};

} //end of namespace bpp.

#endif // _TREECANVASCONTROLERS_H_

