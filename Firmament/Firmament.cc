#include <Firmament.h>
//#include <mathsym.h>

namespace sky{

//The flux of diffuse radiation coming from the sky is accomplished
//according to J. Ross 1981 The radiation regime and architecture of plant
//stands, Dr W. Junk Publishers Eq. II.2.4a which defines the zonal brightness
//of the standard overcast sky. The brigthness is thus changing only with inclination
//inc according to the following equation:
// d(inc)=(6/7)*(1 + 2 * sin(inc)) / (2*PI)
//This formula is scaled so that the irradiance caused by it on the horizontal plane
//equals one, that is,
// integral(from 0, to PI/2) d(x) * sin(x) * 2PI*cos(x)*dx = 1
//(2PI*cos(x) comes from geometry, da = 2PI*cos(inc) on the surface of the unit sphere)
//If we know the irradiance on the horizontal plane, Q, we have thus the brightness of
//the sky as Q * d(inc)
//
//Constructor, define the division of the sky into sectors (see Firmament.h for
//the principle of division) and calculate the diffuse radiation coming from each sector.
//The diffuse radiation is initialize so that its irradiance on hozontal pla is
//equal to 1200 MJ/m2 . This corresponds to the radiation sum (direct+diffuse) during
//the growing period in southern Finland (Stenberg).
//Update also other radiation variables.
//Sun's radiation is initialized as 0.


Firmament::Firmament(int no_incl, int no_azim)
{
  num_of_incl = no_incl;
  num_of_azim =  no_azim;
  if(num_of_incl < 1) num_of_incl = 1;
  if(num_of_azim < 2) num_of_azim = 2;
  numOfSectors =  num_of_incl *  num_of_azim + 1;

  //The radiation components are set as follows:
  //diffuseRadPlane = 1200 MJ(PAR)/m2,   equal to radition sum (direct+diffuse) during
  //growing period in Finland according to Stenberg 1996
  //directRadPlane = 0

  diffuseRadPlane = 1200.0;
  directRadPlane = 0.0;
  diffuseRadBall = 0.0;
  sunPosition.resize(3);
  sunPosition[0] =  sunPosition[1] =  sunPosition[2] = 0.0;
  
                  
  //Construct the division of the sky (see Firmament.h)

  //The zenith segment of the sphere is as large (= 2*PI/numOfSectors)
  //as the other sectors; its width (angle)
  thetZ = acos( 1.0 - 1.0 / (double)numOfSectors );

  deltaIncl = (PI_VALUE / 2.0 - thetZ)/ (double) num_of_incl;
  halfDeltaIncl = deltaIncl / 2.0;

  //Set the right dimensions for vectors storing midpoints of inclination zones
  //and number of azimuth divisions in each inclination zone
  inclinations.resize(num_of_incl);
  azimDivisions.resize(num_of_incl);

  int i, im;

  for(i = 0; i < num_of_incl; i++)
    inclinations[i] = (double)i * deltaIncl + halfDeltaIncl;

  //Set up vector for storing areas of sectors in inclination zones
  //for getting equal area sectors 
  double *area, maxA;
  area = new double[num_of_incl];

  areasByInclination.resize(num_of_incl);

  //Allocate sectors to zones trying to end up with as constant sector
  //area (=solid angle) as possible
  //Start off with two sectors in each zone

  for(i = 0; i < num_of_incl; i++) {
    azimDivisions[i] = 2;
    area[i] = sin(inclinations[i]+halfDeltaIncl) - sin(inclinations[i]-halfDeltaIncl);
    area[i] *= 2.0 * PI_VALUE / (double)azimDivisions[i];
  }

  int j;
  i = numOfSectors - 2 * num_of_incl - 1;
  while(i > 0) {
    maxA = 0.0;
    for(j = 0; j < num_of_incl; j++)
      if(area[j] > maxA) {
	maxA = area[j];
	im = j;
      }
    area[im] *= (double)azimDivisions[im] / (double)(azimDivisions[im] + 1);
    areasByInclination[im] = area[im];
    azimDivisions[im] += 1;
    i--;
  }

    //Evaluate the maximum number of sectors in the inclination zones and
    //adjust dimensions of matrices holding azimuths and (diffuse) radiant intensity
    //of sectors accordingly
  im = 0;
    for(i = 0; i < num_of_incl; i++)
      if(im < azimDivisions[i]) im = azimDivisions[i];

    zoneAzims.resize(num_of_incl, im);
    diffuseRad.resize(num_of_incl, im);

    //Update azimuths and radiant intensity of sectors
    for(i = 0; i < num_of_incl; i++)
      for(j = 0; j < azimDivisions[i]; j++) {
	zoneAzims[i][j] = ((double)j + 0.5) * 2.0 * PI_VALUE/(double)azimDivisions[i];
	diffuseRad[i][j] = diffuseRadPlane * 
	                   (6.0 * (1.0 + 2.0*sin(inclinations[i]))/7.0) *
			  (sin(inclinations[i]+halfDeltaIncl)-
			 sin(inclinations[i]-halfDeltaIncl))/(double)azimDivisions[i];
      }

    //Diffuse radiation from zenith sector
    diffuseRadZenith = diffuseRadPlane *(6.0 * (1.0 + 2.0)/7.0) *
			  (1 - cos(thetZ));
    // Note: thetZ is the radial _width_ of the zenith segment
    
    //Discretation of the sky may cause that the radiation sum of the sectors
    //is not 100% same as given by the theory. It is corrected here.
    //Update also ball sensor reading
    double rsum = 0.0;
    for(i = 0; i < num_of_incl; i++)
      for(j = 0; j < azimDivisions[i]; j++) 
	rsum += sin( inclinations[i] ) * diffuseRad[i][j];

    rsum += diffuseRadZenith;

    
    diffuseRadBall = 0.0;
    for(i = 0; i < num_of_incl; i++)
      for(j = 0; j < azimDivisions[i]; j++) {
	diffuseRad[i][j] *= diffuseRadPlane / rsum;
	diffuseRadBall += diffuseRad[i][j];
      }


    //store here the inclination and azimuth indexes as a function of
    //number of the sector

    inclinationIndex.resize(numOfSectors);
    azimuthIndex.resize(numOfSectors);
    int nSector = 0;
    for(i = 0; i < num_of_incl; i++)
      for(j = 0; j < azimDivisions[i]; j++) {
	inclinationIndex[nSector] = i;
	azimuthIndex[nSector] = j;
	nSector++;
      }

    //store the components of direction vectors of sectors (midpoint)
    dir_x.resize(numOfSectors);
    dir_y.resize(numOfSectors);
    dir_z.resize(numOfSectors);
    int nIncl, nAzim;
    nSector = 0;
    for(i = 0; i < num_of_incl; i++)
      for(j = 0; j < azimDivisions[i]; j++) {
	nIncl  = inclinationIndex[nSector];
	nAzim = azimuthIndex[nSector];
	dir_z[nSector] = sin(inclinations[nIncl]);
	dir_x[nSector] = cos(inclinations[nIncl]) * cos(zoneAzims[nIncl][nAzim]);
	dir_y[nSector] = cos(inclinations[nIncl]) * sin(zoneAzims[nIncl][nAzim]);
	nSector++;
      }

    delete[] area;
}


//Input: vector 'direction' (length of 1) pointing to a point in the upper hemisphere.
//	 x-axis is pointing to south, y-axis to east and z -axis to zenith
//Return: Diffuse radiation intensity coming  from the area of 
//        the upper hemisphere pointed by
//	  direction. If direction is pointing to lower hemisphere,
//	  returns 0.0


MJ Firmament::diffuseRadiationSum(const vector<double>& direction)
{

  double rz, rx,ry;
  double theta, fii, cosTheta;


  if( (rz = direction[2]) < 0.0 ) return 0.0;

  rx = direction[0];
  ry = direction[1];

  //Change the direction vector (rx, ry, rz) to inclination and azimuth
  theta = asin( rz );
  if(theta > PI_VALUE / 2.0) theta = PI_VALUE / 2.0;
  cosTheta = cos( theta );


  if((rx > R_EPSILON || -rx > R_EPSILON) && cosTheta > R_EPSILON)
    if(ry < 0.0)
      fii = 2.0 * PI_VALUE - acos( rx / cosTheta );
    else
      fii = acos( rx / cosTheta );
  else if(ry > 0.0)
    fii = PI_VALUE / 2.0; 
  else
    fii = 3.0 * PI_VALUE / 4.0; 

  int ii, ia;

  //If ic == num_of_incl => zenith sector

  for(ii = 0; ii < num_of_incl; ii++)
    if(theta <= inclinations[ii] + halfDeltaIncl) break;

  if(ii == num_of_incl) 
    return diffuseRadZenith;

  double halfDeltaAzim = PI_VALUE / (double)azimDivisions[ii];
  for(ia = 0; ia < azimDivisions[ii]; ia++)
    if(fii <= zoneAzims[ii][ia] + halfDeltaAzim) break;

  if(ia ==  azimDivisions[ii]) ia = 0;

  return diffuseRad[ii][ia];

}

MJ Firmament::diffuseRegionRadiationSum(int n, vector<double>& direction)

// Input: # of region
// Return: Intensity of diffuse radiation from the region and
// vector 'direction' (length of 1) pointing to the midpoint of the region.
//	 x-axis is pointing to south, y-axis to east and z -axis to zenith.
//	 If n < 0 or n > num_of_incl*num_of_azim - 1  returns -1.0

{
  if(n < 0 || n > numOfSectors - 1) return (MJ) -1.0;
           
// Numbering: azimuth is changing faster. If, for example, n < azimDivisions[0]
// nIncl = 0 and nAzim = n, aso.
// if n == numOfSectors - 1 => zenith

  if(n ==  numOfSectors - 1) {             // zenith
    direction[0] = direction[1] = 0.0;
    direction[2] = 1.0;
    return  diffuseRadZenith;
  }

  int nIncl = inclinationIndex[n];
  int nAzim = azimuthIndex[n];

  direction[2] = dir_z[n];
  direction[0] = dir_x[n];
  direction[1] = dir_y[n];

  return diffuseRad[nIncl][nAzim];

}


MJ Firmament::diffuseHalfRegionRadiationSum(int n, vector<double>& direction)

// As regionRadiationSum but regions having azimuth between
// 0 and PI radiate nothing and for these halfRegionRadiationSum = 0

// Input: # of region
// Return: Radiation sum (direct & diffuse) from the region and
// vector 'direction' (length of 1) pointing to the midpoint of the region.
//       x-axis is pointing to south, y-axis to east and z -axis to zenith.
//       If n < 0 or n > num_of_incl*num_of_azim - 1  returns -1.0
{
  if(n < 0 || n > numOfSectors - 1) return (MJ) -1.0;
           
// Numbering: azimuth is changing faster. If, for example, n < azimDivisions[0]
// nIncl = 0 and nAzim = n, aso.
// if n == numOfSectors - 1 => zenith

  if(n ==  numOfSectors - 1) {             // zenith
    direction[0] = direction[1] = 0.0;
    direction[2] = 1.0;
    return  diffuseRadZenith;
  }

  int nIncl = inclinationIndex[n];
  int nAzim = azimuthIndex[n];

  direction[2] = dir_z[n];
  direction[0] = dir_x[n];
  direction[1] = dir_y[n];


  if(zoneAzims[nIncl][nAzim] < (PI_VALUE+0.5) &&
     zoneAzims[nIncl][nAzim] > 0.5)
        return (MJ) 0.0;
  else
        return diffuseRad[nIncl][nAzim];

}




MJ Firmament::diffuseForestRegionRadiationSum(int n, float z, float x, float la,
					      float ke, float H, float Hc,
					      vector<double>& direction)

