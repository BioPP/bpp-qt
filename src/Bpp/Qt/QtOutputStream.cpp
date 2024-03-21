// Copyright or © or Copr. CNRS, (November 16, 2006)
// SPDX-FileCopyrightText: The Bio++ Development Group
//
// SPDX-License-Identifier: CECILL-2.1

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

