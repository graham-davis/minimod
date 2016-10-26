/*
  ==============================================================================

    Perform.h
    Created: 20 Oct 2016 11:37:57am
    Author:  Graham Davis

  ==============================================================================
*/

#ifndef PERFORM_H_INCLUDED
#define PERFORM_H_INCLUDED


class Perform       :
public Component {
public:
    Perform(){
    }
    
    ~Perform(){}
    
    void paint (Graphics& g) override
    {
        g.fillAll(Colours::black);

        g.setColour(Colour::fromRGB(253, 253, 253));
        
        g.setColour(Colour::fromRGB(107, 119, 123));
        g.drawLine(0, 0, getWidth(), 0, 2);
        
        g.setFont(Font("Avenir", 20.0f, Font::plain));
        g.drawText("This is where my awesome audio visualizer would go if I had time!", 0, 0, getWidth(), getHeight()/2, Justification::centred);
    }
    
    void resized() override
    {
        
    }
};


#endif  // PERFORM_H_INCLUDED
