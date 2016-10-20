/*
  ==============================================================================

    Edit.h
    Created: 20 Oct 2016 11:38:07am
    Author:  Graham Davis

  ==============================================================================
*/

#ifndef EDIT_H_INCLUDED
#define EDIT_H_INCLUDED

#import "SynthModule.h"

class Edit       : public Component{
public:
    Edit(){
        for (int i = 0; i < 4; i++) {
            modules.add(new SynthModule);
            addAndMakeVisible(modules[i]);
        }
    }
    
    ~Edit(){
    }
    
    void paint (Graphics& g) override
    {
        g.fillAll(Colour::fromRGB(253, 253, 253));
    }
    
    void resized() override
    {
        modules[0]->setBounds(1, 1, (getWidth()/2)-2, (getHeight()/2)-2);
        modules[1]->setBounds(getWidth()/2 + 1, 1, getWidth()/2 - 2, getHeight()/2 - 2);
        modules[2]->setBounds(1, getHeight()/2 + 1, getWidth()/2 - 2, getHeight()/2 - 2);
        modules[3]->setBounds(getWidth()/2 + 1, getHeight()/2 + 1, getWidth()/2 - 2, getHeight()/2 - 2);
    }
    
    SynthModule *getModule(int index) {
        return modules[index];
    }
    
private:
    OwnedArray<SynthModule> modules;
};



#endif  // EDIT_H_INCLUDED
