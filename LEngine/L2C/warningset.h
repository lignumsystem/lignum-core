#ifndef __WARNINGSET_H__
#define __WARNINGSET_H__

#ifdef WIN32
#pragma warning(disable : 4201) // nonstandard extension used : nameless struct/union
#pragma warning(disable : 4514) // unreferenced inline/local function has been removed
#endif

#else
	#error File already included
#endif
