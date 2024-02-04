/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
//==============================================================================
/**
*/
class OtherLookandFeel : public juce::LookAndFeel_V4
{
public:
    void drawRotarySlider(juce::Graphics &g, int x, int y, int width, int height, float sliderPos,
                          float rotaryStartAngle, float RotaryEndAngle, juce::Slider &slider) override
    {
        float diameter = fmin(width, height); //Find lesser of width or height
        float radius = diameter / 2;
        float centreX = x + width / 2;
        float centreY = y + height / 2;
        float rx = centreX - radius; //Starting point for right position of dial
        float ry = centreY - radius;
        float angle = rotaryStartAngle + (sliderPos * (RotaryEndAngle - rotaryStartAngle)); //Compute the angle
        
        juce::Rectangle<float> dialArea (rx, ry, diameter, diameter);
        
        g.setColour(juce::Colour(0xff6D97F2)); //Sets colour of the dial fill
        g.fillEllipse(dialArea);
        
        g.setColour(juce::Colours::white);
        
        //Adding tick mark in dial
        juce::Path dialTick;
        dialTick.addRectangle(0, -radius, 10.f, radius * 0.33);
        
        g.fillPath(dialTick, juce::AffineTransform::rotation(angle).translated(centreX,centreY));

    }
    /*
    OtherLookandFeel()
    {
        setColour(juce::Slider::thumbColourId, juce::Colours::black);
    }
    */
};

class DistortionVSTAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    DistortionVSTAudioProcessorEditor (DistortionVSTAudioProcessor&);
    ~DistortionVSTAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:

    OtherLookandFeel otherLookAndFeel;
    
    juce::Slider driveKnob, rangeKnob, mixKnob, volumeKnob; // Visual slider components
    
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
    driveAttachment, rangeAttachment, mixAttachment, volumeAttachment;
    
    DistortionVSTAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionVSTAudioProcessorEditor)
};
