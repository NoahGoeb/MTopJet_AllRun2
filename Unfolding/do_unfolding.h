#include "unfold.h"
#include "plotter.h"
#include "sys_handler.h"
#include "chi2fit.h"
#include "normalise.h"
#include "modelsys.h"

TString directory;
TString input_file;
TString output_file;
TString binning_xml;


class Tools{
 public:
  TH2D* GetDiagonalCovMatrix(TH1D* hist);
};
