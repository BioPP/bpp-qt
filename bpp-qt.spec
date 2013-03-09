%define _basename bpp-qt
%define _version 2.1.0
%define _release 1
%define _prefix /usr

URL: http://biopp.univ-montp2.fr/

Name: %{_basename}
Version: %{_version}
Release: %{_release}
License: CECILL-2.0
Vendor: The Bio++ Project
Source: http://biopp.univ-montp2.fr/repos/sources/%{_basename}-%{_version}.tar.gz
Summary: Bio++ Qt graphic library
Group: Development/Libraries/C and C++
Requires: bpp-core = 2.0.3
Requires: bpp-phyl = 2.0.3
%if 0%{?fedora} || 0%{?rhel_version} || 0%{?centos_version}
Requires: qt >= 4.6.0
%endif
%if 0%{?suse_version}
Requires: libqt4 >= 4.6.0
%endif
%if 0%{?mdkversion}
%ifarch x86_64
Requires: lib64qtgui4 >= 4.6.0
%else
Requires: libqtgui4 >= 4.6.0
%endif
%endif

BuildRoot: %{_builddir}/%{_basename}-root
BuildRequires: cmake >= 2.6.0
BuildRequires: gcc-c++ >= 4.0.0
BuildRequires: libbpp-core2 = 2.1.0
BuildRequires: libbpp-core-devel = 2.1.0
BuildRequires: libbpp-phyl9 = 2.1.0
BuildRequires: libbpp-phyl-devel = 2.1.0

%if 0%{?fedora} || 0%{?rhel_version} || 0%{?centos_version}
BuildRequires: qt >= 4.6.0
BuildRequires: qt-devel >= 4.6.0
%endif
%if 0%{?suse_version}
BuildRequires: libqt4 >= 4.6.0
BuildRequires: libqt4-devel >= 4.6.0
%endif
%if 0%{?mdkversion}
%ifarch x86_64
BuildRequires: lib64qtgui4 >= 4.6.0
BuildRequires: lib64qt4-devel >= 4.6.0
%else
BuildRequires: libqtgui4 >= 4.6.0
BuildRequires: libqt4-devel >= 4.6.0
%endif
%endif

AutoReq: yes
AutoProv: yes

%description
This library contains graphic classes developed in Qt.
It is part of the Bio++ project.

%package -n libbpp-qt1
Summary: Bio++ Qt graphic library
Group: Development/Libraries/C and C++

%description -n libbpp-qt1
This library contains graphic classes developed in Qt.
It is part of the Bio++ project.

%package -n libbpp-qt-devel
Summary: Libraries, includes to develop applications with %{_basename}.
Group: Development/Libraries/C and C++
Requires: libbpp-qt1 = %{_version}
Requires: libbpp-phyl9 = 2.1.0
Requires: libbpp-phyl-devel = 2.1.0
Requires: libbpp-core2 = 2.1.0
Requires: libbpp-core-devel = 2.1.0
%if 0%{?fedora} || 0%{?rhel_version} || 0%{?centos_version}
Requires: qt >= 4.6.0
Requires: qt-devel >= 4.6.0
%endif
%if 0%{?suse_version}
Requires: libqt4 >= 4.6.0
Requires: libqt4-devel >= 4.6.0
%endif
%if 0%{?mdkversion}
%ifarch x86_64
Requires: lib64qtgui4 >= 4.6.0
Requires: lib64qt4-devel >= 4.6.0
%else
Requires: libqtgui4 >= 4.6.0
Requires: libqt4-devel >= 4.6.0
%endif
%endif

%description -n libbpp-qt-devel
The %libbpp-qt-devel package contains the header files and static libraries for
building applications which use %{_basename}.

%prep
%setup -q

%build
CFLAGS="$RPM_OPT_FLAGS"
CMAKE_FLAGS="-DCMAKE_INSTALL_PREFIX=%{_prefix} -DBUILD_TESTING=OFF"
if [ %{_lib} == 'lib64' ] ; then
  CMAKE_FLAGS="$CMAKE_FLAGS -DLIB_SUFFIX=64"
fi
cmake $CMAKE_FLAGS .
make

%install
make DESTDIR=$RPM_BUILD_ROOT install

%clean
rm -rf $RPM_BUILD_ROOT

%post -n libbpp-qt1 -p /sbin/ldconfig

%post -n libbpp-qt-devel
createGeneric() {
  echo "-- Creating generic include file: $1.all"
  #Make sure we run into subdirectories first:
  dirs=()
  for file in "$1"/*
  do
    if [ -d "$file" ]
    then
      # Recursion:
      dirs+=( "$file" )
    fi
  done
  for dir in ${dirs[@]}
  do
    createGeneric $dir
  done
  #Now list all files, including newly created .all files:
  if [ -f $1.all ]
  then
    rm $1.all
  fi
  dir=`basename $1`
  for file in "$1"/*
  do
    if [ -f "$file" ] && ( [ "${file##*.}" == "h" ] || [ "${file##*.}" == "all" ] )
    then
      file=`basename $file`
      echo "#include \"$dir/$file\"" >> $1.all
    fi
  done;
}
# Actualize .all files
createGeneric %{_prefix}/include/Bpp
exit 0

%preun -n libbpp-qt-devel
removeGeneric() {
  if [ -f $1.all ]
  then
    echo "-- Remove generic include file: $1.all"
    rm $1.all
  fi
  for file in "$1"/*
  do
    if [ -d "$file" ]
    then
      # Recursion:
      removeGeneric $file
    fi
  done
}
# Actualize .all files
removeGeneric %{_prefix}/include/Bpp
exit 0

%postun -n libbpp-qt1 -p /sbin/ldconfig

%postun -n libbpp-qt-devel
createGeneric() {
  echo "-- Creating generic include file: $1.all"
  #Make sure we run into subdirectories first:
  dirs=()
  for file in "$1"/*
  do
    if [ -d "$file" ]
    then
      # Recursion:
      dirs+=( "$file" )
    fi
  done
  for dir in ${dirs[@]}
  do
    createGeneric $dir
  done
  #Now list all files, including newly created .all files:
  if [ -f $1.all ]
  then
    rm $1.all
  fi
  dir=`basename $1`
  for file in "$1"/*
  do
    if [ -f "$file" ] && ( [ "${file##*.}" == "h" ] || [ "${file##*.}" == "all" ] )
    then
      file=`basename $file`
      echo "#include \"$dir/$file\"" >> $1.all
    fi
  done;
}
# Actualize .all files
createGeneric %{_prefix}/include/Bpp
exit 0

%files -n libbpp-qt1
%defattr(-,root,root)
%doc AUTHORS.txt COPYING.txt INSTALL.txt ChangeLog
%{_prefix}/%{_lib}/lib*.so.*

%files -n libbpp-qt-devel
%defattr(-,root,root)
%doc AUTHORS.txt COPYING.txt INSTALL.txt ChangeLog
%{_prefix}/%{_lib}/lib*.so
%{_prefix}/%{_lib}/lib*.a
%{_prefix}/include/*

%changelog
* Fri Mar 08 2013 Julien Dutheil <julien.dutheil@univ-montp2.fr> 2.1.0-1
- Compatibility update with other libraries.
* Thu Feb 09 2012 Julien Dutheil <julien.dutheil@univ-montp2.fr> 2.0.2-1
* Thu Jun 09 2011 Julien Dutheil <julien.dutheil@univ-montp2.fr> 2.0.1-1
* Mon Feb 28 2011 Julien Dutheil <julien.dutheil@univ-montp2.fr> 2.0.0-1
- First draft of the spec file

