/********************************************
 *Skip the branch in search of right context*
 *Moving from left to right in the string   *
 ********************************************/
inline void SkipBranchFromLeft(LstringIterator& pos)
{
  //we know we are in a branch so set stack to 1
  int stack = 1;
  while (stack && !(pos.AtEnd())){
    //cout << "     Skipping: "  << pos.GetCurrentModuleName() << endl;
    if (pos.GetModuleId() == SB_id)
      stack++;
    if (pos.GetModuleId() == EB_id)
      stack--;
    pos++;
  }
  //now you are one passed the ]. Back up one module.
  pos--;
  //subbranch skipped, go to the first module that has to match
  //having branch order one higher.
}

/*******************************************
 *Skip the branch in search of left context*
 *Moving from right to left in the string  *
 *******************************************/
inline void SkipBranchFromRight(LstringIterator& pos)
{
  if (pos.GetModuleId() == EB_id){
    int stack = 1;
    pos--;
    //if stack goes to 0 we have found matching "["
    while (!pos.AtBeginning() && stack){
      //cout << "    Skipping: "  << pos.GetCurrentModuleName() 
      //     << " " << stack << endl;
      //matching [ found
      if (pos.GetModuleId() == SB_id)
	stack--;
      //entered a subbranch
      if (pos.GetModuleId() == EB_id)
	stack++;
      pos--; 
    }
  }
  //else do nothing
}

inline int GoNextModuleInSameAxis(list<ModuleIdType>::iterator& first,
				  list<ModuleIdType>& fm_ls, int& branches)
{
  int nofs = 0;
  int level = 0;
  branches = 0;

  while (first != fm_ls.end()){
    if (*first == SB_id){
      if (level == 0){
	branches++;
      }
      level++;
    }
    else if (*first == EB_id)
      level--;
    else if (level == 0){
      nofs++;
      break;
    }
    first++;
  }

  return nofs;
}

/**********************************************************************
 *For the backward compatibility "A > [] J" must be read "at least one*
 *branch between A and J". To do so count the number of branches      *
 *between A and J and  insert the missing number of empty branches.   *
 *Like this the context will become as the default algorithm for right*
 *context where the branches are enumerated explicitely. Naturally the*
 *ordering is difficult to manage. In  "A > [B] J" the B has its      *
 *position and to interpret if "A > [] [B] J" or "A > [B] [] J" etc.  *
 *is meant would require permutations. So the empty branches are      *
 *always inserted in front of J.                                      *   
 **********************************************************************/ 
inline void BackwardCompatibilityRightContext(LstringIterator& pos,
					      ProductionModules& right_cntxt,
					      list<ModuleIdType>& fm_ls)
{
  int current_pos = pos.CurrentPosition();
  int branches_string = 0;
  int branches_cntxt  = 0;
  int empty_branches_needed  = 0;
  int i = 0;
  list<ModuleIdType>::iterator first;
  
  //create the list of symbols in right context
  while (i < right_cntxt.count){
    fm_ls.push_back(right_cntxt.arr[i]);
    i++;
  }

  first = fm_ls.begin();
  pos++; //proceed one right to A in A > []...J
  while (first != fm_ls.end() && !pos.AtEnd()){
    //In the context go to the symbol at A's level in the axis, i.e., find
    //the first J in A > []...J
    GoNextModuleInSameAxis(first,fm_ls,branches_cntxt);
    //Find  the  same symbol in the string, skip the branches in search
    branches_string = 0;
    while (pos.GetModuleId() == SB_id){
      branches_string++;
      pos.FindEOB();
      pos++;
    }
    //If at end of string the search failed and no context
    //If the first symbols don't match (i.e. pos.GetModuleId() != *first) 
    //then let the matching algorithm fail at these symbols. 
    if (pos.AtEnd())
      return;

    empty_branches_needed = branches_string - branches_cntxt;
 
    while (empty_branches_needed > 0){
      fm_ls.insert(first,SB_id);
      fm_ls.insert(first,EB_id);
      empty_branches_needed--;
    }
    branches_cntxt = branches_string =  empty_branches_needed = 0;
    first++; //Advance now in the context list to next symbol
    pos++;//Also in the string
  }
  //Now an original context "A > [] J" should look A > [] [] ... J
  //where there are right number of empty branches to match A's context.
  //Also handled are cases like "A > J and "A > [B][]...J" and "A > []B[]C[]J".

  //Reset the string for context match
  while (pos.CurrentPosition() != current_pos)
    pos--;
}

