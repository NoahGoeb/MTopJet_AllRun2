LIBRARY := SUHH2ZprimeSemiLeptonic
USERLDFLAGS := -lSUHH2core -lSUHH2common -lGenVector -lTMVA -lHOTVR
# enable par creation; this is necessary for all packages containing AnalysisModules
# to be loaded from by AnalysisModuleRunner.
PAR := 1
include ../Makefile.local
include ../Makefile.common
