/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "Tab.h"
#include "Perform.h"
#include "Edit.h"
#include "SynthModule.h"


//==============================================================================
/**
*/
class Hw3AudioProcessorEditor  :
public AudioProcessorEditor,
private Slider::Listener
{
public:
    Hw3AudioProcessorEditor (Hw3AudioProcessor&);
    ~Hw3AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void tabSelected(String tab);
    void mouseDown(const MouseEvent &) override;
    void sliderValueChanged(Slider *slider) override;
    
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Hw3AudioProcessor& processor;
    
    struct moduleSlidersObject {
        Slider *levelSlider;
        Slider *tuneSlider;
        double level;
        int tune;
    };

    Tab edit, perform;
    
    Perform performScene;
    Edit editScene;
    
    MouseListener *mouse;
    
    OwnedArray<moduleSlidersObject> modules;
    
    int numModules;
    int slidersPerModule;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Hw3AudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
