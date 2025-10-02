/// \file Lignum.h
/// \brief Lignum main header file
///
/// The only required header file to build Lignum models.
#ifndef LIGNUM_H
#define LIGNUM_H

//Please do not wrap Tree.h into namespace Lignum. 
//That will create a nested namespace and will cause strange
//errors difficult to track when including header files
#include <Tree.h>
#include <LGMUtility.h>
#endif
