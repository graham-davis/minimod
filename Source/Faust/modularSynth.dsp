import("stdfaust.lib");
nOsc = 4;
freq0 = hslider("freq0",440,20,20000,0.01);
freq1 = hslider("freq1",440,20,20000,0.01);
freq2 = hslider("freq2",440,20,20000,0.01);
freq3 = hslider("freq3",440,20,20000,0.01);

gain0 = hslider("gain0",1,0,1,0.01) : si.smoo;
gain1 = hslider("gain1",1,0,1,0.01) : si.smoo;
gain2 = hslider("gain2",1,0,1,0.01) : si.smoo;
gain3 = hslider("gain3",1,0,1,0.01) : si.smoo;

trigger = button("gate");

synth = (os.sawtooth(freq0)*gain0*trigger)+(os.osc(freq1)*gain1*trigger)+(os.square(freq2)*gain2*trigger)+(os.triangle(freq3)*gain3*trigger);

process = hgroup("modSynth", synth / nOsc);