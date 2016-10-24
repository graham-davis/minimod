/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
Hw3AudioProcessor::Hw3AudioProcessor()
{
    // Initialize synth module control listeners
    for (int i=0; i<4; i++) {
        synthModuleControl *newSynthModule = new synthModuleControl;
        newSynthModule->level = .5;
        newSynthModule->tune = 0;
        synthModules.add(newSynthModule);
    }
    
    // Initialize synthesizer voices and sound
    int numVoices = 4;
    for (int i=numVoices; --i >= 0;)
    {
        synth.addVoice(new SynthVoice());
    }
    synth.clearSounds();
    synth.addSound(new SynthSound());
}

Hw3AudioProcessor::~Hw3AudioProcessor()
{
}

//==============================================================================
const String Hw3AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Hw3AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Hw3AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double Hw3AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Hw3AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Hw3AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Hw3AudioProcessor::setCurrentProgram (int index)
{
}

const String Hw3AudioProcessor::getProgramName (int index)
{
    return String();
}

void Hw3AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Hw3AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void Hw3AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Hw3AudioProcessor::setPreferredBusArrangement (bool isInput, int bus, const AudioChannelSet& preferredSet)
{
    // Reject any bus arrangements that are not compatible with your plugin

    const int numChannels = preferredSet.size();

   #if JucePlugin_IsMidiEffect
    if (numChannels != 0)
        return false;
   #elif JucePlugin_IsSynth
    if (isInput || (numChannels != 1 && numChannels != 2))
        return false;
   #else
    if (numChannels != 1 && numChannels != 2)
        return false;

    if (! AudioProcessor::setPreferredBusArrangement (! isInput, bus, preferredSet))
        return false;
   #endif

    return AudioProcessor::setPreferredBusArrangement (isInput, bus, preferredSet);
}
#endif

void Hw3AudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

//==============================================================================
bool Hw3AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Hw3AudioProcessor::createEditor()
{
    return new Hw3AudioProcessorEditor (*this);
}

//==============================================================================
void Hw3AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Hw3AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Hw3AudioProcessor();
}

//==============================================================================
void Hw3AudioProcessor::updateModuleLevel(int index, float newLevel) {
    synthModules[index]->level = newLevel;
    std::cout << "Module: " << index << "Level: " << newLevel << std::endl;
}

void Hw3AudioProcessor::updateModuleTune(int index, int newTune) {
    synthModules[index]->tune = newTune;
    std::cout << "Module: " << index << "Tune: " << newTune << std::endl;

}
