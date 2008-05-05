#pragma once

#include <boost/shared_ptr.hpp>
#include "Egl/SurfaceProperties.hpp"

namespace Egl
{
    /** All surface properties. */
    namespace SurfaceProperties
    {
        namespace detail
        {
            /** Converts Egl surface properties to Cpw ones. */
            unsigned int ToCpw(const boost::int64_t nSurfaceProperties)
            {
                // Convert a DGL surface propery to CPW
                unsigned int nCpwSurfaceProperties = 0;
            #   define MAP_SURFACE_PROP_TO_CPW(MSurfaceProp, MCpwSurfaceProp) \
                    if (MSurfaceProp == (nSurfaceProperties & MSurfaceProp)) \
                        nCpwSurfaceProperties |= MCpwSurfaceProp;
                    
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_RGBA,CPW_SURFACE_RGBA);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_INDEX,CPW_SURFACE_INDEX);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_SINGLE,CPW_SURFACE_SINGLE);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_DOUBLE,CPW_SURFACE_DOUBLE);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_ACCUM,CPW_SURFACE_ACCUM);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_DEPTH,CPW_SURFACE_DEPTH);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_STENCIL,CPW_SURFACE_STENCIL);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_STEREO,CPW_SURFACE_STEREO);

                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_COLOR8,CPW_SURFACE_COLOR8);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_COLOR16,CPW_SURFACE_COLOR16);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_COLOR32,CPW_SURFACE_COLOR32);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_COLOR64,CPW_SURFACE_COLOR64);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_RED2,CPW_SURFACE_RED2);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_RED4,CPW_SURFACE_RED4);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_RED8,CPW_SURFACE_RED8);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_RED16,CPW_SURFACE_RED16);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_GREEN2,CPW_SURFACE_GREEN2);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_GREEN4,CPW_SURFACE_GREEN4);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_GREEN8,CPW_SURFACE_GREEN8);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_GREEN16,CPW_SURFACE_GREEN16);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_BLUE2,CPW_SURFACE_BLUE2);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_BLUE4,CPW_SURFACE_BLUE4);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_BLUE8,CPW_SURFACE_BLUE8);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_BLUE16,CPW_SURFACE_BLUE16);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_ALPHA2,CPW_SURFACE_ALPHA2);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_ALPHA4,CPW_SURFACE_ALPHA4);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_ALPHA8,CPW_SURFACE_ALPHA8);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_ALPHA16,CPW_SURFACE_ALPHA16);

                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_DEPTH2,CPW_SURFACE_DEPTH2);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_DEPTH4,CPW_SURFACE_DEPTH4);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_DEPTH8,CPW_SURFACE_DEPTH8);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_DEPTH16,CPW_SURFACE_DEPTH16);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_DEPTH32,CPW_SURFACE_DEPTH32);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_DEPTH64,CPW_SURFACE_DEPTH64);

                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_ACOLOR8,CPW_SURFACE_ACOLOR8);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_ACOLOR16,CPW_SURFACE_ACOLOR16);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_ACOLOR32,CPW_SURFACE_ACOLOR32);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_ACOLOR64,CPW_SURFACE_ACOLOR64);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_ARED2,CPW_SURFACE_ARED2);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_ARED4,CPW_SURFACE_ARED4);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_ARED8,CPW_SURFACE_ARED8);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_ARED16,CPW_SURFACE_ARED16);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_AGREEN2,CPW_SURFACE_AGREEN2);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_AGREEN4,CPW_SURFACE_AGREEN4);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_AGREEN8,CPW_SURFACE_AGREEN8);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_AGREEN16,CPW_SURFACE_AGREEN16);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_ABLUE2,CPW_SURFACE_ABLUE2);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_ABLUE4,CPW_SURFACE_ABLUE4);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_ABLUE8,CPW_SURFACE_ABLUE8);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_ABLUE16,CPW_SURFACE_ABLUE16);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_AALPHA2,CPW_SURFACE_AALPHA2);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_AALPHA4,CPW_SURFACE_AALPHA4);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_AALPHA8,CPW_SURFACE_AALPHA8);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_AALPHA16,CPW_SURFACE_AALPHA16);

                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_ADEPTH2,CPW_SURFACE_ADEPTH2);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_ADEPTH4,CPW_SURFACE_ADEPTH4);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_ADEPTH8,CPW_SURFACE_ADEPTH8);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_ADEPTH16,CPW_SURFACE_ADEPTH16);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_ADEPTH32,CPW_SURFACE_ADEPTH32);
                MAP_SURFACE_PROP_TO_CPW(SurfaceProperties::SURFACE_ADEPTH64,CPW_SURFACE_ADEPTH64);
            #   undef MAP_SURFACE_PROP_TO_CPW
                return nCpwSurfaceProperties;
            }

        } // namespace detail
    } // SurfaceProperties 
} //namespace Egl
