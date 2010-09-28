// File: QtOutputStream.h
// Created by: Julien Dutheil
// Created on: Mon Jan 25 2010
//

/*
Copyright or © or Copr. CNRS, (November 16, 2006)

This software is a computer program whose purpose is to provide 
graphical components using the Qt library.
This file belongs to the Bio++ Project.

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

#include "QtOutputStream.h"

using namespace bpp;

void QtOutputStream::checkNumberOfLines()
{
  QString text = toPlainText();
  unsigned int nbLines = static_cast<unsigned int>(text.count('\n'));
  if (nbLines > maxNbLines_)
  {
    unsigned int rm = nbLines - maxNbLines_;
    for (unsigned int i = 0; i < rm; i++)
    {
      text.remove(0, text.indexOf('\n') + 1);
    }
    setPlainText(text);
  }
}

