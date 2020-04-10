from pyspark.sql import SparkSession


import os
import argparse
from nptdms import TdmsFile as td
import time
import glob
import hdfs

from pyspark import SparkContext, SparkConf

SERVER = 'ec2-XXX-XXX-XXX-XXX.eu-central-1.compute.amazonaws.com:50070'

def transform_and_store(f,number):
    name = os.path.split(os.path.dirname(f))[1]+'.csv';
    td("/home/ec2-user/"+f).as_dataframe().to_csv(name)
    hdfs.InsecureClient(SERVER)\
        .upload('/generated/output'+number+'/'+name,name, overwrite=True)
    
 
def main(number,workers):
    spark = SparkSession\
        .builder\
        .appName("Locomotion-Extract-TDMS")\
        .getOrCreate()
    sc = spark.sparkContext
    hdfs.InsecureClient(SERVER).makedirs('/generated/output'+number)
    files = glob.glob('generated/input'+number+'/**/*.tdms')
    g = sc.parallelize(files, workers).map(lambda f : transform_and_store(f,number)).collect()
    spark.stop()


if __name__ == "__main__":
    # Configure options
    parser = argparse.ArgumentParser(description='Converts tdms files stored in a folder into csv')
    parser.add_argument('--n', help='Number of copies generated', default=10)
    parser.add_argument('--w', help='Number of workers', default=2)

    args = parser.parse_args()
    
    start = time.time()
    main(str(args.n), args.w)
    end = time.time()
    print("Walltime for ",args.n, "time: ",end - start)
