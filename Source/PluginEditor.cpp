/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
Hw3AudioProcessorEditor::Hw3AudioProcessorEditor (Hw3AudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    numModules = 4;
    slidersPerModule = 2;
    
    // Set up tabs and mouse listeners
    mouse = new MouseListener;
    this->addMouseListener(mouse, true);
    
    // Set up listeners for modules and their sliders
    for (int i = 0; i < numModules; i++) {
        SynthModule *module = editScene.getModule(i);
        moduleSlidersObject *sliderObj = new moduleSlidersObject;
        Slider *levelSliderP = module->getSlider(0);
        Slider *tuneSliderP = module->getSlider(1);
        levelSliderP->addListener(this);
        tuneSliderP->addListener(this);
        
        sliderObj->levelSlider = levelSliderP;
        sliderObj->tuneSlider = tuneSliderP;
        modules.add(sliderObj);
    }
    
    
    edit.setText("Edit");
    perform.setText("Perform");
    edit.flip();
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 500);
}

Hw3AudioProcessorEditor::~Hw3AudioProcessorEditor()
{
}

//==============================================================================
void Hw3AudioProcessorEditor::paint (Graphics& g)
{
}

void Hw3AudioProcessorEditor::resized()
{
    // Add Tabs to the canvas
    addAndMakeVisible(edit);
    addAndMakeVisible(perform);
    
    int tabHeight = 45;
    
    Rectangle<int> area = getLocalBounds();
    {
        Rectangle<int> tabArea = area.removeFromTop(tabHeight);
        {
            edit.setBounds(tabArea.removeFromLeft(getWidth()/2));
            perform.setBounds(tabArea.removeFromRight(getWidth()/2));
        }
        Rectangle<int> mainArea = area.removeFromBottom(getHeight()-tabHeight);
        if (edit.isEngaged()) {
            addAndMakeVisible(editScene);
            performScene.setVisible(false);
            editScene.setBounds(mainArea);
        } else if (perform.isEngaged()) {
            addAndMakeVisible(performScene);
            performScene.setBounds(mainArea);
            editScene.setVisible(false);
        }
    }

}

void Hw3AudioProcessorEditor::mouseDown (const MouseEvent &e)
{
    if (edit.getBounds().contains(e.x, e.y) && !edit.isEngaged()) {
        edit.flip();
        perform.flip();
        this->resized();
    } else if (perform.getBounds().contains(e.x, e.y) && !perform.isEngaged()) {
        perform.flip();
        edit.flip();
        this->resized();
    }
}

void Hw3AudioProcessorEditor::sliderValueChanged(Slider *slider)
{
    for (int i = 0; i < numModules; i++) {
        if (slider == modules[i]->levelSlider) {
            modules[i]->level = modules[i]->levelSlider->getValue();
            processor.updateModuleLevel(i, modules[i]->level);
        } else if (slider == modules[i]->tuneSlider) {
            modules[i]->tune = modules[i]->tuneSlider->getValue();
            processor.updateModuleTune(i, modules[i]->tune);
        }
    }
}
