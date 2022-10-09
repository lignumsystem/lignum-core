##\example{lineno} rayplane.py 
import numpy as np
def rayplane(planeN,planeP,rayD,rayP):
    """!
    Check for line - plane intersection 
    \param planeN plane normal
    \param planeP point on the plane
    \param rayD ray direction
    \param rayP point on a ray
    """!
    NdotR = planeN.dot(rayD)
    print("NdotR",NdotR)
    w = planeP-rayP
    print("w",w)
    print("planeN",planeN)
    print("NdotW",-planeN.dot(w))
    t = planeN.dot(w)/NdotR
    print("t",t)
    p = rayP+t*rayD
    return p

    
