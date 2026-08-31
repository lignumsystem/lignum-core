/// \file VoxelSpace.h
/// \brief  Voxel space 
/// \todo File content needs improved documentation and  clean-up 
#ifndef VOXELSPACE_H
#define VOXELSPACE_H

#include <vector>
#include <utility>
#include <climits>
#include <Lignum.h>
#include <TMatrix3D.h>
#include <VoxelBox.h>
#include <VOBookKeeper.h>
#include <ForestDescriptor.h>
#include <Firmament.h>
#include <Nearby.h>

///\brief Implementation of 3D VoxelSpace for radiation calculation
///\todo Documentation for classes  and functions in voxelspace
namespace voxelspace {

struct VoxelMovement
{
    VoxelMovement():x(0),y(0),z(0),l(0.0),af(0.0),tau(0.0),
        STAR_mean(0.0),n_segs_real(0.0),mean_direction(PositionVector(0,0,1)),
        wood_area(0.0),starDir(7,0.0){}
    int x;//box indices
    int y;
    int z;
    LGMdouble l;//Path length in the box
    LGMdouble af;//Foliage area in the box
    LGMdouble tau;//the  extinction  caused  by  objects  in  the  box
    //(pairwise comparison)
    LGMdouble STAR_mean;
    LGMdouble n_segs_real;
    PositionVector  mean_direction;
    LGMdouble wood_area; //Surface area of segments
    //Area of those that do not have needles in conifers
    vector<LGMdouble>  starDir; // Vector to record STAR values in all the inclination angles.
};

//The value for 'kb'  (angle of incidence, c.f.star mean for coniferous)
//for broadleaf
enum VAD {LGAkb};

//Exception thrown  (instead of assert) in getVoxelBox  if the point
//is not in the VoxelSpace
class OutOfVoxelSpaceException{
public:
    OutOfVoxelSpaceException(const Point& p1, const Point p2)
        :box(p1),p(p2){}
    Point getPoint()const{return p;}
    Point getBox()const{return box;}
private:
    Point box;//The voxel box indices where the segment would belong to
    Point p;//The global point of the segment causing the excepetion
};

  class VoxelSpace
  {
    //VoxelBox::update Value  accesses private data  members--> friend
    //declaration needed due to lack of access methods/functions
    friend class VoxelBox;
    friend class InsertHwEllipse;

    ///\brief Insert coniferous tree segment
    ///
    ///Insert coniferous tree segment into VoxelSpace without wooden poart
    ///\tparam TS Tree segment
    ///\tparam BUD Bud
    ///\param vs VoxelSpace
    ///\param tree Lignum tree
    ///\param num_parts Divide the coniferous tree segment into \p num_parts and insert data piecewise
    ///\note Final step VoxelSpace::updateBoxValues() is \e not called
    ///\sa DumpCfTreeFunctor
    ///\todo Merge with DumpCfTree(VoxelSpace &vs, Tree<TS, BUD> &tree,int num_parts, bool wood),
    ///      then remove from use.
    template <class TS,class BUD>
    friend void DumpCfTree(VoxelSpace &vs, Tree<TS, BUD> &tree,int num_parts);

    ///\brief Insert coniferous tree segment into VoxelSpace
    ///Insert coniferous tree segment into VoxelSpace with wooden part
    ///\tparam TS Tree segment
    ///\tparam BUD Bud
    ///\param vs VoxelSpace
    ///\param tree Lignum tree
    ///\param num_parts Divide the coniferous tree segment into \p num_parts and insert data piecewise
    ///\param wood \e true: insert wooden part, \e false: omit wooden part
    ///\post VoxelSpace::updateBoxValues() \e is called
    ///\post Wooden part insertion only if no foliage
    ///\sa DumpCfTreeFunctor
    ///\todo  \htmlonly <span style="color:orange;">&#9679;</span>\endhtmlonly Merge with DumpCfTree(VoxelSpace &vs, Tree<TS, BUD> &tree,int num_parts):
    ///    - Make call to VoxelSpace::updateBoxValues() behind boolean flag
    ///    - Remove woody part insertion depenency on foliage mass.
    ///    - Remove  DumpCfTree(VoxelSpace &vs, Tree<TS, BUD> &tree,int num_parts) from use.
    template <class TS,class BUD>
    friend void DumpCfTree(VoxelSpace &vs, Tree<TS, BUD> &tree,int num_parts, bool wood);

