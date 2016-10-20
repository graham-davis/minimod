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
    
    // Set up tabs and mouse listeners
    mouse = new MouseListener;
    this->addMouseListener(mouse, true);
    
    // Set up listeners for modules and their sliders
    for (int i = 0; i < 4; i++) {
        SynthModule *module = editScene.getModule(i);
        moduleSlidersObject *sliderObj = new moduleSlidersObject;
        Slider *levelSlider = module->getSlider(0);
        Slider *tuneSlider = module->getSlider(1);
        levelSlider->addListener(this);
        tuneSlider->addListener(this);
        
        sliderObj->level = levelSlider;
        sliderObj->tune = tuneSlider;
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
    std::cout << slider->getValue() << std::endl;
}
