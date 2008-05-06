#pragma once

#include <boost/shared_ptr.hpp>

namespace Egl
{
    /** Forward declaration of C3DPoint<TPrecision>. */
    template <class TPrecision>
    class C3DPoint;

    /** Forward declaration of CWindow */
    class CWindow;

    /** Shared pointer to a CWindow. */
    typedef boost::shared_ptr<CWindow> WindowPtr_t;

    /** Forward declaration of CContext */
    class CContext;

    /** Shared pointer to a CContext. */
    typedef boost::shared_ptr<CContext> ContextPtr_t;

    /** Forward declaration of CModel */
    class CModel;

    /** Shared pointer to a CModel. */
    typedef boost::shared_ptr<CModel> ModelPtr_t;

    /** Forward declaration of CLight */
    class CLight;

    /** Shared pointer to a CLight. */
    typedef boost::shared_ptr<CLight> LightPtr_t;

    /** Forward declaration of CMenu */
    class CMenu;

    /** Shared pointer to a CMenu. */
    typedef boost::shared_ptr<CMenu> MenuPtr_t;

    /** Forward declaration of CTimer */
    class CTimer;

    /** Shared pointer to a CTimer. */
    typedef boost::shared_ptr<CTimer> TimerPtr_t;

    /** Forward declaration of CCamera */
    class CCamera;

    /** Shared pointer to a CCamera. */
    typedef boost::shared_ptr<CCamera> CameraPtr_t;

    /** Forward declaration of IPositionable */
    class IPositionable;

    /** Shared pointer to a IPositionable. */
    typedef boost::shared_ptr<IPositionable> PositionablePtr_t;

    /** Forward declaration of IRotatable. */
    class IRotatable;

    /** Shared pointer to a IRotatable. */
    typedef boost::shared_ptr<IRotatable> RotatablePtr_t;

    /** Forward declaration of CAnimator. */
    class CAnimator;

    /** Shared pointer to a CAnimator. */
    typedef boost::shared_ptr<CAnimator> AnimatorPtr_t;

    /** Forward declaration of CStraightPathAnimator. */
    class CStraightPathAnimator;

    /** Shared pointer to a CStraightPathAnimator. */
    typedef boost::shared_ptr<CStraightPathAnimator> StraightPathAnimatorPtr_t;    

    /** Forward declaration of CRotatingAnimator. */
    class CRotatingAnimator;

    /** Shared pointer to a CRotatingAnimator. */
    typedef boost::shared_ptr<CRotatingAnimator> RotatingAnimatorPtr_t;    

    /** Forward declaration of CFont. */
    class CFont;

    /** Shared pointer to a CFont. */
    typedef boost::shared_ptr<CFont> FontPtr_t;    

    /** Forward declaration of CTexture. */
    class CTexture;

    /** Type of image shared pointer. */
    typedef boost::shared_ptr<CTexture> TexturePtr_t;

    /** Forward declaration of CImage. */
    class CImage;

    /** Type of CImage shared pointer. */
    typedef boost::shared_ptr<CImage> ImagePtr_t;

    /** Forward declaration of CImageButton. */
    class CImageButton;

    /** Type of CImageButton shared pointer. */
    typedef boost::shared_ptr<CImageButton> ImageButtonPtr_t;

    /** Forward declaration of CScene. */
    class CScene;

    /** Type of scene shared pointer. */
    typedef boost::shared_ptr<CScene> ScenePtr_t;
} //namespace Egl
