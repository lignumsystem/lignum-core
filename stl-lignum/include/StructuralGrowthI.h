
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
			direction.rotate(Point(0,0,0), pv, -angleRad);	//Sven	minimikulma 60  getZ()<0.3
			direction.normalize();

			if (direction.getZ() < 0)
			{
				direction = PositionVector(direction.getX(), direction.getY(), 0);
				direction.normalize();
			}
			SetDirection(*ts, direction);
		}

		LGMdouble length = GetValue(*ts,LGAL);
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
		if(GetValue(*ts,LGAage) < R_EPSILON) 
		{ // new segment, must adjust subsequent elements	
			Point base = GetPoint(*ts);
			PositionVector dir = GetDirection(*ts);
			LGMdouble length = GetValue(*ts,LGAL);
			Point end = base + (Point)(length * dir);
			
			SetValue(*ts, LGARTop, GetValue(*ts, LGAR));
			SetLastRing(*ts);
			sa.changed = true;
			sa.location = end;
		}
		else //old_segment - radius is set from annual_rings list
		{
	
			SetRadius(*ts);

			LGMdouble radius = GetValue(*ts, LGAR);
			Tree<TS,BUD> &tree = GetTree(*ts);

			LGMdouble dAs = GetValue(tree, ss) * GetSapwoodArea(*ts);		
			LGMdouble r_h = sqrt(pow(GetValue(*ts, LGARh), 2) + (dAs / PI_VALUE));

			LGMassert(r_h >= 0);

			SetValue(*ts, LGARh, r_h);

			Point base = GetPoint(*ts);
			PositionVector dir = GetDirection(*ts);
			LGMdouble length = GetValue(*ts,LGAL);
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


#endif
