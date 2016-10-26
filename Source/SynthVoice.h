/*
  ==============================================================================

    SynthVoice.h
    Created: 24 Oct 2016 3:13:41pm
    Author:  Graham Davis

  ==============================================================================
*/

#ifndef SYNTHVOICE_H_INCLUDED
#define SYNTHVOICE_H_INCLUDED

#include "./SynthSound.h"
#include "./Sine.h"
#include "./Smooth.h"
#include "./Faust/Saw.h"
#include "./Faust/ModularSynth.h"
#include "./Faust/FaustReverb.h"



// The FM synth voice. The FM synth is hardcoded here but ideally it should be in its own class
// to have a clear hierarchy (Sine -> FMSynth -> FMVoice)
struct SynthVoice : public SynthesiserVoice
{
    SynthVoice(): tune(0.0), level(0.5), onOff(false), keyVelocity(0.0), envelope(0.0)
    {
        for(int i=0; i<4; i++) {
            synthModule *module = new synthModule;
            module->tune = 0.0;
            module->level = 0.5;
            synthModules.add(module);
            
            sinusoids[i].setSamplingRate(getSampleRate());
        }
        
        reverb.init(getSampleRate());
        
        modSynth.init(getSampleRate());
        modSynth.buildUserInterface(&synthControl);

        miniBuffer = new float*[2];
        miniBuffer[0] = new float;
        miniBuffer[1] = new float;
    }
    
    ~SynthVoice()
    {
        delete [] miniBuffer;
    }
    
    bool canPlaySound (SynthesiserSound* sound) override
    {
        return dynamic_cast<SynthSound*> (sound) != nullptr;
    }
    
    void startNote (int midiNoteNumber, float velocity,
                    SynthesiserSound*, int /*currentPitchWheelPosition*/) override
    {
        midiFrequency = midiNoteNumber;
        level = velocity;
        onOff = true;
        
        for(int i=0; i<9; i++) {
            smooth[i].setSmooth(0.999);
        }
        
        synthControl.setParamValue("/modSynth/gate", 1);

    }
    
    void stopNote (float /*velocity*/, bool allowTailOff) override
    {
        onOff = false;
        level = 0;
    }
    
    void pitchWheelMoved (int /*newValue*/) override
    {
        // Pitch wheel is an important standard MIDI feature that should be implemented
    }
    
    void controllerMoved (int /*controllerNumber*/, int /*newValue*/) override
    {
        // Thats where you would change the value of the modulator index and frequency
        // if you wanted to control them with MIDI controllers
    }
    
    void renderNextBlock (AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override
    {
        if (envelope != 0 || onOff) {
            synthControl.setParamValue("/modSynth/freq0", MidiMessage::getMidiNoteInHertz(midiFrequency+synthModules[0]->tune));
            synthControl.setParamValue("/modSynth/freq1", MidiMessage::getMidiNoteInHertz(midiFrequency+synthModules[1]->tune));
            synthControl.setParamValue("/modSynth/freq2", MidiMessage::getMidiNoteInHertz(midiFrequency+synthModules[2]->tune));
            synthControl.setParamValue("/modSynth/freq3", MidiMessage::getMidiNoteInHertz(midiFrequency+synthModules[3]->tune));
            
            synthControl.setParamValue("/modSynth/gain0", synthModules[0]->level);
            synthControl.setParamValue("/modSynth/gain1", synthModules[1]->level);
            synthControl.setParamValue("/modSynth/gain2", synthModules[2]->level);
            synthControl.setParamValue("/modSynth/gain3", synthModules[3]->level);
            
            while (--numSamples >= 0) {
                for (int i = outputBuffer.getNumChannels(); --i >= 0;) {
                    modSynth.compute(1, NULL, miniBuffer);
                    
                    envelope = smooth[0].tick(level);
                    double currentSample = miniBuffer[0][0] * envelope;
                    outputBuffer.addSample(i, startSample, currentSample);
                }

                if(!onOff && envelope < 0.0001){
                    envelope = 0;
                    synthControl.setParamValue("/modSynth/gate", 0);
                    clearCurrentNote();
                }
                
                ++startSample;
            }
        }
    }
    
    void updateTune(int index, int newTune) {
        synthModules[index]->tune = newTune;
    }
    
    void updateLevel(int index, float newLevel) {
        synthModules[index]->level = newLevel;
    }
    
private:
    int tune;
    float level;
    bool onOff;
    int midiFrequency;
    double sawFrequency;
    int keyVelocity;
    float envelope;
    Sine sinusoids[3];
    Smooth smooth[9];
    
    float **audioBuffer;
    float **miniBuffer;
    
    FaustReverb reverb;
    
    ModularSynth modSynth;
    MapUI synthControl;
    
    struct synthModule {
        int tune;
        float level;
    };
    
    OwnedArray<synthModule> synthModules;
};



#endif  // SYNTHVOICE_H_INCLUDED
