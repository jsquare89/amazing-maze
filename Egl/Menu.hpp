#pragma once

#include <string>
#include <boost/scoped_ptr.hpp>
#include "Egl/Common.hpp"

namespace Egl
{
    namespace detail
    {
        /** Forward declaration of CMenuImpl. */
        class CMenuImpl;

        /** Forward declaration of CWindowImpl. */
        class CWindowImpl;

    } // namespace detail

    /** A menu. */
    class CMenu
    {
    public:        

        /**
         * Adds an item to this menu.
         *
         * @param strTitle Menu item title.
         * @param nId Menu item id.
         * @param bChecked Whether the menu item is checked.
         *
         * @return (*this).
         */
        CMenu & AddItem(const std::string & strTitle, const int nId, const bool bChecked);
        
        /**
         * Adds a separator to this menu.
         *
         * @param nId Separator id.
         *
         * @return (*this).
         */
        CMenu & AddSeparator(const int nId);

        /**
         * Removes an item from this menu.
         *
         * @param nId Menu item id.
         *
         * @return (*this).
         */
        CMenu & RemoveItem(const int nId);

        /**
         * Checks an item in this menu.
         *
         * @param nId Menu item id.
         *
         * @return (*this).
         */
        CMenu & CheckItem(const int nId);

        /**
         * Unchecks an item in this menu.
         *
         * @param nId Menu item id.
         *
         * @return (*this).
         */
        CMenu & UncheckItem(const int nId);

        /** 
         * Retrieves the context that was used to create 
         * this menu.
         */
        const ContextPtr_t & GetContext() const;

        /** Destructor. */
        ~CMenu() throw();

    protected:

        /** Creates a menu. */
        CMenu();  

    private:

        /** 
         * Gets the impl of this menu.
         */
        detail::CMenuImpl & GetImpl() const { return *m_pImpl; }

        // Avoid copy ctor and op=
        CMenu(const CMenu&);
        CMenu & operator=(const CMenu &);

    private:

        /** Menu impl. */
        boost::scoped_ptr<detail::CMenuImpl> m_pImpl;        
    private:

        /** CContext is our friend so it can create us. */
        friend class CContext;

        /** CWindowImpl is our friend so it can get our impl. */
        friend class detail::CWindowImpl;
    };

} // namespace Egl
