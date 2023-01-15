/* Jingxin Zhang */

ushort change_any(ushort bits, ushort value, ushort mask, ushort shift);
ushort decrement_angle(ushort bits);
ushort decrement_force(ushort bits);
int get_angle(ushort bits);
int get_force(ushort bits);
int get_type(ushort bits);
int in_air(void *data);
ushort increment_angle(ushort bits);
ushort increment_force(ushort bits);
int on_ground(ushort bits);
int on_ground2(void *data);
ushort set_in_flight(ushort bits);
ushort set_to_impacted(ushort bits);
