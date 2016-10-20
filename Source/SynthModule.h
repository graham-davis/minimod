/*
  ==============================================================================

    SynthModule.h
    Created: 20 Oct 2016 1:02:28pm
    Author:  Graham Davis

  ==============================================================================
*/

#ifndef SYNTHMODULE_H_INCLUDED
#define SYNTHMODULE_H_INCLUDED

class SynthModule       :
public Component {

public:
    SynthModule(){
        
        sliders.add(new Slider);
        sliders.add(new Slider);
        
        // Add level meter
        addAndMakeVisible(sliders[0]);
        sliders[0]->setRange(0, 1, .01);
        sliders[0]->setValue(0.5);
        sliders[0]->setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        sliders[0]->setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 30);
        sliders[0]->setColour(Slider::ColourIds::rotarySliderFillColourId, Colour::fromRGB(91, 199, 235));
        
        // Add label for level meter
        addAndMakeVisible(levelLabel);
        levelLabel.setText("Level", dontSendNotification);
        levelLabel.setColour(Label::ColourIds::textColourId, Colour::fromRGB(64, 71, 73));
        levelLabel.setJustificationType(Justification::centredTop);
        levelLabel.attachToComponent(sliders[0], false);
        
        // Add tune meter
        addAndMakeVisible(sliders[1]);
        sliders[1]->setRange(-12, 12, 1);
        sliders[1]->setValue(0);
        sliders[1]->setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        sliders[1]->setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 30);
        sliders[1]->setColour(Slider::ColourIds::rotarySliderFillColourId, Colour::fromRGB(91, 199, 235));
        
        // Add tune label
        addAndMakeVisible(tuneLabel);
        tuneLabel.setText("Tune", dontSendNotification);
        tuneLabel.setColour(Label::ColourIds::textColourId, Colour::fromRGB(64, 71, 73));
        tuneLabel.setJustificationType(Justification::centredTop);
        tuneLabel.attachToComponent(sliders[1], false);
    }
    
    ~SynthModule(){}
    
    void paint (Graphics& g) override
    {
        g.fillAll (Colour::fromRGB(107, 119, 123));
    }
    
    void resized() override
    {
        int sliderHeight = 100;
        int border = 10;
        Rectangle<int> area = getLocalBounds();
        {
            Rectangle<int> rotaryArea = area.removeFromTop(sliderHeight + border*2).withTrimmedLeft(border).withTrimmedRight(border);
            {
                sliders[0]->setBounds(getWidth()/2 - border - sliderHeight, border*3, sliderHeight, sliderHeight);
                sliders[1]->setBounds(getWidth()/2 + border, border*3, sliderHeight, sliderHeight);
            }
        }
    }
    
    Slider *getSlider(int index) {
        return sliders[index];
    }
    
private:
    OwnedArray<Slider> sliders;
    Label levelLabel, tuneLabel;
};



#endif  // SYNTHMODULE_H_INCLUDED
