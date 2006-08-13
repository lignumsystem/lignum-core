inline const char* GetModuleName(int mid)
{
  assert(mid>=0);
  assert(mid<NumOfModules());
  const ModuleData* pMData = GetModuleData(mid);
  return pMData->Name;
}

inline int GetSizeOf(int mid)
{
  assert(mid>=0);
  assert(mid<NumOfModules());
  const ModuleData* pMData = GetModuleData(mid);
  return pMData->size;
}


inline ActualParameters::ActualParameters()
{
  _count = 0;
}


inline const char* ActualParameters::pArg(int i) const
{
  assert(i>=0);
  assert(i<Count());
  assert(_arr[i] != NULL);
  return _arr[i]+sizeof(ModuleIdType);
}

inline void ActualParameters::AddModuleAddr(const char* pX)
{
  assert(_count<eMaxFormalModules);
  _arr[_count] = pX;
  _count++;
}

//Reverse the  order of modules. It  is needed in left  context to get
//the parameters in right order.
inline void ActualParameters::Reverse()
{
  const char* tmp_arr[eMaxFormalModules];
  int i = 0;
  for (int tmp_count=_count-1; tmp_count >= 0; tmp_count--,i++){
    tmp_arr[i] = _arr[tmp_count];
  }
  for (i = 0; i <= _count; i++){
    _arr[i] =  tmp_arr[i];
  }
}
inline void ActualParameters::Reset()
{
  _count = 0;
}

inline void CallerData::Reset()
{
  LCntxt.Reset();
  Strct.Reset();
  RCntxt.Reset();
}

