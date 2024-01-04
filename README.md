# Continuous Complex-Valued Cellular Automata
Inspired by Lenia and quantum mechanics, this cellular automata evolves according to the Schrödinger equation, with a convolutional Hamiltonian. 

The kernel and initial state are defined within the relevant funtions inside main.cpp. 


https://github.com/MicahBrun/ContinuousComplexValuedCellularAutomata/assets/55516590/c8526b67-51bc-4f8e-9663-20c422b3e83e

## Visualisation
SFML is used for the visualisation of the system at a certain time. The system is made up of a 2-D grid where each point stores a complex value. In the visualisation, the complex number is converted into a colour. The hue of the colour corresponds to the phase of the complex number; the brightness is proportional to the arctangent of the magnitude. 

## Theory
The system transforms as:
$$i \frac{\partial \psi}{\partial t} = h * \psi$$
Where $h*\psi$ represents the convolution of the functions $h$ and $\psi$. $h$ is a real valued function while $\psi$ may be complex valued.

From this we can derive that:
$$\psi(t + \Delta t) = \mathrm{exp}(-i \Delta t ~ h *) \psi(t) $$

In the frequency domain, making use of the convolution theorem, this becomes:
$$\tilde{\psi}(t + \Delta t) = \mathrm{exp}(-i \Delta t ~ \tilde{h}) \tilde{\psi}(t) $$
Where $\tilde{f}$ represents the Fourier transform of a function.

If $h$ is a real valued function, than the operator $h*$ is hermition. This fact means that $\mathrm{exp}(-i \Delta t ~ h *)$ is a unitary operator. As a consequence the total square magnitude (probability density in quantum mechanics) of the space is conserved. This is useful as it ensures a stable evolution of the system.

## Installation

Ensure you have the following dependency installed before running the project:

- [OpenCV](https://opencv.org/)
