# Continuous Complex-Valued Cellular Automata
Inspired by Lenia and quantum mechanics, this cellular automata evolves according to the Schrödinger equation, with a convolutional Hamiltonian. 

The kernel and initial state is defined within the relevant funtions inside main.cpp. 


https://github.com/MicahBrun/ContinuousComplexValuedCellularAutomata/assets/55516590/c8526b67-51bc-4f8e-9663-20c422b3e83e



## Theory
The system transforms as:
$$i \frac{\partial \psi}{\partial t} = h * \psi$$
Where $h*\psi$ represents the convolution of the functions $h$ and $\psi$. $h$ is a real valued function while $\psi$ may be complex valued.

From this we can derive that:
$$\psi(t + \Delta t) = \mathrm{exp}(-i \Delta t ~ h *) \psi(t) $$

In the frequency domain, via the convolution theorem, this becomes:
$$\tilde{\psi}(t + \Delta t) = \mathrm{exp}(-i \Delta t ~ \tilde{h}) \tilde{\psi}(t) $$
Where $\tilde{f}$ represents the Fourier transform of a function.

If $h$ is a real valued function, than the operator $h*$ is hermition. This fact means that $\mathrm{exp}(-i \Delta t ~ h *)$ is a unitary operator. As a consequence the total square magnitude (probability density in quantum mechanics) of the space is conserved. This is useful as it ensures a stable evolution of the system.

## Installation

Ensure you have the following dependency installed before running the project:

- [OpenCV](https://opencv.org/)