/***********************************************************
 *Find if the candidate right context pointed by "pp"      *
 *is the left context of the module on position "pos".     *
 ***********************************************************/
inline bool MatchRightContext(LstringIterator& pos, 
			      const ProductionPrototype& pp, 
			      CallerData& caller_data,  
			      set<ModuleIdType>& ignore_set,
			      set<ModuleIdType>& consider_set)
{
  //backward compatilbility interprets "A > [] J" as "at least one branch"
  bool backward_compatibility_mode = true;
  bool has_right_context = true;
  list<ModuleIdType> fm_ls;
  list<ModuleIdType>::iterator front;
  int current_pos = pos.CurrentPosition();
  ProductionModules right_cntxt = pp.RCntxt;

  //insert the left context to a list
  //cout << "Candidate Right Context: " << endl;

  //no need for right context
  if (right_cntxt.count == 0)
    return true;
  //string at the end -->certainly no right context
  if (pos.AtEnd())
    return false;


  int i = 0;
  if (backward_compatibility_mode){
    BackwardCompatibilityRightContext(pos,right_cntxt,fm_ls);
  }
  else{
    while (i < right_cntxt.count){
      fm_ls.push_back(right_cntxt.arr[i]);
      i++;
    }
  }

  front = fm_ls.begin();
  while (front != fm_ls.end()){
    //cout << GetModuleName(*front) << " ";
    front++;
  }
  //cout << endl;

  //start matching, the right context is
  //the immediate modules in the same branch
  //and/or modules in immediate subbranches 
  pos++;
  while (!fm_ls.empty() && !pos.AtEnd()){
    front = fm_ls.begin();
    //if ] in the _context_ then the sequence of symbols matched
    //in a branch, skip the rest of the branch in string
    if (*front == EB_id){
      //Check for empty branch
      if (pos.GetModuleId()!= EB_id)
	pos.FindEOB();
    }
    //compare modules and [ literally
    //cout << "Right Context Comparing: "  << string(pos.GetCurrentModuleName()) << " " 
    //	 << GetModuleName(*front) << endl;
    //Consider and ignore statements makes this a bit complicated
    //If the consider set is not empty consider only Modules in the set and brackets
    //If ignore list is not empty ignore Module if in the set
    //Assume that either consider or ignore set is empty or both are empty.
    //1. if member in consider set and not match --> no context
    //2. if not in ignore set and not match --> no context
    //3. if in ignore set then the if-statement is false --> search context 
    //cout      <<      ((consider_set.find(pos.GetModuleId())      !=
    //consider_set.end()) && !(pos.GetModuleId() == *front)) << endl;
    //cout       <<       ((ignore_set.find(pos.GetModuleId())      ==
    //ignore_set.end()) && (!(pos.GetModuleId() == *front))) << endl;
    if (((consider_set.find(pos.GetModuleId()) != consider_set.end()) && !(pos.GetModuleId() == *front)) ||
	((ignore_set.find(pos.GetModuleId()) == ignore_set.end()) && (!(pos.GetModuleId() == *front)))){
      has_right_context = false;
      break; //break the while loop
    }
    //pop only the Module if we had to compare (current position in a _string_
    //was not in ignore list) 
    if (ignore_set.find(pos.GetModuleId()) == ignore_set.end()){
      fm_ls.pop_front();
    }
    else{
      //cout << "Ignoring: " << GetModuleName(pos.GetModuleId()) << endl;
    }
    //move in the string
    if (!pos.AtEnd())
      pos++;
  }
  //no match if context not exhausted but the string is
  if (pos.AtEnd() && !(fm_ls.empty()))
    has_right_context = false;
    
  //return to the original place in string
  while (current_pos != pos.CurrentPosition())
    pos--;
  //if right context exists add the arguments (see MatchStrictPredecessor)
  if (has_right_context)
    caller_data.RCntxt.AddModuleAddr(pos.Ptr());
  return has_right_context;
}

