#ifndef __TYPES_H__
#define __TYPES_H__

typedef unsigned char uint8;
typedef char int8;
typedef unsigned short uint16;
typedef short int16;
typedef unsigned int uint32;
typedef int int32;
typedef unsigned long long uint64;
typedef long long int64;

typedef int8 Pos;

struct MovePos
{
	MovePos()
		:
	from(0),
	to(0)
	{
	}

	MovePos(Pos a_from, Pos a_to)
		:
	from(a_from),
	to(a_to)
	{
	}

	Pos from;
	Pos to;
};

#endif // ifndef __TYPES_H__