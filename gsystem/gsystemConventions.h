#ifndef  GSYSTEM_CONVENTIONS_H
#define  GSYSTEM_CONVENTIONS_H  1

// number of database pars defining a gvolume and a gmaterial
#define GVOLUMENUMBEROFPARS    19
#define GMATERIALNUMBEROFPARS  18
#define DEFAULTPOSITION       "0*cm, 0*cm, 0*cm";
#define DEFAULTROTATION       "0*deg, 0*deg, 0*deg";

// exit codes: 200s
#define EC__GVOLUMEALREADYPRESENT  201
#define EC__GWRONGNUMBEROFPARS     202
#define EC__GSETUPFILENOTOFOUND    203
#define EC__GVOLUMENOTFOUND        204
#define EC__GDIRNOTFOUND           205

#define GSYSTEMLOGHEADER           " ❖ GSystem ▸ "
#define GSYSTEMNOMODIFIER          "noModifier"

#define GEMCDB_ENV        "GEMCDB_ENV"
#define GSYSTEMTXTFACTORY  "GSystemTEXTFactory"
#define GSYSTEMCADFACTORY  "GSystemCADFactory"
#define GSYSTEMGDMLFACTORY "GSystemGDMLFactory"
#define GSYSTEMYSQLFACTORY "GSystemMYSQLFactory"

#define ROOTWORLDGVOLUMENAME "root"
#define MOTHEROFUSALL        "akasha"

#define GSYSTEMTEXTFACTORY   "text"
#define GSYSTEMCADTFACTORY   "cad"
#define GSYSTEMGDMLTFACTORY  "gdml"
#define GSYSTEMMYSQLTFACTORY "mysql"

#endif
