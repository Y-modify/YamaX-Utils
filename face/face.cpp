/*
   (c) Copyright 2012-2013  DirectFB integrated media GmbH
   (c) Copyright 2001-2013  The world wide DirectFB Open Source Community (directfb.org)
   (c) Copyright 2000-2004  Convergence (integrated media) GmbH

   All rights reserved.

   Written by Denis Oliver Kropp <dok@directfb.org>,
              Andreas Shimokawa <andi@directfb.org>,
              Marek Pikarski <mass@directfb.org>,
              Sven Neumann <neo@directfb.org>,
              Ville Syrjälä <syrjala@sci.fi> and
              Claudio Ciccani <klan@users.sf.net>.

   This file is subject to the terms and conditions of the MIT License:

   Permission is hereby granted, free of charge, to any person
   obtaining a copy of this software and associated documentation
   files (the "Software"), to deal in the Software without restriction,
   including without limitation the rights to use, copy, modify, merge,
   publish, distribute, sublicense, and/or sell copies of the Software,
   and to permit persons to whom the Software is furnished to do so,
   subject to the following conditions:

   The above copyright notice and this permission notice shall be
   included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
   CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
   TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
   SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include "face.hpp"

using namespace yamax;

Face::Face(std::string facesdir, std::string fontp) {
  _facesdir = facesdir;

  DirectFB::Init( NULL, NULL );

  DFBSurfaceDescription dsc;

  /* create super interface */
  _dfb = DirectFB::Create();

  try {
      /* try fullscreen mode */
      _dfb.SetCooperativeLevel( DFSCL_FULLSCREEN );
  }
  catch (DFBException *ex) {
      if (ex->GetResultCode() == DFB_ACCESSDENIED)
           std::cerr << "Warning: " << ex << std::endl;
      else
           throw;
  }

  /* fill surface description */
  dsc.flags = DSDESC_CAPS;
  dsc.caps  = DSCAPS_PRIMARY;

  if (_flipping)
      DFB_ADD_SURFACE_CAPS( dsc.caps, DSCAPS_FLIPPING );

  if (_width) {
      DFB_ADD_SURFACE_DESC( dsc.flags, DSDESC_WIDTH );
      dsc.width  = _width;
  }

  if (_height) {
      DFB_ADD_SURFACE_DESC( dsc.flags, DSDESC_HEIGHT );
      dsc.height = _height;
  }

  /* create the primary surface */
  _primary = _dfb.CreateSurface( dsc );

  DFBFontDescription font_dsc;
  font_dsc.flags = DFDESC_HEIGHT;
  font_dsc.height = 13;
  _font = _dfb.CreateFont(fontp.c_str(), font_dsc);

  _primary.SetFont(_font);

  setFace("normal");
}

Face::~Face() {
  _image.DisposeImage();
}

void Face::setFace(std::string face) {
  _face = face;
  _image.LoadImage(_facesdir+"/"+_face+".png");
  Render();
}

void Face::setMessage(std::string msg){
  _message = msg;
  Render();
}

void Face::Render() {
  int x = ((int) _primary.GetWidth()  - (int) _image.GetWidth())  / 2;
  int y = ((int) _primary.GetHeight() - (int) _image.GetHeight()) / 2;
  _primary.Clear();
  _image.PrepareTarget( _primary );
  _primary.Blit( _image, NULL, x, y );

  _primary.SetColor (0, 0, 0, 0xFF);
  _primary.DrawString (_message.c_str(), -1, 10, _primary.GetHeight() * 3 / 4, DSTF_LEFT);
}
