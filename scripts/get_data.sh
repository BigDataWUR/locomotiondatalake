# Script to pull data from Zenodo
mkdir -p files/
wget https://zenodo.org/record/3563513/files/Walking%20trial_IDmatch_edu.csv -O files/Walking_trial_IDmatch_edu.csv

mkdir -p files/forceplate/18936
wget https://zenodo.org/record/3563513/files/18936%20Voltage_meta.txt   -O 'files/forceplate/18936/Voltage_meta.txt'
wget https://zenodo.org/record/3563513/files/18936%20Voltage.tdms       -O 'files/forceplate/18936/Voltage.tdms'
wget https://zenodo.org/record/3563513/files/18936%20Voltage.tdms_index -O 'files/forceplate/18936/Voltage.tdms_index'


mkdir -p files/forceplate/19778
wget https://zenodo.org/record/3563513/files/19778%20Voltage_meta.txt   -O 'files/forceplate/19778/Voltage_meta.txt'
wget https://zenodo.org/record/3563513/files/19778%20Voltage.tdms       -O 'files/forceplate/19778/Voltage.tdms'
wget https://zenodo.org/record/3563513/files/19778%20Voltage.tdms_index -O 'files/forceplate/19778/Voltage.tdms_index'


mkdir -p files/forceplate/19873
wget https://zenodo.org/record/3563513/files/19873%20Voltage_meta.txt   -O 'files/forceplate/19873/Voltage_meta.txt'
wget https://zenodo.org/record/3563513/files/19873%20Voltage.tdms       -O 'files/forceplate/19873/Voltage.tdms'
wget https://zenodo.org/record/3563513/files/19873%20Voltage.tdms_index -O 'files/forceplate/19873/Voltage.tdms_index'


mkdir -p files/accelerometer
wget https://zenodo.org/record/3563513/files/MT_0120067F_007.mtb -O 'files/accelerometer/MT_0120067F_007.mtb'
wget https://zenodo.org/record/3563513/files/MT_0120067F_017.mtb -O 'files/accelerometer/MT_0120067F_017.mtb'
wget https://zenodo.org/record/3563513/files/MT_0120067F_047.mtb -O 'files/accelerometer/MT_0120067F_047.mtb'


mkdir -p work/forceplate/original/
mkdir -p work/accelerometer/original/
