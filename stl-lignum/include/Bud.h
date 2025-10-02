/// \file Bud.h
/// \brief Tree bud
#ifndef BUD_H
#define BUD_H

#include <Point.h>
#include <PositionVector.h>
#include <LGMSymbols.h>
#include <LGMdecl.h>
#include <TreeCompartment.h>

namespace Lignum{

  using namespace cxxadt;
  ///\brief Bud attributes for radiation calculation and state
  class BudAttributes{
  public:
    BudAttributes();
    LGMdouble collision;      ///< Collision detection
    LGMdouble ip;             ///< Shadiness as available relative photosynthetic radiation
    LGMdouble omega;          ///< Gravelius order
    LGMdouble qin;            ///< Incoming radiation
    LGMdouble type;           ///< Dominant, apical, lateral etc.
    LGMdouble status;         ///< Counter from N to 0;
    LGMdouble state;          ///< Dead, alive, dormant etc. 
  };

  ///\brief Bud template
  ///\tparam TS Tree segment
  ///\tparam BUD Bud
  template <class TS,class BUD=DefaultBud<TS> >
  class Bud: public TreeCompartment<TS,BUD>{
    ///\brief Bud stdout printing
    ///\param os Output stream
    ///\param bud Bud
    template <class TS1,class BUD1>
    friend ostream &operator << (ostream& os, Bud<TS1,BUD1>& bud);

    ///\brief Get bud attribute value
    ///\param bud Bud
    ///\param name Attribute name in cxxadt::LGMAD  
    template <class TS1,class BUD1>
    friend LGMdouble GetValue(const Bud<TS1,BUD1>& bud, const LGMAD name);
    ///\brief  Set new bud attribute value
    ///\param bud Bud
    ///\param name Attribute name in cxxadt::LGMAD
    ///\param value Attribute value
    ///\return Previous attribute value
    template <class TS1,class BUD1>
    friend LGMdouble SetValue(Bud<TS1,BUD1>& bud, const LGMAD name, const LGMdouble value);
  public:
    Bud();
    ///\brief Constructor
    ///\param p Bud position
    ///\param d Bud direction
    ///\param omega Gravelius order
    ///\param tree Tree bud belongs to
    Bud(const Point& p, const PositionVector& d, const LGMdouble omega, Tree<TS,BUD>* tree);
    Bud(Tree<TS,BUD>* tree):TreeCompartment<TS,BUD>(tree) { }
    TS& createTreeSegment()const;
    Bud<TS,BUD>& createBud()const;
    BranchingPoint<TS,BUD>& createBranchingPoint()const;
    virtual void Production(){/*do nothing*/}
    virtual LGMdouble GetProduction(){return 0.0;}
    void move(PositionVector dir, LGMdouble length);
  private:
    BudAttributes ba;///< Bud attributes
  };

}//closing namespace Lignum

#include <BudI.h>
#endif
