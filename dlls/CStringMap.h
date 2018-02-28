#ifndef CFIXEDSTRINGMAP_H
#define CFIXEDSTRINGMAP_H

#include "CString.h"

/*
* A string to string map
*/
class CStringMap
{
public:
	struct Entry_t
	{
		CString szKey;
		CString szValue;
	};

	//Every time we resize, increase by this many entries
	//Helps avoid constant reallocation, without dramatically increasing array size
	static const size_t RESIZE_ENTRY_COUNT = 4;

public:
	CStringMap( const size_t uiInitialCapacity = 0 );
	~CStringMap();

	inline size_t Capacity() const { return m_uiCapacity; }

	inline size_t Size() const { return m_uiSize; }

	/*
	* Performs a case insensitive search for the given key
	* If found, returns the value associated with the key
	* Otherwise, returns NULL
	*/
	const char* Find( const char* const pszKey ) const;

	/*
	* Inserts a new entry into the map
	* Returns false if the entry could not be inserted
	*/
	bool AddEntry( const char* const pszKey, const char* const pszValue );

	const char* operator[]( const size_t uiIndex ) const;

private:
	void Reserve( const size_t uiMinimum );

private:
	size_t m_uiCapacity;
	size_t m_uiSize;		//Number of entries that have been filled in

	//Must be last
	//Is actually an array of m_uiMaxEntries entries
	Entry_t* m_pEntries;

private:
	CStringMap( const CStringMap& );
	CStringMap& operator=( const CStringMap& );
};

typedef void ( * ReplacementLoadedCallback )( CStringMap& replacements );

struct ReplacementSettings
{
	const char* const pszName;					//Pretty print name, like "Sound"
	const char* const pszDirectory;				//Directory name, like "sound"

	ReplacementLoadedCallback loadedCallback;	//Callback to handle loaded replacement file
};

bool LoadReplacementMap( const char* pszFilename, const bool fIsGlobalReplacementFile, const ReplacementSettings& settings, CStringMap& map );

#endif //CFIXEDSTRINGMAP_H