// Part of Arac Neural Network Composition Library.
// (c) 2008 by Justin S Bayer, <bayer.justin@googlemail.com>


#include <iostream>

#include "linear.h"


using arac::structure::connections::LinearConnection;
using arac::structure::connections::Connection;
using arac::structure::Parametrized;
using arac::structure::modules::Module;


LinearConnection::LinearConnection(Module* incoming_p, Module* outgoing_p) :
    Connection(incoming_p, outgoing_p),
    Parametrized(incoming_p->insize())
{
    // TODO: make sure the sizes of the modules and slices are correct.
}


LinearConnection::LinearConnection(Module* incoming_p, Module* outgoing_p,
                               int incomingstart, int incomingstop, 
                               int outgoingstart, int outgoingstop) :
    Connection(incoming_p, outgoing_p, 
               incomingstart, incomingstop, 
               outgoingstart, outgoingstop),
    Parametrized(incoming_p->insize())
{
    // TODO: make sure the sizes of the modules and slices are correct.
}


LinearConnection::LinearConnection(Module* incoming_p, Module* outgoing_p,
               double* parameters_p, double* derivatives_p,
               int incomingstart, int incomingstop, 
               int outgoingstart, int outgoingstop) :
    Connection(incoming_p, outgoing_p, 
               incomingstart, incomingstop,
               outgoingstart, outgoingstop),
    Parametrized((incomingstop - incomingstart), parameters_p, derivatives_p)           
{
    // TODO: make sure the sizes of the modules and slices are correct.
}   

            
LinearConnection::~LinearConnection()
{
    if (parameters_owner())
    {
        delete _parameters_p;
        _parameters_p = 0;
    }
    if (derivatives_owner())
    {
        delete _derivatives_p;
        _derivatives_p = 0;
    }
}


void LinearConnection::forward_process(double* sink_p, const double* source_p)
{
    double* weights_p = get_parameters();
    int size = get_outgoingstop() - get_outgoingstart();
    for(int i = 0; i < size; i++)
    {
        sink_p[i] += source_p[i] * weights_p[i];
    }
}


void LinearConnection::backward_process(double* sink_p, const double* source_p)
{
    double* weights_p = get_parameters();
    double* input_p = \
        _incoming_p->output()[timestep() - 1] + _incomingstart;

    int size = get_outgoingstop() - get_outgoingstart();

    for (int i = 0; i < size; i++)
    {
        sink_p[i] += weights_p[i] * source_p[i];
    }

    double* derivs_p = get_derivatives();
    for (int i = 0; i < size; i++)
    {
        derivs_p[i] += source_p[i] * input_p[i];
    }
}

