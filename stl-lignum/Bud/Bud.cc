#include "stdafx.h"
#include <Bud.h>
namespace Lignum{


#ifdef _MSC_VER

//cvs: korjaa!
BudAttributes::BudAttributes()
  :ip(0.0),omega(0.0),state(ALIVE)
{
}

#else
BudAttributes::BudAttributes()
  :collision(0.0),ip(0.0),omega(0.0),type(0.0),status(0.0),state(ALIVE)
{
}

#endif // _MSC_VER


}//closing namespace Lignum
