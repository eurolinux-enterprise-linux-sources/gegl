
/* !!!! AUTOGENERATED FILE generated by blend.rb !!!!! 
 *
 * This file is an image processing operation for GEGL
 *
 * GEGL is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * GEGL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with GEGL; if not, see <http://www.gnu.org/licenses/>.
 *
 *  Copyright 2006 Øyvind Kolås <pippin@gimp.org>
 *
 * The formulas used for the blend modes are from:
 *     http://www.pegtop.net/delphi/articles/blendmodes/
 *
 * !!!! AUTOGENERATED FILE !!!!!
 */
#include "config.h"
#include <glib/gi18n-lib.h>


#ifdef GEGL_CHANT_PROPERTIES

/* no properties */

#else

#define GEGL_CHANT_TYPE_POINT_COMPOSER
#define GEGL_CHANT_C_FILE          "average.c"

#include "gegl-chant.h"
#include <math.h>

static void prepare (GeglOperation *self)
{
  Babl *format = babl_format ("RaGaBaA float");

  gegl_operation_set_format (self, "input", format);
  gegl_operation_set_format (self, "aux", format);
  gegl_operation_set_format (self, "output", format);
}

static gboolean
process (GeglOperation       *op,
         void                *in_buf,
         void                *aux_buf,
         void                *out_buf,
         glong                n_pixels,
         const GeglRectangle *roi)
{
  gfloat *in  = in_buf;
  gfloat *aux = aux_buf;
  gfloat *out = out_buf;
  gint    i;

  if (aux == NULL)
    return TRUE;

  for (i = 0; i < n_pixels; i++)
    {
      gfloat aA, aB;
      gint   j;

      aA = in[3];
      aB = aux[3];
      for (j = 0; j < 3; j++)
        {
          gfloat cA, cB;

          cA = in[j];
          cB = aux[j];
          out[j] = cA + ((cA + aB)/2-cA) * cB;
        }
      out[j] = aA;
      in  += 4;
      aux += 4;
      out += 4;
    }

  return TRUE;
}


static void
gegl_chant_class_init (GeglChantClass *klass)
{
  GeglOperationClass              *operation_class;
  GeglOperationPointComposerClass *point_composer_class;

  operation_class      = GEGL_OPERATION_CLASS (klass);
  point_composer_class = GEGL_OPERATION_POINT_COMPOSER_CLASS (klass);

  point_composer_class->process = process;
  operation_class->prepare = prepare;

  operation_class->name        = "gegl:average";
  operation_class->categories  = "compositors:blend";
  operation_class->description =
        _("Image blending operation 'average' (<tt>c = (cA + aB)/2</tt>)");
}

#endif
