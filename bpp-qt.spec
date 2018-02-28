%define _prefix /usr

URL: https://github.com/BioPP/bpp-qt

Name: bpp-qt
Version: 2.4.0
Release: 1
License: CECILL-2.0
Vendor: The Bio++ Project
Source: %{name}-%{version}.tar.gz
Summary: Bio++ Qt graphic library
Group: Development/Libraries/C and C++
Requires: bpp-core = %{version}
Requires: bpp-phyl = %{version}
%if 0%{?fedora} || 0%{?rhel_version} || 0%{?centos_version} || 0%{?scientificlinux_version}
Requires: libqt5core5 >= 5.0.0
Requires: libqt5gui5 >= 5.0.0
Requires: libqt5widgets5 >= 5.0.0
%endif
%if 0%{?suse_version}
Requires: libQt5Core5 >= 5.0.0
Requires: libQt5Gui5 >= 5.0.0
Requires: libQt5Widgets5 >= 5.0.0
%endif
%if 0%{?mageia} || 0%{?mdkversion}
%ifarch x86_64
Requires: lib64proxy-webkit >= 0.4.14
Requires: lib64qt5core5 >= 5.0.0
Requires: lib64qt5gui5 >= 5.0.0
Requires: lib64qt5widgets5 >= 5.0.0
Requires: qt5-qtdeclarative >= 5.0.0
Requires: qt5-qtbase >= 5.0.0
%else
Requires: libproxy-webkit >= 0.4.14
Requires: libqt5core5 >= 5.0.0
Requires: libqt5gui5 >= 5.0.0
Requires: libqt5widgets5 >= 5.0.0
Requires: qt5-qtdeclarative >= 5.0.0
Requires: qt5-qtbase >= 5.0.0
%endif
%endif



BuildRoot: %{_builddir}/%{name}-root

BuildRequires: cmake >= 2.8.11
BuildRequires: gcc-c++ >= 4.7.0
BuildRequires: libbpp-core4 = %{version}
BuildRequires: libbpp-core-devel = %{version}
BuildRequires: libbpp-phyl12 = %{version}
BuildRequires: libbpp-phyl-devel = %{version}

%if 0%{?fedora} || 0%{?rhel_version} || 0%{?centos_version} || 0%{?scientificlinux_version}
BuildRequires: qt5-qtdeclarative >= 5.0.0
BuildRequires: qt5-qtbase >= 5.0.0
BuildRequires: qt5-qtdeclarative-devel >= 5.0.0
BuildRequires: qt5-qtbase-devel >= 5.0.0
%endif
%if 0%{?suse_version}
BuildRequires: libQt5Core5 >= 5.0.0
BuildRequires: libQt5Gui5 >= 5.0.0
BuildRequires: libQt5Widgets5 >= 5.0.0
BuildRequires: libqt5-qtdeclarative-devel >= 5.0.0
BuildRequires: libqt5-qtbase-devel >= 5.0.0
%endif
%if 0%{?mageia} || 0%{?mdkversion}
%ifarch x86_64
BuildRequires: lib64proxy-webkit >= 0.4.14
BuildRequires: lib64qt5core5 >= 5.0.0
BuildRequires: lib64qt5gui5 >= 5.0.0
BuildRequires: lib64qt5widgets5 >= 5.0.0
BuildRequires: lib64qt5base5-devel >= 5.0.0
%else
BuildRequires: libproxy-webkit >= 0.4.14
BuildRequires: libqt5core5 >= 5.0.0
BuildRequires: libqt5gui5 >= 5.0.0
BuildRequires: libqt5widgets5 >= 5.0.0
BuildRequires: libqt5base5-devel >= 5.0.0
%endif
%endif

AutoReq: yes
AutoProv: yes

%description
This library contains graphic classes developed in Qt.
It is part of the Bio++ project.

%package -n libbpp-qt2
Summary: Bio++ Qt graphic library
Group: Development/Libraries/C and C++

%description -n libbpp-qt2
This library contains graphic classes developed in Qt.
It is part of the Bio++ project.

%package -n libbpp-qt-devel
Summary: Libraries, includes to develop applications with %{_basename}
Group: Development/Libraries/C and C++
Requires: libbpp-qt2 = %{version}
Requires: libbpp-phyl12 = %{version}
Requires: libbpp-phyl-devel = %{version}
Requires: libbpp-core4 = %{version}
Requires: libbpp-core-devel = %{version}
%if 0%{?fedora} || 0%{?rhel_version} || 0%{?centos_version} || 0%{?scientificlinux_version}

Requires: qt5-qtdeclarative >= 5.0.0
Requires: qt5-qtbase >= 5.0.0
Requires: qt5-qtdeclarative-devel >= 5.0.0
Requires: qt5-qtbase-devel >= 5.0.0
%endif
%if 0%{?suse_version}
Requires: libQt5Core5 >= 5.0.0
Requires: libQt5Gui5 >= 5.0.0
Requires: libQt5Widgets5 >= 5.0.0
Requires: libqt5-qtdeclarative-devel >= 5.0.0
Requires: libqt5-qtbase-devel >= 5.0.0
%endif
%if 0%{?mageia} || 0%{?mdkversion}
%ifarch x86_64
Requires: lib64proxy-webkit >= 0.4.14
Requires: lib64qt5core5 >= 5.0.0
Requires: lib64qt5gui5 >= 5.0.0
Requires: lib64qt5widgets5 >= 5.0.0
Requires: lib64qt5base5-devel >= 5.0.0
%else
Requires: libproxy-webkit >= 0.4.14
Requires: libqt5core5 >= 5.0.0
Requires: libqt5gui5 >= 5.0.0
Requires: libqt5widgets5 >= 5.0.0
Requires: libqt5base5-devel >= 5.0.0
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
cmake $CMAKE_FLAGS .
make

%install
make DESTDIR=$RPM_BUILD_ROOT install

%clean
rm -rf $RPM_BUILD_ROOT

%post -n libbpp-qt2 -p /sbin/ldconfig

%postun -n libbpp-qt2 -p /sbin/ldconfig

%files -n libbpp-qt2
%defattr(-,root,root)
%doc AUTHORS.txt COPYING.txt INSTALL.txt ChangeLog
%{_prefix}/%{_lib}/lib*.so.*

%files -n libbpp-qt-devel
%defattr(-,root,root)
%doc AUTHORS.txt COPYING.txt INSTALL.txt ChangeLog
%dir %{_prefix}/%{_lib}/cmake/
%dir %{_prefix}/%{_lib}/cmake/bpp-qt
%{_prefix}/%{_lib}/lib*.so
%{_prefix}/%{_lib}/lib*.a
%{_prefix}/%{_lib}/cmake/bpp-qt/bpp-qt*.cmake
%{_prefix}/include/*

%changelog
* Mon Feb 26 2018 Julien Dutheil <julien.dutheil@univ-montp2.fr> 2.4.0-1
- Removed dynamic exception specifications
- Port to Qt5
- Increased interface number
* Tue Jun 06 2017 Julien Dutheil <julien.dutheil@univ-montp2.fr> 2.3.1-1
- Increased interface number
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