    ///\brief Insert coniferous segment to a voxel.
    ///
    ///Construct  VoxelObject by extracting geometric data from the segment.
    ///\note This function is meant to copy a single tree in origo (0,0,0) to many locations
    ///      in a voxel space. See UKScotsPine project.
    ///\tparam TS Tree segment
    ///\param s Voxel space
    ///\param ts Coniferous tree segment 
    ///\param d Direction to the new location
    ///\param t Distance to the new location
    ///\param beam_start Relative position  on the segment [0:1] where  the light beam
    ///                  starts. Needed to avoid comparison of a segment with itself.
    ///\param parts Number of parts a segment will be divived into
    ///\pre \f$ |d|=1 \f$
    ///\sa voxelspace::InsertVoxelObjects 
    template <class TS>
    friend void InsertCfVoxelObject(VoxelSpace& s, const TS& ts,
                                    const PositionVector& d,
                                    double t,double beam_start,
                                    int parts);
    //\brief Broadleaved trees with ellipse leaf model
    template <class TS, class BUD,class S>
    friend void InsertHwVoxelObject(VoxelSpace& s, HwTreeSegment<TS,BUD,S>& ts,
                                    const PositionVector& d,
                                    double t,int parts);
    ///\brief Insert tree segment into voxel
    ///
    ///Insertion is based on  tree segment midpoint.
    ///\tparam TS Tree segment
    ///\param s Voxel space
    ///\param ts Tree segment
    template <class TS>
    friend void InsertTreeSegmentAsVoxelObject(VoxelSpace& s, TS& ts);

    template <class TS,class BUD>
    friend void SetCfTreeQabs(VoxelSpace &s, Tree<TS, BUD> &tree,int num_parts);

    template <class TS,class BUD>
    friend void DumpHwTree(VoxelSpace &s, Tree<TS, BUD> &ts);

    template <class TS, class BUD, class S>
    friend void DumpHwTreeSegment(VoxelSpace &s,
                                  HwTreeSegment<TS, BUD, S> &ts);

    template <class TS,class BUD>
    friend void SetHwTreeQabs(VoxelSpace &s, Tree<TS, BUD> &tree);

    template <class TS, class BUD, class SHAPE>
    friend void SetHwTreeSegmentQabs(VoxelSpace &space,
                                     HwTreeSegment<TS,BUD,SHAPE>& ts);

    friend LGMdouble GetValue(const VoxelSpace& s,VAD LGAkb);
    friend void PrintVoxelObjectLocations(const VoxelSpace& s,const
                                          string& fname);

    friend void PrintBoxCfData(const VoxelSpace& s,const
                               string& fname, bool empty);

    
  public:
    VoxelSpace(Point corner1, Point corner2,
               int xn, int yn, int zn,
               Firmament& f);
    //constructor defining  corner points,  voxel box size,  number of
    //boxes (size of the matrix), the sky.and the k_b for broad leaf
    VoxelSpace(Point corner1, Point corner2,
               double xsize, double ysize, double zsize,
               int xn, int yn, int zn,
               Firmament& f, LGMdouble k_b=0.50);

    //constructor on the basis of lower left corner,  voxel box size, and number of
    //boxes (size of the matrix) & the sky
    VoxelSpace(Point cll, double xsize, double ysize, double zsize,
	       int xn, int yn, int zn, Firmament &f);
    
    void reset();
    void resetQinQabs();
    void resetOccupied();       //set variable occupied in VoxelBoxes to false
    void resetOccupiedTry();    //set variable occupied_try in VoxelBoxes to false

    void resize(int nX, int nY, int nZ); //change number of VoxelBoxes
    //in x, y, and
    //z-directions. The extent
    //of VoxelSpace does not
    //change.Contents are lost.
    void resize(LGMdouble lX, LGMdouble lY,
                LGMdouble lZ);           //Change sizes of VoxelBoxes
    //in x, y, and
    //z-directions. The extent of
    //VoxelSpace does not change
    //(only by size of the
    //VoxelBox). Contents are lost.

    void resize(LGMdouble lX, LGMdouble lY, LGMdouble lZ,int nX, int nY,
                int nZ );           //Change both number and size of
    //VoxelBoxes. The extent of
    //VoxelSpace changes. Contents are
    //lost.

