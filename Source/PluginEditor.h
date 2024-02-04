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
class DistortionVSTAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    DistortionVSTAudioProcessorEditor (DistortionVSTAudioProcessor&);
    ~DistortionVSTAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:

    juce::Slider driveKnob, rangeKnob, mixKnob, volumeKnob; // Visual slider components
    
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
    driveAttachment, rangeAttachment, mixAttachment, volumeAttachment;
    
    DistortionVSTAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionVSTAudioProcessorEditor)
};
