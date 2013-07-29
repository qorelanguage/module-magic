%define module_api %(qore --latest-module-api 2>/dev/null)
%define module_dir %{_libdir}/qore-modules

%if 0%{?sles_version}

%define dist .sles%{?sles_version}

%else
%if 0%{?suse_version}

# get *suse release major version
%define os_maj %(echo %suse_version|rev|cut -b3-|rev)
# get *suse release minor version without trailing zeros
%define os_min %(echo %suse_version|rev|cut -b-2|rev|sed s/0*$//)

%if %suse_version > 1010
%define dist .opensuse%{os_maj}_%{os_min}
%else
%define dist .suse%{os_maj}_%{os_min}
%endif

%endif
%endif

# see if we can determine the distribution type
%if 0%{!?dist:1}
%define rh_dist %(if [ -f /etc/redhat-release ];then cat /etc/redhat-release|sed "s/[^0-9.]*//"|cut -f1 -d.;fi)
%if 0%{?rh_dist}
%define dist .rhel%{rh_dist}
%else
%define dist .unknown
%endif
%endif

Summary: Libmagic module for Qore
Name: qore-magic-module
Version: 0.0.1
Release: 1%{dist}
License: LGPL-2.0+
Group: Development/Languages/Other
URL: http://qore.org
Source: %{name}-%{version}.tar.bz2
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root
BuildRequires: gcc-c++
BuildRequires: qore-devel
BuildRequires: qore
BuildRequires: cmake
BuildRequires: file-devel
BuildRequires: doxygen


%description
libmagic (file) wrapper for Qore programming language

%prep
%setup -q
cmake -DCMAKE_INSTALL_PREFIX=/usr .

%build
find test -name *.q|xargs chmod 644
%{__make}

%install
make install VERBOSE=1 DESTDIR=$RPM_BUILD_ROOT

%post
ldconfig %{_libdir}

%postun
ldconfig %{_libdir}

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root,-)
%{module_dir}
%doc COPYING README test/* doc/html


%changelog
* Mon Jul 29 2013 Petr Vanek <petr.vanek@qoretechnologies.com> 0.0.1
- initial package for Version 0.0.1

