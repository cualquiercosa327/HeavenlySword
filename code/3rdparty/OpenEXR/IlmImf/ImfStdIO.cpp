///////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004, Industrial Light & Magic, a division of Lucas
// Digital Ltd. LLC
// 
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
// *       Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
// *       Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
// *       Neither the name of Industrial Light & Magic nor the names of
// its contributors may be used to endorse or promote products derived
// from this software without specific prior written permission. 
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
///////////////////////////////////////////////////////////////////////////


//-----------------------------------------------------------------------------
//
//	Low-level file input and output for OpenEXR
//	based on C++ standard iostreams.
//
//-----------------------------------------------------------------------------

#include <ImfStdIO.h>
#include <Iex.h>
#include <errno.h>

using namespace std;

namespace Imf {
namespace {

void
clearError ()
{
    errno = 0;
}


bool
checkError (istream &is)
{
    if (!is)
    {
	if (errno)
	    Iex::throwErrnoExc();

#ifdef BROKEN_ISTREAM_HACK
	// HACK - this is a workaround for a bug in Apple's
	// implementation of istream::read.  It's present as of
	// OS X 10.2.3 and the December 2002 developer's tools.
	//
	// When OpenEXR reaches the end of the file, Apple's
	// istream implementation mistakenly sets the stream's
	// failbit.  This hack clears the bits, but note that it
	// may cause problems if there is a legitimate error
	// condition.
	
	is.clear (std::ios_base::goodbit);
#endif	
	return false;
    }

    return true;
}


void
checkError (ostream &os)
{
    if (!os)
    {
	if (errno)
	    Iex::throwErrnoExc();

	throw Iex::ErrnoExc ("File output failed.");
    }
}

} // namespace


StdIFStream::StdIFStream (const char fileName[]):
    IStream (fileName),
#ifndef HAVE_IOS_BASE
    _is (new ifstream (fileName, ios::binary|ios::in)),
#else
    _is (new ifstream (fileName, ios_base::binary)),
#endif
    _deleteStream (true)
{
    if (!*_is)
    {
	delete _is;
	Iex::throwErrnoExc();
    }
}

    
StdIFStream::StdIFStream (ifstream &is, const char fileName[]):
    IStream (fileName),
    _is (&is),
    _deleteStream (false)
{
    // empty
}


StdIFStream::~StdIFStream ()
{
    if (_deleteStream)
	delete _is;
}


bool
StdIFStream::read (char c[/*n*/], int n)
{
    if (!*_is)
	throw Iex::InputExc ("Unexpected end of file.");

    clearError();
    _is->read (c, n);
    return checkError (*_is);
}


Int64
StdIFStream::tellg ()
{
    return std::streamoff (_is->tellg());
}


void
StdIFStream::seekg (Int64 pos)
{
	_is->seekg ((std::streamoff)pos);
    checkError (*_is);
}


void
StdIFStream::clear ()
{
    _is->clear();
}


StdOFStream::StdOFStream (const char fileName[]):
    OStream (fileName),
#ifndef HAVE_IOS_BASE
    _os (new ofstream (fileName, ios::binary)),
#else
    _os (new ofstream (fileName, ios_base::binary)),
#endif
    _deleteStream (true)
{
    if (!*_os)
    {
	delete _os;
	Iex::throwErrnoExc();
    }
}


StdOFStream::StdOFStream (ofstream &os, const char fileName[]):
    OStream (fileName),
    _os (&os),
    _deleteStream (false)
{
    // empty
}


StdOFStream::~StdOFStream ()
{
    if (_deleteStream)
	delete _os;
}


void
StdOFStream::write (const char c[/*n*/], int n)
{
    clearError();
    _os->write (c, n);
    checkError (*_os);
}


Int64
StdOFStream::tellp ()
{
    return std::streamoff (_os->tellp());
}


void
StdOFStream::seekp (Int64 pos)
{
    _os->seekp ((std::streamoff)pos);
    checkError (*_os);
}


StdOSStream::StdOSStream (): OStream ("(string)")
{
    // empty
}


void
StdOSStream::write (const char c[/*n*/], int n)
{
    clearError();
    _os.write (c, n);
    checkError (_os);
}


Int64
StdOSStream::tellp ()
{
    return std::streamoff (_os.tellp());
}


void
StdOSStream::seekp (Int64 pos)
{
    _os.seekp ((std::streamoff)pos);
    checkError (_os);
}


} // namespace Imf
