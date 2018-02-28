#include "extdll.h"
#include "util.h"

#include "CStringMap.h"

CStringMap::CStringMap( const size_t uiInitialCapacity )
	: m_uiCapacity( 0 )
	, m_uiSize( 0 )
	, m_pEntries( nullptr )
{
	Reserve( uiInitialCapacity );
}

CStringMap::~CStringMap()
{
	if( m_pEntries )
	{
		delete[] m_pEntries;
		m_pEntries = nullptr;

		m_uiSize = m_uiCapacity = 0;
	}
}

const char* CStringMap::Find( const char* const pszKey ) const
{
	if( !pszKey )
		return nullptr;

	for( size_t uiIndex = 0; uiIndex < m_uiSize; ++uiIndex )
	{
		if( stricmp( pszKey, m_pEntries[ uiIndex ].szKey.CStr() ) == 0 )
			return m_pEntries[ uiIndex ].szValue.CStr();
	}

	return nullptr;
}

bool CStringMap::AddEntry( const char* const pszKey, const char* const pszValue )
{
	if( !pszKey || !pszValue )
		return false;

	Reserve( m_uiSize + 1 );

	Entry_t& entry = m_pEntries[ m_uiSize++ ];

	entry.szKey = pszKey;
	entry.szValue = pszValue;

	return true;
}

const char* CStringMap::operator[]( const size_t uiIndex ) const
{
	ASSERT( uiIndex < m_uiSize );

	return m_pEntries[ uiIndex ].szValue.CStr();
}

void CStringMap::Reserve( const size_t uiMinimum )
{
	if( uiMinimum <= m_uiCapacity )
		return;

	//Increase array to match requested size
	const size_t uiNewCapacity = uiMinimum + RESIZE_ENTRY_COUNT;

	Entry_t* pNewEntries = new Entry_t[ uiNewCapacity ];

	if( m_pEntries )
	{
		for( size_t uiIndex = 0; uiIndex < m_uiSize; ++uiIndex )
		{
			pNewEntries[ uiIndex ] = m_pEntries[ uiIndex ];
		}

		delete[] m_pEntries;
	}

	m_pEntries = pNewEntries;

	m_uiCapacity = uiNewCapacity;
}

bool LoadReplacementMap( const char* pszFilename, const bool fIsGlobalReplacementFile, const ReplacementSettings& settings, CStringMap& map )
{
	if( !pszFilename || !( *pszFilename ) )
		return false;

	char szBaseDir[ MAX_PATH_LENGTH + 1 ];

	UTIL_FormatString( szBaseDir, "%s/%s", settings.pszDirectory, STRING( gpGlobals->mapname ) );

	char szCompleteFilename[ MAX_PATH_LENGTH + 1 ];

	UTIL_FormatString( szCompleteFilename, "%s/%s", szBaseDir, pszFilename );

#ifndef WIN32
	//This should create a directory in both the base game dir (svencoop), the addon directory (svencoop_addon), and the downloads directory (svencoop_downloads) - Solokiller
	g_pFileSystem->CreateDirHierarchy( szBaseDir, FILESYSTEM_MOD_PATH );
	g_pFileSystem->CreateDirHierarchy( szBaseDir, "GAME" );
	g_pFileSystem->CreateDirHierarchy( szBaseDir, FILESYSTEM_DOWNLOADS_PATH );
#endif

	if( !g_pFileSystem->IsDirectory( szCompleteFilename ) )
	{
		//Passing in nullptr causes it to search all paths
		FileHandle_t hFile = g_pFileSystem->Open( szCompleteFilename, "r", nullptr );

		if( hFile != FILESYSTEM_INVALID_HANDLE )
		{
			char szOriginal[ MAX_MESSAGE_LENGTH ];
			szOriginal[ MAX_MESSAGE_LENGTH - 1 ] = 0;
			char szReplacement[ MAX_MESSAGE_LENGTH ];
			szReplacement[ MAX_MESSAGE_LENGTH - 1 ] = 0;
			char* pch1;
			char* pch2;

			char szLine[ MAX_MESSAGE_LENGTH * 2 ];

			while ( !g_pFileSystem->EndOfFile( hFile ) )
			{
				if ( g_pFileSystem->ReadLine( szLine, sizeof( szLine ), hFile ) != nullptr )
				{
					// Ignore blank and comment lines
					if ( szLine[ 0 ] == '\0' || szLine[ 0 ] == '#' || szLine[ 0 ] == '/' || strlen( szLine ) == 0 )
						continue;

					char* pPos1 = nullptr, * pPos2 = nullptr;

					if ( sscanf( szLine, "%s %s\n", szOriginal, szReplacement ) > 0 )
					{
						pch1 = strtok_s( szOriginal,"\"", &pPos1 );
						pch2 = strtok_s( szReplacement,"\"", &pPos2 );

						map.AddEntry( pch1, pch2 );

						szLine[ 0 ] = 0;
					}
				}
			}
			

			g_pFileSystem->Close( hFile );
		}
		else
		{
			if( fIsGlobalReplacementFile )
				ALERT( at_error, "%s Replacement file not found: %s\n", settings.pszName, szCompleteFilename ); //-SvenV
			return false;
		}
	}
	else
	{
		ALERT( at_error, "%s Replacement File '%s' is a directory!\n", settings.pszName, szCompleteFilename );
		return false;
	}

	if( settings.loadedCallback )
		settings.loadedCallback( map );

	if( fIsGlobalReplacementFile )
		ALERT( at_console, "Finished precaching custom %ss.\n", settings.pszName );

	return true;
}
