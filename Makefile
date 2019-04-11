LIBRARY := SUHH2VBFresonanceToWW
LHAPDFINC=$(shell scram tool tag lhapdf INCLUDE)
LHAPDFLIB=$(shell scram tool tag LHAPDF LIBDIR)
USERCXXFLAGS := -I${LHAPDFINC}
#USERLDFLAGS := -lSUHH2core -lSUHH2common -lGenVector -lSUHH2JetMETObjects -L${LHAPDFLIB} -lLHAPDF #robin
USERLDFLAGS := -lSUHH2core -lSUHH2common -lGenVector -L${LHAPDFLIB} -lLHAPDF
#USERLDFLAGS := -lSUHH2core -lSUHH2common -lGenVector #old
# enable par creation; this is necessary for all packages containing AnalysisModules
# to be loaded from by AnalysisModuleRunner.
PAR := 1
include ../Makefile.common