   // This method calculates the radiation reaching a segment  in a
   // tree that is growing in a stand among indentical trees (dens trees/ha).
   // The idea here is that the tree grows in a "hole" in the stand. The "hole" is
   // a circular cylinder, the gross-sectional area of which is 10000/dens m2 and height
   // equal to tree height. Outside this "hole" the foliage area (calculated with
   // the aid of tree's leaf area and dens) is evenly distributed in the crown volume
   // (leaf area density) that is between top height and the height of the crown base.
   // The shading caused by the surrounding stand depends on the distance light beam
   // travels in the stand volume on its way from a point in the sky to the segment:
   // travelled distance * leaf area density * extinction coefficient
   // ( extinction coefficient = 0.14 for Scots pine)
   // The radiation coming from a point in the sky (sector) is obtained from
   // method Firmament::regionRadiationSum(int n, vector<double>& direction).
   //
   // Both height of the segment and its distance from the tree stem affect the path
   // lenght in the surrounding canopy. The path length of the beam inside the
   // canopy depends on the height it hits the mantle of the "hole".
   // Since the the segment is not in the middle of the (bottom) circle of the "hole",
   // the distance the beam travels inside the "hole" and consequently the height
   // at which it hits the wall depends on the direction of the beam. This effect is
   // treated here in an average manner. For all azimuthal directions of the coming
   // beam the mean distance from a point (inside the circle) to the circumference of
   // it is used in calculations. It seems that as an fairly accurate approximation
   // mean distance = r*(1 - 0.35*(x/r)^2.5), where r is the radius of the circle and
   // x is the distance of the point from center of the circle (0 <= x <= r).

