/*
  ==============================================================================

    Tab.h
    Created: 20 Oct 2016 9:46:58am
    Author:  Graham Davis

  ==============================================================================
*/

#include "PluginEditor.h"

#ifndef TAB_H_INCLUDED
#define TAB_H_INCLUDED

class Tab       : public Component{
public:
    Tab(): text("Tab"), engaged(false){
       setInterceptsMouseClicks(false, false);
    }
    
    ~Tab(){}
    
    void paint (Graphics& g) override
    {
        g.fillAll(Colours::black);
        if (engaged) {
            g.setColour(Colour::fromRGB(91, 199, 235));
        } else {
            g.setColour(Colour::fromRGB(253, 253, 253));

        }
        g.setFont(Font("Avenir", 20.0f, Font::plain));
        g.drawText(text, 0, 0, getWidth(), (getHeight()/2)+20, Justification::centred);
    }
    
    void resized() override
    {
        
    }
    
    void setText(String newText) {
        text = newText;
    }
    
    void flip() {
        engaged = !engaged;
        repaint();
    }
    
    bool isEngaged() {
        return engaged;
    }
    
private:
    String text;
    bool engaged;
};



#endif  // TAB_H_INCLUDED