    void resize(const Point lower_left, const Point upper_right);
    //Change physical dimensions of
    // voxelspace (i.e. extent, i.e. opposite corners)
    // The number of VoxelBoxes may change
    //Contents are lost (because TMatrix3D resize
    //destroys contents)

    void move(const Point corner1); //Move Voxelspace so that its
    //lower left corner is set at
    //corner1
    VOBookKeeper& getBookKeeper(){return book_keeper;}
    ForestDescriptor& getForestDescriptor(){return forest_descriptor;}
    double getArea()const{return (Xn*Xbox)*(Yn*Ybox);}
    Point getLowerLeftCorner()const{return corner1;}
    Point getUpperRightCorner()const{return corner2;}
    int getNumberOfBoxes()const{ return Xn*Yn*Zn; }
    int getNumberOfFilledBoxes()const;
    int getNumberOfTreeSegments()const;
    LGMdouble getBoxVolume()const{ return Xbox*Ybox*Zbox; }
    LGMdouble getXSideLength()const{ return Xbox; }
    LGMdouble getYSideLength()const{ return Ybox; }
    LGMdouble getZSideLength()const{ return Zbox; }
    int getNoBoxX()const{return Xn;}
    int getNoBoxY()const{return Yn;}
    int getNoBoxZ()const{return Zn;}
    LGMdouble getQabs()const;
    LGMdouble getQin()const;
    pair<double,double> getMinMaxNeedleMass()const;
    // returns the total foliage mass of the tree segments dumped into
    // the VoxelSpace
    LGMdouble getFoliageMass(void);
    const TMatrix3D<VoxelBox>& getVoxelBoxes()const{
      return voxboxes;
    }
    VoxelBox& getVoxelBox(const Point& p);
    //Given a point 'p' in global coordinate system, return a point in
    //VoxelSpace coordinate system (=indexes)
    //returns the indexes in a vector: v[0] = Xindex, v[1] = Yindex, v[2] = Zindex
    vector<int> getBoxIndexes(const Point& p);
    //Returns indexes of boxes that are within distance dist from point p.
    //(May work even if p is outside VoxelSpace but be careful).
    //Within distance = if any point of box may be closer than dist.
    //Indexes in a vector: v[0] = Xindex, v[1] = Yindex, v[2] = Zindex
    //If permissive = true  returns the VoxelBoxes in the big box, that is
    // p +- dist along all coordinate axes. If permissive = false,
    //it is checked whether any corner of the VoxelBox
    //is within distance dist, and if not, box is not included. This
    //may discard some boxes in the corners of the "big" box but may fail
    //to notice that part of the ball with radius dist around p intersects the
    //VoxelBox.
    list<vector<int> > getBoxesAroundPoint(const Point& p, const double& dist,
                                           const bool permissive = true);
    ///\brief Calculate the light beam route through the  voxel space.
    ///
    ///Implementation of Amanatides and Woo (1987), A fast voxel traversal algorithm for
    ///ray casting. This implementation integrates radiation attenuation tracking and data collection.
    ///\param vec [out] The route, includes path lengths and extincion in each voxel
    ///\param p0  The light beam start point in the voxel
    ///\param dir The light beam direction
    ///\param K   The directional light extinction coefficient (Oker-Blom and Smolander, 1988)
    ///\param pairwise \e true: Use the voxel objects in voxels to calculate radiation attenuation<br>
    ///                \e false: Calculate the path lengths in voxels
    ///\param dir_star \e true: Collect  STAR values from all directions<br>
    ///                \e false: Use voxel's STAR mean values
    ///\pre \p |vec| = 0
    ///\pre \p |dir| = 1
    ///\pre \p p0 must be inside the voxel space
    ///\retval vec Vector containing the beam route data in VoxelMovement
    ///\sa VoxelMovement
    ///
    ///\par Details for calculating the beam route
    ///
    ///The Fast Voxel Traversal Algorithm is divided into an initialization phase and an incremental
    ///loop phase. In the initialization phase the algorithm sets the loop variables based on the
    ///starting position and the beam direction. In the loop phase the algorithm travels forward by identifying
    ///which of the X,Y or Z voxel plane boundary is reached first, jumps to the corresponding voxel and updates
    ///the current voxel indices. The process is repeated until voxel space boundary is reached.
    ///
    ///\par Initialization phase
    ///
    ///Initialization phase sets computes the starting conditions from the ray's origin and direction.
    ///These conditions consists of four sets of variables.
    ///
    ///\par The current voxel
    ///
    ///Setting the current voxel, \f$ \mathtt{startx, starty, startz} \f$, is trivial based on the starting position.
    ///
    ///\par Direction of the step
    ///
    ///The step directions, \f$ \mathtt{x\_jump, y\_jump, z\_jump} \f$, are set to \f$ \pm 1 \f$ based on the ray's direction vector.
    ///A negative component results in \f$ -1 \f$, while a positive component results in \f$ +1 \f$.
    ///
    ///\par Calculate strides
    ///
    ///For each dimension - \f$ \mathtt{xmove, ymove, zmove} \f$ - calculate the voxel stride to cross a voxel boundary.
    ///\f[
    /// \mathtt{xmove}=\frac{\mathtt{Xbox}}{\mathtt{dir.x}},  \mathtt{ymove}=\frac{\mathtt{Ybox}}{\mathtt{dir.y}}, \mathtt{zmove}=\frac{\mathtt{Zbox}}{\mathtt{dir.z}}
    ///\f]
    ///During the iteration phase, these values do not change.
    ///\sa VoxelSpace::Xbox, VoxelSpace::Ybox, VoxelSpace::Zbox
    ///\note Although the voxel space traversal algorithm itself does not require a normalized direction vector,
    ///normalization (\f$|\mathtt{dir}| = 1 \f$) is necessary to ensure the traversal route reflects true geometric
    ///distance for accurate radiation attenuation calculations.
    ///
    ///\par The first voxel face crossings
    ///
    ///Calculate the total distances, \f$ \mathtt{next\_x, next\_y} \f$ and \f$ \mathtt{next\_z} \f$, the light beam must travel
    ///before crossing a voxel face for the first time  in all \f$ X, Y \f$ and \f$ Z \f$ directions.  This is for example the problem
    ///of deciding if a ray intersects with a plane. The  beam  is represented as \f$ p_0+td \f$, where \f$ p_0 \f$ is the starting
    ///point and \f$ d \f$ is the direction unit vector of the ray. The \f$ t \f$ is the parametric distance to the plane.
    ///
    ///The plane is represented as \f$ Ax+By+Cz+D=0 \f$, where \f$ A, B \f$ and \f$ C \f$ is the  normal to the  plane (unit  vector) and
    ///\f$ D \f$  is the shortest distance of  the plane  to  origo. At the point  of intersection the ray satisfies
    ///the  plane   equation: \f$ A\left(p_0.x+td.x\right)+B\left(p_0.y+td.y\right)+C\left(p_0.z+td.z\right)+D = 0 \f$.
    ///
    ///Both the  normals (\f$ A, B, C \f$) and the distances (\f$D\f$) are known for all six voxel faces as the voxel space is aligned
    ///with the \f$ X, Y \f$ and \f$ Z \f$ axes. Set \f$ A, B, C \f$ and \f$ D \f$ for each of the six voxel sides and solve the
    ///equations for \f$ t \f$ :
    ///\f[
    ///t=-(Ap_0.x+Bp_0.y+Cp_0.z+D)/(Ad.x+Bd.y+Cd.z)
    ///\f]
    ///This results in at most three positive values for \f$ t \f$, and three corresponding voxel face intersection points.
    ///Negative values indicate intersection points behind the ray's origin, while a zero denominator implies that the ray is
    ///parallel to the corresponding voxel face.
    ///
    ///\par Iteration phase
    ///
    ///In the iteration phase compare the total distances \f$ \mathtt{next\_x, next\_y} \f$ and \f$ \mathtt{next\_z} \f$ to find the smallest.
    ///Enter the corresponding voxel, and update that distance by adding its step size.
    ///
    ///The iteration phase calculates radiation attenuation (\f$ \tau \f$) and collects data from each voxel in \p vec:
    /// - STAR mean based on foliage area in the voxel, aggregate voxel based method 
    /// - Radiation attenuation (\f$ \tau \f$), pairwise comparison of shading tree segments
    /// - Number tree segments
    /// - Mean segment direction
    /// - Foliage area
    /// - Wood area
    ///.
    ///
    ///\par Example
    ///
    ///The set-up
    /// - Voxel size: \f$ \left(1.0 \times 1.0 \times 1.0\right)\f$
    /// - Ray origin: (0.1, 0.4, 0.7)
    /// - Normalized ray direction: (0.4402, 0.8805, 0.1761)
    ///.
    ///Initialization
    /// - Start voxel: X=0, Y=0, Z=0
    /// - Step direction: +1,+1,+1
    /// - Calculate strides:
    ///   - xmove = \f$ 1.0 / 0.4402 = 2.2716 \f$
    ///   - ymove = \f$ 1.0 / 0.8805 = 1.1358 \f$
    ///   - zmove = \f$ 1.0 / 0.1761 = 5.6789 \f$
    ///.
    /// - Calculate the first intersections:
    ///   - next_x = 2.0444
    ///   - next_y = 0.6815
    ///   - next_z = 1.7037
    ///.
    ///Traversal
    /// - Step 1:
    ///  - Status: next_x = 2.0444, next_y = 0.6815, next_z = 1.7037
    ///  - Compare: The mininum intersection Y =  0.6815
    ///  - Action:
    ///    - Y increase \f$ 0 \rightarrow 1 \f$ 
    ///    - Current voxel (0,1,0)
    ///    - next_y = 0.6815 + 1.1358 = 1.8173
    /// - Step 2:
    ///  - Status: next_x = 2.0444, next_y = 1.8173, next_z = 1.7037
    ///  - Compare: The mininum intersection Z = 1.7037
    ///  - Action:
    ///   - Z increase \f$ 0 \rightarrow 1 \f$
    ///   - Current voxel (0,1,1)
    ///   - next_z = 1.7037+5.6789 = 7.3826
    ///.
    /// Repeat Step 2. until one voxel space slab is encountered
    vector<VoxelMovement>& getRoute(vector<VoxelMovement>& vec,const Point& p0,const PositionVector& dir,const ParametricCurve& K,bool pairwise, bool dir_star)const;
    ///\todo \htmlonly <span style="color:orange;">&#9679;</span>\endhtmlonly
    /// Merge with getRoute(vector<VoxelMovement>& vec,const Point& p0,const PositionVector& dir,const ParametricCurve& K,bool pairwise, bool dir_star)const
    ///
    ///\overload  vector<VoxelMovement>& getRoute(vector<VoxelMovement> &vec, int startx, int starty, int startz, PositionVector dir)const;
    ///\note Not tested or documented
    vector<VoxelMovement>& getRoute(vector<VoxelMovement> &vec, int startx,int starty, int startz, PositionVector dir)const;
    ///The extinction caused by the border stand
    ///\param p0   Start point of the light beam
    ///\param dir  Direction of the light beam, |dir| == 1 (!!!)
    ///\return The extinction caused by the border stand
    double getBorderStandExtinction(const Point& p0, const PositionVector& dir)const;
    ///\brief Loop through VoxelBoxes and update VoxelBox values
    ///
    ///\invariant It seeems  VoxelBox::updateValues() is strictly local, no cross-voxel dependencies.
    ///
    ///\todo VoxelSpace::updateBoxValues() is called:
    /// - Every time in DumpCfTree(VoxelSpace &s, Tree<TS, BUD> &tree,int num_parts, bool wood)
    /// - In the LignumForest::GrowthLoop::setVoxelSpaceAndBorderForest()
    /// \todo  \htmlonly <span style="color:orange;">&#9679;</span>\endhtmlonly Minimize calls to VoxelSpace::updateBoxValues():
    /// - VoxelSpace::updateBoxValues() loops each time 3D voxel space matrix.
    void updateBoxValues();  
    LGMdouble calculateTurbidLight(bool border_forest, bool self_shading = true);
    //diffuse is to calcluate the real diffuse from standard 1200, structureFlag is
    //used to indicate if it is the first time light calculation after structure update
    LGMdouble calculatePoplarLight(LGMdouble diffuse, LGMdouble structureFlag);
    void setLightValues();
    void setLight();

