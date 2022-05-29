#ifndef ALGOSLIB_GLOBAL_H
#define ALGOSLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ALGOSLIB_LIBRARY)
#  define ALGOSLIB_EXPORT Q_DECL_EXPORT
#else
#  define ALGOSLIB_EXPORT Q_DECL_IMPORT
#endif

#endif // ALGOSLIB_GLOBAL_H
