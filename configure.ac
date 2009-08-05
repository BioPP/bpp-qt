#Copyright or © or Copr. CNRS, (November 16, 2004-2008)
#
#This software is a computer program whose purpose is to provide classes
#for phylogenetic data analysis.
#
#This software is governed by the CeCILL  license under French law and
#abiding by the rules of distribution of free software.  You can  use, 
#modify and/ or redistribute the software under the terms of the CeCILL
#license as circulated by CEA, CNRS and INRIA at the following URL
#"http://www.cecill.info". 
#
#As a counterpart to the access to the source code and  rights to copy,
#modify and redistribute granted by the license, users are provided only
#with a limited warranty  and the software's author,  the holder of the
#economic rights,  and the successive licensors  have only  limited
#liability. 
#
#In this respect, the user's attention is drawn to the risks associated
#with loading,  using,  modifying and/or developing or reproducing the
#software by the user in light of its specific status of free software,
#that may mean  that it is complicated to manipulate,  and  that  also
#therefore means  that it is reserved for developers  and  experienced
#professionals having in-depth computer knowledge. Users are therefore
#encouraged to load and test the software's suitability as regards their
#requirements in conditions enabling the security of their systems and/or 
#data to be ensured and,  more generally, to use and operate it in the 
#same conditions as regards security. 
#
#The fact that you are presently reading this means that you have had
#knowledge of the CeCILL license and that you accept its terms.

AC_INIT(Bio++ Qt library, 0.1.0, Julien.Dutheil@univ-montp2.fr, bpp-qt)
AC_CONFIG_SRCDIR(Bpp/Qt/QtGraphicDevice.h)
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE()
AC_PROG_CC
AC_PROG_CXX
AC_LANG_CPLUSPLUS
AC_CHECK_LIB(bpp-utils,   main, , [AC_MSG_ERROR([Library bpp-utils not found.])])
AC_CHECK_LIB(bpp-numcalc, main, , [AC_MSG_ERROR([Library bpp-numcalc not found.])])
AC_CHECK_LIB(bpp-seq,     main, , [AC_MSG_ERROR([Library bpp-seq not found.])])
AC_CHECK_LIB(bpp-phyl,    main, , [AC_MSG_ERROR([Library bpp-phyl not found.])])




AC_MSG_CHECKING(QT4 directory)
QTDIR=xxx
AC_ARG_WITH([qt-dir],
             AC_HELP_STRING([--with-qt-dir=/path/to/Qt-4.4.0],
                            [to specify the path to the Qt-4.4.0 directory.]),
             [QTPATHS="$withval"],
             [QTPATHS="/usr/"])

for x in $QTPATHS; do
    if test -d $x ; then
       QTDIR="$x"
    fi
done
if test $QTDIR = xxx ; then
   AC_MSG_ERROR(Could not locate QT 4.4)
