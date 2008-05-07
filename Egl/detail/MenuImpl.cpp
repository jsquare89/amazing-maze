#include "Precompiled.hpp"
#include "Egl/Menu.hpp"
#include "Egl/Context.hpp"
#include "Egl/detail/MenuImpl.hpp"
#include "Egl/detail/WindowImpl.hpp"

namespace Egl
{
    namespace detail
    {        
        /** CMenu implementation using Cpw. */
        CMenuImpl::CMenuImpl() : m_nId(0),
                                 m_pContext(),
                                 m_pContextHandle(0)
        {
        }

        void 
        CMenuImpl::Init(const ContextPtr_t & pContext,
                          const pCpw pContextHandle,
                          bool bSubMenu)
        {
            // Initialize all the internal values
            m_pContext = pContext;
            m_pContextHandle = pContextHandle;

            // Create menu
            if (!bSubMenu)
                m_nId = cpwCreateMenu(pContextHandle, &OnMenuItemSelected);
            else
                m_nId = cpwCreateSubMenu(pContextHandle);
        }

        CMenuImpl::~CMenuImpl() throw()
        {
            // Set the event as user data for the CPW window
            if (m_nId > 0)
                cpwDestroyMenu(m_pContextHandle, m_nId);
        }

        void 
        CMenuImpl::AddItem(const std::string & strTitle, 
                           const int nId,
                           const bool bChecked)
        {
            cpwAddMenuEntry(m_pContextHandle, m_nId, const_cast<char*>(
                strTitle.c_str()), nId, bChecked);
        }
        
        void 
        CMenuImpl::AddSeparator(const int nId)
        {
            cpwAddMenuSeperator(m_pContextHandle, m_nId, nId);
        }

        void 
        CMenuImpl::RemoveItem(const int nId)
        {
            cpwRemoveMenuItem(m_pContextHandle, m_nId, nId);
        }

        void 
        CMenuImpl::CheckItem(const int nId)
        {
            cpwCheckMenuEntry(m_pContextHandle, m_nId, nId);
        }

        void 
        CMenuImpl::UncheckItem(const int nId)
        {
            cpwUncheckMenuEntry(m_pContextHandle, m_nId, nId);
        }
    }    
} // namespace Egl