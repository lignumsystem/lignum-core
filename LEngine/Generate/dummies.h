#ifndef __DUMMIES_H__
#define __DUMMIES_H__


enum 
{
  A_id = 0,
  B_id,
  C_id,
  D_id,
  E_id,
  F_id,
  G_id,
  H_id,
  I_id,
  J_id,
  K_id,
  L_id,
  LBRCT_id,
  RBRCT_id
};

const char* GetModuleName(ModuleIdType);

int GetSizeOf(ModuleIdType);


#else
  #error File already included
#endif

