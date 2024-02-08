<!-- omit in toc -->

# Distortion VST

<!-- omit in toc -->

## An audio harmonic distortion plugin created with [JUCE](https://juce.com/)

<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/shyamal10">
    <img src="images/logo.png" alt="Logo" width="100" height="100">
  </a>

  <h3 align="center">Distortion VST</h3>

  <p align="center">
    <br />
    <a href="https://github.com/othneildrew/Best-README-Template"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="">View Demo</a>
    ·
    <a href="https://github.com/shyamal10/DistortionVST/issues">Report Bug</a>
    ·
    <a href="https://github.com/shyamal10/DistortionVST/issues">Request Feature</a>
  </p>
</div>
<!-- omit in toc -->

## Contents

- [Introduction](#introduction)
- [Features](#features)
- [Manual](#manual)
  - [General](#general)
- [Technical](#technical)
  - [Design Approach](#design-approach)
  - [Overview](#overview)
    - [Level Detection](#level-detection)
    - [Log and Lin Conversion](#log-and-lin-conversion)
    - [Gain Computer](#gain-computer-1)
    - [Ballistics](#ballistics-1)
    - [Parameter Automation](#parameter-automation-1)
      - [Automating the time constants](#automating-the-time-constants)
      - [Automating the makeup gain](#automating-the-makeup-gain)
    - [LookAhead](#lookahead)
- [References](#references)

## Introduction

This VST3/AU distortion plugin was developed with the aim of creating a high-quality distortion suitable for a diverse range of signals and applications. The minimalist GUI enhances usability and avoids screen clutter. The project served as a valuable learning experience, significantly advancing my understanding of digital signal processing and digital audio effects as well as the JUCE framework. Audio programming requires fast and effecient code as audio buffers are refreshed constantly, so this was a good learning experience for me. [A demonstration is available on YouTube.]()

## Features

![VST image](images/VST.png)

- Drive
- Range
- Mix
- Volume

## Manual

#### General

- **Drive:** The drive knob is adjusts the signal level (in dB) being introduced to the amplifying algorithm. More drive pushes the signal closer to the limiting reigion, introducing more distorted artifacts.

- **Range:** The range knob configures how much the drive knob is allowed to clip the signal. So increasing the range knob would increase the maximum drive value as well.

- **Mix:** The Mix knob enables you to mix between the dry and processed signal. This can be used for parallel processing.

- **Volume:** The volume knob adjusts the level of the signal leaving the distortion algorithm, and could be applied as a general output volume slider.

## References

- (1) https://www.youtube.com/watch?v=iNCR5flSuDs&pp=ygUVanVjZSBwbHVnaW4gdHV0b3JpYWwg
- (2) http://c4dm.eecs.qmul.ac.uk/audioengineering/compressors/documents/Reiss-Tutorialondynamicrangecompression.pdf
- (3) http://c4dm.eecs.qmul.ac.uk/audioengineering/compressors/documents/Giannoulis.pdf
- (4) http://www.eecs.qmul.ac.uk/~josh/documents/2013/Giannoulis%20Massberg%20Reiss%20-%20dynamic%20range%20compression%20automation%20-%20JAES%202013.pdf
- (5) https://github.com/DanielRudrich/SimpleCompressor/blob/master/docs/lookAheadLimiter.md

[1]: https://www.youtube.com/watch?v=iNCR5flSuDs&pp=ygUVanVjZSBwbHVnaW4gdHV0b3JpYWwg
[2]: http://c4dm.eecs.qmul.ac.uk/audioengineering/compressors/documents/Reiss-Tutorialondynamicrangecompression.pdf
[3]: http://c4dm.eecs.qmul.ac.uk/audioengineering/compressors/documents/Giannoulis.pdf
[4]: http://www.eecs.qmul.ac.uk/~josh/documents/2013/Giannoulis%20Massberg%20Reiss%20-%20dynamic%20range%20compression%20automation%20-%20JAES%202013.pdf
[5]: https://github.com/DanielRudrich/SimpleCompressor/blob/master/docs/lookAheadLimiter.md
