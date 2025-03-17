# Firmament visualization
The class Firmament has has a simple Python interface (package) `firmament` 
that allows to use the Python test program  `plotrad.py` to visualize 
the configuration  of the Firmamnt model from the Terminal command line. 
Create a Python virtual environment as adviced in *lignum-core* README. 
To build the `firmament` package activate first the virtual environment
before building the package:
        
        source ~/venv/lignumsystem/bin/activate
        (lignumsystem) python3 setup.py build_ext --inplace
			
To run `plotrad.py` type for example:
	
		(lignumsystem) python3 plotrad.py -i 20 -a 20 -r 1200
		
`plotrad.py` has the help (`-h/--help`) option to find instructions for usage.
	
		
