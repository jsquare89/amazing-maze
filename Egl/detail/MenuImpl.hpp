#pragma once

#include "Egl/Common.hpp"
#include "Egl/Menu.hpp"

namespace Egl
{
    namespace detail
    {        
        /** CMenu implementation using Cpw. */
        class CMenuImpl
        {
        public:

            /** Constructor. */
            CMenuImpl();

            /** 
             * Initialization. We use 2 step initalization 
             * because it is easier for CContext to create us that way.
             */
            void Init(const ContextPtr_t & pContext, const pCpw pContextHandle, bool bSubMenu);

            /** Destructor. */
            ~CMenuImpl() throw();

            /**
             * Retrieves a given menu item.
             */
            void AddItem(const std::string & strTitle, const int nId, const bool bChecked);
            
            /**
             * Adds a separator to this menu.
             */
            void AddSeparator(const int nId);

            /** Remove menu item or separator. */
            void RemoveItem(const int nId);

            /** Check menu item. */
            void CheckItem(const int nId);

            /** Uncheck menu item. */
            void UncheckItem(const int nId);

            /** Retrieves the context for this menu. */
            const ContextPtr_t & GetContext() const { return m_pContext; }
            
            /** Retrieves the identifier for this menu. */
            int GetId() const { return m_nId; }

        private:

            /** Prevent copy ctor and op=. */
            CMenuImpl(const CMenuImpl &);
            CMenuImpl & operator=(const CMenuImpl &);
        
        private:

            /** Cpw menu identifier. */
            unsigned int m_nId;

            /** Context that created the window. */
            ContextPtr_t m_pContext;

            /** Cpw handle. */
            pCpw m_pContextHandle;     

        private:

            /** CWindowImpl is our friend so it can get our id. */
            friend class CWindowImpl;
        };
    } // namespace detail
} // namespace Egl