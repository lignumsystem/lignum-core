######################################################################
# Automatically generated by qmake (2.00a) Thu Aug 17 11:07:49 2006
######################################################################

CONFIG+=staticlib
CONFIG-=qt
TEMPLATE =  lib 
DESTDIR = lib
TARGET = LGM
DEPENDPATH += include \
              Axis \
              BranchingPoint \
              Bud \
              RootSystem \
              Tree \
              TreeCompartment \
              TreeSegment
INCLUDEPATH += . include ../c++adt/include ../Firmament/include
# Input
HEADERS += include/Algorithms.h \
           include/AlgorithmsI.h \
           include/Axis.h \
           include/AxisI.h \
           include/BetulaTortuosa.h \
           include/BetulaWithFlow.h \
           include/BetulaWithFlowI.h \
           include/BranchingPoint.h \
           include/BranchingPointI.h \
           include/BroadLeaf.h \
           include/BroadLeafI.h \
           include/Bud.h \
           include/BudI.h \
           include/CfTreeFunctor.h \
           include/CfTreeFunctorI.h \
           include/CfTreeSegment.h \
           include/CfTreeSegmentI.h \
           include/CfTreeSegmentMetabolismI.h \
           include/Collision.h \
           include/CollisionI.h \
           include/CompareLeaves.h \
           include/CreateLeaves.h \
           include/DefaultBud.h \
           include/Forest.h \
           include/ForestAlgorithms.h \
           include/HwTreeSegment.h \
           include/HwTreeSegmentI.h \
           include/HwTreeSegmentMetabolismI.h \
           include/InitializeTree.h \
           include/InitializeTreeI.h \
           include/LGMdecl.h \
           include/LGMSymbols.h \
           include/LGMUnits.h \
           include/LGMUtility.h \
           include/LGMUtilityI.h \
           include/Lignum.h \
           include/MapParameterType.h \
           include/MyBud.h \
           include/MyTreeSegment.h \
           include/RootAlgorithms.h \
           include/RootAlgorithmsI.h \
           include/RootFunctor.h \
           include/RootSystem.h \
           include/RootSystemI.h \
           include/Shading.h \
           include/ShadingI.h \
           include/StructuralGrowth.h \
           include/StructuralGrowthI.h \
           include/Tree.h \
           include/TreeBookkeeping.h \
           include/TreeBookkeepingI.h \
           include/TreeCharacteristics.h \
           include/TreeCompartment.h \
           include/TreeCompartmentI.h \
           include/TreeFunctor.h \
           include/TreeFunctorI.h \
           include/TreeGrowth.h \
           include/TreeGrowthAllocator.h \
           include/TreeGrowthI.h \
           include/TreeI.h \
           include/TreeMetabolism.h \
           include/TreeMetabolismI.h \
           include/TreeMetaFileParser.h \
           include/TreeRadiation.h \
           include/TreeRadiationI.h \
           include/TreeSegment.h \
           include/TreeSegmentFlow.h \
           include/TreeSegmentI.h \
           include/TreeSegmentWithFlow.h \
           include/VisualFunctor.h \
           include/VisualFunctorI.h \
           include/VTree.h \
           include/Zbrent.h \
           include/zbrentFunctor.h \
           include/zbrentFunctorI.h \
           include/ZbrentI.h
SOURCES += Axis/AxisFriend.cc \
           BranchingPoint/BranchingPointFriend.cc \
           Bud/Bud.cc \
           Bud/BudFriend.cc \
           Tree/Tree.cc \
           Tree/TreeFriend.cc \
           TreeCompartment/TreeCompartmentFriend.cc \
           TreeMetaFileParser/TreeMetaFileParser.cc\
           TreeSegment/BeamShading.cc \
           TreeSegment/BroadLeaf.cc \
           TreeSegment/BroadLeafMetabolism.cc \
           TreeSegment/CfTreeSegment.cc \
           TreeSegment/MyTreeSegment.cc \
           TreeSegment/TreeSegment.cc \
           TreeSegment/TreeSegmentFriend.cc