#ifndef INITIALIZE_TREEI_H
#define INITIALIZE_TREEI_H


namespace Lignum{

  template <class TS, class BUD>
    InitializeTree<TS,BUD>::InitializeTree(const string& file, const LGMVERBOSE v)
    :tmfp(file),verbose(v)
    {
    }

  template <class TS, class BUD>
    void  InitializeTree<TS,BUD>::initialize(Tree<TS,BUD>& tree)
    {
      Lex lex;
      map<string,LGMPD,Cmpstring>::iterator itpd =  maplgmpd.begin();
      map<string,LGMTD,Cmpstring>::iterator ittd =  maplgmtd.begin();

      //Parse the configuration file (meta file) for a tree/forest
      //tmfp will contain name of the files 
      //where the actual parameters/configuration are
      tmfp.parse();
      
      //1. Parse parameters for a tree
      string file = tmfp.getParameterFile("Tree");
      if (verbose){
	cout << "Reading parameters for tree from: " << file << endl;
      }
      
      lex.scan(file);

      //name of the parameter
      Token name = lex.getToken();
      while (name.getType() != ENDFILE){
	//value of the parameter (as string)
	Token value = lex.getToken();
	LGMdouble p = static_cast<LGMdouble>(atof(value.getValue().c_str()));
	if (verbose){
	  cout << "Parameter: " << name.getValue() << " = " << p << endl;
	}
	//Check if this is known parameter
	//First, if it is a parameter configuring tree segment
	//Check if found, then install
	if ((itpd = maplgmpd.find(name.getValue())) != maplgmpd.end()){
	  SetValue(tree,(*itpd).second,p);
	}
	//Second, could be transit parameter, e.g., intitial value for lambda
	else if ((ittd = maplgmtd.find(name.getValue())) != maplgmtd.end()){  
	  SetValue(tree,(*ittd).second,p);
	}
	//Unkonown, parameter (check MapLGMPD and MapLGMTD listings in TreeFriend.cc)
	else{
	  if (verbose){
	    cerr << "Unknown parameter for tree: " << name.getValue() << endl;
	  }
	}
	//next parameter
	name = lex.getToken();
      }
      
      //2. Configure the firmament
      file = tmfp.getParameterFile("Firmament");
      if (verbose){
	cout << "Reading Configuration for Firmament from: " << file << endl;
      }

      GetFirmament(tree).configure(file);

      if (verbose){
	cout << "Azimuths: "  << GetFirmament(tree). getNoOfAzimuths() 
	     << " Inclinations: " << GetFirmament(tree). getNoOfInclinations() << endl;
	cout << "Radiation (Ball sensor): " << GetFirmament(tree). diffuseBallSensor()
	     << " Radiation (Plane sensor): " << GetFirmament(tree). diffusePlaneSensor()
	     << endl;
	
	cout << "Radiation sector by sector:"  << endl;
	int r = GetFirmament(tree).numberOfRegions();
	vector<double> d(3);
	for (int i = 0; i < r; i++){
	  MJ rad = GetFirmament(tree).diffuseRegionRadiationSum(i,d);
	  cout << d[0] << ":" <<  d[1] << ":" <<  d[2 ] << ":" << rad << endl;
	}
      }
      //3. Parse functions for a tree
      //1.
      file = tmfp.getFunctionFile("LGMAL");
      if (verbose){
	cout << "Configuring functions" << endl;
	cout << "Reading LGMAL from: " << file << endl;
      }
      //2.
      file = tmfp.getFunctionFile("LGMFM");
      if (verbose){
	cout << "Reading LGMFM from: " << file << endl;
      }
      tree.tf.fm.install(file);
      //3.
      file = tmfp.getFunctionFile("LGMIP");
      if (verbose){
	cout << "Reading LGMIP from: " << file << endl;
      }
      tree.tf.fm.install(file);
      //4.
      file = tmfp.getFunctionFile("LGMLONB");
      if (verbose){
	cout << "Reading LGMLONB from: " << file << endl;
      }
      tree.tf.fm.install(file);
      //5.
      file = tmfp.getFunctionFile("LGMNB");
      if (verbose){
	cout << "Reading LGMNB from: " << file << endl;
      }
      tree.tf.nb.install(file);
      //6.
      file = tmfp.getFunctionFile("LGMVI");
      if (verbose){
	cout << "Reading LGMVI from: " << file << endl;
      }
      tree.tf.nb.install(file);
      //7.
      file = tmfp.getFunctionFile("LGMVIONB");
      if (verbose){
	cout << "Reading LGMVIONB from: " << file << endl;
      }
      tree.tf.ip.install(file);
    }
}//closing namespace Lignum

#endif