    void fillVoxelBoxes(M2 needleA, M2 leafA);
    void fillVoxelBoxes(LGMdouble inivalue, int beginZ, int endZ);
    //First four arguments are for box.S() STAR sum
    void fillVoxelBoxesWithNeedles(LGMdouble Sf, LGMdouble Wf, LGMdouble Rf,
                                   LGMdouble L, int beginZ, int endZ);

    BoundingBox& searchDimensions(BoundingBox &bbox,
                                  bool boolDimensionsWithNumBoxes);

    void searchDimensions(bool boolDimensionsWithNumBoxes=true){
      searchDimensions(bbox, boolDimensionsWithNumBoxes);
    }

    void dumpTrees();

    //Write voxel  boxes to file. If  'all' is true  write all boxes
    //else write only  boxes with foliage. By default  'all' is true
    //(old behaviour).
    void writeVoxBoxesToFile(const string& filename, bool all = true);
    //Write voxel  boxes to file up to Z index
    void writeVoxBoxesToFile(const string& filename, int z);
    void writeVoxBoxesToFile2(const string& filename);
    void writeVoxelBoxesToGnuPlotFile(const string& filename,
                                      const string& sep=" ");
    void writeVoxelSpaceContents();
    void writeStarMean();
    void writeMeanDirection();

