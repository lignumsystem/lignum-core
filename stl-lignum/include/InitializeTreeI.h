#ifndef INITIALIZE_TREEI_H
#define INITIALIZE_TREEI_H


namespace Lignum{
  template <class TS, class BUD>
    void  InitializeTree<TS,BUD>::initialize(Tree<TS,BUD>& tree)
    {
      Lex lex;
      map<string,LGMPD,Cmpstring>::iterator itpd =  maplgmpd.begin();
      
      //1. Parse parameters for a tree
      string file = tmfp.getParameterFile("Tree");
      if (verbose){
	cout << "Reading parameters for tree from: " << file.c_str() << endl;
      }
      
      lex.scan(file);

      //name of the parameter
      Token name = lex.getToken();
      while (name.getType() != VC_ENDFILE){
	//value of the parameter (as string)
	Token value = lex.getToken();
	LGMdouble p = static_cast<LGMdouble>(atof(value.getValue().c_str()));
	if (verbose){
	  cout << "Parameter: " << name.getValue().c_str() << " = " << p << endl;
	}
	//Check if this is known parameter
	//First, if it is a parameter configuring tree segment
	//Check if found, then install
	if ((itpd = maplgmpd.find(name.getValue())) != maplgmpd.end()){
	  SetValue(tree,(*itpd).second,p);
	}
	//Unkonown, parameter (check MapLGMPD and listing in TreeFriend.cc)
	else{
	  if (verbose){
	    cerr << "Unknown parameter for tree: check MapLGMPD listing in TreeFriend.cc" 
		 << name.getValue().c_str()
		 << endl;
	  }
	}
	//next parameter
	name = lex.getToken();
      }
      
      //2. Configure the firmament
      file = tmfp.getParameterFile("Firmament");
      if (verbose){
	cout << "Reading Configuration for Firmament from: " << file.c_str() << endl;
      }

      GetFirmament(tree).configure(file);

      if (verbose){
	cout << "Azimuths: "  << GetFirmament(tree). getNoOfAzimuths() 
	     << " Inclinations: " 
	     << GetFirmament(tree). getNoOfInclinations() << endl;
	cout << "Radiation (Ball sensor): " 
	     << GetFirmament(tree). diffuseBallSensor()
	     << " Radiation (Plane sensor): " 
	     << GetFirmament(tree). diffusePlaneSensor()
	     << endl;
	cout << "Change of radiation due this mask, Planesensor: " <<
		 GetFirmament(tree).getPlaneChange() << "  Ballsensor:  " <<
		 GetFirmament(tree).getBallChange() << endl;
      }
      //3. Parse functions for a tree
      //1.
      file = tmfp.getFunctionFile("LGMAL");
      if (verbose){
	cout << "Configuring functions" << endl;
      }
      if (file != string("")){
	if (verbose){
	  cout << "Reading LGMAL from: " << file << endl;
	}
	tree.tf.al.install(file);
      }
      //2.
      file = tmfp.getFunctionFile("LGMFM");
      if (file != string("")){
	if (verbose){
	  cout << "Reading LGMFM from: " << file << endl;
	}
	tree.tf.fm.install(file);
      }
      //3.
      file = tmfp.getFunctionFile("LGMIP");
      if (file != string("")){
	if (verbose){
	  cout << "Reading LGMIP from: " << file<< endl;
	}
	tree.tf.ip.install(file);
      }
      //4.
      file = tmfp.getFunctionFile("LGMLONB");
      if (file != string("")){
	if (verbose){
	  cout << "Reading LGMLONB from: " << file << endl;
	}
	tree.tf.LightOnNumBuds.install(file);
      }
      //5.
      file = tmfp.getFunctionFile("LGMNB");
      if (file != string("")){
	if (verbose){
	  cout << "Reading LGMNB from: " << file << endl;
	}
	tree.tf.nb.install(file);
      }
      //6.
      file = tmfp.getFunctionFile("LGMVI");
      if (file != string("")){
	if (verbose){
	  cout << "Reading LGMVI from: " << file << endl;
	}
	tree.tf.vi.install(file);
      }
      //7.
      file = tmfp.getFunctionFile("LGMVIONB");
      if (file != string("")){
	if (verbose){
	  cout << "Reading LGMVIONB from: " << file << endl;
	}
	tree.tf.VigourOnNumBuds.install(file);
      }
    }
}//closing namespace Lignum

#endif
