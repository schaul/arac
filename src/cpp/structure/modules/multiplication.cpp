// Part of Arac Neural Network Composition Library.
// (c) 2008 by Justin S Bayer, <bayer.justin@googlemail.com>


#include <iostream>
#include <cstring>

#include "multiplication.h"
#include "../../common/functions.h"


using arac::common::sigmoid;
using arac::common::sigmoidprime;

using arac::structure::modules::MultiplicationLayer;


void
MultiplicationLayer::_forward()
{
    double* input_p = input()[timestep()];
    double* output_p = output()[timestep()];
    for(int i = 0, j =  outsize(); i < outsize(); i++, j++)
    {
        output_p[i] = input_p[i] * input_p[j];
    }
}


void
MultiplicationLayer::_backward()
{
    // Shortcuts.
    double* inerror_p = inerror()[timestep() - 1];
    double* outerror_p = outerror()[timestep() - 1];
    double* input_p = input()[timestep() - 1];

    for (int i = 0; i < outsize(); i++)
    {
        inerror_p[i] = input_p[i + outsize()] * outerror_p[i];
    }
    for(int i = 0; i < outsize(); i++)
    {
        inerror_p[i + outsize()] = input_p[i] * outerror_p[i];
    }
}