fi
AC_MSG_RESULT($QTDIR)
host=`uname -a` # AC_CANONICAL_HOST is broken at the time of this writing.
case $host in
  MINGW32*)
    AC_MSG_NOTICE(MinGW detected.)
    QTLIBS="-L$QTDIR/lib -lopengl32 -lglu32 -lgdi32 -luser32 -lmingw32 -lqtmain -lQtOpenGL4 -lQtGui4 -lQtCore4 -mthreads -Wl,-enable-stdcall-fixup -Wl,-enable-auto-import -Wl,-enable-runtime-pseudo-reloc -Wl,-s -Wl,-s -Wl,-subsystem,windows"
    QTINC="-I$QTDIR/include -I$QTDIR/include/QtCore -I$QTDIR/include/QtGui -I$QTDIR/include/QtOpenGL -DUNICODE -DQT_LARGEFILE_SUPPORT -DQT_DLL -DQT_NO_DEBUG -DQT_OPENGL_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_THREAD_SUPPORT -DQT_NEEDS_QMAIN -frtti -fexceptions"
    QTBIN="$QTDIR/bin"
    ;;
  *)
    AC_MSG_NOTICE(I'm assuming this in Linux)
    AC_PATH_XTRA
    QTLIBS="-Wl,-rpath,$QTDIR/lib -L$QTDIR/lib -lQtGui -lQtOpenGL -lQtCore $X_LIBS -lX11 -lXext -lXmu -lXt -lXi $X_EXTRA_LIBS -lGLU -lGL -lpthread"
    QTINC="-I$QTDIR/include/qt4 -I$QTDIR/include/qt4/QtGui -I$QTDIR/include/qt4/QtCore -I$QTDIR/include/qt4/QtOpenGL $X_CFLAGS -DQT_OPENGL_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED"
    QTBIN="$QTDIR/bin"
    ;;
esac

LIBS="$LIBS $QTLIBS"
INCLUDES="$INCLUDES $QTINC"
PATH="$PATH:$QTBIN"
CXXFLAGS="$CXXFLAGS $QTINC"

# Now we check whether we can actually build a Qt app.
cat > myqt.h << EOF
#include <QObject>
class Test : public QObject
{
Q_OBJECT
public:
  Test() {}
  ~Test() {}
public slots:
  void receive() {}
signals:
  void send();
};
EOF

cat > myqt.cpp << EOF
#include "myqt.h"
#include <QApplication>
int main( int argc, char **argv )
{
  QApplication app( argc, argv );
  Test t;
  QObject::connect( &t, SIGNAL(send()), &t, SLOT(receive()) );
}
EOF

AC_MSG_CHECKING(does moc work?)
bnv_try_1="moc myqt.h -o moc_myqt.cpp"
AC_TRY_EVAL(bnv_try_1)
if test x"$ac_status" != x0; then
   AC_MSG_ERROR(moc doesn't work)
fi
AC_MSG_RESULT(yes)
AC_MSG_CHECKING(can I compile moc_myqt.cpp?)
bnv_try_2="$CXX -c $CXXFLAGS -o moc_myqt.o moc_myqt.cpp"
AC_TRY_EVAL(bnv_try_2)
if test x"$ac_status" != x0; then
   AC_MSG_ERROR(couldn't compile moc_myqt.cpp)
fi
AC_MSG_RESULT(yes)
AC_MSG_CHECKING(can I compile myqt.cpp?)
bnv_try_3="$CXX $QTINC -c $CXXFLAGS -o myqt.o myqt.cpp"
AC_TRY_EVAL(bnv_try_3)
if test x"$ac_status" != x0; then
   AC_MSG_ERROR(couldn't compile myqt.cpp)
fi
AC_MSG_RESULT(yes)
AC_MSG_CHECKING(can I link against QT?)
nv_try_4="$CXX $LIBS -o myqt myqt.o moc_myqt.o"
AC_TRY_EVAL(bnv_try_4)
if test x"$ac_status" != x0; then
   AC_MSG_ERROR(couldn't link)
fi
AC_MSG_RESULT(yes)

AC_MSG_CHECKING(for mkoctfile)
AC_TRY_EVAL(mkoctfile)
if test x"$ac_status" != x0; then
   AC_MSG_ERROR(mkoctfile is not in the path)
fi
AC_MSG_RESULT(yes)
rm -f moc_myqt.cpp myqt.h myqt.cpp myqt.o myqt moc_myqt.o

AC_PROG_INSTALL
AC_PROG_LIBTOOL
AC_MSG_CHECKING([Covariant return with virtual inheritance])
AC_ARG_WITH(
	[virtual-cov],
	[  --with-virtual-cov      Enable covariant return type with
	                  virtual inheritance (GCC >= 3.4)],
  ,
  with_virtual_cov="yes"
)
AC_MSG_RESULT($with_virtual_cov);
if test "$with_virtual_cov" == "no"
then
	AC_MSG_WARN([
+--------------------------------------------------------+
|Covariant return type with virtual inheritance disabled.|
+--------------------------------------------------------+
]);
	AC_DEFINE(NO_VIRTUAL_COV, yes)
fi
AC_OUTPUT(Makefile Bpp/Qt/Makefile)
