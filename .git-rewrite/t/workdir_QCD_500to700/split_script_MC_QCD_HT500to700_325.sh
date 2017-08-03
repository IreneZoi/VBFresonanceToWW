#!/bin/bash

##This is a simple example of a SGE batch script
##Use home server with scientific linux 6 
#$ -l os=sld6 
#$ -l site=hh 
#$ -cwd
##You need to set up sframe
#$ -V 
##email Notification
#$ -m as
#$ -M irene.zoi@desy.de
##running in local mode with 8-12 cpu slots
##$ -pe local 8-12
##CPU memory
#$ -l h_vmem=8G
##DISK memory
#$ -l h_fsize=2G   
cd workdir_QCD_500to700
sframe_main MC_QCD_HT500to700_325.xml

