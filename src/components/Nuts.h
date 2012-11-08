/**********************************************************************
 *
 * This code is part of the RepRap Plastic Valley project
 * Authors: Alberto Valero-Gomez
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

#ifndef OOML_NUTS_H
#define OOML_NUTS_H

#include "../core.h"

#include <core/AbstractPart.h>

#ifdef WIN32
#ifdef OOMLParts_EXPORTS
#define OOMLParts_EXP_DEC __declspec(dllexport)
#else
#define OOMLParts_EXP_DEC __declspec(dllimport)
#endif
#else
#define OOMLParts_EXP_DEC
#endif

enum Metric{M3,M4};

class OOMLParts_EXP_DEC NutShape : public AbstractPart
{
public:

    /**
      * Part Data
      */
    struct Data{
        double width_across_flats; // (mm)
        double witdth_across_coners; //<! the rod diameter (mm)
        double thickness; //<! the rod lenght (mm)
    };

    /**
      * Constructor
      */
    NutShape(Metric m);

    /**
     * \brief returns part data
     * \return part data
     */
    inline const Data getData() const{return data;}

protected:
  /**
   * \brief Build the piece.
   *
   * This method build the piece from simpler objects.
   *
   * \return The piece built.
   */
  virtual Component build();

private:
    Data data;
};



#endif