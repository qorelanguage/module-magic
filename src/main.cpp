/* -*- mode: c++; indent-tabs-mode: nil -*- */
/*
  libmagic Qore wrapper

  Qore Programming Language

  Copyright 2012 - 2013 Petr Vanek, Qore Technologies

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
/** @mainpage %Qore Magic Module

\tableofcontents

This is a module for recognizing the type of data contained in a computer
file using so called magic numbers. It is a wrapper around <a href="http://darwinsys.com/file/">\c libmagic C
library</a> (covered by the standard Berkeley Software Distribution copyright).

This module is released under the <a href="http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html">LGPL 2.1</a>
and is tagged as such in the module's header (meaning it can be loaded unconditionally
regardless of how the %Qore library was initialized).

The *Single Unix Specification (SUS)* specifies that a series of tests are
performed on the file specified on the command line:
- if the file cannot be read, its status undetermined, or its type undetermined,
  @ref Magic will indicate that the file was processed and its type was undetermined.
- file must be able to determine the types directory, FIFO, socket, block
  special file, and character special file
- zero-length files are identified as such
- an initial part of file is considered and @ref Magic is to use position-sensitive tests
- the entire file is considered and @ref Magic is to use context-sensitive tests
- the file is identified as a data file

@ref Magic position-sensitive tests are normally implemented by matching various
locations within the file against a textual database of magic numbers.
This differs from other simpler methods such as file extensions and
schemes like MIME.

In most implementations, the file command uses a database to drive
the probing of the lead bytes. That database is implemented in 
file called magic, whose location is usually in /etc/magic
/usr/share/file/magic or a similar location.

To use the module in a %Qore script, use the \c %%requires directive as follows:
    @code %requires magic @endcode

*/