    double getMeanFoliageAreaDensity();
    void calculateMeanQabsQin();
    LGMdouble getNeedleArea();      //Returns sum of needle area in voxelboxes
    LGMdouble getLeafArea();        //Returns sum of leaf area in voxelboxes
    LGMdouble getFoliageArea();     //Returns sum of needle + leaf area in voxelboxes

    void evaluateVerticalNeedleAreaDensity(LGMdouble& Hmax, LGMdouble& Hmin, int& n,
                                           vector<pair<LGMdouble,LGMdouble> >& NAD);
    LGMdouble evaluateLacunarityNeedles();

    bool inVoxelSpace(const Point& p);

    void setDiffuseSkyRadiation(const LGMdouble radiation) {
      sky->setDiffuseRadiation(radiation); }
    void setDirectSkyRadiation(const LGMdouble radiation) {
      sky->setDirectRadiation(radiation); }
    void setDirectRadiationDirection(const vector<double> dir) {
      sky->setSunPosition(dir); }
    //
    // Returns vector of VoxelBoxes for a end point of vector (specified with the
    // end point, and direction of vector) and neighboring voxelboxes in a positive
    // dierction of the vector. That is, when the indexes of the end point of the 
    // the vector are (0, 0, 0), then in addition to (0,0,0) the voxels 
    // (+1, 0, 0), (0, +1, 0), (0, 0, +1),
    // (+1, +1, 0), (0, +1, +1), (+1, 0, +1), (+1, +1, +1) (8 voxels)
    // are included when all components of the direction vector are positive.
    // When components of the direction vector are negative the corresponding +1
    // is replaced with -1 in the above permutation.
    // It is possible that either the voxel of the end point or the neighboring voxels
    // are outside of VoxelSpace. Nothing is returned from such a "voxel". The length of
    // of returned vector thus varies between 0 and 8, 0 meaning that both the end point
    // and the neighboring "voxels" are outside of VoxelSpace.

