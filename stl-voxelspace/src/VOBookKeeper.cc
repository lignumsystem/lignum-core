#include <VOBookKeeper.h>

namespace voxelspace{
long_size VOBookKeeper::newTag()
{
  long_size tmp = tag;
  tag++;
  return tmp;
}

bool VOBookKeeper::rayHit(long_size tag)const
{
  return v[tag] == true;
}

void VOBookKeeper::setRayHit(long_size tag)
{
  v[tag] = true;
}

void VOBookKeeper::resetVector()
{
  fill(v.begin(),v.end(),false);
}

void VOBookKeeper::reset()
{
  v.clear();
  tag = 0;
}

void VOBookKeeper::init()
{
  initVector();
}

void VOBookKeeper::initVector()
{
  v.resize(tag,false);
}
}//end namespace voxelspace
