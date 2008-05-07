#include "Precompiled.hpp"
#include "Egl/Menu.hpp"
#include "Egl/detail/MenuImpl.hpp"

namespace Egl
{
    CMenu & 
    CMenu::AddItem(const std::string & strTitle, 
                   const int nId, 
                   const bool bChecked)
    {
        // Forward call
        m_pImpl->AddItem(strTitle, nId, bChecked);
        return *this;
    }
    
    CMenu & 
    CMenu::AddSeparator(const int nId)
    {
        // Forward call
        m_pImpl->AddSeparator(nId);
        return *this;
    }

    CMenu & 
    CMenu::RemoveItem(const int nId)
    {
        // Forward call
        m_pImpl->RemoveItem(nId);
        return *this;
    }

    CMenu & 
    CMenu::CheckItem(const int nId)
    {
        // Forward call
        m_pImpl->CheckItem(nId);
        return *this;
    }

    CMenu & 
    CMenu::UncheckItem(const int nId)
    {
        // Forward call
        m_pImpl->UncheckItem(nId);
        return *this;
    }

    const ContextPtr_t & 
    CMenu::GetContext() const
    {
        // Return context
        return m_pImpl->GetContext();
    }

    CMenu::~CMenu() throw() 
    {
    }

    CMenu::CMenu() : m_pImpl(new detail::CMenuImpl())
    {
    }

} // namespace Egl
