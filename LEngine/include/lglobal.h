
#define CountOf(arr) (int)(sizeof(arr)/sizeof(arr[0])) 

/*
template <class T>
int inline CountOf(T arr) {return (int)(sizeof(arr)/sizeof(arr[0]));} 
*/

enum DerivationDirection
{
	eForward,
	eBackward
};


enum
{
        eMaxIdentifierLength = 32,
        eMaxParams = 64,
        eMaxFormalModules = 32
};

typedef short int ModuleIdType;

enum mReservedModuleValues
{
	SB_id = 0,
	EB_id,
	eFirstModuleId
};

#define StartBranchIdent "SB"
#define EndBranchIdent "EB"



