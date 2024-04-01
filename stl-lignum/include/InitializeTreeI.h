///\file InitializeTreeI.h
///\brief Implementation of InitializeTree::initialize 
#ifndef INITIALIZE_TREEI_H
#define INITIALIZE_TREEI_H


namespace Lignum{
  template <class TS, class BUD>
  void  InitializeTree<TS,BUD>::initialize(Tree<TS,BUD>& tree, LGMINITSTYLE style)
    {
      Lex lex;
      map<string,LGMPD,Cmpstring>::iterator itpd =  maplgmpd.begin();
      
      ///\par 1. Parse parameters for a tree
      ///Retrieve the parameter file for tree, parse for parameter names for their values and install parameters 
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
      
      ///\par 2. Configure the firmament
      ///The firmament can have one (Lignum::OLD_INIT) or many mask files (Lignum::NEW_INIT)
      file = tmfp.getParameterFile("Firmament");
      if (verbose){
	cout << "Reading Configuration for Firmament from: " << file.c_str() << endl;
      }
   
      //OLD_INIT can only have one mask
      if (style == OLD_INIT){
	GetFirmament(tree).configure(file);
      }
      //NEW_INIT can  have a many mask files
      else{
	//Read and remember all mask files
	GetFirmament(tree).readAllMasks(file);
	//Initialize the first of them
	GetFirmament(tree).configure(0,false);
      }
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
      ///\anchor ParseFunctions
      ///\par 3. Parse functions for a tree
      ///Retrieve the function by name and install it via \p tree.tf.
      ///The following functions are known and installed if the corresponding file exists:
      ///+ Lignum::LGMAL
      ///+ Lignum::LGMFM
      ///+ Lignum::LGMIP
      ///+ Lignum::LGMLONB
      ///+ Lignum::LGMNB
      ///+ Lignum::LGMVI
      ///+ Lignum::LGMVIONB
      ///+ Lignum::LGMGO
      ///
      ///All other (experimental) functions must be installed in the related program.
      ///The list of known functions can be extended following the implementation pattern.
      ///As an example:
      //1.
      ///\snippet{lineno} InitializeTreeI.h InstallFunc
      ///\internal
      //[InstallFunc]
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
      //[InstallFunc]
      ///\endinternal
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
      //8.
      file = tmfp.getFunctionFile("LGMGO");
      if (file != string("")){
	if (verbose){
	  cout << "Reading LGMGO from: " << file << endl;
	}
	tree.tf.go.install(file);
      }
    }
}//closing namespace Lignum

#endif
