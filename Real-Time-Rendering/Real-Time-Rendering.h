#ifndef REALTIME_RENDERING_H
#define REALTIME_RENDERING_H

//Header to group all Real-Time-Reandering headers into a single include
// Possibly bad idea?
// Need to research includes more.

#include "Camera.h"
#include "Device.h"
#include "Mesh.h"
#include "Object.h"
#include "ObjectParser.h"
#include "Pipeline.h"
#include "RasterizerMode.h"
#include "RasterizeVertex.h"
#include "RasterizeWireframe.h"
#include "RasterizeFilled.h"
#include "VertexProcessor.h"
#include "VertexShader.h"
#include "ViewMode.h"
#include "ViewPerspective.h"
#include "ViewOrthogonal.h"
#include "DefaultVertexShader.h"

#endif // !REALTIME_RENDERING_H



//Main page documentation for doxygen
/*! \mainpage Real-Time Rendering 
 *
 * \section intro_sec Introduction
 *
 * A real-time software rendering library for C++, developed by Andrew Richardson
 *
 * \section install_sec Installation
 * 
 * Can be compiled from source using cmake
 * 
 * - define REALTIME_EXPORTS for dll building
 * - define STATICLIB for static lib
 * 
 * VS2017 solutions made with cmake can be found in cmakebuilds folder
 * you may need to add the resources folder and some of the dlls to working
 * directory to get these to compile though. A hand made solution is available
 * int he root directory of this project which may compile easier, though you may
 * need to switch the compiler version
 * 
 * \section About
 * 
 * This was a self-directed project for university, I am interested in rendering tech
 * and felt it would be worthwhile to learn how GPUs actually render objects. The functionality
 * is fairly limited for a renderer at this point.
 * 
 * \section Disclaimer
 * 
 * This project was created for a University project, it is my first large project
 * in C++. As such this is far from perfect C++ code and contains some bad practices
 * I became aware of during in development and likely some I am unware of.
 * 
 * Due to time constaints some of the code is a mess (ObjectParser is a good example) and 
 * needs cleaning up.
 * 
 * \section Usage
 * There is a little bit of setup up required but the general loop once set up is
 * simple. See BasicCube.cpp in Real-Time-Rendering demos for a working code example
 * with SDL controls
 * 
 * Setup:
 * - Load in a mesh using ObjectParser
 * - Instantiate a DefaultVertexShader
 * - Instantiate an implementer of RasterizerMode
 * - Instantiate an Object and pass it the Mesh, VertexShader and RasterizerMode
 * - If you have a texture load it with SDL_image and assign it to the object
 * - Create an SDL_Surface to act as the frame buffer
 * - Instantiate a camera
 * - Instantiate a device and pass it the camera and sercice
 * - Instantiate a pipeline with a view mode and the device
 * - If you want to use RenderThreaded set the threadlimit of pipeline 
 *  default is 4
 * 
 * Render an object:
 * - Call pipeline::Render() or pipeline::RenderThreaded() with the object
 *
 * \section Other Libraries and their licenses
 * 
 * The library itself has a very small dependency on SDL2 that I hope to remove to
 * lower the dependcy count. GLM is used for most of methematics.
 * 
 * The demo uses SDL2, SDL2_image, SDL_ttf, libpng, zlib, libfreetype
 * 
 * Licences:
 * \subsection license Licenses for: SDl2, SDL2_Image, Zlib1, SDL_ttf 
 * 
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 *  arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * 
 * \subsection libfreetype
 *                      The FreeType Project LICENSE
 *                    ----------------------------
 *
 *                            2006-Jan-27
 *
 *                    Copyright 1996-2002, 2006 by
 *          David Turner, Robert Wilhelm, and Werner Lemberg
 *
 *
 *
 * Introduction
 * ============
 *
 *  The FreeType  Project is distributed in  several archive packages;
 *  some of them may contain, in addition to the FreeType font engine,
 *  various tools and  contributions which rely on, or  relate to, the
 *  FreeType Project.
 *
 *  This  license applies  to all  files found  in such  packages, and
 *  which do not  fall under their own explicit  license.  The license
 *  affects  thus  the  FreeType   font  engine,  the  test  programs,
 *  documentation and makefiles, at the very least.
 *
 *  This  license   was  inspired  by  the  BSD,   Artistic,  and  IJG
 *  (Independent JPEG  Group) licenses, which  all encourage inclusion
 *  and  use of  free  software in  commercial  and freeware  products
 *  alike.  As a consequence, its main points are that:
 *
 *    o We don't promise that this software works. However, we will be
 *      interested in any kind of bug reports. (`as is' distribution)
 *
 *    o You can  use this software for whatever you  want, in parts or
 *      full form, without having to pay us. (`royalty-free' usage)
 *
 *    o You may not pretend that  you wrote this software.  If you use
 *      it, or  only parts of it,  in a program,  you must acknowledge
 *      somewhere  in  your  documentation  that  you  have  used  the
 *      FreeType code. (`credits')
 *
 *  We  specifically  permit  and  encourage  the  inclusion  of  this
 *  software, with  or without modifications,  in commercial products.
 *  We  disclaim  all warranties  covering  The  FreeType Project  and
 *  assume no liability related to The FreeType Project.
 *
 *
 *  Finally,  many  people  asked  us  for  a  preferred  form  for  a
 *  credit/disclaimer to use in compliance with this license.  We thus
 *  encourage you to use the following text:
 *
 *   """
 *    Portions of this software are copyright © <year> The FreeType
 *    Project (www.freetype.org).  All rights reserved.
 *   """
 *
 *  Please replace <year> with the value from the FreeType version you
 *  actually use.
 *
 *
 * Legal Terms
 * ===========
 *
 * 0. Definitions
 * --------------
 *
 *  Throughout this license,  the terms `package', `FreeType Project',
 *  and  `FreeType  archive' refer  to  the  set  of files  originally
 *  distributed  by the  authors  (David Turner,  Robert Wilhelm,  and
 *  Werner Lemberg) as the `FreeType Project', be they named as alpha,
 *  beta or final release.
 *
 *  `You' refers to  the licensee, or person using  the project, where
 *   `using' is a generic term including compiling the project's source
 *   code as  well as linking it  to form a  `program' or `executable'.
 *   This  program is  referred to  as  `a program  using the  FreeType
 *   engine'.
 * 
 *   This  license applies  to all  files distributed  in  the original
 *   FreeType  Project,   including  all  source   code,  binaries  and
 *   documentation,  unless  otherwise  stated   in  the  file  in  its
 *   original, unmodified form as  distributed in the original archive.
 *   If you are  unsure whether or not a particular  file is covered by
 *   this license, you must contact us to verify this.
 * 
 *   The FreeType  Project is copyright (C) 1996-2000  by David Turner,
 *   Robert Wilhelm, and Werner Lemberg.  All rights reserved except as
 *   specified below.
 * 
 * 1. No Warranty
 * --------------
 * 
 *   THE FREETYPE PROJECT  IS PROVIDED `AS IS' WITHOUT  WARRANTY OF ANY
 *   KIND, EITHER  EXPRESS OR IMPLIED,  INCLUDING, BUT NOT  LIMITED TO,
 *   WARRANTIES  OF  MERCHANTABILITY   AND  FITNESS  FOR  A  PARTICULAR
 *   PURPOSE.  IN NO EVENT WILL ANY OF THE AUTHORS OR COPYRIGHT HOLDERS
 *   BE LIABLE  FOR ANY DAMAGES CAUSED  BY THE USE OR  THE INABILITY TO
 *   USE, OF THE FREETYPE PROJECT.
 * 
 * 2. Redistribution
 * -----------------
 * 
 *   This  license  grants  a  worldwide, royalty-free,  perpetual  and
 *   irrevocable right  and license to use,  execute, perform, compile,
 *   display,  copy,   create  derivative  works   of,  distribute  and
 *   sublicense the  FreeType Project (in  both source and  object code
 *   forms)  and  derivative works  thereof  for  any  purpose; and  to
 *   authorize others  to exercise  some or all  of the  rights granted
 *   herein, subject to the following conditions:
 * 
 *     o Redistribution of  source code  must retain this  license file
 *       (`FTL.TXT') unaltered; any  additions, deletions or changes to
 *       the original  files must be clearly  indicated in accompanying
 *       documentation.   The  copyright   notices  of  the  unaltered,
 *       original  files must  be  preserved in  all  copies of  source
 *       files.
 * 
 *     o Redistribution in binary form must provide a  disclaimer  that
 *       states  that  the software is based in part of the work of the
 *       FreeType Team,  in  the  distribution  documentation.  We also
 *       encourage you to put an URL to the FreeType web page  in  your
 *       documentation, though this isn't mandatory.
 * 
 *   These conditions  apply to any  software derived from or  based on
 *   the FreeType Project,  not just the unmodified files.   If you use
 *   our work, you  must acknowledge us.  However, no  fee need be paid
 *   to us.
 * 
 * 3. Advertising
 * --------------
 * 
 *   Neither the  FreeType authors and  contributors nor you  shall use
 *   the name of the  other for commercial, advertising, or promotional
 *   purposes without specific prior written permission.
 * 
 *   We suggest,  but do not require, that  you use one or  more of the
 *   following phrases to refer  to this software in your documentation
 *   or advertising  materials: `FreeType Project',  `FreeType Engine',
 *   `FreeType library', or `FreeType Distribution'.
 * 
 *   As  you have  not signed  this license,  you are  not  required to
 *   accept  it.   However,  as  the FreeType  Project  is  copyrighted
 *   material, only  this license, or  another one contracted  with the
 *   authors, grants you  the right to use, distribute,  and modify it.
 *   Therefore,  by  using,  distributing,  or modifying  the  FreeType
 *   Project, you indicate that you understand and accept all the terms
 *   of this license.
 * 
 * 4. Contacts
 * -----------
 * 
 *   There are two mailing lists related to FreeType:
 * 
 *     o freetype@nongnu.org
 * 
 *       Discusses general use and applications of FreeType, as well as
 *       future and  wanted additions to the  library and distribution.
 *       If  you are looking  for support,  start in  this list  if you
 *       haven't found anything to help you in the documentation.
 * 
 *     o freetype-devel@nongnu.org
 * 
 *       Discusses bugs,  as well  as engine internals,  design issues,
 *       specific licenses, porting, etc.
 * 
 *   Our home page can be found at
 * 
 *     https://www.freetype.org
 * 
 * 
 * 
 * 
 * \subsection libpng
 * 
 * This copy of the libpng notices is provided for your convenience.  In case of
 * any discrepancy between this copy and the notices in the file png.h that is
 * included in the libpng distribution, the latter shall prevail.
 * 
 * COPYRIGHT NOTICE, DISCLAIMER, and LICENSE:
 * 
 * If you modify libpng you may insert additional notices immediately following
 * this sentence.
 * 
 * This code is released under the libpng license.
 * 
 * libpng versions 1.0.7, July 1, 2000 through 1.6.32, August 24, 2017 are
 * Copyright (c) 2000-2002, 2004, 2006-2017 Glenn Randers-Pehrson, are
 * derived from libpng-1.0.6, and are distributed according to the same
 * disclaimer and license as libpng-1.0.6 with the following individuals
 * added to the list of Contributing Authors:
 * 
 *    - Simon-Pierre Cadieux
 *    - Eric S. Raymond
 *    - Mans Rullgard
 *    - Cosmin Truta
 *    - Gilles Vollant
 *    - James Yu
 *    - Mandar Sahastrabuddhe
 *    - Google Inc.
 *    - Vadim Barkov
 * 
 * and with the following additions to the disclaimer:
 * 
 *    There is no warranty against interference with your enjoyment of the
 *    library or against infringement.  There is no warranty that our
 *    efforts or the library will fulfill any of your particular purposes
 *    or needs.  This library is provided with all faults, and the entire
 *    risk of satisfactory quality, performance, accuracy, and effort is with
 *    the user.
 * 
 * Some files in the "contrib" directory and some configure-generated
 * files that are distributed with libpng have other copyright owners and
 * are released under other open source licenses.
 * 
 * libpng versions 0.97, January 1998, through 1.0.6, March 20, 2000, are
 * Copyright (c) 1998-2000 Glenn Randers-Pehrson, are derived from
 * libpng-0.96, and are distributed according to the same disclaimer and
 * license as libpng-0.96, with the following individuals added to the list
 * of Contributing Authors:
 * 
 *    - Tom Lane
 *    - Glenn Randers-Pehrson
 *    - Willem van Schaik
 * 
 * libpng versions 0.89, June 1996, through 0.96, May 1997, are
 * Copyright (c) 1996-1997 Andreas Dilger, are derived from libpng-0.88,
 * and are distributed according to the same disclaimer and license as
 * libpng-0.88, with the following individuals added to the list of
 * Contributing Authors:
 * 
 *    - John Bowler
 *    - Kevin Bracey
 *    - Sam Bushell
 *    - Magnus Holmgren
 *    - Greg Roelofs
 *    - Tom Tanner
 * 
 * Some files in the "scripts" directory have other copyright owners
 * but are released under this license.
 * 
 * libpng versions 0.5, May 1995, through 0.88, January 1996, are
 * Copyright (c) 1995-1996 Guy Eric Schalnat, Group 42, Inc.
 * 
 * For the purposes of this copyright and license, "Contributing Authors"
 * is defined as the following set of individuals:
 * 
 *    - Andreas Dilger
 *    - Dave Martindale
 *    - Guy Eric Schalnat
 *    - Paul Schmidt
 *    - Tim Wegner
 * 
 * The PNG Reference Library is supplied "AS IS".  The Contributing Authors
 * and Group 42, Inc. disclaim all warranties, expressed or implied,
 * including, without limitation, the warranties of merchantability and of
 * fitness for any purpose.  The Contributing Authors and Group 42, Inc.
 * assume no liability for direct, indirect, incidental, special, exemplary,
 * or consequential damages, which may result from the use of the PNG
 * Reference Library, even if advised of the possibility of such damage.
 * 
 * Permission is hereby granted to use, copy, modify, and distribute this
 * source code, or portions hereof, for any purpose, without fee, subject
 * to the following restrictions:
 * 
 *   1. The origin of this source code must not be misrepresented.
 * 
 *   2. Altered versions must be plainly marked as such and must not
 *      be misrepresented as being the original source.
 * 
 *   3. This Copyright notice may not be removed or altered from any
 *      source or altered source distribution.
 * 
 * The Contributing Authors and Group 42, Inc. specifically permit, without
 * fee, and encourage the use of this source code as a component to
 * supporting the PNG file format in commercial products.  If you use this
 * source code in a product, acknowledgment is not required but would be
 * appreciated.
 * 
 * END OF COPYRIGHT NOTICE, DISCLAIMER, and LICENSE.
 * 
 * TRADEMARK:
 * 
 * The name "libpng" has not been registered by the Copyright owner
 * as a trademark in any jurisdiction.  However, because libpng has
 * been distributed and maintained world-wide, continually since 1995,
 * the Copyright owner claims "common-law trademark protection" in any
 * jurisdiction where common-law trademark is recognized.
 * 
 * OSI CERTIFICATION:
 * 
 * Libpng is OSI Certified Open Source Software.  OSI Certified Open Source is
 * a certification mark of the Open Source Initiative. OSI has not addressed
 * the additional disclaimers inserted at version 1.0.7.
 * 
 * EXPORT CONTROL:
 * 
 * The Copyright owner believes that the Export Control Classification
 * Number (ECCN) for libpng is EAR99, which means not subject to export
 * controls or International Traffic in Arms Regulations (ITAR) because
 * it is open source, publicly available software, that does not contain
 * any encryption software.  See the EAR, paragraphs 734.3(b)(3) and
 * 734.7(b).
 * 
 * Glenn Randers-Pehrson
 * glennrp at users.sourceforge.net
 * April 1, 2017 
 * 
 * 
 */