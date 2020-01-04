#include <iostream>
#include <math.h>
#include "seno.h"
#include "keyvalue.h"

#include <stdlib.h>

using namespace upc;
using namespace std;

Seno::Seno(const std::string &param)
  : adsr(SamplingRate, param) {
  bActive = false;
  x.resize(BSIZE);

  /*
    You can use the class keyvalue to parse "param" and configure your instrument.
    Take a Look at keyvalue.h
  */

  KeyValue kv(param);
  int N;


  if (!kv.to_int("N",N))
    N = 40; //default value

  if (!kv.to_float("vel",vel))
    vel= 0,8; //default value


  if (!kv.to_float("fm",fm))
    fm = 10; //default value

    float note, fo, dif, dim;



  //Create a tbl with one period of a sinusoidal wave
  tbl.resize(N);
  float phase = 0, step = 2 * M_PI /(float) N;
  index = 0;
  for (int i=0; i < N ; ++i) {
    tbl[i] = sin(phase);
    phase += step;
  }
}


void Seno::command(long cmd, long note, long vel) {
  if (cmd == 9) {		//'Key' pressed: attack begins
    bActive = true;
    adsr.start();
    index = 0;

    float fo = 440.0 * pow(2,((float)note-69.0)/12.0);
    float dif = fo/SamplingRate;
    float difm=fm/SamplingRate;

    A = vel/127.0F;
    B = fm*(pow(2,vel/12)-1)/(fo*(pow(2, vel/12)+1));

    alpha = 2*M_PI*dif;
    betha=2*M_PI*difm;
    tetha = 0;
    phi=0;


  }
  else if (cmd == 8) {	//'Key' released: sustain ends, release begins
    adsr.stop();
  }
  else if (cmd == 0) {	//Sound extinguished without waiting for release to end
    adsr.end();
  }
}


const vector<float> & Seno::synthesize() {
  if (not adsr.active()) {
    x.assign(x.size(), 0);
    bActive = false;
    return x;
  }
  else if (not bActive)
    return x;

  for (unsigned int i=0; i<x.size(); ++i) {
    x[i] = A * sin(tetha+B*sin(phi));
    tetha+=alpha;
    phi+=betha;

    while(tetha>M_PI){
      tetha-=2*M_PI;
    }
    while(phi>M_PI){
      phi-=2*M_PI;
    }
  }
  adsr(x); //apply envelope to x and update internal status of ADSR

  return x;
}
