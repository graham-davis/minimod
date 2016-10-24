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

// The FM synth voice. The FM synth is hardcoded here but ideally it should be in its own class
// to have a clear hierarchy (Sine -> FMSynth -> FMVoice)
struct SynthVoice : public SynthesiserVoice
{
    SynthVoice()
    {
    }
    
    bool canPlaySound (SynthesiserSound* sound) override
    {
        return dynamic_cast<SynthSound*> (sound) != nullptr;
    }
    
    void startNote (int midiNoteNumber, float velocity,
                    SynthesiserSound*, int /*currentPitchWheelPosition*/) override
    {

    }
    
    void stopNote (float /*velocity*/, bool allowTailOff) override
    {

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

    }
    
private:
};



#endif  // SYNTHVOICE_H_INCLUDED
