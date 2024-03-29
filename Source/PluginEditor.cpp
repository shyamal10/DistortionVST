/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DistortionVSTAudioProcessorEditor::DistortionVSTAudioProcessorEditor (DistortionVSTAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Set slider styles
    driveKnob.setSliderStyle (juce::Slider::SliderStyle::Rotary);
    driveKnob.setTextBoxStyle (juce::Slider::NoTextBox, false, 100, 100);
    addAndMakeVisible(driveKnob);
    
    rangeKnob.setSliderStyle (juce::Slider::SliderStyle::Rotary);
    rangeKnob.setTextBoxStyle (juce::Slider::NoTextBox, false, 100, 100);
    addAndMakeVisible(rangeKnob);
    
    mixKnob.setSliderStyle (juce::Slider::SliderStyle::Rotary);
    mixKnob.setTextBoxStyle (juce::Slider::NoTextBox, false, 100, 100);
    addAndMakeVisible(mixKnob);
    
    volumeKnob.setSliderStyle (juce::Slider::SliderStyle::Rotary);
    volumeKnob.setTextBoxStyle (juce::Slider::NoTextBox, false, 100, 100);
    addAndMakeVisible(volumeKnob);
    
    //Set custom look and feel for dials
    driveKnob.setLookAndFeel(&otherLookAndFeel);
    rangeKnob.setLookAndFeel(&otherLookAndFeel);
    mixKnob.setLookAndFeel(&otherLookAndFeel);
    volumeKnob.setLookAndFeel(&otherLookAndFeel);
    
    // Create attachments for each slider
    driveAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "drive", driveKnob);
    rangeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "range", rangeKnob);
    mixAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "mix", mixKnob);
    volumeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "volume", volumeKnob);
    setResizable(true, true);
    setSize (600, 200);
}

DistortionVSTAudioProcessorEditor::~DistortionVSTAudioProcessorEditor()
{
}

//==============================================================================
void DistortionVSTAudioProcessorEditor::paint (juce::Graphics& g)
{
    //g.fillAll(juce::Colour(0xFF28282B)); //Matte Black Colour
    Background = juce::ImageCache::getFromMemory(BinaryData::Background_png, BinaryData::Background_pngSize);
    g.drawImageWithin(Background, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::stretchToFit);
    
    
    g.setColour(juce::Colours::whitesmoke);
    g.setFont(juce::Font("Avenir Next Condensed", 20.f, 1));
    
    //Set labels
    g.drawText("DistortionVST", ((getWidth() / 5) * 4.5) - (100/ 2), (getHeight() / 2) + 40, 100, 100, juce::Justification::centred, false);
    g.drawText("Drive", ((getWidth() / 5) * 1) - (100/ 2 ), (getHeight() / 2) + 15, 100, 100, juce::Justification::centred, false);
    g.drawText("Range", ((getWidth() / 5) * 2) - (100/ 2 ), (getHeight() / 2) + 15, 100, 100, juce::Justification::centred, false);
    g.drawText("Mix", ((getWidth() / 5) * 3) - (100/ 2 ), (getHeight() / 2) + 15, 100, 100, juce::Justification::centred, false);
    g.drawText("Volume", ((getWidth() / 5) * 4) - (100/ 2 ), (getHeight() / 2) + 15, 100, 100, juce::Justification::centred, false);

    
}

void DistortionVSTAudioProcessorEditor::resized()
{
    auto componentSize = 100;
    // Layout components
    driveKnob.setBounds(((getWidth() / 5) * 1) - (componentSize/ 2 ), (getHeight() / 2) - (componentSize / 2), componentSize, componentSize);
    rangeKnob.setBounds(((getWidth() / 5) * 2) - (componentSize/ 2 ), (getHeight() / 2) - (componentSize / 2), componentSize, componentSize);
    mixKnob.setBounds(((getWidth() / 5) * 3) - (componentSize/ 2 ), (getHeight() / 2) - (componentSize / 2), componentSize, componentSize);
    volumeKnob.setBounds(((getWidth() / 5) * 4) - (componentSize/ 2 ), (getHeight() / 2) - (componentSize / 2), componentSize, componentSize);

}

