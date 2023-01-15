/* Jingxin Zhang 
 * code based on Professor Kirby's lab2 reference code*/

#include <stdio.h>
#include "unsigned.h"
#include "struct.h"
#include "bits.h"

#define FORCE_MASK 0x3f
#define FORCE_SHIFT 0
#define FORCE_LIMIT 63

#define ANGLE_MASK 0x0f
#define ANGLE_SHIFT 6
#define ANGLE_LIMIT 15

#define TYPE_MASK 0x0f
#define TYPE_SHIFT 10

#define STATUS_MASK 0x03
#define STATUS_SHIFT 14

#define INVALID_STATUS 0
#define GROUND_STATUS 1
#define AIR_STATUS 2
#define IMPACTED_STATUS 3

/* general purpose extractor */
static int extract_bits(ushort bitfield, int mask, int shift)
{
	return (bitfield >> shift) & mask;

}

/* get angle field from a hex number */
int get_angle(ushort bits)
{
	return(extract_bits(bits, ANGLE_MASK, ANGLE_SHIFT) );
}

/* get force field from a hex number */
int get_force(ushort bits)
{
	return( extract_bits(bits, FORCE_MASK, FORCE_SHIFT) );
}

/* get type field  from a hex number */
int get_type(ushort bits)
{
	return( extract_bits(bits, TYPE_MASK, TYPE_SHIFT) );
}

/* check if a bits is in ground status */
int on_ground(ushort bits)
{	
	return GROUND_STATUS == extract_bits(bits, STATUS_MASK, STATUS_SHIFT);
}

/* criteria function that takes in a pointer, the other take in bits */
int on_ground2(void *data)
{
        Bird *p2bird = data;
	return GROUND_STATUS == extract_bits(p2bird->bits, STATUS_MASK, STATUS_SHIFT);
}

/* criteria function that checks if a bird is in air */
int in_air(void *data)
{
	Bird *p2bird = data;
	return AIR_STATUS == extract_bits(p2bird->bits, STATUS_MASK, STATUS_SHIFT);
}

/* set a bird to the impacted status(1) */
ushort set_to_impacted(ushort bits)
{
	bits = bits & ~(STATUS_MASK);
	bits = bits | (GROUND_STATUS << STATUS_SHIFT);

	return bits;
}

/* set a bird into flight status (2) */
ushort set_in_flight(ushort bits)
{
	/* the negation of the mask keeps everything but the mask */
	bits = bits & (~ (STATUS_MASK << STATUS_SHIFT));
	/* OR in the new status value */
	bits = bits | (AIR_STATUS << STATUS_SHIFT);

	return bits;
}

/* the increment / decrement crowd need this, but they have to do their own
 * error checks */
ushort change_any(ushort bits, ushort value, ushort mask, ushort shift)
{
	/* clear out the old value */
	bits = bits & (~ (mask << shift));
	/* upshift the new value into place */
	value = value << shift;
	/* OR in the new value into its place */
	bits = bits | value;

	return bits;

}

/* increment the angle field of a bits */
ushort increment_angle(ushort bits)
{
	ushort angle = (ushort) get_angle(bits);

	if(angle >= ANGLE_LIMIT)return bits;
	angle++;
	return change_any(bits, angle, ANGLE_MASK, ANGLE_SHIFT);
}

/* decrement the angle field of a hex number by 5 */
ushort decrement_angle(ushort bits)
{
	ushort angle = (ushort) get_angle(bits);

	if(angle <= 0)return bits;
	angle--;
	return change_any(bits, angle, ANGLE_MASK, ANGLE_SHIFT);
}

/* increment the force field of a hex number by 1 */
ushort increment_force(ushort bits)
{
	ushort force = (ushort) get_force(bits);

	if(force >= FORCE_LIMIT)return bits;
	force++;
	return change_any(bits, force, FORCE_MASK, FORCE_SHIFT);
}

/* decrement the force field of a hex number by 1 */
ushort decrement_force(ushort bits)
{
	ushort force = (ushort) get_force(bits);

	if(force <= 0)return bits;
	force--;
	return change_any(bits, force, FORCE_MASK, FORCE_SHIFT);
}

