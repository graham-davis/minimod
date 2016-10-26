import("stdfaust.lib");
frequency = nentry("freq",440,20,20000,0.01) : si.smoo;
level = nentry("gain",1,0,1,0.01) : si.smoo;
onoff = button("gate") : si.smoo;
process = hgroup("saw",os.sawtooth(frequency) * level * onoff);