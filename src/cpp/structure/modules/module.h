// Part of Arac Neural Network Composition Library.
// (c) 2008 by Justin S Bayer, <bayer.justin@googlemail.com>


#ifndef Arac_STRUCTURE_MODULES_MODULE_INCLUDED
#define Arac_STRUCTURE_MODULES_MODULE_INCLUDED


#include "../component.h"
#include "../../common/common.h"


namespace arac {
namespace structure {
namespace modules {
    
///
/// A module is something that has input data and produces output data out of 
/// this. The inputs and outputs do not necessarily have to be of the same size.
/// 

class Module : public arac::structure::Component
{
    public:

        Module();
        
        ///
        /// Create a new module and allocate the necessary buffers.
        ///
        Module(int insize, int outsize);

        ///
        /// Destroy the module. 

        virtual ~Module();

        ///
        /// Interpret the input and produce the modules output by this.
        ///
        virtual void forward();
    
        ///
        /// Add the contents at the given pointer to the input.
        ///
        void add_to_input(double* addend_p);

        ///
        /// Add the contents at the given pointer to the outerror.
        ///
        void add_to_outerror(double* addend_p);
        
        ///
        /// Clear input, output, inerror and outerror by setting them to zero.
        ///
        virtual void clear();

        ///
        /// Return a reference to the input Buffer.
        ///
        arac::common::Buffer& input();
        
        ///
        /// Return a reference the output Buffer.
        ///
        arac::common::Buffer& output();
        
        ///
        /// Return a reference to the inerror Buffer.
        ///
        arac::common::Buffer& inerror();
        
        ///
        /// Return a reference to the outerror Buffer.
        ///
        arac::common::Buffer& outerror();
        
        ///
        /// Return the input size of the module.
        ///
        int insize();
        
        ///
        /// Return the output size of the module.
        ///
        int outsize();

        ///
        /// Tell if the modules internal timestep counter points to the last timestep.
        ///
        bool last_timestep();

        
    protected:

        ///
        /// Initialize all the buffers.
        ///
        virtual void init_buffers();
        
        ///
        /// Free the space used by the buffers. Do nothing if the buffers are 
        /// not the owners of the memory.
        ///
        virtual void free_buffers();
        
        ///
        /// Expand the size of all the buffers by one row.
        ///
        virtual void expand();

        int _insize;
        int _outsize;
        
        arac::common::Buffer* _input_p;
        arac::common::Buffer* _output_p;
        arac::common::Buffer* _inerror_p;
        arac::common::Buffer* _outerror_p;
};


inline
int
Module::insize()
{
    return _insize;
}


inline
int
Module::outsize()
{
    return _outsize;
}


inline
bool 
Module::last_timestep()
{
    return (timestep() == _input_p->size());
}


inline 
void
Module::add_to_input(double* addend_p)
{
    _input_p->add(addend_p, timestep());
}


inline 
void
Module::add_to_outerror(double* addend_p)
{
    _outerror_p->add(addend_p, timestep() - 1);
}


inline
arac::common::Buffer&
Module::input()
{
    return *_input_p; 
}


inline
arac::common::Buffer&
Module::output()
{
    return *_output_p;
}


inline
arac::common::Buffer&
Module::inerror()
{
    return *_inerror_p;
}


inline
arac::common::Buffer&
Module::outerror()
{
    return *_outerror_p;
}


}
}
}


#endif