   // Obs. density is read from file (if exists) "density.fun"

{
  // When this method is called first time it reads density (dens, trees/ha) from the
  // file density.fun. If this file does not exist default density 1 tree/ha is used.

  static bool first_time = true;
  static float dens = 1.0;

  if(first_time) {
    first_time = false;
    ifstream densfun("density.fun");
    if(densfun) {
      densfun >> dens;
      if(dens < 1.0) dens = 1.0;
      if(dens > 100000.0) dens = 100000.0;
      densfun.close();
    }
    else 
      dens = 1.0;
  }

  //Check for suitable segment number

  if(n < 0 || n > numOfSectors - 1) return (MJ) -1.0;

  // Get first unshaded radiation coming from the sector

  float Qunshaded = diffuseRegionRadiationSum(n, direction);

  // Inclination angle of the direction (from horizon),
  // length of direction = 1, hence z coordinate = tan(alpha)

  float tan_alpha; 
  float length_of_direction = pow((pow(direction[0],2)+pow(direction[1],2)),0.5);
  if(length_of_direction > 1.0e-10) 
    tan_alpha = direction[2] / length_of_direction;
  else
    tan_alpha = 1.0e10; 

  // Area (m2) occupied by one tree = 10000/dens => radius of the opening that is
  // occupied by one tree

  float r_tree = (float) sqrt((double) ((10000.0/dens) / (float)PI_VALUE));

  // The beam hits the mantle of the cylinder that is occupied by the tree at height Hh,
  // the distance of the point from the stem is considered too,
  // as mean for different directions, see explanation at the beginning
  // Obs the segment cannot be outside the cylinder

  float xcheck = minimum(x, r_tree);
  float avdist = r_tree * (1.0 - 0.35 * (float)pow((double)(xcheck/r_tree), 2.5));
  float Hh = z + tan_alpha * avdist;

  // If Hh < Hc the beam goes through the whole canopy, otherwise not

  if(Hh < Hc)  Hh = Hc;

  float leaf_dens = dens * la / 10000.0 / (H - Hc);

  float distance, shading;

  if(Hh < H)
    distance = (H - Hh) / (float) sin(atan((double)tan_alpha));
  else
    distance = 0.0;

  shading = (float) exp((double)(-ke * distance * leaf_dens));

  return shading * Qunshaded;
}

void Firmament:: setDiffuseRadiation(const double rad)

// Input: Diffuse radiation falling on a horizontal plane
// Return: void
// Sets the radiation of sectors to correspond input.
// Updates also diffuseRadPlane, diffuseRadBall, diffuseRadZenith  -variables

{

  int i, j;
  for(i = 0; i < num_of_incl; i++)
    for(j = 0; j < azimDivisions[i]; j++) {
      diffuseRad[i][j] *= rad / diffuseRadPlane;
    }

  diffuseRadZenith *= rad / diffuseRadPlane;

  diffuseRadBall *=  rad / diffuseRadPlane;
  diffuseRadPlane = rad;

}

void Firmament::setSunPosition(const vector<double>& v)

// Input: Vector pointing to sun
// Return: void
// Sets the the vector of Firmament that points to the sun

{
  int i;
  for(i = 0; i < 3; i++)
    sunPosition[i] = v[i];

}

MJ Firmament::directRadiation(vector<double>& direction)

