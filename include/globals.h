/** DJS - Moved from M6502.h. ********************************/
/** Simple Datatypes *****************************************/
/** NOTICE: sizeof(byte)=1 and sizeof(word)=2               **/
/*************************************************************/

#ifndef GLOBALS_H
#define GLOBALS_H

#ifndef BYTE_TYPE_DEFINED
#define BYTE_TYPE_DEFINED
typedef unsigned char byte;
#endif
#ifndef WORD_TYPE_DEFINED
#define WORD_TYPE_DEFINED
typedef unsigned short word;
#endif
typedef signed char offset;

#ifndef DISALLOW_COPY_AND_ASSIGN
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
 TypeName(const TypeName&);               \
 void operator=(const TypeName&)
#endif

#endif /* GLOBALS_H */