    vector<VoxelBox> getVoxelBoxPositiveNeighborhood(const Point& p,
						     const PositionVector& dir);

    //
    // Returns vector of VoxelBoxes that are neighbors of a box including a Point
    // (not this box)
    // Only boxes that are inside the voxelspace are returned

    vector<VoxelBox> getVoxelBoxNeighborhood(const Point& p);



    //==========================================================

    LGMdouble Xbox, Ybox, Zbox;
    int Xn, Yn, Zn;
    TMatrix3D<VoxelBox> voxboxes;
    //debug
    int sgmnt;//segments inserted (to compare with)
    int hitw;//wood hits;
    int hitfol;//foliage hits
    int nohit;//no hits
    int hitself; //Self comparison
  private:


    BoundingBox bbox;

    Point corner1;  //origo
    Point corner2;  //diagonallly opposite corner(??)

    int getXindex(LGMdouble xcoord)const;
    int getYindex(LGMdouble ycoord)const;
    int getZindex(LGMdouble zcoord)const;

    Firmament* sky;

    LGMdouble k_b; //impact angle of a broad  leaf (c.f. star mean for
    //coniferous)
    VOBookKeeper book_keeper; //maintains   information  if   a  voxel
    //object has been hit by a light beam
    ForestDescriptor forest_descriptor;//maintains         descripitive
    //statistics and indices of the
    //forest in the voxel space
  };


