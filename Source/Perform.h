/*
  ==============================================================================

    Perform.h
    Created: 20 Oct 2016 11:37:57am
    Author:  Graham Davis

  ==============================================================================
*/

#ifndef PERFORM_H_INCLUDED
#define PERFORM_H_INCLUDED


class Perform       : public Component{
public:
    Perform(){
    }
    
    ~Perform(){}
    
    void paint (Graphics& g) override
    {
        g.fillAll (Colour::fromRGB(107, 119, 123));
    }
    
    void resized() override
    {
        
    }
};





#endif  // PERFORM_H_INCLUDED
