/*
  ==============================================================================

    SynthSound.h
    Created: 24 Oct 2016 3:15:01pm
    Author:  Graham Davis

  ==============================================================================
*/

#ifndef SYNTHSOUND_H_INCLUDED
#define SYNTHSOUND_H_INCLUDED

struct SynthSound : public SynthesiserSound
{
    SynthSound() {}
    ~SynthSound() {}
    
    bool appliesToNote (int /*midiNoteNumber*/) override        { return true; }
    bool appliesToChannel (int /*midiChannel*/) override        { return true; }
};



#endif  // SYNTHSOUND_H_INCLUDED
