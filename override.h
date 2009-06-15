/*
 * Softcam plugin to VDR (C++)
 *
 * This code is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This code is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 * Or, point your browser to http://www.gnu.org/copyleft/gpl.html
 */

#ifndef ___OVERRIDE_H
#define ___OVERRIDE_H

#include "data.h"

// ----------------------------------------------------------------

class cValidityRange {
private:
  int fromCaid, toCaid;
  int fromSource, toSource;
  int fromFreq, toFreq;
  //
  bool ParseCaidRange(const char *str);
  bool ParseSourceRange(const char *str);
  bool ParseFreqRange(const char *str);
protected:
  char *Parse3(char *s);
  char *Parse2(char *s);
  cString Print(void);
public:
  cValidityRange(void);
  bool Match(int caid, int source, int freq) const;
  };

// ----------------------------------------------------------------

class cOverride : public cStructItem, public cValidityRange {
protected:
  int type;
public:
  virtual ~cOverride() {}
  virtual bool Parse(char *str)=0;
  int Type(void) { return type; }
  };

// ----------------------------------------------------------------

class cOverrides : public cStructList<cOverride> {
protected:
  cOverride *Find(int type, int caid, int source, int freq, cOverride *ov=0);
  virtual cOverride *ParseLine(char *line);
public:
  cOverrides(void);
  int GetCat(int source, int transponder, unsigned char *buff, int len);
  void UpdateEcm(cEcmInfo *ecm, bool log);
  bool AddEmmPids(int caid, int source, int transponder, cPids *pids, int pid);
  };

extern cOverrides overrides;

#endif //___OVERRIDE_H