
#ifndef STRUCTURALGROWTHI_H
#define STRUCTURALGROWTHI_H

namespace Lignum{

template <class TS, class BUD>
TreeCompartment<TS,BUD>*  FoliageLoss<TS,BUD>::operator()(TreeCompartment<TS,BUD>* tc)const
{

	return tc;
}


template <class TS, class BUD>
TreeCompartment<TS,BUD>*  BranchBending<TS,BUD>::operator()
  (Point &position, TreeCompartment<TS,BUD>* tc)const
{
  	if (TreeSegment<TS,BUD>* ts = dynamic_cast<TreeSegment<TS,BUD>*>(tc))
	{
		PositionVector direction = GetDirection(*ts);
		direction.normalize();

		SetPoint(*ts, position);
		Point point = GetPoint(*ts);
		
		if (direction.getZ() != 1)
		{
			PositionVector up(0,0,1);

			//toinen kohtisuora
			PositionVector pv = Cross(direction, up);
			direction.rotate(Point(0,0,0), pv, -angleRad);
			direction.normalize();

			if (direction.getZ() < 0)
			{
				direction = PositionVector(direction.getX(), direction.getY(), 0);
				direction.normalize();
			}
			SetDirection(*ts, direction);
		}

		LGMdouble length = GetValue(*ts,L);
		position = point + (Point)(length * direction);
		return tc;
	}

	if(BranchingPoint<TS,BUD>* bp = dynamic_cast<BranchingPoint<TS,BUD>*>(tc)) 
	{
		SetPoint(*bp, position);
		return tc;
	}

	if(Bud<TS,BUD>* b = dynamic_cast<Bud<TS,BUD>*>(tc)) 
	{
		SetPoint(*b, position);
		return tc;
	}
	return tc;
}


template <class TS, class BUD>
TreeCompartment<TS,BUD>*  AdjustStructureAfterZbrent<TS,BUD>::operator()(StructureAdjustment& sa, TreeCompartment<TS,BUD>* tc)const
{
  	if (TreeSegment<TS,BUD>* ts = dynamic_cast<TreeSegment<TS,BUD>*>(tc))
	{
		SetPoint(*ts, sa.location);
		if(GetValue(*ts,age) < R_EPSILON) 
		{ // new segment, must adjust subsequent elements	
			Point base = GetPoint(*ts);
			PositionVector dir = GetDirection(*ts);
			LGMdouble length = GetValue(*ts,L);
			Point end = base + (Point)(length * dir);
			
			SetValue(*ts, RTop, GetValue(*ts, R));
			SetLastRing(*ts);
			sa.changed = true;
			sa.location = end;
		}
		else //old_segment - radius is set from annual_rings list
		{
			Tree<TS,BUD> &tree = GetTree(*ts);
			LGMdouble s_s = GetValue(tree, ss);
			LGMdouble r_h = GetValue(*ts, Rh);
			LGMdouble dA_s = s_s * GetSapwoodArea(*ts);

			r_h = sqrt(r_h*r_h + (dA_s/PI_VALUE));
			SetValue(*ts, Rh, r_h);
			SetRadius(*ts);


			Point base = GetPoint(*ts);
			PositionVector dir = GetDirection(*ts);
			LGMdouble length = GetValue(*ts,L);
			Point end = base + (Point)(length * dir);
			sa.location = end;
		}


		return tc;
	}
    

  if(BranchingPoint<TS,BUD>* bp = dynamic_cast<BranchingPoint<TS,BUD>*>(tc)) 
  {
	SetPoint(*bp, sa.location);
    return tc;
  }

  if(Bud<TS,BUD>* b = dynamic_cast<Bud<TS,BUD>*>(tc)) 
  {
    SetPoint(*b, sa.location);
    return tc;
  }

  return tc;

}




}

#endif
