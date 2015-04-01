#include "PlottingTool.hh"

#include <fstream>   // reading file
#include <iostream>  // printing
#include <pthread.h> // multithreading
#include <unistd.h>  // delay (usleep)
#include <stdlib.h>  // system calls

using namespace std;

ofstream gnuplot_script;

string scriptTitle, scriptXLabel, scriptYLabel, scriptFile;
string scriptParams;

PlottingTool::PlottingTool(){
}

PlottingTool::~PlottingTool() {
}

void PlottingTool::setTitle(string title) {
  scriptTitle = title;
}

void PlottingTool::setXLabel(string xLabel) {
  scriptXLabel = xLabel;
}

void PlottingTool::setYLabel(string yLabel) {
  scriptYLabel = yLabel;
}

void PlottingTool::setFile(string file) {
  scriptFile = file;
}

void PlottingTool::setPlotParameters(string params) {
  scriptParams = params;
}

void PlottingTool::plotXY(int xCol, int yCol) {
  int scriptXCol = xCol;
  int scriptYCol = yCol;

  gnuplot_script.open("gnuplot_tmp");

  gnuplot_script << "set datafile separator ','" << endl;

  gnuplot_script << "set title '" << scriptTitle << "'" << endl;
  gnuplot_script << "set xlabel '" << scriptXLabel << "'" << endl;
  gnuplot_script << "set ylabel '" << scriptYLabel << "'" << endl;
  gnuplot_script << "plot '" << scriptFile
		 << "' using " << scriptXCol << ":" << scriptYCol << " "
		 << scriptParams
		 << endl;

  gnuplot_script.close();

  system("gnuplot -p gnuplot_tmp");
}

void PlottingTool::plotHist(int nBins, double minValue, double maxValue, int col) {
  int scriptNBins = nBins;
  double scriptMinValue = minValue;
  double scriptMaxValue = maxValue;
  int scriptCol = col;

  gnuplot_script.open("gnuplot_tmp");

  gnuplot_script << "set datafile separator ','" << endl;

  gnuplot_script << "set title '" << scriptTitle << "'" << endl;
  gnuplot_script << "set xlabel '" << scriptXLabel << "'" << endl;
  gnuplot_script << "set ylabel '" << scriptYLabel << "'" << endl;

  gnuplot_script << "n=" << scriptNBins << "." << endl;
  gnuplot_script << "min=" << scriptMinValue << "." << endl;
  gnuplot_script << "max=" << scriptMaxValue << "." << endl;

  gnuplot_script << "width=(max-min)/n" << endl;
  gnuplot_script << "hist(x,width)=width*floor(x/width)+width/2.0" << endl;

  gnuplot_script << "set xrange [" << scriptMinValue << ":" << scriptMaxValue << "]" << endl;
  gnuplot_script << "set yrange [0:]" << endl;

  gnuplot_script << "set boxwidth width*0.9" << endl;
  gnuplot_script << "set tics out nomirror" << endl;

  gnuplot_script << "plot '" << scriptFile
		 << "' using (hist($" << scriptCol << ",width)):(1.0)" << " "
		 << scriptParams << endl;

  gnuplot_script.close();

  system("gnuplot -p gnuplot_tmp");
}
