#ifndef COLLISIONI_H
#define COLLISIONI_H


//General comments: see Collision.h


//Evaluation of collision is done for all Buds in the tree with this
//functor.

template <class TS, class BUD>
void EvaluateCollisionForAllBuds<TS,BUD>::operator()
     (TreeCompartment<TS, BUD>* tc)const {

  if(Bud<TS,BUD>* its_me = dynamic_cast<Bud<TS,BUD>*>(tc)) {
    
    EvaluateCollisionForThisBud<TS, BUD> col_eval(c_angle, c_distance);

    col_eval.point = GetPoint(*tc);
    col_eval.direction = GetDirection(*tc);
    col_eval.direction.normalize();
    
    Tree<TS,BUD>& tt = dynamic_cast<Tree<TS,BUD> &>(GetTree(*its_me));
    
    int initial = 0;
    int collision = Accumulate(tt, initial, col_eval);

    if(collision>=1) {
      SetValue(*its_me,LGAcollision,1.0);

    }
  }

}


//Checking of all other Treesegments and Bud done for one particular
//Bud. Further comments: see Collision.h

template <class TS,class BUD>
int& EvaluateCollisionForThisBud<TS,BUD>::
    operator()(int& coll, TreeCompartment<TS,BUD>* tc)const {

  if(coll != 1) {
    if (TS* ts = dynamic_cast<TS*>(tc))
      ;
    else if(BUD* b = dynamic_cast<BUD*>(tc))
      ;
    else
      return coll;

    Point p = GetPoint(*tc);
    PositionVector diff(p - point);

    LGMdouble len = diff.length();

    if(len < R_EPSILON) {      
      return coll;
    }

    LGMdouble dotp = Dot(direction, diff);
    //If the dotp angle is inside the c_cos angle, then there is collision 
    if(c_cos > dotp / len) {
      //if the len is within the given distance
      if(len < c_distance) {
	coll = 1;
      }
    }
    
  }

  return coll;
}

#undef C_ANGLE
#undef COS_ANGLE
#undef C_DISTANCE

#endif

