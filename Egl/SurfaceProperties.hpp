#pragma once

#include <boost/shared_ptr.hpp>
#include <boost/cstdint.hpp>

namespace Egl
{
    /** All surface properties. */
    namespace SurfaceProperties
    {
        /** General Surface Characteristics */
        
        static const boost::int64_t SURFACE_RGBA = 0x0000000000000001;
        static const boost::int64_t SURFACE_INDEX = 0x0000000000000002;
        static const boost::int64_t SURFACE_SINGLE = 0x0000000000000004;
        static const boost::int64_t SURFACE_DOUBLE = 0x0000000000000008;
        static const boost::int64_t SURFACE_ACCUM = 0x0000000000000010;
        static const boost::int64_t SURFACE_DEPTH = 0x0000000000000020;
        static const boost::int64_t SURFACE_STENCIL = 0x0000000000000040;
        static const boost::int64_t SURFACE_STEREO = 0x0000000000000080;

        /** Color depth specific requests. */
        
        static const boost::int64_t SURFACE_COLOR8 = 0x0000000000000100;
        static const boost::int64_t SURFACE_COLOR16 = 0x0000000000000200;
        static const boost::int64_t SURFACE_COLOR32 = 0x0000000000000400;
        static const boost::int64_t SURFACE_COLOR64 = 0x0000000000000800;
        static const boost::int64_t SURFACE_RED2 = 0x0000000000001000;
        static const boost::int64_t SURFACE_RED4 = 0x0000000000002000;
        static const boost::int64_t SURFACE_RED8 = 0x0000000000004000;
        static const boost::int64_t SURFACE_RED16 = 0x0000000000008000;
        static const boost::int64_t SURFACE_GREEN2 = 0x0000000000010000;
        static const boost::int64_t SURFACE_GREEN4 = 0x0000000000020000;
        static const boost::int64_t SURFACE_GREEN8 = 0x0000000000040000;
        static const boost::int64_t SURFACE_GREEN16 = 0x0000000000080000;
        static const boost::int64_t SURFACE_BLUE2 = 0x0000000000100000;
        static const boost::int64_t SURFACE_BLUE4 = 0x0000000000200000;
        static const boost::int64_t SURFACE_BLUE8 = 0x0000000000400000;
        static const boost::int64_t SURFACE_BLUE16 = 0x0000000000800000;
        static const boost::int64_t SURFACE_ALPHA2 = 0x0000000001000000;
        static const boost::int64_t SURFACE_ALPHA4 = 0x0000000002000000;
        static const boost::int64_t SURFACE_ALPHA8 = 0x0000000004000000;
        static const boost::int64_t SURFACE_ALPHA16 = 0x0000000008000000;        

        /** Depth buffer specific requests. */
        
        static const boost::int64_t SURFACE_DEPTH2 = 0x0000000010000000;
        static const boost::int64_t SURFACE_DEPTH4 = 0x0000000020000000;
        static const boost::int64_t SURFACE_DEPTH8 = 0x0000000040000000;
        static const boost::int64_t SURFACE_DEPTH16 = 0x0000000080000000;
        static const boost::int64_t SURFACE_DEPTH32 = 0x0000000100000000;
        static const boost::int64_t SURFACE_DEPTH64 = 0x0000000200000000;

        /** Accumulation buffer's color depth specific requests. */
        
        static const boost::int64_t SURFACE_ACOLOR8 = 0x0004000000000000;
        static const boost::int64_t SURFACE_ACOLOR16 = 0x0008000000000000;
        static const boost::int64_t SURFACE_ACOLOR32 = 0x0010000000000000;
        static const boost::int64_t SURFACE_ACOLOR64 = 0x0020000000000000;
        static const boost::int64_t SURFACE_ARED2 = 0x0000000400000000;
        static const boost::int64_t SURFACE_ARED4 = 0x0000000800000000;
        static const boost::int64_t SURFACE_ARED8 = 0x0000001000000000;
        static const boost::int64_t SURFACE_ARED16 = 0x0000002000000000;
        static const boost::int64_t SURFACE_AGREEN2 = 0x0000004000000000;
        static const boost::int64_t SURFACE_AGREEN4 = 0x0000008000000000;
        static const boost::int64_t SURFACE_AGREEN8 = 0x0000010000000000;
        static const boost::int64_t SURFACE_AGREEN16 = 0x0000020000000000;
        static const boost::int64_t SURFACE_ABLUE2 = 0x0000040000000000;
        static const boost::int64_t SURFACE_ABLUE4 = 0x0000080000000000;
        static const boost::int64_t SURFACE_ABLUE8 = 0x0000100000000000;
        static const boost::int64_t SURFACE_ABLUE16 = 0x0000200000000000;
        static const boost::int64_t SURFACE_AALPHA2 = 0x0000400000000000;
        static const boost::int64_t SURFACE_AALPHA4 = 0x0000800000000000;
        static const boost::int64_t SURFACE_AALPHA8 = 0x0001000000000000;
        static const boost::int64_t SURFACE_AALPHA16 = 0x0002000000000000;
        
        /** Accumulation buffer's depth buffer specific requests. */
        
        static const boost::int64_t SURFACE_ADEPTH2 = 0x0040000000000000;
        static const boost::int64_t SURFACE_ADEPTH4 = 0x0080000000000000;
        static const boost::int64_t SURFACE_ADEPTH8 = 0x0100000000000000;
        static const boost::int64_t SURFACE_ADEPTH16 = 0x0200000000000000;
        static const boost::int64_t SURFACE_ADEPTH32 = 0x0400000000000000;
        static const boost::int64_t SURFACE_ADEPTH64 = 0x0800000000000000;

    } // SurfaceProperties 

    /** Type of surface property enumeration. */
    typedef boost::int64_t SurfaceProperties_e;

} //namespace Egl
