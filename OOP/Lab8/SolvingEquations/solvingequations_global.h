#ifndef SOLVINGEQUATIONS_GLOBAL_H
#define SOLVINGEQUATIONS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SOLVINGEQUATIONS_LIBRARY)
#  define SOLVINGEQUATIONSSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SOLVINGEQUATIONSSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SOLVINGEQUATIONS_GLOBAL_H