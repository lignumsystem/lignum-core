
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
		if(GetValue(*ts,LGAage) < R_EPSILON) 
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
	
			SetRadius(*ts);

			LGMdouble radius = GetValue(*ts, R);
			Tree<TS,BUD> &tree = GetTree(*ts);

			LGMdouble dAs = GetValue(tree, ss) * GetSapwoodArea(*ts);		
			LGMdouble r_h = sqrt(pow(GetValue(*ts, Rh), 2) + (dAs / PI_VALUE));

			#ifdef _MSC_VER
			ASSERT(r_h >= 0);
			#endif

			SetValue(*ts, Rh, r_h);

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

/*


//Structural growth i.e. adding new elements
//The reference to mother segment is propagated up
//If Axis, expandd the terninating bud using the information of
//of the mother segment. The mother segment is either in the axis
//or the pointer  ms is specifying it (in this case it is question of
//an axis containing the lateral bud only).

TreeCompartment<GCSegment, GCBud>* StructuralGrowth::operator()
  (GCSegment* ms, TreeCompartment<GCSegment, GCBud>* tc)const
{
  if(Axis<GCSegment,GCBud>* ax = dynamic_cast<Axis<GCSegment,GCBud>*>(tc)) {
	  std::list<TreeCompartment<GCSegment,GCBud>*>& ax_list =
	GetTreeCompartmentList(*ax);
    GCSegment* mother;
	std::list<TreeCompartment<GCSegment,GCBud>*>::iterator ls_i;
    if(ax_list.size() == 1)
      mother = ms;
    else {
       ls_i = ax_list.end();
      ls_i--; ls_i--; ls_i--;
      mother = dynamic_cast<GCSegment*>(*ls_i);    //segment is the third last
      //item of the list
    }

    GCBud* bud = dynamic_cast<GCBud*>(GetTerminatingBud(*ax));
    if(GetValue(*bud,LGAage) > 0.0 && (GetValue(*bud,state) == ALIVE)) {
      
      //OK, add new elements, some preparations
      
      ls_i = ax_list.end();    ls_i--;    //pointing to bud

      GCTree& tree = dynamic_cast<GCTree&>(GetTree(*bud));

      Point base = GetPoint(*bud);

      PositionVector dir = GetDirection(*bud);
      dir.normalize();

      int no_sect = GetFirmament(tree).numberOfRegions();

      PositionVector up(0,0,1);
            

      //New GCSegment for the axis
      LGMdouble r_new = GetValue(tree, lambda);
      LGMdouble l_new = GetValue(tree, lr) * r_new;
      LGMdouble go = GetValue(*bud, omega);
      LGMdouble rh_new = sqrt(GetValue(tree,xi))*r_new;
      GCSegment* ts = new GCSegment(base, dir, go, l_new, r_new, rh_new, &tree);
      SetValue(*ts,di_stempX,GetValue(*mother,di_stempX));
      SetValue(*ts,di_stempY,GetValue(*mother,di_stempY));
      SetValue(*ts,dR,0.0);
      SetValue(*ts,dAs,0.0);
      SetValue(*ts,dW,0.0);
      SetValue(*ts, LGAage, 0.0);
      if(GetValue(*mother,to_right))
	SetValue(*ts,to_right,false);
      else
	SetValue(*ts,to_right,true);
      PositionVector to_stemp(GetValue(*ts,di_stempX), GetValue(*ts,di_stempY),0.0);
      SetValue(*ts, growing, true);
      PositionVector to_side;
      if(GetValue(*ts,to_right))
	to_side = -1.0 * Cross(to_stemp,up);
      else
	to_side = Cross(to_stemp,up);
      to_side.normalize();
      PositionVector d_pet = to_side + 0.1*up - 0.1*to_stemp;
      d_pet.normalize();
      Point end = base + (Point)(l_new*dir);
      
      BroadLeaf* leaf =
	new BroadLeaf(GetValue(tree,sf_p),0.06,GetValue(tree,dof_p),no_sect,
		      Petiole(end,end+(Point)(GetValue(tree,pet_len)*d_pet)),
		      up,
		      Ellipsis(GetValue(tree,leaf_a),GetValue(tree,leaf_b)));
      LGMdouble ellipsis_a = GetValue(tree,phif_p)*PI_VALUE*
	(pow(r_new,2.0)-pow(rh_new,2.0))/GetValue(*leaf,LGAdof);
      SetValue(*leaf, A, ellipsis_a);
      InsertLeaf(*ts, leaf);
      SetValue(*ts,LGAWf,GetValue(tree,dof_p)*ellipsis_a/GetValue(*leaf,sf));
      SetValue(*ts,LGAWs,GetValue(tree,rho)*PI_VALUE*
	       (pow(r_new,2.0)-pow(rh_new,2.0))*l_new);
      SetValue(*ts,Wh,GetValue(tree,rho)*PI_VALUE*pow(rh_new,2.0)*l_new);
      SetValue(*ts,dAs,0.0);
      SetValue(*ts,dW,0.0);
      SetValue(*ts,dR,0.0);
      
      ax_list.insert(ls_i,ts);       //tree segment added to axis

      //New branchingpoint
      BranchingPoint<GCSegment,GCBud>* bp =
	new BranchingPoint<GCSegment,GCBud>(end, dir, &tree);
      ax_list.insert(ls_i,bp);

      //update the information of the bud (at the end of axis)
      SetPoint(*bud, end);
      SetValue(*bud, state, ALIVE);

      //Bend the apical bud of each axis towards zenith using the
      //method by Prusinkiewicz & Lindenmayer (1990), p. 61

      PositionVector dev_v = Cross(dir,up);
      LGMdouble dev = dev_v.length();
      LGMdouble angle = GetValue(tree,branch_bend)*dev;
      PositionVector turn = Cross(to_side,dir);
      if(turn.getZ() < 0.0)
	turn = -1.0*turn;
      PositionVector new_dir = dir + tan(angle) * turn;
      new_dir.normalize();
      SetDirection(*bud, new_dir);
      SetValue(*bud, LGAage, 0.0);
    }


    //Note that in the case of axis, mother (ms) propagated up
    // does not change
  }

  else if(GCSegment* ts = dynamic_cast<GCSegment*>(tc)) {
    ms = ts; //If segment propagate up pointer to yourself
  }
  //If branching point or bud do nothing
  return tc;
}
*/



}

#endif
