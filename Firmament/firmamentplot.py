## \file firmamentplot.py
## \brief Visualize radiant intensity in Firmament sectors 
import argparse
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits import mplot3d
import firmament

plt.rcParams['text.usetex'] = True

def plot_firmament(incl,azim,rad,cmap,unit):
    """
    Create 4D scatter plot of the Firmament model
    @param incl Number of inclinations
    @param azim Number of azimuths
    @param rad Total incoming radiation
    @param cmap Colormap
    """
    axis_title=str(incl*azim)+" sectors" 
    main_title="Incoming radiation in Firmament"+"\n"+r"$\mathrm{"+str(rad)+unit+"}$"+"\n\n"+axis_title
    
    f = firmament.PyFirmament(incl,azim,rad)
    x = []
    y = []
    z = []
    r = []
    for sec in range(0,f.number_of_regions()):
        rad = f.diffuse_region_radiation_sum(sec)
        dir = f.get_direction(sec)
        x.append(dir[0])
        y.append(dir[1])
        z.append(dir[2])
        r.append(rad)

    X = np.array(x)
    Y = np.array(y)
    Z = np.array(z)
    R = np.array(r)
    rmin = R.min()
    rmax = R.max()
    #print(rmin,rmax)
    fig = plt.figure()
    fig.suptitle(main_title,multialignment='center')
    ax = fig.add_subplot(111,projection='3d')
    ax.set(xlabel=str(azim)+" azimuths ",zlabel=str(incl)+" inclinations ")
    img = ax.scatter(X, Y, Z, c=R, cmap=cmap)
    #print(type(img))
    #print(img.get_clim())
    cbar=fig.colorbar(img,label="Sector intensity "+r"$\mathrm{"+unit+"}$",shrink=0.8,pad=0.10,location='right')
    cbar.set_ticks(np.linspace(rmin,rmax,8))
    plt.show()

if __name__ == "__main__":
    parser = argparse.ArgumentParser(formatter_class=argparse.ArgumentDefaultsHelpFormatter,
        description="Visualize radiant intensity in Firmament sectors",
        epilog="One can use LaTeX formatting in the -u/--units option for units")
    parser.add_argument("-i","--inclination",dest="i",type=int,required=True,help="Number of inclination")
    parser.add_argument("-a","--azimuth",dest="a",type=int,required=True,help="Number of azimuths")
    parser.add_argument("-r","--rad",dest="r",type=float,required=True,help="Total incloming radiation")
    parser.add_argument("-c","--cmap",dest="c",type=str,default="plasma",help="Colormap")
    parser.add_argument("-u","--units",dest="u",type=str,default="MJyr^{-1}",help="Units used in radiant intensity")
    args = parser.parse_args()
    plot_firmament(args.i,args.a,args.r,args.c,args.u)
   