  // INPUT: NONE
  // OUTPUT: intensity of the direct (sun) radiation on the plane perpendicular
  //         to the dirction of the sun (return)
  //         direction of the sun (in vector direction)
  //
  // Obs, sunPosition[2] = sin(iclination)
{
  int i;
  for(i = 0; i < 3; i++)
    direction[i] = sunPosition[i];

   if(sunPosition[2] <= 0.0) return 0.0;

  return directRadPlane / sunPosition[2];

}


MJ Firmament::directHalfRegionRadiationSum(vector<double>& direction)


  // INPUT: NONE
  // OUTPUT: intensity of the direct (sun) radiation on the plane perpendicular
  //         to the dirction of the sun (return)
  //         direction of the sun (in vector direction)
  //
  // Obs, sunPosition[2] = sin(iclination)
{
  int i;
  for(i = 0; i < 3; i++)
    direction[i] = sunPosition[i];

   if(sunPosition[2] <= 0.0) return 0.0;


  //Change the direction vector (rx, ry, rz) to inclination and azimuth
  double theta = asin( sunPosition[2] );
  if(theta > PI_VALUE / 2.0) theta = PI_VALUE / 2.0;
  double cosTheta = cos( theta );

  double rx = sunPosition[0];
  double ry = sunPosition[1];
  double fii;
  if((rx > R_EPSILON || -rx > R_EPSILON) && cosTheta > R_EPSILON)
    if(ry < 0.0)
      fii = 2.0 * PI_VALUE - acos( rx / cosTheta );
    else
      fii = acos( rx / cosTheta );
  else if(ry > 0.0)
    fii = PI_VALUE / 2.0; 
  else
    fii = 3.0 * PI_VALUE / 4.0; 

  if(fii< (PI_VALUE+0.5) &&
     fii > 0.5)
        return (MJ) 0.0;
  else
        return directRadPlane / sunPosition[2];

}

double Firmament::getInclination(int n)
{
  if(n < 0 || n > numOfSectors - 1) return -1.0;
           
// Numbering: azimuth is changing faster. If, for example, n < azimDivisions[0]
// nIncl = 0 and nAzim = n, aso.
// if n == numOfSectors - 1 => zenith

  if(n ==  numOfSectors - 1) {             // zenith
       return  PI_VALUE / 2.0;
  }

  int nIncl = inclinationIndex[n];

  return inclinations[nIncl];
}  

double Firmament::getAzimuth(int n)
{
  if(n < 0 || n > numOfSectors - 1) return -1.0;
           
// Numbering: azimuth is changing faster. If, for example, n < azimDivisions[0]
// nIncl = 0 and nAzim = n, aso.
// if n == numOfSectors - 1 => zenith

  if(n ==  numOfSectors - 1) {             // zenith
       return  0.0;
  }

  int nIncl = inclinationIndex[n];
  int nAzim = azimuthIndex[n];

  return zoneAzims[nIncl][nAzim];
}  



#ifdef  FIRMAMENT
#define LINE_LENGTH 255
int  main(int argc, char* argv[])
{
  double alphaA, betaA, alphaB, betaB;
  double Rs=0.5, Rw = 0.1, L = 5.0;

  vector<double> a(3);
  vector<double> b(3);
  vector<double> r0(3);
  vector<double> rs(3);
  char buffer[LINE_LENGTH], c;

  Firmament firmament(9, 24);

  ifstream file("shatest.run");
  if(!file)       {
    cerr << "Cannot open " << "shatest.run" << " !\n";
    return 0;
  }

  file.getline(buffer, LINE_LENGTH, '\n');
  file >> Rs >> Rw >> L;	file.get(buffer[0]);
  file.getline(buffer, LINE_LENGTH, '\n');
  file >> rs[0] >> rs[1] >> rs[2] >> alphaA >> betaA; file.get(c);
  file.getline(buffer, LINE_LENGTH, '\n');
  file >> r0[0] >> r0[1] >> r0[2] >> alphaB >> betaB; file.get(c);

  file.close();

  double PI = PI_VALUE;

  // alpha = vektorin kiertokulma xy-tasossa  (vektorit a ja b)
  // beta = vektorin ja xy-tason v„linen kulma (vektorit a ja b)

  alphaA *= PI / 180.0;	betaA *= PI / 180.0;
  alphaB *= PI / 180.0;	betaB *= PI / 180.0;
  a[0] = cos( betaA ) * cos( alphaA );
  a[1] = cos( betaA ) * sin( alphaA );
  a[2] = sin( betaA );
  b[0] = cos( betaB ) * cos( alphaB );
  b[1] = cos( betaB ) * sin( alphaB );
  b[2] = sin( betaB );
  file.close();


  double sum = firmament.diffuseRadiationSum(a);

  cout << "diffuseRadiationSum(a): " << sum << endl;
  sum = firmament.diffuseRegionRadiationSum(215, a);

  cout << "diffuseRegionRadiationSum(215): " << sum << endl;
  int nn = firmament.numberOfRegions();

  cout << "nn: " << nn << endl;

  sum = firmament.diffusePlaneSensor();
  cout << "plane: " << sum << endl;

  sum = firmament.diffuseBallSensor();
  cout << "ball: " << sum << endl;

  sum = firmament.diffuseHalfRegionRadiationSum(0, a);
  cout << "halfregion(0) = " << sum << endl;

  sum = firmament.diffuseHalfRegionRadiationSum(11, a);
  cout << "halfregion(11) = " << sum << endl;

  sum = firmament.diffuseHalfRegionRadiationSum(12, a);
  cout << "halfregion(12) = " << sum << endl;

  sum = firmament.diffuseHalfRegionRadiationSum(215, a);
  cout << "halfregion(215) = " << sum << endl;

  sum = firmament.diffuseForestRegionRadiationSum(1, 0.1, 0.0,
                                       1.4, 0.14, 2.0, 0.5, a);
  cout << "forestRegion(1) = " << sum << endl;


  cout << "directRadiation: " << firmament.directRadiation(a) << endl;

  a[0] = 0.70711; a[1] = 0; a[2] = 0.70711;
  firmament.setSunPosition(a);
  firmament.setDirectRadiation(100.0);

  cout << "directRadiation: " << firmament.directRadiation(a) << endl;
  cout << "direction: " << a[0] << a[1] << a[2] << endl;

  cout << "directHalf:" << firmament.directHalfRegionRadiationSum(a) << endl;

  cout << "\n Diffuse Radiation -> 120" << endl << endl;
  firmament.setDiffuseRadiation( 120.0 );
   sum = firmament.diffuseRadiationSum(a);

  cout << "diffuseRadiationSum(a): " << sum << endl;
  sum = firmament.diffuseRegionRadiationSum(215, a);

  cout << "diffuseRegionRadiationSum(215): " << sum << endl;
  nn = firmament.numberOfRegions();

  cout << "nn: " << nn << endl;

  sum = firmament.diffusePlaneSensor();
  cout << "plane: " << sum << endl;

  sum = firmament.diffuseBallSensor();
  cout << "ball: " << sum << endl;


  cout << "diffuse sky: " << endl;
  
  firmament.outDiff();

  cout << "Azimuths: " << endl;

  firmament.outAz();
  
  cout << "\nDiffuse Radiation back -> 1200 MJ/m2\n";
  firmament.setDiffuseRadiation( 1200.0 );

  cout << endl << " Radiation sector by sector\n" <<
    " no.    incl    azim    radiation\n";
  int i;
  for (i=0; i < firmament.numberOfRegions(); i++)
    cout << i << " " << firmament.getInclination(i) <<
      " " << firmament.getAzimuth(i) << " " <<
      firmament.diffuseRegionRadiationSum(i, a) << "\n";

  cout << endl << " Inclination and azimuth indexes by sector number" << endl;
  cout << " sector " << " incl index " << " azim index" << endl;
  for (i=0; i < firmament.numberOfRegions(); i++)
    cout << i << " " << firmament.getInclinationIndex(i) << " " <<
      firmament.getAzimuthIndex(i) << endl;

  cout << endl << " Area of sector in inclination class" << endl;
  cout << " n   " << "Area (,steradians?)" << endl;
  for(i = 0; i < firmament.getNoOfInclinations() - 1; i++)
    cout << " " << i << "  " << firmament.getSectorArea(i) << endl;

  return 0;
}


#endif

}//closing namespace sky




