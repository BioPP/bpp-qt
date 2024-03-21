<!--
SPDX-FileCopyrightText: The Bio++ Development Group

SPDX-License-Identifier: CECILL-2.1
-->

# bpp-qt
Bio++ Qt Graphic Library

To install:
```bash
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=$HOME/.local ..
```

If Qt5 is installed in a non-standard place (for instance using homebrew on MacOS):
```bash
cmake -DCMAKE_INSTALL_PREFIX=$HOME/.local -DQt5_DIR=/usr/local/opt/qt5/lib/cmake/Qt5 ..
```

Then
```bash
make install
```

(Assuming all dependencies have previously been installed.)
