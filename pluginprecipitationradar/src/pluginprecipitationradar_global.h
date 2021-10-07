#ifndef TEST_GLOBAL_H
#define TEST_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(INTERFACE_LIBRARY)
#  define INTERFACE_EXPORT Q_DECL_EXPORT
#else
#  define INTERFACE_EXPORT Q_DECL_IMPORT
#endif

#endif // TEST_GLOBAL_H