  ///\brief Insert coniferous segment into VoxelSpace 
  template <class TS,class BUD>
  class DumpCfTreeFunctor
  {
  public:
    ///\brief Constructor
    ///\param n Number of segment parts
    ///\param wood Boolean flag to insert wooden part or not
    DumpCfTreeFunctor(int n, bool wood):num_parts(n), dumpWood(wood) {}
    ///\brief Functor to insert conferous segment foliage and wooden part
    ///\pre Wooden part is inserted if foliage mass \p LGAWf <= R_EPSILON and \p dumpWood = \e true
    ///When \p num_parts is 1 (whole segment) then 1/2 of the segment (middle point) is
    ///checked for the right voxel. When \p num_parts is 2 then 1/3 and 2/3 are checked.
    ///When \p num_parts is 3 then 1/4, 2/4 and 3/4 are checked etc.
    TreeCompartment<TS,BUD>* operator ()(TreeCompartment<TS,BUD>* tc)const;
    mutable VoxelSpace *space;///< VoxelSPace
    double num_parts;///< Number of segment parts 
    bool dumpWood;///< Insert wooden part or not
  };


template <class TS,class BUD>
class SetCfTreeQabsFunctor
{
public:
    SetCfTreeQabsFunctor(int n):num_parts(n){}
    TreeCompartment<TS,BUD>* operator ()(TreeCompartment<TS,BUD>* tc)const;
    mutable VoxelSpace *space;
    double num_parts;
};

//For deciduous trees, that is, hardwoods
template <class TS,class BUD>
class DumpHwTreeFunctor
{
public:
    TreeCompartment<TS,BUD>* operator ()(TreeCompartment<TS,BUD>* tc)const;
    mutable VoxelSpace *space;
};


template <class TS,class BUD>
class SetHwTreeQabsFunctor
{
public:
    TreeCompartment<TS,BUD>* operator ()(TreeCompartment<TS,BUD>* tc)const;
    mutable VoxelSpace *space;
};

//Insert all tree segments as voxel objects
//Usage:
//VoxelSpace vs;
//ForEach(tree,InsertTreeAsVoxelObjects(vs))
template <class TS, class BUD>
class InsertTreeAsVoxelObjects{
public:
    InsertTreeAsVoxelObjects(VoxelSpace& vs1):vs(vs1){}
    void operator ()(TreeCompartment<TS,BUD>* tc)const;
private:
    VoxelSpace& vs;
};

//InsertForestAsVoxelObjects
//Inserts a vector of trees into a voxel space
//VoxelSpace must have proper size to contain the trees
//Usage: for_each(treels.begin(),treels.end(),InsertForestAsVoxelObjects(vs))
template <class TREE, class TS, class BUD>
class InsertForestAsVoxelObjects{
public:
    InsertForestAsVoxelObjects(VoxelSpace& vs1):vs(vs1){}
    void operator()(TREE* t)const;
private:
    VoxelSpace& vs;
};

// This functor checks only if woody part of this TreeSegment occupies a VoxelBox and sets 
// variable occupied accordingly.
// Checks only segments that have foliage and are older than 0 years. 
template <class TS, class BUD>
  class DumpTreeOccupy {
 public:
 DumpTreeOccupy(const int& n) : num_parts(n) {}
  TreeCompartment<TS,BUD>* operator ()(TreeCompartment<TS,BUD>* tc)const;
  mutable VoxelSpace *space;
  double num_parts;
};

// This functor checks if the axis of this TreeSegment in a VoxelBox and sets 
// variable occupied accordingly. Whether TreeSegment has foliage or not does not matter.
template <class TS, class BUD>
  class DumpTreeOccupyTreeSegment {
 public:
 DumpTreeOccupyTreeSegment(const int& n) : num_parts(n) {}
  TreeCompartment<TS,BUD>* operator ()(TreeCompartment<TS,BUD>* tc)const;
  mutable VoxelSpace *space;
  double num_parts;
};




} // namespace Lignum

#endif
#include "VoxelSpaceI.h"
#include "VoxelSpaceRadiationI.h"
