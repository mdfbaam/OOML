﻿/**********************************************************************
 *
 * This code is part of the OOML project
 * Authors: Juan Gonzalez-Gomez, Alberto Valero-Gomez, Rafael Trevio
 *
 * OOML is licenced under the Common Creative License,
 * Attribution-ShareAlike 3.0
 *
 * You are free:
 *   - to Share - to copy, distribute and transmit the work
 *   - to Remix - to adapt the work
 *
 * Under the following conditions:
 *   - Attribution. You must attribute the work in the manner specified
 *     by the author or licensor (but not in any way that suggests that
 *     they endorse you or your use of the work).
 *   - Share Alike. If you alter, transform, or build upon this work,
 *     you may distribute the resulting work only under the same or
 *     similar license to this one.
 *
 * Any of the above conditions can be waived if you get permission
 * from the copyright holder.  Nothing in this license impairs or
 * restricts the author's moral rights.
 *
 * It is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.
 **********************************************************************/

#ifndef ROUNDEDCYLINDER_H_INCLUDED
#define ROUNDEDCYLINDER_H_INCLUDED

#ifdef WIN32
#ifdef OOMLComponents_EXPORTS
#define OOMLComponents_EXP_DEC __declspec(dllexport)
#else
#define OOMLComponents_EXP_DEC __declspec(dllimport)
#endif
#else
#define OOMLComponents_EXP_DEC
#endif

#include <components/Cylinder.h>
#include <components/Sphere.h>
#include <components/Toroid.h>
#include <core/MinkowskiDecorator.h>
#include <core/Union.h>
#include <core/Difference.h>

/**
 * \brief Rounded cylinder primitive object
 *
 * This class provides a rounded cylinder.
 */
class OOMLComponents_EXP_DEC RoundedCylinder: public Component
{
public:
    /**
             * \brief Static factory method.
             *
             * Creates a rounded cylinder.
             *
             * \param radius Cylinder radius.
             * \param height Cylinder height.
             * \param cornerRadius Cylinder corner radius.
             * \param up Rounded upper corner?
             * \param down Rounded downer corner?
             * \param faces Number of faces of the rendered rounded cylinder.
             * \param center Centered cylinder flag.
             *
             * \return A rounded cylinder component.
             */
            RoundedCylinder(double radius, double height, double cornerRadius, bool up = true, bool down = true, unsigned int faces=100, bool center=true) :
                    Component()
            {
                    if (cornerRadius > radius)
                            cornerRadius = radius;
                    if (cornerRadius > height / 2)
                            cornerRadius = height / 2;

                    Component c_in = Cylinder(radius - cornerRadius,height,faces);
                    Component c_out = Cylinder(radius,height - 2*cornerRadius,faces);
                    Component rc = c_in + c_out;

                    if(up)
                    {
                            Component tup = Toroid(radius-cornerRadius,cornerRadius,faces);
                            Component t_up = tup.translate(0,0,height/2-cornerRadius);
                            rc = rc + t_up;
                    }
                    else
                    {
                            Component c1 = Cylinder(radius,2*cornerRadius,faces);
                            Component cc1 = c1.translate(0,0,height/2-cornerRadius);
                            rc = rc + cc1;
                    }
                    if(down)
                    {
                            Component tdown = Toroid(radius-cornerRadius,cornerRadius,faces);
                            Component t_down = tdown.translate(0,0,-height/2+cornerRadius);
                            rc = rc + t_down;
                    }
                    else
                    {
                            Component c2 = Cylinder(radius,2*cornerRadius,faces);
                            Component cc2 = c2.translate(0,0,-height/2+cornerRadius);
                            rc = rc + cc2;
                    }

                    if(!center)
                        rc.translate(0,0,height/2);

                    set(rc.get());
            }
	/**
	 * \brief Static factory method.
	 *
	 * Creates a rounded cylinder.
	 *
	 * \param radius1 Cylinder top radius.
	 * \param radius2 Cylinder bottom radius.
	 * \param height Cylinder height.
	 * \param cornerRadius Cylinder corner radius.
	 * \param faces Number of faces of the rendered rounded cylinder.
	 * \param center Centered cylinder flag.
	 *
	 * \return A rounded cylinder component.
	 */
	RoundedCylinder(double radius1, double radius2, double height, double cornerRadius, unsigned int faces=100, bool center=true) :
		Component()
	{
		if (cornerRadius > radius1)
			cornerRadius = radius1;
		if (cornerRadius > radius2)
			cornerRadius = radius2;
		if (cornerRadius > height / 2)
			cornerRadius = height / 2;

		Component cylinder(Cylinder(radius1 - cornerRadius, radius2 - cornerRadius, height - cornerRadius, faces, center));
		Component sphere(Sphere(cornerRadius, faces, center));
		sphere.translate(radius1 - cornerRadius, 0.0, height - cornerRadius);

		set(MinkowskiDecorator::create(cylinder.get(), sphere.get()).get());
	}
};


#endif // ROUNDEDCYLINDER_H_INCLUDED
