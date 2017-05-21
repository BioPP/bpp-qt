%define _basename bpp-qt
%define _version 2.3.0
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
Requires: bpp-core = %{_version}
Requires: bpp-phyl = %{_version}
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
BuildRequires: cmake >= 2.8.11
BuildRequires: gcc-c++ >= 4.7.0
BuildRequires: libbpp-core2 = %{_version}
BuildRequires: libbpp-core-devel = %{_version}
BuildRequires: libbpp-phyl9 = %{_version}
BuildRequires: libbpp-phyl-devel = %{_version}

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
Summary: Libraries, includes to develop applications with %{_basename}
Group: Development/Libraries/C and C++
Requires: libbpp-qt1 = %{_version}
Requires: libbpp-phyl9 = %{_version}
Requires: libbpp-phyl-devel = %{_version}
Requires: libbpp-core2 = %{_version}
Requires: libbpp-core-devel = %{_version}
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
The libbpp-qt-devel package contains the header files and static libraries for
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

%postun -n libbpp-qt1 -p /sbin/ldconfig

%files -n libbpp-qt1
%defattr(-,root,root)
%doc AUTHORS.txt COPYING.txt INSTALL.txt ChangeLog
%{_prefix}/%{_lib}/lib*.so.*

%files -n libbpp-qt-devel
%defattr(-,root,root)
%doc AUTHORS.txt COPYING.txt INSTALL.txt ChangeLog
%dir %{_prefix}/lib/cmake/
%dir %{_prefix}/lib/cmake/bpp-qt
%{_prefix}/%{_lib}/lib*.so
%{_prefix}/%{_lib}/lib*.a
%{_prefix}/lib/cmake/bpp-qt/bpp-qt*.cmake
%{_prefix}/include/*

%changelog
* Wed May 10 2017 Julien Dutheil <julien.dutheil@univ-montp2.fr> 2.3.0-1
- Upgrade to C++11
* Fri Sep 26 2014 Julien Dutheil <julien.dutheil@univ-montp2.fr> 2.2.0-1
- Removed CLang warnings.
* Fri Mar 08 2013 Julien Dutheil <julien.dutheil@univ-montp2.fr> 2.1.0-1
- Compatibility update with other libraries.
* Thu Feb 09 2012 Julien Dutheil <julien.dutheil@univ-montp2.fr> 2.0.2-1
* Thu Jun 09 2011 Julien Dutheil <julien.dutheil@univ-montp2.fr> 2.0.1-1
* Mon Feb 28 2011 Julien Dutheil <julien.dutheil@univ-montp2.fr> 2.0.0-1
- First draft of the spec file

