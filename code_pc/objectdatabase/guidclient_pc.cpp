#include <cstdio>
#include <time.h>
#include <windows.h>
#include <winsock.h>

#include "objectdatabase/guidclient.h"

#pragma comment(lib, "Rpcrt4")

class GuidClientImpl
{
public:
	typedef ntstd::Map< ntstd::String, ntstd::String > GuidToName;
	typedef ntstd::Map< ntstd::String, ntstd::String > NameToGuid;

	NameToGuid m_NameToGuid;
	GuidToName m_GuidToName;

};

/**************************************************************************************************
*
*	FUNCTION		GuidClient ctor
*
**************************************************************************************************/
GuidClient::GuidClient() :
	m_impl( *(NT_NEW GuidClientImpl) )
{
	m_impl.m_NameToGuid[ "NULL" ] = "00000000-0000-0000-0000-000000000000";
	m_impl.m_NameToGuid[ "00000000-0000-0000-0000-000000000000" ] = "00000000-0000-0000-0000-000000000000";
	m_impl.m_GuidToName[ "00000000-0000-0000-0000-000000000000" ] = "NULL";

}


/**************************************************************************************************
*
*	FUNCTION		GuidClient dtor
*
**************************************************************************************************/
GuidClient::~GuidClient()
{
	NT_DELETE( &m_impl );
}


/**************************************************************************************************
*
*	FUNCTION		GuidClient::Lookup
*
*	DESCRIPTION		Look up the guid, return String in pcResultBuf.
*
*	INPUTS			uiHash - the hash to resolve
*					pcResultBuf - buffer to receive returned String
*					iResultBufSize - size of pcResultBuf
*
*	RESULT			Returns success.
*					Note that there is no way to distinguish between
*					network errors and hash-not-found.
*
**************************************************************************************************/
bool GuidClient::Lookup( const char* name , char* pcResultBuf, int iResultBufSize )
{
	GuidClientImpl::NameToGuid::const_iterator nmIt = m_impl.m_NameToGuid.find( name );
	if( nmIt == m_impl.m_NameToGuid.end() )
	{
		return false;
	}
	if( iResultBufSize < (int) nmIt->second.size() )
	{
		return false;
	}
	// return the String guid
	strncpy( pcResultBuf, nmIt->second.c_str(), iResultBufSize );
	return true;
}

/**************************************************************************************************
*
*	FUNCTION		GuidClient::Lookup
*
*	DESCRIPTION		Look up the hash, return String in pcResultBuf.
*
*	INPUTS			uiHash - the hash to resolve
*					pcResultBuf - buffer to receive returned String
*					iResultBufSize - size of pcResultBuf
*
*	RESULT			Returns success.
*					Note that there is no way to distinguish between
*					network errors and hash-not-found.
*
**************************************************************************************************/
bool GuidClient::LookupGuid( const char* guid, char* pcResultBuf, int iResultBufSize )
{
	GuidClientImpl::GuidToName::const_iterator nmIt = m_impl.m_GuidToName.find( guid );
	if( nmIt == m_impl.m_GuidToName.end() )
	{
		return false;
	}
	if( iResultBufSize < (int) nmIt->second.size() )
	{
		return false;
	}
	// return the String guid
	strncpy( pcResultBuf, nmIt->second.c_str(), iResultBufSize );
	return true;

}


/**************************************************************************************************
*
*	FUNCTION		GuidClient::Add
*
*	DESCRIPTION		Tell the server to add the String to its list. It's a send-and-forget
*					operation - there's no confirmation that the String ever actually made it to
*					the server or that the server is even running.
*
*	INPUTS			pcString - the String to add.
*
**************************************************************************************************/
bool GuidClient::Add( const char* pcString )
{
	GuidClientImpl::NameToGuid::const_iterator nmIt = m_impl.m_NameToGuid.find( pcString );
	if( nmIt == m_impl.m_NameToGuid.end() )
	{
		UUID winUuid;
		UuidCreate( &winUuid );
		ntstd::String realString;

		char *temp;
		UuidToStringA( &winUuid, (unsigned char **) &temp );
		realString = ntstd::String( temp );
		RpcStringFreeA( (unsigned char **) &temp );

		m_impl.m_NameToGuid[ pcString ] = realString;
		m_impl.m_GuidToName[ realString ] = pcString;
		return true;
	}
	return false;
}

/**************************************************************************************************
*
*	FUNCTION		GuidClient::AddUnique
*
*	DESCRIPTION		Tell the server to a unique name to its list. Return the name
*
*	INPUTS			pcString - the String to add.
*
**************************************************************************************************/
bool GuidClient::AddUnique( char* pcString )
{
	UUID winUuid;
	UuidCreate( &winUuid );
	ntstd::String realString;

	char *temp;
	UuidToStringA( &winUuid, (unsigned char **) &temp );
	realString = ntstd::String( temp );
	RpcStringFreeA( (unsigned char **) &temp );

	ntstd::String uniqueName = ntstd::String("Unique")+ realString;
	m_impl.m_NameToGuid[ uniqueName ] = realString;
	m_impl.m_GuidToName[ realString ] = uniqueName;

	strcpy( pcString, uniqueName.c_str() );

	return true;

}
/**************************************************************************************************
*
*	FUNCTION		GuidClient::Rename
*
*	DESCRIPTION		Tell the server to rename an entry in its list. Returns true on succes and
*                   false on failure.
*
*	INPUTS			pcString - the String to add.
*
**************************************************************************************************/
bool GuidClient::Rename( const char* guid, const char* newname )
{
	// does guid exist
	GuidClientImpl::GuidToName::iterator guIt = m_impl.m_GuidToName.find( guid );
	if( guIt== m_impl.m_GuidToName.end() )
	{
		return false;
	}
	// does new name already exist
	GuidClientImpl::NameToGuid::iterator nnmIt = m_impl.m_NameToGuid.find( newname );
	if( nnmIt != m_impl.m_NameToGuid.end() )
	{
		return false;
	}

	// get old name and delete it
	GuidClientImpl::NameToGuid::iterator nmIt = m_impl.m_NameToGuid.find( m_impl.m_GuidToName[guid] );
	m_impl.m_NameToGuid.erase( nmIt );

	// repoint guid and add the new name to guid
	m_impl.m_GuidToName[ guid ] = newname;
	m_impl.m_NameToGuid[ newname ] = guid;
	return true;

}
/**************************************************************************************************
*
*	FUNCTION		GuidClient::Remove
*
*	DESCRIPTION		Tell the server to remove a GUID from its list. Returns true on succes and
*                   false on failure.
*
*	INPUTS			pcString - the String to add.
*
**************************************************************************************************/
bool GuidClient::Remove( const char* guid )
{
	GuidClientImpl::GuidToName::iterator guIt = m_impl.m_GuidToName.find( guid );
	if ( guIt == m_impl.m_GuidToName.end() )
	{
		return false;
	}
	GuidClientImpl::NameToGuid::iterator nmIt = m_impl.m_NameToGuid.find( guIt->second.c_str() );
	if ( nmIt == m_impl.m_NameToGuid.end() )
	{
		return false;
	}

	// remove both the guid and name from their respective mappings now
	m_impl.m_GuidToName.erase( guIt );
	m_impl.m_NameToGuid.erase( nmIt );
	return true;
}