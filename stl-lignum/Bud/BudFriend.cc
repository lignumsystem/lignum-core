#include <Bud.h>

TP GetAttributeValue(const Bud& bud, const TAD name)
{
  if (name == omega)
    return bud.ba.omega;

  else if (name == ip)
    return bud.ba.ip;

  else{
    cout << "Unknown attribute: " << name << endl;
    cout << "Returning 0.0" << endl;
  }

  return 0.0;
}
    
TP SetAttributeValue(Bud& bud, const TAD name, const TP value)
{
  TP old_value = GetAttributeValue(bud,name);

  if (name == omega)
    bud.ba.omega = value;

  else if (name == ip)
   bud.ba.ip = value;

  return old_value;
}
  
