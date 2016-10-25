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
        
        for(int i=0; i<4; i++) {
            smooth[i].setSmooth(0.999);
        }

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
            while (--numSamples >= 0){
                envelope = smooth[0].tick(level);
                for (int i=0; i<4; i++) {
                    sinusoids[i].setFrequency(MidiMessage::getMidiNoteInHertz(midiFrequency+synthModules[i]->tune));
                }
                float currentSample = 0;
                for (int i=0; i<4; i++) {
                    currentSample += sinusoids[i].tick()*synthModules[i]->level;
                }
                currentSample = (currentSample / 4) * envelope;
                for (int i = outputBuffer.getNumChannels(); --i >= 0;){
                    outputBuffer.addSample (i, startSample, currentSample);
                }
                ++startSample;
                
                if(!onOff && envelope < 0.001){
                    envelope = 0;
                    clearCurrentNote();
                }
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
    int keyVelocity;
    float envelope;
    Sine sinusoids[4];
    Smooth smooth[4];
    
    struct synthModule {
        int tune;
        float level;
    };
    
    OwnedArray<synthModule> synthModules;
};



#endif  // SYNTHVOICE_H_INCLUDED