/**********************************************************
 *Find if the candidate left context pointed by "pp"*
 *is the left context of the module on position "pos".    *
 **********************************************************/
inline bool MatchLeftContext(LstringIterator& pos, 
			     const ProductionPrototype& pp, 
			     CallerData& caller_data, 
			     set<ModuleIdType>& ignore_set,
			     set<ModuleIdType>& consider_set)
{
  bool has_left_context = true;
  list<ModuleIdType> fm_ls;
  list<ModuleIdType>::iterator front;
  int current_pos = pos.CurrentPosition();
  ProductionModules left_cntxt = pp.LCntxt;

  //cout << "Candidate Left Context: " << endl; 
  //no need for left context
  if (left_cntxt.count == 0)
    return true;
  //string at the beginning -->no left context for the string
  if (pos.AtBeginning())
    return false;
  
  //insert the left context to a list
  //we have to scan it in reverse order
  int i = 0;
  while (i < left_cntxt.count){
    fm_ls.push_front(left_cntxt.arr[i]);
    //cout << GetModuleName(left_cntxt.arr[i]) << " ";
    i++;
  }
  //cout << endl;

  //Start matching left context
  pos--;
  //skip beginning of branch
  while (!fm_ls.empty() && !pos.AtBeginning()){
    //skip beginning of branch
    while (pos.GetModuleId() == SB_id){
      pos--;
    }
    //now we should be on a path leading to module for which we serch 
    //the left context.
    //skip branch
    while (pos.GetModuleId() == EB_id){
      pos--;//Go into a branch
      //There might be an empty branch!!!: []
      if (pos.GetModuleId() != SB_id)
	pos.FindBOB(); //Find [ symbol
      pos--;//and the next symbol to the left should be on the path
    }
    //The head of left context should match current module in string
    front = fm_ls.begin();
    //Consider and ignore statements makes this a bit complicated
    //If the consider set is not empty consider only Modules in the set and brackets
    //If ignore list is not empty ignore Module if in the set
    //Assume that either consider or ignore set is empty or both are empty.
    //1. if member in consider set and not match --> no context
    //2. if not in ignore set and not match --> no context
    //3. if in ignore set then the if-statement is false --> search context 
    //cout      <<      ((consider_set.find(pos.GetModuleId())      !=
    //consider_set.end()) && !(pos.GetModuleId() == *front)) << endl;
    //cout       <<       ((ignore_set.find(pos.GetModuleId())      ==
    //ignore_set.end()) && (!(pos.GetModuleId() == *front))) << endl;
    if (((consider_set.find(pos.GetModuleId()) != consider_set.end()) && !(pos.GetModuleId() == *front))||
	((ignore_set.find(pos.GetModuleId()) == ignore_set.end()) && (!(pos.GetModuleId() == *front)))) {
      //if no match then no left context
      has_left_context = false;
      break;
    }
    //pop only the Module if we had to compare (current position in a string
    //was not in ignore list) move in the string 
    if (ignore_set.find(pos.GetModuleId()) ==  ignore_set.end()){
      fm_ls.pop_front();
    }
    else{
      //cout << "Ignoring: " << GetModuleName(pos.GetModuleId()) << endl;
    }
    if (!pos.AtBeginning())
      pos--;
  }

  //cout << pos.AtBeginning() << " "  << (fm_ls.size() == 1) << " " <<
  //(ignore_set.find(pos.GetModuleId()) != ignore_set.end()) << " " <<
  //GetModuleName(pos.GetModuleId())    <<    (pos.GetModuleId()    ==
  //fm_ls.front())<<  endl; 

  //the above loop  ends when the string is  AtBeginning (or breaks if
  //context  or not),  check the  possible last  symbol 
  //1. if  at the beginning and 
  //2. there  is exactly one symbol to  be checked and  
  //3. the  symbol is  not in  the ignore  set and
  //4. the symbols match
  //Note: the idea  is to change current value  of has_left_context if
  //all 4 conditions are true.  If 1) fails either context is found or
  //not, if  2) fails we cannot  have context, if 3)  fails the symbol
  //can be  ignored and current value of  has_left_context remains and
  //if 4) fails we cannot have context.
  //&& (ignore_set.find(pos.GetModuleId()) == ignore_set.end)
  if (pos.AtBeginning() && (fm_ls.size() == 1)&& (ignore_set.find(pos.GetModuleId()) == ignore_set.end()) && 
						  (pos.GetModuleId() == fm_ls.front())){
    //cout << "  Comparing: " << GetModuleName(pos.GetModuleId()) << " " <<  GetModuleName( fm_ls.front())<< endl;
    has_left_context = true;
  }
  //no match if context not exhausted but the string is 
  else if (pos.AtBeginning() && (fm_ls.size() >= 1)){
    
    has_left_context = false;
  }	
  //return to the original place in string
  while (current_pos != pos.CurrentPosition())
    pos++;
  //if left context add the arguments (see MatchStrictPredecessor)
  if (has_left_context)
    caller_data.LCntxt.AddModuleAddr(pos.Ptr());
  return has_left_context;
}

