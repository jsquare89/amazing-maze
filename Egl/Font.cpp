#include "Precompiled.hpp"
#include "Egl/Font.hpp"
#include "Egl/detail/FontImpl.hpp"

namespace Egl
{
    CFont::CFont() : m_pImpl(new detail::CFontImpl())
    {
    }    
    
    CFont::~CFont(void) throw()
    {
    }
    
    const ContextPtr_t & 
    CFont::GetContext() const
    {
        // forward call
        return m_pImpl->GetContext();
    }    

} // namespace Egl
