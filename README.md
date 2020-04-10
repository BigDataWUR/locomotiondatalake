# Locomotion data lake  

[![Binder](https://mybinder.org/badge_logo.svg)](https://mybinder.org/v2/gh/ionathan/datalake-locomotion/master)
[![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.3563513.svg)](https://doi.org/10.5281/zenodo.3563513)
[![License: CC BY-NC 4.0](https://img.shields.io/badge/License-CC%20BY--NC%204.0-lightgrey.svg)](https://creativecommons.org/licenses/by-nc/4.0/)

Software accompanying the paper "Storing, combining, and analysing animal experimental data in the big data era" 



This work is embedded within the Big Data project of Breed4Food (http://breed4food.com). 
We experiment with data lake stack for storing and analysing sensor data, using an animal experiment as use case to have improved scalability, modularity, and interoperability. This repository includes the code (notebooks and scripts) of the corresponding paper, currently under review.



The use case was an animal experiment in which the gait score of 84 turkeys was determined. 

Gait scoring is traditionally performed by an expert.
In this experiment different type of sensors were used to explore to what extent sensors can describe or mirror the gait score of an expert.

Data & Sensors
- Gait score (Visually trained person)
- Force Plate (Kistler)
- Accelerometers / inertial measurement units {IMUs} (Xsense MTw awinda)

An [Extract, Transform, and Load (ETL)]() procedure, is the general procedure of copying data from one or more sources into a destination system which represents the data differently from the source(s).
Extract: retrieve data from a source
Transform: Converting retrieved data according to rules and lookup tables or creating combinations of data from different sources
Load: save the data in a different location
The ETL procedure will become more important because we need to handle ever increasing datasets, varying data structures, as well as heterogeneous and multimodal data. In the animal experiment different data types were acquired by each sensor. For example for the Force Plate (Kistler) this were binary files, so called Technical Data Management Streaming (TDMS) files, and this file format was generated to help engineers and scientists to properly store the large amounts of data they generate during simulation(s) and test(s). In our data lake stack we want to be able to scale up the ETL procedure for each sensor, so when large number of animals are being investigated with a certain sensor, we can minimize the time for the ETL procedure.
 
In short, we want to combine different sensors in a massive way (and extract features), as well as going from proprietary formats to FAIR data. When these data are loaded it will be possible to visualize these data and perform a linear regression (and Machine Learning)


Original data are proprietary. An subset of 3 turkeys has been released as open access on Zenodo, and can be used to run the code in this repository. The whole solution can be launched through Binder.
To launch the notebooks, click on the button [![Binder](https://mybinder.org/badge_logo.svg)](https://mybinder.org/v2/gh/ionathan/datalake-locomotion/master)

<a rel="license" href="http://creativecommons.org/licenses/by-nc/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc/4.0/88x31.png" /></a>This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc/4.0/">Creative Commons Attribution-NonCommercial 4.0 International License</a>.
