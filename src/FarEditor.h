#ifndef _FAREDITOR_H_
#define _FAREDITOR_H_

#include <colorer/editor/BaseEditor.h>
#include <colorer/handlers/StyledRegion.h>
#include <colorer/editor/Outliner.h>
#include "pcolorer.h"

const intptr_t CurrentEditor = -1;
extern const CString DDefaultScheme;
extern const CString DShowCross;
extern const CString DNone;
extern const CString DVertical;
extern const CString DHorizontal;
extern const CString DBoth;
extern const CString DCrossZorder;
extern const CString DBottom;
extern const CString DTop;
extern const CString DYes;
extern const CString DNo;
extern const CString DTrue;
extern const CString DFalse;
extern const CString DBackparse;
extern const CString DMaxLen;
extern const CString DDefFore;
extern const CString DDefBack;
extern const CString DFullback;
extern const CString DHotkey;
extern const CString DFavorite;

#define revertRGB(x) (BYTE)(x>>16 & 0xff)|((BYTE)(x>>8 & 0xff)<<8)|((BYTE)(x & 0xff)<<16)

/** FAR Editor internal plugin structures.
    Implements text parsing and different
    editor extended functions.
    @ingroup far_plugin
*/
class FarEditor : public LineSource
{
public:
  /** Creates FAR editor instance.
  */
  FarEditor(PluginStartupInfo* info, ParserFactory* pf);
  /** Drops this editor */
  ~FarEditor();

  void endJob(int lno);
  /**
  Returns line number "lno" from FAR interface. Line is only valid until next call of this function,
  it also should not be disposed, this function takes care of this.
  */
  SString* getLine(size_t lno);

  /** Changes current assigned file type.
  */
  void setFileType(FileType* ftype);
  /** Returns currently selected file type.
  */
  FileType* getFileType() const;

  /** Selects file type with it's extension and first lines
  */
  void chooseFileType(String* fname);


  /** Installs specified RegionMapper implementation.
  This class serves to request mapping of regions into
  real colors.
  */
  void setRegionMapper(RegionMapper* rs);

  /**
  * Change editor properties. These overwrites default HRC settings
  */
  void setDrawCross(const String* cross_style);
  void setDrawPairs(bool drawPairs);
  void setDrawSyntax(bool drawSyntax);
  void setOutlineStyle(bool oldStyle);
  void setTrueMod(bool _TrueMod);

  /** Editor action: pair matching.
  */
  void matchPair();
  /** Editor action: pair selection.
  */
  void selectPair();
  /** Editor action: pair selection with current block.
  */
  void selectBlock();
  /** Editor action: Selection of current region under cursor.
  */
  void selectRegion();
  /** Editor action: Lists fuctional region.
  */
  void listFunctions();
  /** Editor action: Lists syntax errors in text.
  */
  void listErrors();
  /**
  * Locates a function under cursor and tries to jump to it using outliner information
  */
  void locateFunction();

  /** Invalidates current syntax highlighting
  */
  void updateHighlighting();

  /** Handle passed FAR editor event */
  int editorEvent(intptr_t event, void* param);
  /** Dispatch editor input event */
  int editorInput(const INPUT_RECORD &Rec);

  void cleanEditor();

  void getNameCurrentScheme();
private:
  PluginStartupInfo* info;

  ParserFactory* parserFactory;
  BaseEditor* baseEditor;

  int  maxLineLength;
  bool fullBackground;

  int drawCross;//0 - off,  1 - always, 2 - if included in the scheme
  int CrossStyle; // 0 - both; 1 - vertical; 2 - horizontal
  bool showVerticalCross;
  bool showHorizontalCross;
  int crossZOrder;
  FarColor horzCrossColor;
  FarColor vertCrossColor;

  bool drawPairs;
  bool drawSyntax;
  bool oldOutline;
  bool TrueMod;

  int WindowSizeX;
  int WindowSizeY;
  bool inRedraw;
  int idleCount;

  int prevLinePosition;
  int blockTopPosition;

  SString* ret_str;
  size_t ret_strNumber;

  int newfore;
  int newback;
  const StyledRegion* rdBackground;
  LineRegion* cursorRegion;

  int visibleLevel;
  Outliner* structOutliner;
  Outliner* errorOutliner;
  intptr_t editor_id;

  void reloadTypeSettings();
  EditorInfo enterHandler();
  FarColor convert(const StyledRegion* rd) const;
  bool foreDefault(const FarColor &col) const;
  bool backDefault(const FarColor &col) const;
  void showOutliner(Outliner* outliner);
  void addFARColor(intptr_t lno, intptr_t s, intptr_t e, const FarColor &col, EDITORCOLORFLAGS TabMarkStyle = 0) const;
  void deleteFarColor(intptr_t lno, intptr_t s) const;
  const wchar_t* GetMsg(int msg) const;
  static COLORREF getSuitableColor(const COLORREF base_color, const COLORREF blend_color);
};
#endif
/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is the Colorer Library.
 *
 * The Initial Developer of the Original Code is
 * Cail Lomecb <cail@nm.ru>.
 * Portions created by the Initial Developer are Copyright (C) 1999-2005
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */