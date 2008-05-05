#include "Precompiled.hpp"
#include "Egl/Context.hpp"
#include "Egl/Font.hpp"
#include "Egl/detail/FontImpl.hpp"

namespace Egl
{
    namespace detail
    {        
        CFontImpl::CFontImpl() : m_pHandle(0),
                                 m_pContext(),
                                 m_pContextHandle(0)
        {
        }

        void 
        CFontImpl::Init(const std::string & strFontName,
                        const int nFontSize,
                        const ContextPtr_t & pContext,
                        const pCpw pContextHandle)
        {
            // Initialize all the internal values
            m_pContext = pContext;
            m_pContextHandle = pContextHandle;            

            // Load font
            //cpwFontMode( m_pContextHandle, CPW_FONTOPT_PIXELMAP, 0 );
            //cpwFontMode( m_pContextHandle, CPW_FONTOPT_KERN, 0 );
            cpwFontMode( m_pContextHandle, CPW_FONTOPT_ALIGNLEFT, 0 );
            cpwFontMode( m_pContextHandle, CPW_FONTOPT_SIZE, nFontSize);
            cpwFontMode( m_pContextHandle, CPW_FONTOPT_PIXELMAP_GLFORMAT, GL_RGB );

            // CpwFontList pList;
            // cpwListFonts(m_pContextHandle, &pList, "*.ttf", CPW_FONTLOC_HOST);
            // cpwFreeFontList(m_pContextHandle, &pList);

            m_pHandle = cpwLoadFont(m_pContextHandle, const_cast<char*>(
                strFontName.c_str()), CPW_FONTLOC_HOST, "", "");

            // TODO, handle error
        }

        CFontImpl::~CFontImpl() throw()
        {
            // Unload font
            if (0 != m_pHandle)
                cpwUnloadFont(m_pContextHandle, m_pHandle);
        }

        void 
        CFontImpl::DrawString(const std::string & strText) const
        {
            // Draw font
            if (0 != m_pHandle)
            {
                cpwDrawFont(m_pContextHandle, m_pHandle, const_cast<char*>(
                    strText.c_str()), TRUE);
            }
        }
    }    
} // namespace Egl