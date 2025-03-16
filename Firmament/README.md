# Firmament visualization
The class Firmament has has a simple Python interface (package) that allows to use the Python test program 
`plotrad.py` to visualize the configuration  of the Firmamnt model. Create a Python virtual environment, 
install required python packages and build the `firmament`
Python package:
        
        sudo port install python312
        /opt/local/bin/python3.12 -m venv cythonenv
        source cythonenv/bin/activate
        pip install -r requirements.txt
        python3 setup.py build_ext --inplace
			
To run `plotrad.py` type for example:
	
		python plotrad.py -i 20 -a 20 -r 1200
		
`plotrad.py` has the help (`-h/--help`) option to find instructions for usage.
	
		
