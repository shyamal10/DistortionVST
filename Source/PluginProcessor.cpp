/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DistortionVSTAudioProcessor::DistortionVSTAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, nullptr, "Parameters", createParameters())
#endif
{
}

DistortionVSTAudioProcessor::~DistortionVSTAudioProcessor()
{
}

//==============================================================================
const juce::String DistortionVSTAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DistortionVSTAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DistortionVSTAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DistortionVSTAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DistortionVSTAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DistortionVSTAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DistortionVSTAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DistortionVSTAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String DistortionVSTAudioProcessor::getProgramName (int index)
{
    return {};
}

void DistortionVSTAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void DistortionVSTAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void DistortionVSTAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DistortionVSTAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void DistortionVSTAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // Get raw parameter values
    auto drive = apvts.getRawParameterValue("drive")->load();
    auto range = apvts.getRawParameterValue("range")->load();
    auto mix = apvts.getRawParameterValue("mix")->load();
    auto volume = apvts.getRawParameterValue("volume")->load();
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        
        for (int sample = 0; sample < buffer.getNumSamples(); sample++)
        {
            float cleanSig = *channelData;
            
            *channelData *= drive * range;
            // Distortion function
            *channelData = (((((2.f / juce::MathConstants<float>::pi) * atan(*channelData)) * mix) + (cleanSig * (1.f/ mix))) / 2) * volume;
           
            channelData++;
        }

    }
}

//==============================================================================
bool DistortionVSTAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* DistortionVSTAudioProcessor::createEditor()
{
    return new DistortionVSTAudioProcessorEditor (*this);
}

//==============================================================================
void DistortionVSTAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void DistortionVSTAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DistortionVSTAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout DistortionVSTAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"drive", 1}, "Drive", 0.f, 1.f, 0.01f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"range", 1}, "Range", 0.f, 2000.f, 0.01f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"mix", 1}, "Mix", 0.f, 1.f, 1.f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"volume", 1}, "Volume", 0.f, 1.f, 0.01f));

    return {params.begin(), params.end()};

}

