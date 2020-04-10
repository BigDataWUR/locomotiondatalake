# Instructions for the AWS experiments


1. Using the [flintrock configuration](flintrock-config.yaml), launch a small cluster named b4f4

    flintrock launch b4f4 --install-hdfs --num-slaves 6
    
 Keep a note of the master address, and copy it in the ExtractOne.py script.

2. Install python 3 on the cluster

    flintrock run-command b4f4 'sudo yum install python36 -y'
    flintrock run-command b4f4 'sudo yum install -y python-pip'
    flintrock run-command b4f4 'sudo yum install -y python3-pip python3 python3-setuptools'
    flintrock run-command b4f4  'echo "alias python='python3'" >> .bash_profile'

3.  Copy files (get first the forceplate data)

    zip archive.zip -r aws/ *.py *.txt *.sh
    flintrock copy-file  b4f4  archive.zip ./archive.zip
    flintrock run-command  b4f4  'yes | unzip archive.zip'

4. Install Python packages

    flintrock run-command b4f4  'sudo pip install -r requirements.txt'

5. Generate data

    flintrock run-command b4f4  'python copyFiles.py --n 10'
    # flintrock run-command b4f4  'python copyFiles.py --n 100'
    # flintrock run-command b4f4  'python copyFiles.py --n 1000'
    # flintrock run-command b4f4  'python copyFiles.py --n 100000'

6. Run experiments
    
    flintrock run-command --master-only b4f4  'hadoop fs -put generated/ /'

    flintrock run-command --master-only b4f4  'spark-submit --master spark://XXX.XXX.XXX.XXX:7077 extractOne.py --n 100'