inline bool MatchStrictPredecessor(LstringIterator& pos,
				   const ProductionPrototype& pp,
				   CallerData& caller_data)
{
  ProductionModules strct = pp.Strct;
  ModuleIdType head = strct.arr[0];

  //if match 
  if (pos.GetModuleId() == head){
    //insert the arguments, i.e., just the address of the module
    //ID in [...|ID|arg1|arg2...|argn|DI|.....]
    //cout << "Strict Predecessor: " << GetModuleName(pos.GetModuleId()) << " Pos: " << pos.CurrentPosition() << endl;
    caller_data.Strct.AddModuleAddr(pos.Ptr());
    return true;
  }
  else
    //not strict predecessor match
    return false;
}

/************************************************************************************
 *ContextMatch: perform match of the strict predecessor, left and right context     *
 *Arguments:                                                                        *
 *   pos: iterator to the current position in a string                              *
 *Return:                                                                           *
 *   ProdCaller: function to the production caller (NULL if no match)               *
 *   caller_data: parameters  of the strict predecessor, left and right context.    *
 *   prod: number of the production prototype that matched, -1 means no match       *
 ************************************************************************************/  
inline ProdCaller  ContextMatch(const LstringIterator& pos,
				CallerData& caller_data,int& prod)
{  

  set<ModuleIdType> consider_set;
  set<ModuleIdType> ignore_set;
  bool match = false;
  int i = 0;

  //construct consider and ignore sets
  for (i = 0;i < NumOfConsidered();i++)
    consider_set.insert(GetConsidered(i));
  for (i = 0;i < NumOfIgnored();i++)
    ignore_set.insert(GetIgnored(i));

  //consider set overrides ignore list 
  //"consider only Modules in consider_set and brackets"
  if (!consider_set.empty()){
    ignore_set.clear();
    //Insert brackets sowe don't have to change the underlying algorithm
    //for matching context
    consider_set.insert(SB_id);
    consider_set.insert(EB_id);
  }

  i = 0;
  while (!match && i < NumOfProductions()){
    caller_data.Reset();
    match = MatchStrictPredecessor(const_cast<LstringIterator&> (pos),GetProductionPrototype(i),caller_data);
    if (match){
      match = MatchLeftContext(const_cast<LstringIterator&> (pos),GetProductionPrototype(i),caller_data,
			       ignore_set,consider_set);
    }
    if (match){
      match = MatchRightContext(const_cast<LstringIterator&> (pos),GetProductionPrototype(i),caller_data,
				ignore_set,consider_set);
    }
    i++;
  }
 
  //the rules are counted 0,1,...,n and the "i" is now 1,2,...,n+1 if match
  if (match){
    prod = i-1;
    return GetProductionPrototype(i-1).pCaller;
  }
  else{
    prod = -1;
    return NULL;
  }
}


